#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

namespace DataStructure {
    class LinkedList {
        // A class for basic linked-list with included enqueue and deque functions

    public:
        class LinkedListNode {
        public:
            int value, weight;
            LinkedListNode * next;
            LinkedListNode(int value, int weight) {
                // Constructor
                this -> value = value;
                this -> next = nullptr;
                this -> weight = weight;
            }
            // User-defined Destructor for this is not needed!
        };
        LinkedListNode * HEAD;
        int size;
        LinkedList() {
            // Constructor
            this -> HEAD = nullptr;
            this -> size = 0;
        }
        ~LinkedList() {
            // Destructor because insert() dynamically allocates memory
            LinkedListNode * currentLinkedListNode = this -> HEAD, * nextLinkedListNode;
            while(currentLinkedListNode) {
                nextLinkedListNode = currentLinkedListNode -> next;
                delete currentLinkedListNode;
                currentLinkedListNode = nextLinkedListNode;
            }
        }
        
        void insert(int value, int weight) {
            // Simple function to insert a value at TAIL of a linked-list
            size = size + 1;

            LinkedListNode * new_node = new LinkedListNode(value, weight);
            if ( !HEAD ) {
                HEAD = new_node;
                return;
            }
            LinkedListNode * currentLinkedListNode = HEAD;
            while ( currentLinkedListNode -> next ) {
                currentLinkedListNode = currentLinkedListNode -> next;
            }
            currentLinkedListNode -> next = new_node;
        }

        bool isEmpty() {
            // Simple isEmpty function to tell if a list is empty or not
            return HEAD == nullptr;
        }

        void traverse() {
            // Linked list traversal(used for case with 'B' in assignment 5)
            LinkedListNode * currentLinkedListNode = HEAD;
            while ( currentLinkedListNode ) {
                std::cout << "value = " << currentLinkedListNode->value << "\t weight = " << currentLinkedListNode->weight << std::endl;
                currentLinkedListNode = currentLinkedListNode -> next;
            }
            std::cout << std::endl;
        }
    };
}