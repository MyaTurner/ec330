//
// Created by Mya Turner on 11/30/21.
//
/*source(s):https://www.softwaretestinghelp.com/cpp-dfs-program-to-traverse-graph/ ,
 * */

#include <vector>
#include <string>
#include <algorithm>

#ifndef HW8_GRAPH_H
#define HW8_GRAPH_H

using namespace std;


//Get the number of vertices and edges in the file
int * getGraphinfo(string file);

//Get the vertices of graph
vector<vector<string>> getVertices(string filename);

//Get the edges of a graph
vector<vector<string>> getEdges(string filename, vector<vector<string>> adjList, int numVertices, int numEdges);

//Finds and prints distance-3 neighbors from given vertex
vector<string> distThreeNeighbors(vector<vector<string>> adjList, string src_vertex);

//Print distance 3 neighbors
void printdistanceThreeNeighbors(vector<string> neighbors);


#endif //HW8_GRAPH_H
