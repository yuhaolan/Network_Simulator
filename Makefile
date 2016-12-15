all :
	clang++ -o GraphGenerator GraphGenerator.cc Function.cc
	clang++ -std=c++0x -o NetworkSimulator NetworkSimulator.cc  Network_Graph.cc sending_routing.cc 
clean :
	rm GraphGenerator
	rm NetworkSimulator
