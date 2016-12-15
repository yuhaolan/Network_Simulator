#include <iostream>
#include <list>
#include <time.h>       /* time */
using namespace std;
#include <cstdlib>
#include <vector>
#include <string>     // std::string, std::to_string
#include "Network.h"
#include <sstream>
#include <set>


//Simulate the Networking
Node::Node()
{
}
//add edge from node1 to node2
void Node::addEdge(int node1,int node2,int weight,int delay)
{
	string edge_message = to_string(node1) + "," + to_string(node2) + "," + to_string(weight) + "," + to_string(delay);
	V.push_back(edge_message);
}

vector<int>  Node::Dijkstra(int node1,int node2)//edges is total number of edges
{
	int length[150][150];//use 2D array to save each node to another node's bandwidth
	for(int i = 0; i < 150 ; i++)
		for(int j = 0; j < 150; j++)
		{
			length[i][j] = -1;//-1 means no edge
		}
		
		for (int i=0; i<V.size(); i++)
		{
			istringstream ss(V.at(i));
			string token;
			getline(ss,token,',');
			int source = stoi(token);
			getline(ss,token,',');
			int dest = stoi(token);//NULL is about the same string strtok
			getline(ss,token,',');
			int weight = stoi(token);

			length[source][dest] = weight;
			length[dest][source] = weight;
		}
		//Run Dijkstra
		//Create a set to put all nodes in Q


		//node1 ----->  node2   
		//source -----> destnatioin

		set <int> Q;
		int dist[150];
		int prev[150];
		int v = 0;
		int u = 0;
		int temp = 0;//for compare to find the min
		int i = 0;
		int alt = 0;//the length of the pathway
		for (i = 0; i < 150; i++)
		{
			//add nodes
			Q.insert(i);
			dist[i] = INT_MAX;// // Unknown distance function from
								// source to v

		}
		dist[node1] = 0;//distance to source is 0

		while(Q.size() != 0)//Q's size is not empty
		{
			//u := vertex in Q with smallest distance in dist[] ;
			int temp = INT_MAX;

			for(set<int>::iterator it=Q.begin(); it!=Q.end(); ++it)
			{
    			//std::cout << *it << std::endl;
    			if(dist[*it] < temp)
    			{
    				temp = dist[*it];
    				u = *it;
    			}
			}
			
			//remove u from Q ;
			Q.erase(u);
			// if u = target break;
			if(u == node2)
			{
				break;
			}

			// all remaining vertices are
			// inaccessible from source

			if(dist[u] == INT_MAX)  
				break;

			//for each neighbor v of u:
			// where v has not yet been
			// removed from Q.
			for(i = 0; i < 150 ; i++)
			{
				if( (length[u][i] != -1) && (Q.count(i) > 0))
				{
					alt = dist[u] + length[u][i];
					if(alt < dist[i])
					{
						dist[i] = alt;
						prev[i] = u;
					}

				}

			}

		}
		
//define a vector
		vector<int> route;
		int rev;
		rev = node2;
		route.push_back(rev);
		//if the node2 have one previous node
		//but this node cannot be 0
		while(prev[node2])
		{
			if(prev[rev] == node1)
			{
				route.push_back(node1);
				break;
			}
			route.push_back(prev[rev]);
			rev = prev[rev];
		}
		//if this node is 0
		if(prev[node2] == 0)
			route.push_back(0);
		//reverse the route vector,from source to destnation
		std::reverse(route.begin(),route.end());

		return route;
	
}

