#pragma once
#ifndef MAX
#  define MAX(a,b)  ((a) < (b) ? (b) : (a))
#endif
/************************************************************/
// returns true if vertice v and w are directly connected
// O(|V|)
bool edged(const vector<vector<int>> &list,const int &v, const int &w){
	for(int i=0;i<(int)list[v].size();i++){
		if(list[v][i]==w){return true;}
	}
	return false;
}
/************************************************************/
// adds direct edge between vertices v and w
// O(1)
void add_edge(vector<vector<int>> &list,const int &v, const int &w){
	if(!edged(list,v,w)){
		list[v].push_back(w);
		list[w].push_back(v);
	}
}
/************************************************************/
// removes direct edge between vertices v and w
// O (|V|)
void remove_edge_ver(vector<vector<int>> &list,const int &v, const int &w){
	for(int i=0;i<(int)list[v].size();i++){if(list[v][i]==w){list[v].erase(list[v].begin()+i);break;}}
	for(int i=0;i<(int)list[w].size();i++){if(list[w][i]==v){list[w].erase(list[w].begin()+i);break;}}
}
/************************************************************/
// removes the xth connection of vertice u
// O (|V|), we use vector.erase command which has O(n) (In this case n = V) complexity
int remove_edge_ind(vector<vector<int>> &list,const int &u, const int &x){	
	int tmp=list[u][x];
	list[u].erase(list[u].begin()+x);

	for(int i=0;i<(int)list[tmp].size();i++){
		if(list[tmp][i]==u){
			list[tmp].erase(list[tmp].begin()+i);
			return tmp;
		}
	}
	return -1;
}
/************************************************************/
// the complexity is O(V^3 * O(DFSUtil))=O(V^4)   O(DFSUtil) = O(V+E)
bool find_uvw(	const vector<vector<int>> &G,
				const vector<vector<int>> &T,
				int &u_ind,int &u,int &v, int &w){
	int V=(int)T.size();
	vector<int>d(V);
	vector<vector<int>> aux_T;

	for (int i=0;i<V;i++){
		d[i]=(int)T[i].size();
		if(d[u]<d[i]){u=i;}		// u is the vertice that has max. degree
	}
	if(d[u]<=2){return false;}	// best case is achieved

	// u,v and w should not be same vertice
	// in the raw graph (G) connection between v and w must exist
	// in the MDST graph (T) connection between v and w must NOT exist
	// in the inner v != w and edged(G,v,w) are guaranteed becouse by default G doesnt have unit loop
	// and for(j...) loop is  searching over v's neighbours
	for(u_ind=0;u_ind<(int)T[u].size();u_ind++){
		for(v=0;v<V;v++){
			if(v!=u){
				for(int j=0;j<(int)G[v].size();j++){
					w=G[v][j];
					aux_T.clear();
					for(int i=0;i<(int)T.size();i++){aux_T.push_back(T[i]);}
					if((w!=u) && MAX(d[v],d[w])<=(d[u]-2) && !edged(aux_T,v,w)){
						int x=remove_edge_ind(aux_T,u, u_ind);	// removes u_ind connection of vertice u. "0" is an arbitrary selection
						add_edge(aux_T,v, w);
						if(S_Conn_UNDIR(aux_T)){return true;}
					}
				}
			}
		}
	}
	return false; // no more improvement
}
/************************************************************/
// CNT is the number of cycle without any improvement after the last successful attemp.
// CNT can be maximum O(T* + logV)
// O((D*-T*)O(T* + logV)0(find_uvw))
// where T* = overall minimum degrees, D* is the initial degree
void L_SEARCH(const vector<vector<bool>> mat,int &degree){
	vector<vector<int>> G;
	vector<vector<int>> T;

	matrix_to_list(mat,G);
	dijkstra(mat, 0,T);

	MAKE_UNDIRECTED_LIST(G);
	MAKE_UNDIRECTED_LIST(T);
	degree=find_degree(T);

#ifdef verbose
	cout<<"Graph to be checked (G)";
	print_list(G);
	cout<<"Initial graph(T)\n";
	print_list(T);
	if(degree<=2){cout<<"graph alreaedy has min degree spanning tree (MDST)\n"; return;}
	else{ cout<<"Initial degree is: "<<degree<<"\n"; }
	cout<<"_____________________________\n";
#else
	if(degree<=2){return;}
#endif

	/*********************************************************************************/
	int u_ind=0,u=0,v=0,w=0;
	int old_degree=degree;
	
	int pass=0;
	int CNT=0;
	int CNT_S=0;
	int CNT_U=0;
	while(find_uvw(G,T,u_ind,u,v,w)){
		remove_edge_ind(T,u, u_ind);
		add_edge(T,v, w);
		degree=find_degree(T);
		pass++;
#ifdef verbose
		cout<<pass<<" optimization using falloving edges u_ind: "<<u_ind<<"  u: "<<u<<"  v: "<<v<<"  w: "<<w<<"\n";
		cout<<"new degree after reduction "<<degree<<"\n";
		if(old_degree>degree){			
			old_degree=degree;
			CNT=0;
			CNT_S++;
			if(degree<=2){
				cout<<"graph has min degree spanning tree (MDST)\n";
				break;
			}
		}
		else if(old_degree<degree){cout<<"Getting worse. Terminating...\n";break;}
		else{
			CNT_U++;
			CNT++;
			cout<<"number of iteration without any improvement is "<<CNT<<"\n";
			if(CNT>(int)T.size()){
				cout<<"terminating...\n";
				break;
			}
		}
		print_list(T);
		cout<<"_____________________________\n";
#else
		if(old_degree>degree){			
			old_degree=degree;
			CNT=0;
			CNT_S++;
			if(degree<=2){break;}
		}
		else if(old_degree<degree){break;}
		else{
			CNT_U++;
			CNT++;
			if(CNT>(int)T.size()){break;}
		}

#endif
	}
//	cout<<CNT_S<<" sucseeded\n";
//	cout<<CNT_U<<" useless\n";
}
/************************************************************/