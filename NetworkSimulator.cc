#include <iostream>
#include <list>
#include <time.h>       /* time */
using namespace std;
#include "sending_routing.h"
#include <cstdlib>
#include <fstream>
#include <set>
#include <sstream>
#include <deque>


int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		cout<<"Usage:./NetworkSimulator InputGraphFile SeedNumber"<<endl;
	}
	else
	{
		FILE * fp;
	
		//generate 20 random number of nodes
		int SeedNumber = atoi(argv[2]);
		int bandwidth = 0;//0-1000 bits
		int delay = 0;//1-10 s
		int i;
		int delay_array[150][150];//keep track of the delay
		srand (SeedNumber);
		set<int> select_nodes;

		while(select_nodes.size() < 20)
			select_nodes.insert(rand() % 150);
		
		std::ifstream infile(argv[1]);
		int a, b;

		infile >> a >> b;//first line is about the number of nodes and the number of edges
		//read the edges
		Node* array[150];//150 nodes
		Node g;//use one node to run Dijkstra

		for(i = 0;i < 150;i++)
		{
			array[i] = new Node();
		}
		//initiate delay_array
		for(int i = 0; i < 150 ; i++)
			for(int j = 0; j < 150; j++)
			{
				delay_array[i][j] = 1;
			}
		//
		while (infile >> a >> b)
		{
			bandwidth = rand()%1000+1;
			delay = rand()%10+1;
			//cout << delay << " ";
			array[a]->addEdge(a,b,bandwidth,delay);//each node has own vector
			g.addEdge(a,b,bandwidth,delay);
			delay_array[a][b] = delay;
			delay_array[b][a] = delay;
		}
		
		

		//20 nodes is in select_nodes
		int nodes_20[20];
		i = 0;
		for (std::set<int>::iterator it=select_nodes.begin(); it!=select_nodes.end(); ++it)
		{

			// std::cout << ' ' << *it << ' ' <<endl;
			 nodes_20[i] = *it;
			 i++;

		}
		//set up the routing table for each node
		//array[each node] --> routing_table[dest_node] = next node to go;
		Set_up_routing_table(nodes_20,array,g);
		//Simulate the Network
		unsigned char* packet;
		int total_number_packets = 0;
		int total_number_packets_receive_success = 0;
		float overall_delay_of_one_packet = 0;//all the time from delivering packets/number of packets
		int max_number_drop[20];
		int min_number_drop[20];
		int total_delay;
		int Path_Delay = 0;
		int average_delay_each_flow[150][150];
		int Total_Delay_All_packet =0;
		float pack_loss_rate = 0.0;
		int pack_drop = 0;
		int pack_rev = 0;
		//packet receive and drop
		int p_revd[150][150];
		int p_dp[150][150];		
		//simulate 1900 packets
		for(int i = 0; i < 10; i++)
			for(int j = 0; j < 20; j++)
				for(int k = j+1; k < 20;k++)
				{
					if(j+1 == 20)
						break;
					unsigned char* packet = new unsigned char[100];
					deque<unsigned char* > Global_Queue;

					//send packets from one node to other 19 nodes
					Path_Delay = 0;
					pack_drop = 0;
					pack_rev = 0;
					Path_Delay = Send_packet(array,nodes_20[j],nodes_20[k],packet,delay_array,Global_Queue,pack_drop,pack_rev);
					Total_Delay_All_packet += Path_Delay;
					//because many nodes will in same link that's why +=
					average_delay_each_flow[nodes_20[j]][nodes_20[k]] += Path_Delay;
					p_revd[nodes_20[j]][nodes_20[k]] += pack_rev;
					p_dp[nodes_20[j]][nodes_20[k]] += pack_drop;
					total_number_packets++;
					delete [] packet;
				}

		//STATISTICS
		//• The total number of packets generated by sources.
		cout << "###################################################" << endl;
		cout << "The total number of packets generated by sources : " << total_number_packets <<endl;
		int aa;
		for(int i;i < 20;i++)
		{
			total_number_packets_receive_success += array[nodes_20[i]]->packet_receive;
			aa+=array[nodes_20[i]]->packet_drop;
		}
		//• The total number of packets which reached their destinations successfully.
		cout << "The total number of packets which reached their destinations successfully :" << total_number_packets_receive_success << endl;
		cout << "The total number of packets which droped their destinations successfully :" << aa << endl;
		
		//• The overall average total delay for a packet (measured from source to destination).
		cout << "The overall average total delay for a packet " << (float) Total_Delay_All_packet/total_number_packets << "s" << endl;
		//• The average delay of the packets within each flow (per source-destination pair).	
		for(int j = 0; j < 20; j++)
				for(int k = j+1; k < 20;k++)
				{
					cout << "Average Delay: Path:Node "<<nodes_20[j]<<" To Node " << nodes_20[k] << " = " <<(float) average_delay_each_flow[nodes_20[j]][nodes_20[k]]/10 << "s"<<endl;
				}	
		//• The packet loss rate, as a percentage, for each source-destination pair.
		for(int j = 0; j < 20; j++)
				for(int k = j+1; k < 20;k++)
				{
					cout << "The packet loss rate in Node "<<nodes_20[j]<<" To Node " << nodes_20[k] << " = " << (float)  p_dp[nodes_20[j]][nodes_20[k]]/(p_dp[nodes_20[j]][nodes_20[k]]+p_revd[nodes_20[j]][nodes_20[k]]) <<endl;
				}	
		//• The maximum, minimum, and average number of packets dropped per router.
		int max_drop = 0;
		int min_drop = INT_MAX;
		float average_drop = 0.0;
		int total_drop = 0;
		for(int i;i < 150;i++)
		{
			if(max_drop < array[i]->packet_drop)
				max_drop = array[i]->packet_drop;

			if( array[i]->packet_drop < min_drop)
				min_drop = array[i]->packet_drop;
			total_drop +=  array[i]->packet_drop;
		}
		cout << "Maximum packets dropped per router = " << max_drop << endl;
		cout << "Minimum packets dropped per router = " << min_drop << endl;
		cout << "Average packets dropped per router = " << total_drop/150 << endl;


	}



	return 0;
}