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
    if((*stream) >> temp && ((*a)=stoi(temp)))
        return;

    (*a)=-1;
    std::cout << "Invalid input!" << std::endl;
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
                if(a==-1) break;                // Invalid input for a
                myGraph = new DataStructure::Graph(a);
                break;

            case 'E':
                getInput(&myStream, &a);    // stores `u` for the list
                if(a == -1 || a > myGraph->size) break;            // Invalid input for a
                while(myStream >> b && myStream >> c) {
                    // b has v(i) and c has w(u, v(i))
                    if( b > myGraph->size ) break;
                    myGraph -> addEdge(a, b, c);
                }
                break;

            case '?':
                getInput(&myStream, &a);
                getInput(&myStream, &b);
                if(a!=-1 && b!=-1)
                    std::cout << myGraph->containsEdge(a,b) << std::endl;
                break;

            case 'P':
                getInput(&myStream, &a);
                getInput(&myStream, &b);
                if(a!=-1 && b!=-1 && a <= myGraph->size && b <= myGraph->size)
                    myGraph->showPath(a,b);
                else
                    std::cout << "-1" << std::endl;
                break;

            case 'D':
                getInput(&myStream, &a);
                if(a!=-1)
                    myGraph->showDijkistra(a);
                break;

        }
    }
    delete myGraph;
}