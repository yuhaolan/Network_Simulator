#ifndef NK
#define NK

#include <iostream>
#include <list>
#include <time.h>       /* time */
using namespace std;
#include <cstdlib>
#include <vector>
#include <string>     // std::string, std::to_string
#include <deque>
#include <sstream>



class Node
{
	public:
		int routing_table[150];//choose 20 nodes, destnatiion,
		//router table has 19 index, 19 final destation nodes, 19 next nodes need to go
		deque<unsigned char*> InputQ;
		deque<unsigned char*> OutputQ;
		int packet_drop = 0;
		int packet_send = 0;
		int packet_receive = 0;
		int average_delay_each_flow[150][150];

		vector<string> V;
		Node();
		void addEdge(int node1,int node2,int weight,int delay);
		void sendpacket(int node1,int node2, char* Packet);
		vector<int>  Dijkstra(int node1,int node2);

};
#endif