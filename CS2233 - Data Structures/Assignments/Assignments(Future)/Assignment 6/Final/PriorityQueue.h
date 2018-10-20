#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef LIMITS
#define LIMITS
#include <limits>
#endif

namespace DataStructure {
    class PriorityQueue {
    public:
        class Node {
        public:
            int priority_dist;    // priority based on this
            int vertexIndex;
            Node(int priority_dist, int vertexIndex) {
                this -> priority_dist = priority_dist;
                this -> vertexIndex = vertexIndex;
            }
            void setPriority(int priority_dist) {
                this -> priority_dist = priority_dist;
            }
        };
        
        Node ** myHeapNodes;
        int size, maxSize;

        PriorityQueue(int maxSize) {
            myHeapNodes = new Node*[maxSize+1];
            size = 0;
            this->maxSize = maxSize;
        }

        ~PriorityQueue() {
            for(int i=1;i<=size; i++) delete myHeapNodes[i];
            delete[] myHeapNodes;
        }

        void insert(int new_priority_dist, int vertexIndex) {
            int i, prevPriority;
            for(i=1;i<=size;i++) {
                if(myHeapNodes[i]->vertexIndex == vertexIndex)
                    break;
            }
            if(i!=size+1) {
                // Found already! Change priority!
                prevPriority = myHeapNodes[i]->priority_dist;
                myHeapNodes[i]->priority_dist = new_priority_dist;
                if(new_priority_dist >= prevPriority) heapify(i);
                else revHeapify(i); 
            }
            else if(size < maxSize) {
                // Not found. But the size is less than max possible size.
                myHeapNodes[++size] = new Node(new_priority_dist, vertexIndex);
                revHeapify(size);
            }
            else {
                std::cout << "You are inserting over the max size" << std::endl;
            }
        }

        void initInf(int limit) {
            for(int i=1;i<=limit && limit <= maxSize;i++) {
                insert(std::numeric_limits<int>::max(), i);
            }
        }

        int getRightChildIndex(int index){
            // 1 based indexing
            return index * 2;
        }

        int getLeftChildIndex(int index) {
            return index * 2 + 1;
        }

        int getParentIndex(int index) {
            return index / 2;
        }

        Node extract_min() {
            if(size != 0 ) {
                Node returningNode(myHeapNodes[1]->priority_dist, myHeapNodes[1]->vertexIndex);
                delete myHeapNodes[1];
                myHeapNodes[1] = myHeapNodes[size--];
                heapify(1);
                return returningNode;
            }
        }

        int isEmpty() {
            return size == 0;
        }

        void revHeapify(int index) {
            int p = getParentIndex(index);
            if(!myHeapNodes[index] || p < 1) return;
            Node * parent = myHeapNodes[p];
            if( myHeapNodes[index]->priority_dist < parent->priority_dist) {
                myHeapNodes[p] = myHeapNodes[index];
                myHeapNodes[index] = parent;
                revHeapify(p);
            }
        }

        void heapify(int index) {
            int l = getLeftChildIndex(index), r = getRightChildIndex(index);
            int next=-1;
            if(l<=size && myHeapNodes[l]->priority_dist < myHeapNodes[index]->priority_dist 
                && (myHeapNodes[l]->priority_dist < myHeapNodes[r]->priority_dist || r > size))
                next = l;
            else if(r <= size && myHeapNodes[r]->priority_dist < myHeapNodes[index]->priority_dist
                && (myHeapNodes[r]->priority_dist < myHeapNodes[l]->priority_dist || l > size))
                next = r;

            if(next != -1) {
                Node * temp = myHeapNodes[next];
                myHeapNodes[next] = myHeapNodes[index];
                myHeapNodes[index] = temp;
                heapify(next);
            }
        }

        void traverse() {
            for(int i=1;i<=size;i++) std::cout << myHeapNodes[i]->vertexIndex << " -> " << myHeapNodes[i]->priority_dist << std::endl;
        }
    };
}