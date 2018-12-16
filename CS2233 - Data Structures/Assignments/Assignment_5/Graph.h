#include <iostream>
#include "LinkedList.h"

namespace DataStructure {
    class Graph {

    public:
        class GraphNode {
            // Class for a node in a Graph
        public:
            DataStructure::LinkedList * adjacencyList;
            GraphNode() {
                // Default Constructor
                adjacencyList = new DataStructure::LinkedList();

            }
            ~GraphNode() {
                // Destructor
                delete this -> adjacencyList;
            }
        };
        
        GraphNode * nodes;
        // A 2-D array for storing parents when BFS is carried on a node where first
        // index is start for BFS and second index marks the vertex for which parent is needed
        int ** parentArray; 
        int size;
        
        Graph ( int size ) {
            // Contructor for init an object of Graph
            this -> size = size + 1;
            this -> parentArray = new int*[this -> size];
            for(int i = 0; i < this -> size; i++ ) {
                parentArray[i] = new int[this -> size];
                // Filling with default values -1
                std::fill_n(this -> parentArray[i], this -> size, -1);
            }

            this -> nodes = new GraphNode [ this -> size ];
        }

        ~Graph() {
            // Destructor for object
            delete[] this->nodes;
            for ( int i = 0; i < this -> size; i++ ) {
                delete[] (this -> parentArray)[i];
            }
            delete[] this -> parentArray;
        }

        void addEdge ( int start, int end ) {
            // Adds an edge in the graph
            (this -> nodes [ start ]).adjacencyList -> insert ( end );
        }

        bool containsEdge(int start, int end) {
            // Checks if a gra[h contains an edge
            DataStructure::LinkedList::LinkedListNode * currentLinkedListNode = (this -> nodes)[start].adjacencyList -> HEAD;
            int found = false;
            while ( currentLinkedListNode ) {
                if ( currentLinkedListNode -> value == end ){
                    found = true;
                    break;
                }
                currentLinkedListNode = currentLinkedListNode -> next;
            }
            return found;
        }

        void BFS ( int start, bool isTraversal ) {
            // Does a BFS and stores the parent of `i` in parentArray[start][i]
            if ( start == 0 ) return;
            int color[ this ->  size ] = {0};   // 0 - White, 1 - Gray, 2 - Black
            DataStructure::LinkedList queue;
            queue.enqueue(start);
            color[start] = 1;
            while( !queue.isEmpty() ) {
                // Dequeue a vertex = u (the first one)
                int u = queue.dequeue();
                if (isTraversal) std::cout << u << " ";                
                LinkedList::LinkedListNode * currentLinkedListNode = nodes[u].adjacencyList -> HEAD;
                // Traverse the adjacency list of this adding all those which are white in color to the queue.
                // Coloring them to gray
                while ( currentLinkedListNode ) {
                    int v = currentLinkedListNode -> value;
                    if(color [v] == 0) {
                        color[v] = 1;
                        (this -> parentArray)[start][v] = u;
                        queue.enqueue(v);
                    }
                    currentLinkedListNode = currentLinkedListNode -> next;
                }
                color [ u ] = 2;
            }
            if(isTraversal) std::cout << std::endl;
        }

        void BFS( int start ) {
            this -> BFS(start, false);
        }
        void showBFS( int start ) {
            this -> BFS(start, true);
        }

        void showShortestPath(int start, int end) {
            // A function to show the shortest path
            if ( this -> parentArray[start][start] == -1 ) {
                // This happens when BFS with `start` as start has not been done. Hence we do it.
                this -> BFS(start);
            }
            int path[this -> size], index=0;
            std::fill_n(path, this -> size, -1);
            int currentNode = end;
            while( currentNode!=start & (this -> parentArray)[start][currentNode] != -1 ) {
                path[index++] = currentNode;
                currentNode = (this -> parentArray)[start][currentNode];
            }
            if(currentNode == start) {
                // Reverse traversal of array
                std::cout << start << " "; 
                while ( index-- )
                    std::cout << path[index] << " ";
                std::cout << std::endl;
            }
            else {
                std::cout << "-1" << std::endl;
            }
        }
    };
}