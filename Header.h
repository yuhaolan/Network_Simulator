#ifndef Header
#define Header
#include <iostream>
#include <list>
#include <time.h>       /* time */
using namespace std;
#include <cstdlib>

class Graph
{
private:
    int NumberOfNodes;    // No. of nodes
    list<int> *adj;    // Pointer to an array containing adjacency lists
    void DFSUtil(int node, bool visited[]);  // A function used by DFS
public:
    Graph(int NumberOfNodes);   // Constructor
    void addEdge(int node1, int node2);   // function to add an edge to graph
    void DFS();    // prints DFS  of the complete graph
};
Graph GraphGenerator(int nodes);
#endif