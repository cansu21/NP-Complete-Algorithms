#pragma once
#include <iostream>
#include <vector>
/************************************************************/
long long int nCr(int n, int k){
	long long int res=1;
	if (k < n/2){ k = n - k;}
	for(int i = 0; i < k; i++){
		res *= (n-i);
		res /= (i+1);
	}
	return res;
}
/************************************************************/
//O(V^2) because the adcacency matrix is symmertirc, tightest bound is V^2/2
void print_info(const vector<vector<bool>> &mat){
	int V=(int)mat.size();
	int E=0;
	for(int i = 0; i < V; i++){
		for(int j = i + 1; j < V; j++){
			if(mat[i][j]){E++;}
		}
	}
	cout<<"\n";
	cout<<"number of node: "<<V<<"\n";
	cout<<"number of edge: "<<E<<"\n";
	cout<<"number of possible s-tree: "<<nCr(E,V-1)<<"\n";
	cout<<"\n";	
}
/************************************************************/
// complexity O(|V|^2)  V = number of nodes (vertex)
void print_matrix(const vector<vector<bool>> &mat){
	int nrows=(int)mat.size();
	int ncols=(int)mat[0].size();
	cout<<"\n";
	for(int i=0;i<nrows;i++){
		cout<<mat[i][0];	//the first character must be printed out of the loop
							// to avoid space char at the end of the line
		for(int j=1;j<ncols;j++){ 
			cout<<" "<<mat[i][j];  //put space between every character, line is filled
		}
		cout<<"\n";  //go to the next line
	}
	cout<<"\n";
}
/************************************************************/
// O(|V|+|E|) printing adjacency list complexity
void print_list(const vector<vector<int>> &list){
	int V=(int)list.size();
	cout<<"\n";
	for(int i = 0; i < V; i++){
		cout<<i<<" { ";
		for(int j = 0; j < (int)list[i].size(); j++){
			cout<<" -> "<<list[i][j];
		}
		cout<<" }\n";
	}
//	cout<<"\n";
}
/************************************************************/
//O(|E|)
void print_edge(const vector<vector<int>> &edge){
	int E=(int)edge.size();
	cout<<"\n";
	for(int i = 0; i < E; i++){cout<<"{"<<edge[i][0]<<","<<edge[i][1]<<"}\n";}
//	cout<<"\n";
}
/************************************************************/