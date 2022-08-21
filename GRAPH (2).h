#pragma once
#include <iostream>
#include <vector>
/************************************************************/
//O(V) finds the degree of the graph
int find_degree(const vector<vector<int>> &list){
	int degree=(int)list[0].size();
	for (int j = 1; j < (int)list.size(); j++) {
		if(degree<(int)list[j].size()){
			degree=(int)list[j].size();
		}
	}
	return degree;
}
/************************************************************/
//O(V+E) fills true if vertice is reachable
void DFSUtil(const int &v, vector<bool> &visited,const vector<vector<int>> &list){
	visited[v] = true;
	for(int i = 0; i < (int)list[v].size(); i++){
		int ind=list[v][i];
		if(!visited[ind]){DFSUtil(ind, visited,list);}
	}
}
/************************************************************/
//O(V+E) 
bool S_Conn_UNDIR(const vector<vector<int>> &list){
	int V=(int)list.size();	
	vector<bool>  visited(V,false);
	DFSUtil(0, visited,list);
	for (int i = 0; i < V; i++){if (visited[i] == false){return false;}}
	return true;
}
/************************************************************/
//checks if vertice is strongly connected. We check only node 0 because if that satisfies the strong connectivity,
//there is no need to check the others because the graph is undirected
//DFSUtils (O(|V|+E)) is called in this function,
//MAKE_UNDIRECTED_LIST (O(|V|+E)) is called in this function,
//complexity of the other commands are O(|V|)
//the overall complexity of this function is O(|V|+E) including all sub-commands
bool S_Connectivity(const vector<vector<int>> &list){
	int V=(int)list.size();	
	vector<vector<int>> aux_LIST;
	for(int i=0;i<V;i++){aux_LIST.push_back(list[i]);}
	MAKE_UNDIRECTED_LIST(aux_LIST);
	vector<bool>  visited(V,false);
	DFSUtil(0, visited,aux_LIST);
	for (int i = 0; i < V; i++){if (visited[i] == false){return false;}}
	return true;
}
/************************************************************/
// This is a greedy complexity because it has random commands, overbound might be infinite. 
// Because it has rand command, the computer may never leave the while loop, it is undeterministic.
// In case of best situtation (no repeated number is generated) "while" command never executes, 
// the complexity is O(E) if we exclude the other function calls.
// We forced the inital graph to be strongly connected, otherwise it will be meaningless to check spanning trees
void Undirected_Graph_Fill(vector<vector<bool>> &mat, const int &V, const int E){
	vector<vector<int>> LIST;
	int n1,n2;
	int maxE=V*(V-1)/2;
	
	do{
		init_matrix(mat,V,V);	
		if(E>maxE){
			for (int i=0;i<V;i++){
				for (int j=i+1;j<E;j++){mat[i][j]=mat[j][i]=true;}
			}
			for (int i=0;i<maxE-E;i++){
				do{
					n1=rand()%V;
					n2=rand()%V;
				}while(n2==n1 || mat[n1][n2]==false);
				mat[n1][n2]=mat[n2][n1]=false;
			}
		}else{
			for (int i=0;i<E;i++){
				do{
					n1=rand()%V;
					n2=rand()%V;
				}while(n2==n1 || mat[n1][n2]==true);
				mat[n1][n2]=mat[n2][n1]=true;
			}
		}
		LIST.clear();
		matrix_to_list(mat,LIST);
	}while(S_Connectivity(LIST)==false);
}
/************************************************************/
void go(int offset, int k,const int n,vector<int> &combination,const vector<vector<int>>&EDGE,int &minDEGREE,const int V) {
//	cout<<offset<<"  "<<k<<" "<<n<<" "<<V<<" "<<minDEGREE<<"\n";
	if(minDEGREE<=2){return;}
	if (k <= 0) {
		vector<vector<int>> aux_EDGE;
		vector<vector<int>> aux_LIST;
		for (int j = 0; j < (int)combination.size(); j++) {
			int ind=combination[j];
			aux_EDGE.push_back(EDGE[ind]);
		}
		edge_to_list(aux_EDGE,aux_LIST);
		MAKE_UNDIRECTED_LIST(aux_LIST);
		int degree=find_degree(aux_LIST);
#ifdef verbose
		cout<<"_____________________________\n";
		cout<<"{"<<combination[0];
		for (int j = 1; j < (int)combination.size(); j++) {cout<<","<<combination[j];}
		cout<<"}\n";
		print_list(aux_LIST);
		if(degree>=minDEGREE){cout<<"NOT checking (degree condition)\n";return;}
		else if((int)aux_LIST.size()!=V){cout<<"NOT checking (vertice condition)\n";return;}
		if( S_Connectivity(aux_LIST)){
			minDEGREE=degree;
			cout <<"temprorary minimum degree: "<<minDEGREE<<"\n";
		}
#else
		if(degree>=minDEGREE || aux_LIST.size()!=V){return;}
		if(S_Conn_UNDIR(aux_LIST)){minDEGREE=degree;}
//		if(S_Connectivity(aux_LIST)){minDEGREE=degree;}
#endif		
		return;
	}
	for (int i = offset; i <= n - k; ++i) {
		combination.push_back(i);
		go(i+1, k-1,n,combination,EDGE,minDEGREE,V);
		combination.pop_back();
	}
}
/************************************************************/
// adjacency matrix ->mat representation O(V^2)
// Adjacency matrix for undirected graph is always symmetric
void create_sub_trees(const vector<vector<bool>> &mat,int &minDEGREE){
	int V=(int)mat.size();
	vector<vector<int>> EDGE;
	vector<vector<int>> LIST;
	matrix_to_edge(mat,EDGE);
	edge_to_list(EDGE,LIST);
	MAKE_UNDIRECTED_LIST(LIST);
	minDEGREE= find_degree(LIST);
	int n_edge=(int)EDGE.size();
	vector<int> combination;
	

	go(0, V-1,n_edge,combination,EDGE,minDEGREE,V);
}