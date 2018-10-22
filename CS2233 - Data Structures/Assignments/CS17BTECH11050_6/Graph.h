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

        const int INFINITY = std::numeric_limits<int>::max();

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
            this -> size = size;
            this -> parentArray = new int*[size + 1];
            this -> dist = new int*[size+1];
            for(int i = 1; i <=size; i++ ) {
                parentArray[i] = new int[size+1];
                dist[i] = new int[size+1];
                // Filling with default values -1
                std::fill_n(this -> parentArray[i],size+1, -1);
                std::fill_n(this -> dist[i], size+1, INFINITY);
            }

            this -> nodes = new GraphNode [size+1];
        }

        ~Graph() {
            // Destructor for object
            delete[] nodes;
            for ( int i = 1; i <= size; i++ ) {
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

        int containsEdge(int start, int end) {
            return nodes[start].adjacencyList->contains(end);
        }

        int getEdgeWeight(int start, int end) {
            // Checks if a graph contains an edge and returns weight if it does
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

        bool arrayContains(int * array, int length, int value) {
            for(int i=0;i<length;i++) {
                if(array[i] == value) return true;
            }
            return false;
        }

        void dijkstra(int start, bool showDijkistra) {
            if(showDijkistra) {
                // Any previous calculations of parents and distances have to removed.
                std::fill_n(this -> parentArray[start],size+1, -1);
                std::fill_n(this -> dist[start], size+1, INFINITY);
            }
            // Priority -> distances, metadata -> vertex index at the distance
            PriorityQueue myQueue(size);
            dist[start][start] = 0;     // Distance of start from start = 0

            // The array stores the order in which dijkistra vertices are encountered.
            int orderOfDijkstra[size-1]={0}, count = 0; 
            
            // Initializes all distances to infinity for vertex = 1 to vertex = size (1-based indexing)
            myQueue.initInf(size);

            // Starting dijkistra!
            myQueue.insert(0, start);
            
            while(!myQueue.isEmpty()) {

                PriorityQueue::Node queueNode = myQueue.extract_min();
                // u will have the least distance node.
                int u = queueNode.vertexIndex;

                // Adding u to the order!
                orderOfDijkstra[count++] = u;

                if(dist[start][u] == INFINITY) continue;    // No need to add it's neighbours.

                // Traversing adjacency list of u and adding them
                LinkedList::LinkedListNode *currentNode = nodes[u].adjacencyList -> HEAD;
                while(currentNode) {
                    // v is a neighbour of u. u->v edge exists.
                    int v = currentNode->value;

                    if( dist[start][v] > dist[start][u] + getEdgeWeight(u, v)) {
                        
                        // If new dis(u) + w(u,v) < dis(v) then change dis(v) and v must be traversed!
                        dist[start][v] = dist[start][u] + getEdgeWeight(u, v);
                        myQueue.insert(dist[start][v], v);
                        
                        // Handling the parent array (useful while printing path!)
                        parentArray[start][v] = u;
                    }
                    currentNode = currentNode -> next;
                }
            }
            if(showDijkistra) {
                for(int i=0; i<count && orderOfDijkstra[i]!=0; i++) {
                    std::cout << orderOfDijkstra[i] << " ";

                    // Making sure that unconnected vertices are shown at a dis of -1
                    if(dist[start][orderOfDijkstra[i]] == INFINITY) std::cout << "-1" << std::endl;
                    else std::cout << dist[start][orderOfDijkstra[i]] << std::endl;
                }
            }

        }

        void dijkstra(int start) {
            dijkstra(start, false);
        }

        void showDijkistra(int start) {
            dijkstra(start, true);
        }

        void showPath(int start, int end) {

            // If dijkstra has not been done yet, we do it!
            if(dist[start][start]!=0) dijkstra(start);

            if(dist[start][end] == INFINITY) {
                // Means they are not connected!
                std::cout << "-1" << std::endl;
                return;
            }

            // Here, they are definitely connected. path stores the path in reverse order!
            int path[size+1], index=0;
            // Filling path with -1
            std::fill_n(path, size+1, -1);

            // starting from the end and storing parents in path.
            int currentNode = end;

            while ( currentNode!=start && parentArray[start][currentNode]!=-1) {
                path[index++] = currentNode;
                currentNode = parentArray[start][currentNode];
            }
            // showing distance
            std::cout << dist[start][end] << " ";
            // showing the start vertex which was not included in the path!
            std::cout << start << " ";

            while(index--)
                std::cout << path[index] << " ";
            std::cout << std::endl;
        }
    };
}