//---------------------------------------------------------------------------

//#include <vcl.h>
#pragma hdrstop
#include <fstream>
#include <iostream>
#include "Matrix.h"

#include "main.h"

#define GRID_FILE "grid.txt"
//---------------------------------------------------------------------------

#pragma argsused
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
   ifstream in(GRID_FILE, ios::in);
   if(!in){
   	cout<<"Error of open grid file "<<GRID_FILE<<endl;
      return 1;
      }

   vector<int> From;
   vector<int> To;

   while(!in.eof()){
   	int f, t;
      in >> f;
      if(in.eof()) break;
      in >> t;
      From.push_back(f);
      To.push_back(t);
   }
   in.close();

   int cnt_nodes = number_of_nodes(&From, &To);
   int cnt_branches = From.size();

   Matrix<int> grid(cnt_nodes, cnt_branches);

   // заполним матрицу инциденций
   for(int i=0, n=From.size(); i<n; i++){
      grid[ From[i] ][ i ] = -1;
      grid[ To[i] ]  [ i ] = +1;
   	}

   ofstream out( "distances.txt", ios::out | ios::trunc);
   if(!out){
   	cout<<"Error of open output.txt file "<<endl;
      return 2;
      }

   unsigned int *distances = new unsigned int[cnt_nodes];

   out << "n/n" << "\t|\t";
   for(int i=0; i<cnt_nodes; i++)	out << i << "\t";
   out << endl;
   for(int i=-2; i<cnt_nodes; i++)  out << "--\t";
   for(int start_node=0; start_node<cnt_nodes; start_node++){
   	for(int i=0; i<cnt_nodes; i++) distances[i]=-1;
   	distances[start_node] = 0;

   	grid.Distance_From_Node(start_node, distances);

      out << endl << start_node << "\t|\t";
   	for(int end_node=0; end_node<cnt_nodes; end_node++)
   		out << distances[end_node] << "\t";
		}
   out.close();

	return 0;
}
//---------------------------------------------------------------------------
int number_of_nodes(const vector<int> *from, const vector<int> *to){
	Multiplicity nodes;

   for(int i=0, n=from->size(); i<n; i++)
   	if( !nodes.includes( from->at(i) ) )
      	nodes.items.push_back( from->at(i) );

   for(int i=0, n=to->size(); i<n; i++)
   	if( !nodes.includes( to->at(i) ) )
      	nodes.items.push_back( to->at(i) );

   return nodes.items.size();
}
//---------------------------------------------------------------------------
bool Multiplicity::includes(int number){
	for(int i=0, n=items.size(); i<n; i++)
   	if( items[i] == number )
      	return true;
   return false;
}
	

 