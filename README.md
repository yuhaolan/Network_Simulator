# Network_Simulator
•This project has two programs: graph generator and network simulator. 

•Graph generator should always generate a network of 150 nodes, with randomly-determined number of edges. Each edge has random bandwidth and delay. The graph should be connected.  

•Each node should have limited input queue, limited output queue and routing table. Finding the shortest path from each source-destination pairs stores in routing table. 

•Network simulator should load the graph, and randomly select 20 source-destination pairs for your network flow. Then, simulate packets and 1000 seconds of network activity. 

•Collect statistics data about the packet loss rate for each pair, the average delay for a packet, and total number of packets which reach destination successfully.

------------------------------------------------------------------------------------------------------------------------------
I wrote this program on MAC OS. I use clang++ compiler(http://clang.llvm.org). 

USAGE:
$make
$./GraphGenerator
It will Generate Graph.txt
$./NetworkSimulator Graph.txt 2
Usage:./NetworkSimulator InputGraphFile SeedNumber



Design ideas:

1. I create a graph, runing DFS/BFS to check all 150 nodes is connected to each other

(part 1. can be seen in GraphGenerator.h GraphGenerator.cc)

2. I load a graph
	2.1 create a class NODE, it have input and output queue, vector(is to store all the information for each path,for example: source node,destination node, bandwidith, delay)
	2.2 use one object named NODE g, to run Dijkstra algorithm to find the shorest path way 

	(part 2.1 2.2 can be seen in Network.h Network_Graph.cc)

	2.3 cut each path and save it to routing table, the routing table has destination node, and the next node it needs to go
	I use array to store this information

	(part 2.3 can be seen in sending_routing.h sending_routing.cc routing part)

	2.4 I use Node* array[150] this array of pointers to simulate each node. 
		2.4.1 Sending packet: I use bytes array to simulate packet. I create 1900 packets to simulate send, if you want you can generate more. But size of input and output queue is only 30, so it will have more packet loss. 
		2.4.2 How to send: I first finish how to send packet between nodes that are connect directly. Then I cut path from source node to destination node into many times sending packet packet between nodes that are connect directly. I check each node routing table and now next node I can go.
		For example, the Path is A - D - F - G - P - C. 
			Send packet from A to C;
				1. send packet from A to D directly
				2. send packet from D to F directly
				3. send packet from F to G directly
				4. send packet from G to P directly
				5. send packet from P to C directly
		2.4.3 How to check packet loss: In Node class, I have variables to keep track of packet loss and receive for each node
		2.4.4 How to count the delay: we know each direct path's delay, cut long path into small paths, and add delay together
		2.4.5 How to simulate packet on the path: I use global queue, using First Come First Out. I put the packets into queue, first come first put into next node

(part 2.4 can be seen in send_routing.cc NetworkSimulator.cc and header files)

The RESULT is the output that is showing in my MacBook Pro.

Yuhao Lan
