#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <chrono>
using namespace std;
#include "COLOR.h"

//#define verbose 
#include "PRINT.h"
#include "STORAGE.h"
#include "GRAPH.h"
#include "DJKS.h"
#include "L_SEARCH.h"
/************************************************************/
int main(){
	fstream DOSYA;
	DOSYA.open("SONUC.txt",ios::out);
	system("cls");
	srand ((int)time(NULL));
	vector<vector<bool>> mat;

	int V;
	int E;
	int r;	
	cout<<"How many vertices do you need?\n";
	cin>>V;
	cout<<"how many edges do you need?\n";	//minimum number of edges = n-1
	cin>>E;									//maximum number of edges = n*(n-1)/2
	
	while(E < V-1 || E > V*(V-1)/2){
		cout<<"not possible to create this graph, please give a different number: \n";
		cout<<"entry must be in range of ["<<V-1<<","<<V*(V-1)/2<<"]\n";
		cin>>E;
	}
	cout<<"the graph will have "<<E<<" edges\n";
	cout<<"How many graphs do you want to generate?\n";
	cin>>r;

	vector<vector<int>> imat(V);				// row size is determined
	for(int i=0;i<V;i++){imat[i].resize(V);}	// column size is determined for each row
	int degree_F=0;								// MDST for 
	int degree_L=0;								// MDST from L_SEARCH
	int CORR=0;
	int za = 1;
	for(int i = 0; i < r; i++){
		Undirected_Graph_Fill(mat, V, E);
		vector<vector<int>> EDGE;
		vector<vector<int>> LIST;
		matrix_to_edge(mat,EDGE);
		matrix_to_list(mat,LIST);
		degree_F=degree_L=(int)mat.size();
#ifdef verbose
		cout<<"\033[7m";		// swap foreground and background colours
		cout<<"\033[4m";		// underline text
		print_info(mat);
		print_matrix(mat);
		print_edge(EDGE);
		print_list(LIST);
		cout << RESET;			// reset console to defaults
#endif
#ifdef verbose
		cout << Back_RED<<BOLDYELLOW ;
		cout<<"\nFULL SCAN started\n";
#endif
		auto xs1=chrono::high_resolution_clock::now();
		create_sub_trees(mat,degree_F);
		auto xe1=chrono::high_resolution_clock::now();
		cout << RESET ;

#ifdef verbose
		cout << Back_BLACK<<BOLDBLUE ;
		cout<<"\nSEARCH ALGORITHM started\n";
#endif
		auto xs2=chrono::high_resolution_clock::now();
		L_SEARCH(mat,degree_L);
		auto xe2=chrono::high_resolution_clock::now();
		cout << RESET ;

		auto elapsed_F=std::chrono::duration_cast<std::chrono::nanoseconds>(xe1-xs1);
		auto elapsed_L=std::chrono::duration_cast<std::chrono::nanoseconds>(xe2-xs2);
		string INFO=to_string(V)+"\t"+to_string(E)+"\t"+
				to_string(degree_F)+"\t"+to_string(degree_L)+"\t"+
				to_string(elapsed_F.count()*1e-9)+"\t"+
				to_string(elapsed_L.count()*1e-9);
		cout<<za<<"-"<<INFO<<endl;
		za++;
		DOSYA<<INFO<<endl;
		if(degree_F==degree_L){CORR++;}
	}
	cout<<CORR<<"/"<<r<<"\n";
	DOSYA<<CORR<<"/"<<r<<"\n";
	DOSYA.close();

	
	system("pause");
}
/************************************************************/