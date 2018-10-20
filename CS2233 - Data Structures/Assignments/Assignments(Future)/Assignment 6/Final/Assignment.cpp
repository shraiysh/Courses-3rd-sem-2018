#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef GRAPH_H
#define GRAPH_H
#include "Graph.h"
#endif

#include <string>
#include <sstream>
using namespace std;

void getInput(istringstream * stream, int * a) {
    string temp;
    (*stream) >> temp;
    (*a) = stoi(temp);
}

int main() {

    // It has been assumed that the queries to the GRAPH will be done after specifying
    // ALL the edges. In case this is not true, the program breaks down.
    DataStructure::Graph * myGraph = new DataStructure::Graph(0);
    while(!cin.eof()) {
        string input_line;
        getline(cin, input_line);
        if(!input_line.length()) return 0;
        char state = input_line[0];
        istringstream myStream(input_line.substr(1));
        int a, b, c;


        switch(state) {
            case 'N':
                delete myGraph;
                getInput(&myStream, &a);
                myGraph = new DataStructure::Graph(a);
                break;

            case 'E':
                getInput(&myStream, &a);    // stores `u` for the list
                
                while(myStream >> b && myStream >> c) {
                    // b has v(i) and c has w(u, v(i))
                    myGraph -> addEdge(a, b, c);
                }
                break;

            case '?':
                getInput(&myStream, &a);
                getInput(&myStream, &b);

                std::cout << myGraph->containsEdge(a,b) << std::endl;
                break;

            case 'P':
                getInput(&myStream, &a);
                getInput(&myStream, &b);

                myGraph->showPath(a,b);
                break;

            case 'D':
                getInput(&myStream, &a);
                myGraph->showDijkistra(a);
                break;

        }
    }
    delete myGraph;
}