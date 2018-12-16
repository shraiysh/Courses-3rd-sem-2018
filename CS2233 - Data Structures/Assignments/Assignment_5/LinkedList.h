#include <iostream>
namespace DataStructure {
    class LinkedList {
        // A class for basic linked-list with included enqueue and deque functions

    public:
        class LinkedListNode {
        public:
            int value;
            LinkedListNode * next;
            LinkedListNode(int value) {
                // Constructor
                (*this).value = value;
                (*this).next = nullptr;
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
        
        void insert(int value) {
            // Simple function to insert a value at TAIL of a linked-list
            this -> size = this -> size + 1;

            LinkedListNode * new_node = new LinkedListNode(value);
            if ( !this -> HEAD ) {
                this -> HEAD = new_node;
                return;
            }
            LinkedListNode * currentLinkedListNode = this -> HEAD;
            while ( currentLinkedListNode -> next ) {
                currentLinkedListNode = currentLinkedListNode -> next;
            }
            currentLinkedListNode -> next = new_node;
        }

        void enqueue(int value) {
            this -> insert ( value );
        }

        int dequeue () {
            if( !this->HEAD ) {
                // This should never be called
                std::cout << "Deque called on empty queue" << std::endl;
                throw "InvalidIntersection";
            }
            LinkedListNode * poppedLinkedListNode = this -> HEAD;
            int ans = poppedLinkedListNode -> value;
            this -> HEAD = this -> HEAD -> next;
            // Deleting the node from the list
            delete poppedLinkedListNode;
            return ans;
        }

        bool isEmpty() {
            // Simple isEmpty function to tell if a list is empty or not
            return this -> HEAD == nullptr;
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