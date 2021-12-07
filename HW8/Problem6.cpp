//
// Created by Mya Turner on 11/30/21.
//
#include <iostream>
#include <limits>
#include <sstream>
#include "Problem6.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include <sstream>
/*source(s):https://www.geeksforgeeks.org/cpp-program-read-file-word-word/ ,
 * https://stackoverflow.com/questions/14867944/how-can-i-read-first-line-from-file ,
 * https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/ ,
 * https://www.delftstack.com/howto/cpp/how-to-determine-if-a-string-is-number-cpp/ ,
 * https://stackoverflow.com/questions/1784573/iterator-for-2d-vector ,
 * https://www.delftstack.com/howto/cpp/cpp-split-string-by-space/ ,
 * https://www.geeksforgeeks.org/print-all-neigbour-nodes-within-distance-k/ ,
 * https://stackoverflow.com/questions/34757448/sorting-a-vector-of-objects-alphabetically-in-c?rq=1 ,
 * https://www.includehelp.com/cpp-programs/sort-names-in-an-alphabetical-order.aspx
 * */

using namespace std;

bool compareFunction (string a, string b) {return a<b;}

vector<string> alphabaticallySort(vector<string> V){
    int size = V.size();

    //sorts the strings in alphabatical order
    sort(V.begin(),V.end(),compareFunction);
    return V;
}

//Get the number of vertices and edges in the graph
int * getGraphinfo(string filename)
{
    //Open file
    ifstream text_file (filename);
    string firstLine;;

    //Get the edges and vertices in first line
    if (text_file.good())
    {
        getline(text_file, firstLine);
        //cout << firstLine << endl;
    }

    istringstream graphAspects(firstLine);
    string num;
    int vertices, edges;

    //Counter for traversing graphAspects
    int count = 1;
    while (graphAspects >> num)
    {
        //if count equals one, it is referring to the number of vertices
        if(count == 1)
        {
            //If num is an integer
            if(all_of(num.begin(), num.end(), [](char c){ return isdigit(c) != 0; }))
            {
                vertices = stoi(num);
            }
        }

        //if count equals two, it is referring to the number of edges
        if(count == 2)
        {
            //If num is an integer
            if(all_of(num.begin(), num.end(), [](char c){ return isdigit(c) != 0; }))
            {
                edges = stoi(num);
            }
        }

        count++;

    }

    static int graphInfo[2];
    //First element is vertices
    graphInfo[0] = vertices;
    //Second element is edges
    graphInfo[1] = edges;

    return graphInfo;
}

//Get the vertices of graph
vector<vector<string>> getVertices(string filename) {

    //Intializing adjacency list
    vector<vector<string>> adjList;

    //Open file
    ifstream text_file(filename);
    string vertex;

    //Counter for traversing to create adjacency list
    int count = 0;

    if (text_file.good()) {

        //Read in file string by string
        while (text_file >> vertex) {

            if (vertex == "\"\"")
            {
                break;
            }

            //Getting the vertices to add to a vector of vectors
            if(count > 2)
            {
                //cout << vertex << endl;
                //Ignoring the rest of their line
                text_file.ignore(numeric_limits<streamsize>::max(), '\n');

                // Inserting elements into vector
                // Temp vector to store vertices
                vector<string> v1;
                v1.push_back(vertex);

                //Pushing into adjancey list
                adjList.push_back(v1);
                }
            count++;

            }

        }

        return adjList;
    }

//Get the edges of a graph
vector<vector<string>> getEdges(string filename, vector<vector<string>> adjList, int numVertices, int numEdges)
{
    //Open file
    ifstream text_file(filename);
    string line;

    //Counter for traversing to create adjacency list
    int count = 0;

    if (text_file.good()) {

        //Read in file string by string
        while (text_file) {

            getline(text_file, line);

            //While we are looking at the numbr of edges and within the bounds of the file
            if(count > numVertices && count - numVertices - 1 < numEdges ) {

                //Getting the edges to add to the vector of vectors
                string space_delimiter = " ";
                vector<string> vertices{};
                string vertex;
                size_t pos = 0;

                while ((pos = line.find(space_delimiter)) != string::npos) {

                    vertices.push_back(line.substr(0, pos));
                    line.erase(0, pos + space_delimiter.length());
                }

                /*for (const auto &str: vertices) {
                    cout << str << endl;
                } */

                //Pushing edges to vector of vectors
                string source, dst;

                source = vertices.at(1);
                //cout << source << endl;
                dst = vertices.at(2);
                //cout << dst << endl;

               for (int i = 0; i < adjList.size(); i++) {

                    //If this is the source vector, add destination to the vector
                    if(adjList[i][0] == source)
                    {
                        adjList[i].push_back(dst);
                    }

                    //Since this is an undirected graph, also add the source to the destination vector as well
                    if(adjList[i][0] == dst)
                    {
                        adjList[i].push_back(source);
                    }
                }


            }
            count++;
        }

        }

    return adjList;
}

/*distThreeNeighbors prints out takes in a vertex and prints our its 3 distance neighbors in alphabetical order,
// one per line */
vector<string> distThreeNeighbors(vector<vector<string>> adjList, string src_vertex)
{
    vector<string> neighbors, visited, neighborsFinal;
    map<string, int> adjListindex;

    //Putting source vector into visited vector
    visited.push_back(src_vertex);

    //Creating index map to easily find adjacency lists for each vertex
    for(int i = 0; i < adjList.size(); i++)
    {
        //Key: vertex, Value: index to find adjancy list for given vertex
        adjListindex.insert(pair<string, int>(adjList[i][0], i));
        //cout << adjList[i][0] << i << endl;
    }

    vector<string> currentAdjList;
    int currentAdjListindex;

    //Find source vertex's adjacency list
    currentAdjListindex = adjListindex[src_vertex];
    currentAdjList = adjList[currentAdjListindex];

    //Counter to keep track of distance from vertex
    int distance = 1;

    //Push the neighbors of source vertex to visited, neighbors and neighborsFinal vectors
    for(int i = 1; i < currentAdjList.size(); i++)
    {
        //This vector keeps track of what vertices we need to check to find distance 2 neighbors
        neighbors.push_back(currentAdjList[i]);

        //This is the final list of neighbors to be returned.  Includes distance 1, 2 and 3 away neighbors
        neighborsFinal.push_back(currentAdjList[i]);
    }

    //Finding distance 2 and distance 3 neighbors
    while(distance < 3)
    {
        vector<string> nextNeighbor;
        distance++;

        /*For each neighbor, add its adjacent vertices to neighborsFinal if it has not been added already */
        for(int i = 0; i < neighbors.size(); i++)
        {
            //If neighbor is not in visited
            if( !(find(visited.begin(), visited.end(), neighbors[i]) != visited.end()) )
            {
                //Finding adjacency list for current neighbor
                currentAdjListindex = adjListindex[neighbors[i]];
                currentAdjList = adjList[currentAdjListindex];

                for(int j = 1; j < currentAdjList.size(); j++) {

                    //If the nextNeighbor in the adjacency list is not in visited or neighborsFinal, add to both of these!
                    if ( !(find(visited.begin(), visited.end(), currentAdjList[j]) != visited.end()) &&
                            !(find(neighborsFinal.begin(), neighborsFinal.end(), currentAdjList[j]) != neighborsFinal.end())) {

                        neighborsFinal.push_back(currentAdjList[j]);
                        nextNeighbor.push_back(currentAdjList[j]);
                    }
                }

            }

            //This vector keeps track of what vertices have already been seen
            visited.push_back(neighbors[i]);
        }

        neighbors = nextNeighbor;

    }

    return neighborsFinal;
}

//Print distance 3 neighbors
void printdistanceThreeNeighbors(vector<string> neighbors)
{
    //Sort array neighbor vector alphabetically
    neighbors = alphabaticallySort(neighbors);

    //Print out neighbors vector
    for(int i = 0; i < neighbors.size(); i++)
    {
        cout << neighbors[i] << endl;
    }
}


