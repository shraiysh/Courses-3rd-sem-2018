#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "LinkedList.h"
#endif

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "PriorityQueue.h"
#endif

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
                delete adjacencyList;
            }
        };
        
        GraphNode * nodes;
        // A 2-D array for storing parents when BFS is carried on a node where first
        // index is start for BFS and second index marks the vertex for which parent is needed
        int ** parentArray, ** dist;
        int size;
        
        Graph ( int size ) {
            // Contructor for init an object of Graph
            this -> size = size + 1;
            this -> parentArray = new int*[this -> size];
            this -> dist = new int*[this -> size];
            for(int i = 0; i < this -> size; i++ ) {
                parentArray[i] = new int[this -> size];
                dist[i] = new int[this -> size];
                // Filling with default values -1
                std::fill_n(this -> parentArray[i], this -> size, -1);
                std::fill_n(this -> dist[i], this -> size, std::numeric_limits<int>::max());
            }

            this -> nodes = new GraphNode [ this -> size ];
        }

        ~Graph() {
            // Destructor for object
            delete[] nodes;
            for ( int i = 0; i < size; i++ ) {
                delete[] parentArray[i];
                delete[] dist[i];
            }
            delete[] parentArray;
            delete[] dist;
        }

        void addEdge ( int start, int end, int weight ) {
            // Adds an edge in the graph
            nodes[start].adjacencyList -> insert ( end, weight );
        }

        int getEdgeWeight(int start, int end) {
            // Checks if a gra[h contains an edge
            DataStructure::LinkedList::LinkedListNode * currentLinkedListNode = nodes[start].adjacencyList -> HEAD;
            int found = -1;
            while ( currentLinkedListNode ) {
                if ( currentLinkedListNode -> value == end ){
                    found = currentLinkedListNode->weight;
                    break;
                }
                currentLinkedListNode = currentLinkedListNode -> next;
            }
            return found;
        }

        void dijkstra(int start) {
            PriorityQueue myQueue(size);
            // int parent[size];
            dist[start][start] = 0;
            myQueue.initInf(size);
            myQueue.insert(0, start);
            while(!myQueue.isEmpty()) {
                PriorityQueue::Node queueNode = myQueue.extract_min();
                int u = queueNode.vertexIndex;
                LinkedList::LinkedListNode *currentNode = nodes[u].adjacencyList -> HEAD;
                while(currentNode) {
                    int v = currentNode->value;
                    if(dist[start][v] > dist[start][u] + getEdgeWeight(u, v)) {
                        dist[start][v] = dist[start][u] + getEdgeWeight(u, v);
                        myQueue.insert(dist[start][v], v);
                        parentArray[start][v] = u;
                    }
                    currentNode = currentNode -> next;
                }
            }
        }

        void showPath(int start, int end) {
            if(dist[start][start]!=0) dijkstra(start);
            int path[size], index=0;
            std::fill_n(path, size, -1);
            int currentNode = end;
            while ( currentNode!=start && parentArray[start][currentNode]!=-1) {
                path[index++] = currentNode;
                currentNode = parentArray[start][currentNode];
            }
            if(currentNode==start) {
                std::cout << start << " ";
                while(index--)
                    std::cout << path[index] << " ";
                std::cout << std::endl;
            }
            else std::cout << "-1" << std::endl;
        }
    };
}