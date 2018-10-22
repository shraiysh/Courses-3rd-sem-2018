#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif
#ifndef METADATA_H
#define METADATA_H
#include "Metadata.h"
#endif
namespace DataStructure {
    class LinkedList {
        // A class for basic linked-list with included enqueue and deque functions

    public:
        class LinkedListNode {
        public:
            int value;
            LinkedListNode * next;
            Metadata * meta;
            LinkedListNode(int value, Metadata * meta) {
                // Constructor
                (*this).value = value;
                (*this).next = nullptr;
                this -> meta = meta;
            }
            // User-defined Destructor for this is not needed!
        };
        LinkedListNode *HEAD, *TAIL;
        Metadata * meta;
        int size;
        LinkedList(Metadata * meta) {
            // Constructor
            this -> HEAD = this -> TAIL = nullptr;
            this -> size = 0;
            this -> meta = meta;
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
        
        void insert(int value) {
            // Simple function to insert a value at TAIL of a linked-list
            this -> size = this -> size + 1;
            LinkedListNode * new_node = new LinkedListNode(value, meta);
            if ( !this -> HEAD ) {
                HEAD = TAIL = new_node;
                return;
            }
            TAIL -> next = new_node;
            TAIL = new_node;
        }

        bool isEmpty() {
            // Simple isEmpty function to tell if a list is empty or not
            return this -> HEAD == nullptr;
        }

        bool contains(int x) {
            LinkedListNode * currentLinkedListNode = HEAD;
            while(currentLinkedListNode) {
                if(currentLinkedListNode->value == x) break;
                currentLinkedListNode = currentLinkedListNode->next;
            }
            if(currentLinkedListNode!=nullptr) return true;
            return false;
        }

        void traverse() {
            // Linked list traversal(used for case with 'B' in assignment 5)
            LinkedListNode * currentLinkedListNode = this -> HEAD;
            while ( currentLinkedListNode ) {
                std::cout << currentLinkedListNode -> value << " ";
                currentLinkedListNode = currentLinkedListNode -> next;
            }
            std::cout << std::endl;
        }
    };
}