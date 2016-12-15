#include <iostream>
#include <list>
#include <time.h>       /* time */
using namespace std;
#include <cstdlib>
#include <vector>
#include <string>     // std::string, std::to_string
#include <deque>
#include <sstream>
#include "sending_routing.h"

void Set_up_routing_table(int node_20[],Node* array[],Node g)
{
	vector<int> route;
	int k = 0;
	//initiliatez 20 nodes routing table
	for(int i = 0; i < 150; i++)
		for(int j = 0;j < 150; j++)
		{
			array[i]->routing_table[j] = -1;
		}

	for(int i = 0;i < 20;i++)
	{
		for(int j = i+1; j <20 ; j++)
		{
			// i is source j is the destnation
			int route_array[150];
			int len_route_array = 0;
			//node in the path from source to destnation
			int source_node = 0;
			int next_node = 0;
			int last_node = 0;
			//cout << node_20[i] << " TO " << node_20[j] << endl;
			route = g.Dijkstra(node_20[i],node_20[j]);
			
			//map vector of route path to array 
			//array is easy to handle
			k = 0;
			for (vector<int>::iterator it=route.begin(); it!=route.end(); ++it)
			{
				route_array[k] = *it;
				k++;
				
			}
			route_array[k] = '\0';
			k = 0;
			//get the length of the array
			while(route_array[k] != '\0')
			{
				len_route_array++;
				k++;
			}
			k = 0;
			//scan all the array
			//cout <<  "===>" <<len_route_array << endl;
			while(k < len_route_array)
			{
				//if next one is out of range
				if(k+1 ==len_route_array)
					break;
				//source node
				source_node = route_array[k];
				//next node need to go
				next_node = route_array[k+1];
				// dest node
				last_node = route_array[len_route_array-1];
				//find the index of routing table that is free
				array[source_node]->routing_table[last_node]= next_node;			
				k++;	
			}
			len_route_array = 0;	
			//clean up the route vector
			route.clear();


		}
	cout << "Run Dijkstra Find Shorest Path from Node" << node_20[i] <<" To Each Other ===>";
	cout << "Set up Node " << node_20[i]<< " Routing Table successfully" << endl;
	}

}


int Send_Packet_Two_Nodes(Node* array[],int S,int D,unsigned char* packet,deque<unsigned char* > Global_Queue)
{
	//outputQ
	//check size
	if(array[S]->OutputQ.size() > 30)
	{
		return 0;
	}
	else
	{
		array[S]->OutputQ.push_back(packet);
		array[S]->OutputQ.pop_front();
	}
	//put it to Global_Queue to simulate sending 
	array[S]->packet_send++; 


	Global_Queue.push_back(packet);

	Global_Queue.pop_front();
	//put it into destination Q
	//check size
	if(array[D]->InputQ.size() > 30)
	{
		return 0;
	}
	else
	{
		array[D]->InputQ.push_back(packet);
	}
	return 1;

}	

int Send_packet(Node* array[],int S,int D,unsigned char* packet,int delay_array[150][150],deque<unsigned char* > Global_Queue,int& pack_drop,int& pack_recv)
{
	//next node
	
	int Next_Node;
	int Path_Delay = 0;
	int temp1 = S;
	int temp2 = D;
	
	while(array[S]->routing_table[D] != D)
	{
		Next_Node = array[S]->routing_table[D];
		//send packet in two nodes
		
		Path_Delay += delay_array[S][Next_Node];
		//move source to next node
		S = array[S]->routing_table[D];
	}
	if(array[S]->routing_table[D] == D)
		Path_Delay += delay_array[S][D];
	

	S = temp1;
	D = temp2;

	while(array[S]->routing_table[D] != D)
	{
		Next_Node = array[S]->routing_table[D];
		//send packet in two nodes
		//if one sub path has a packet drop then break
		if(Send_Packet_Two_Nodes(array,S,Next_Node,packet,Global_Queue)==0)
		{
			array[D]->packet_drop++;
			pack_drop++;
			break;
		}
		
		//move source to next node
		S = array[S]->routing_table[D];
	}
//the packet has received the Destnation
	if(array[S]->routing_table[D] == D)
	{
		Send_Packet_Two_Nodes(array,S,D,packet,Global_Queue);
		array[D]->packet_receive++; 
		pack_recv++;
	}


	return Path_Delay;

}





















