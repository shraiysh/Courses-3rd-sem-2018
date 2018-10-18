#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.h"
#endif

using namespace std;
int main() {
    DataStructure::Graph myGraph(5);
    myGraph.addEdge(1,2,10);
    myGraph.addEdge(1,3,5);
    myGraph.addEdge(2,3,2);
    myGraph.addEdge(3,2,3);
    myGraph.addEdge(2,5,1);
    myGraph.addEdge(3,5,9);
    myGraph.addEdge(3,4,2);
    myGraph.addEdge(4,5,6);
    myGraph.addEdge(5,4,4);
    myGraph.addEdge(4,1,7);
    // myGraph.dijkstra(5);

    for(int i=1;i<=5;i++) {
        myGraph.showPath(1, i); 
    }

    DataStructure::Graph myGraph2(3);
    myGraph2.addEdge(1,2,1);
    myGraph2.addEdge(3,1,1);
    myGraph2.addEdge(3,2,2);
    myGraph2.dijkstra(3);

}