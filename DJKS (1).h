#pragma once
/*****************************************************************************************/
// O(|V|)
int minDistance(vector<int> dist, vector<bool>sptSet){
	int min = INT_MAX, min_index=0;
	for (int v = 0; v < (int)dist.size(); v++){
		if (sptSet[v] == false && dist[v] <= min) { min = dist[v], min_index = v; }
	}
	return min_index;
}
/*****************************************************************************************/
// Function that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation 
// This function was taken from the internet and the only modification is changing all the weights to 1
// O(|V^2|) (this can be reduced to lower complexities by using list representation)
// The aim to run this function is not to find spanning tree, initial quess which will be subjected to optimization is done by this function
// By using dijkstra contrary to our purpose, maximum degree spanning tree is obtained.
void dijkstra(vector<vector<bool>> mat, int src,vector<vector<int>> &list){
	int V=(int)mat.size();
	vector<int> rota(V);
	rota[src] = src;

	vector<int> dist(V,INT_MAX);					// The output array.  dist[i] will hold the shortest distance from src to i
	vector<bool>sptSet(V,false);					// sptSet[i] will be true if vertex i is included in shortest
													// path tree or shortest distance from src to i is finalized
													// Initialize all distances as INFINITE and stpSet[] as false
	dist[src] = 0;									// Distance of source vertex from itself is always 0
	for (int count = 0; count < V - 1; count++) {	// Find shortest path for all vertices
		int u = minDistance(dist, sptSet);			// Pick the minimum distance vertex from the set of vertices not  yet processed. u is always equal to src in the first iteration.
		sptSet[u] = true;							// Mark the picked vertex as processed
		for (int v = 0; v < V; v++){				// Update dist value of the adjacent vertices of the picked vertex.
			if (!sptSet[v] && mat[u][v] && dist[u] != INT_MAX // Update dist[v] only if is not in sptSet, there is an edge from
				&& dist[u] + 1 < dist[v]) {			// u to v, and total weight of path from src to  v through u is smaller than current value of dist[v]
				dist[v] = dist[u] + 1;
				rota[v]=u;
			}
		}
	}
	vector<vector<int>> edge;
	vector<int>EDGE(2,0);
	for(int i = 1; i < V; i++){
		EDGE[0]=rota[i];
		EDGE[1]=i;
		edge.push_back(EDGE);
	}
	edge_to_list(edge,list);
}
/*****************************************************************************************/