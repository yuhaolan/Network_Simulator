#include <iostream>
#include <list>
#include <time.h>       /* time */
using namespace std;
#include "Header.h"
#include <cstdlib>

Graph::Graph(int NumberOfNodes)
{
    this->NumberOfNodes = NumberOfNodes;
    adj = new list<int>[NumberOfNodes];
}
 
void Graph::addEdge(int node1, int node2)
{
    adj[node1].push_back(node2); // Add w to v’s list.
}
 
void Graph::DFSUtil(int node, bool visited[])
{
    // Mark the current node as visited and print it
    visited[node] = true;
    cout << node << " ";
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[node].begin(); i != adj[node].end(); ++i)
        if(!visited[*i])
            DFSUtil(*i, visited);
}
 
// The function to do DFS. It uses recursive DFSUtil()
void Graph::DFS()
{
    // Mark all the vertices as not visited
    bool *visited = new bool[NumberOfNodes];
    for (int i = 0; i < NumberOfNodes; i++)
        visited[i] = false;
 
    // Call the recursive helper function to print DFS traversal
    // starting from all vertices one by one
    for (int i = 0; i < NumberOfNodes; i++)
        if (visited[i] == false)
            DFSUtil(i, visited);
}

Graph GraphGenerator(int nodes)
{
	FILE * fp;
	fp = fopen ("Graph.txt","w");
    Graph g(nodes);
    int i,numofedges,v1,v2;//v1 is node1 , v2 is node2
    srand (time(NULL));
    numofedges = rand() % 200 + 1;//range 1 to 200
    cout<< nodes << "\t" << numofedges+nodes << endl;
    fprintf(fp, "%d\t%d\n",nodes,numofedges+nodes );
    //satisfy the connectivity, the min edges is nodes -1
    for(i = 0; i < nodes-1; i++)
    {
        g.addEdge(i,i+1);
        fprintf(fp, "%d\t%d\n",i,i+1);
        cout<< i << "\t" << i+1 << endl;
    }
   
    for(i = 0; i <= numofedges; i++)
    {
        v1 = rand() % 150;
        v2 = rand() % 150;
        if(v1 == v2)
        {
            numofedges++;
            continue;
        }
        else
        {
            g.addEdge(v1,v2);
            cout<< v1 << "\t" << v2 << endl;
             fprintf(fp, "%d\t%d\n",v1,v2);

        }
    }
    cout<<"=====>Generate Graph.txt"<<endl;
    return g;

}
 