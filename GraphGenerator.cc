#include <iostream>
#include <list>
#include <time.h>       /* time */
using namespace std;
#include "Header.h"
#include <cstdlib>

int main()
{
    // Create a graph given in the above diagram
    Graph g = GraphGenerator(150);
 
    cout << "Run DFS:\n";
    g.DFS();
 
    return 0;
}