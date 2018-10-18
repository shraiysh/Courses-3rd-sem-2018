#include <cstdlib>

// #include "LinkedList.h"
#include "Graph.h"

using namespace std;

void doAsTheStateSays(DataStructure::Graph ** myGraph, int state, int start, int end, int numExtracted, int number, int adjacencyListIndexExtracted, int adjacencyListIndex) {
    // A utility function that does as the state says after every new line and at EOF, in cse new line was not given there!
    if(state == 'N'){
        delete (*myGraph);
        (*myGraph) = new DataStructure::Graph(number);
    }
    else if(state == 'B') {
        (*myGraph) -> showBFS(number);
    }
    else if(state == '?') {
        end = number;
        cout << (*myGraph) -> containsEdge(start, end) << endl;
    }
    else if(state == 'P') {
        end = number;
        (*myGraph) -> showShortestPath(start, number);
    }
    else if(state == 'E') {
        (*myGraph) -> addEdge(adjacencyListIndex, number);
    }
}

int main() {
    // > `numExtracted` is a flag for encountering first number on a line, `number` stores the number
    // > `adjacencyListIndexExtracted` is a similar flag used only when 'E' is given to mark storage
    //   of the vertex for which the adjacency list is given (stored in `adjacencyListIndex`)
    // > `start` and `end` are start and end for '?' and 'P' where only 2 entries are needed.
    int digit, state = ' ', numExtracted = 0, number = 0;
    int adjacencyListIndexExtracted = 0, adjacencyListIndex = 0;
    int start = 0, end = 0;

    DataStructure::Graph * myGraph = new DataStructure::Graph(0);
    
    while((digit=fgetc(stdin)) != EOF) {
        if(digit == 'N' || digit == 'E' || digit == '?' || digit == 'B' || digit == 'P') {
            adjacencyListIndexExtracted = adjacencyListIndex = 0;
            numExtracted = number = 0;
            start = end = 0;
            state = digit;
        }
        else if(digit == ' ' && numExtracted) {
            if (state == 'E' && adjacencyListIndexExtracted ) {
                myGraph -> addEdge(adjacencyListIndex, number);
            }
            else if ( state == 'E' ) {
                adjacencyListIndex = number;
                adjacencyListIndexExtracted = 1;
            }
            else if (state == '?' || state == 'P') {
                start = number;
            }
            number=0;
        }
        else if(digit == '\n') {
            doAsTheStateSays( &myGraph, state, start, end, numExtracted, number, adjacencyListIndexExtracted, adjacencyListIndex );
            state = ' ';
        }
        else if(digit >= '0' && digit <= '9') {
            number = number * 10 + digit - '0';
            numExtracted = 1;
        }
    }
    if(state != ' ') {
        // In case the file does not end by \n
        doAsTheStateSays( &myGraph, state, start, end, numExtracted, number, adjacencyListIndexExtracted, adjacencyListIndex );
    }
    delete myGraph;
}