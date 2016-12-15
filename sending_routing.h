#ifndef SR
#define SR

#include <iostream>
#include <list>
#include <time.h>       /* time */
using namespace std;
#include <cstdlib>
#include <vector>
#include <string>     // std::string, std::to_string
#include <deque>
#include <sstream>
#include "Network.h"

void Set_up_routing_table(int node_20[],Node* array[],Node g);
					
int Send_packet(Node* array[],int S,int D,unsigned char* packet,int delay_array[150][150],deque<unsigned char* > Global_Queue,int& pack_drop,int& pack_recv);
int Send_Packet_Two_Nodes(Node* array[],int S,int D,unsigned char* packet,deque<unsigned char* > Global_Queue);

#endif