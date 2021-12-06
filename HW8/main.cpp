#include <iostream>
#include <string>
#include "Problem6.h"
#include <algorithm>
#include <fstream>

/*Recieves two command line arguments: file name and then a source vertex.
 * Construct a graph from input file (Graph class), call distThreeNeighbors for given source vertex.*/

using namespace std;
int main(int argc, char** argv) {

    //Reading in user input for filename and source vertex
    string filename = argv[1];
    string src_vertex = argv[2];

    //Get the number of vertices and edges
    int* graphInfo;
    int numVertices, numEdges;

    graphInfo = getGraphinfo(filename);
    numVertices = graphInfo[0];
    numEdges = graphInfo[1];

    //Initializing graph as an adjacency list
    vector<vector<string>> adjList, temp;
    temp = getVertices(filename);
    adjList = getEdges(filename, temp, numVertices, numEdges);

    //Running the distThreeNeighbors function
    vector<string> neighbors;
    neighbors = distThreeNeighbors(adjList, src_vertex);
    printdistanceThreeNeighbors(neighbors);

    return 0;
}
