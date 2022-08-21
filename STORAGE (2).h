#pragma once
#include <iostream>
#include <vector>
/************************************************************/
//O(|V|^2)
void clear_matrix(vector<vector<bool>> &mat){
	int nrows=(int)mat.size();
	int ncols=(int)mat[0].size();
	for(int i=0;i<nrows;i++){
		for(int j=0;j<ncols;j++){mat[i][j]=false;}
	}
}
/************************************************************/
//O(|V|^2)
void init_matrix(vector<vector<bool>> &mat,const int &nrows,const int &ncols){
	mat.resize(nrows);				// row size is determined
	for(int i=0;i<nrows;i++){
		mat[i].resize(ncols);		// column size is determined for each row
	}
	clear_matrix(mat);
}
/************************************************************/
//O(|V|^2), tightest bound is O(|V|^2/2)
void matrix_to_edge(const vector<vector<bool>> &mat,vector<vector<int>> &edge){
	edge.clear();
	edge.shrink_to_fit();
	int V=(int)mat.size();
	vector<int>EDGE(2,0);
	for(int i = 0; i < V; i++){
		for(int j = i + 1; j < V; j++){
			if(mat[i][j]){
				EDGE[0]=i;
				EDGE[1]=j;
				edge.push_back(EDGE);
			}
		}
	}
}
/************************************************************/
//O(|V|^2)
void matrix_to_list(const vector<vector<bool>> &mat,vector<vector<int>> &list){
	list.clear();
	list.shrink_to_fit();
	int V=(int)mat.size();
	vector<int> link;
	for(int i = 0; i < V; i++){
		for(int j = i + 1; j < V; j++){
			if(mat[i][j]){
				link.push_back(j);
			}
		}
		list.push_back(link);
		link.clear();
	}
}
/************************************************************/
//O(|E|), When edge representation is used, we don't have any knowledge about number of vertices which doesn't have any connection
void edge_to_list(const vector<vector<int>> &edge,vector<vector<int>> &list){
	list.clear();
	list.shrink_to_fit();
	int E=(int)edge.size();
	int V=0;
	for(int i = 0; i < E; i++){				// find the maximum indice.
		if(V<edge[i][0]){V=edge[i][0];}
		if(V<edge[i][1]){V=edge[i][1];}
	}										//n of vertices = maximum indice + 1
	list.resize((size_t)V+1);
	for(int i = 0; i < E; i++){
		int ind=edge[i][0];
		list[ind].push_back(edge[i][1]);
	}
	//in some cases, graph could have a vetrice which doesn't have any connection, this information does not exist in edge representation
	//so we could not resolve this situtation. Therefore, the list representaiton may not be true.
}
/************************************************************/
//O(|V|+|E|)
void list_to_edge(const vector<vector<int>> &list,vector<vector<int>> &edge){
	edge.clear();
	edge.shrink_to_fit();
	int V=(int)list.size();
	vector<int>EDGE(2,0);
	for(int i = 0; i < V; i++){
		for(int j = 0;j<(int)list[i].size();j++){
			EDGE[0]=i;
			EDGE[1]=list[i][j];
			edge.push_back(EDGE);
		}
	}
}
/************************************************************/
// Function that returns reverse (or transpose) of this graph
// complexity O(|V|+|E|)
void Transpose_LIST(vector<vector<int>> &list){
	int V=(int)list.size();
	vector<vector<int>> T_list(V);
	for (int i = 0; i < V; i++){
		for(int j = 0; j < (int)list[i].size(); j++){
			int ind=list[i][j];
			T_list[ind].push_back(i);
		}
		list[i].clear();
	}
	list.clear();
	list.shrink_to_fit();
	for (int i = 0; i < V; i++){
		list.push_back(T_list[i]);
	}
}
/************************************************************/
// Function that returns reverse (or transpose) of this graph
// complexity O(|V|+|E|), our list notation is for directed graphs so in order to store the undirected graphs, we doubled the number of edges
// with their reverse forms
void MAKE_UNDIRECTED_LIST(vector<vector<int>> &list){
	int V=(int)list.size();
	vector<vector<int>> T_list;
	for (int i = 0; i < V; i++){
		T_list.push_back(list[i]);
	}
	Transpose_LIST(list);
	for (int i = 0; i < V; i++){
		for (int j = 0; j < (int)T_list[i].size(); j++){
			list[i].push_back(T_list[i][j]);
		}
	}
}
/************************************************************/