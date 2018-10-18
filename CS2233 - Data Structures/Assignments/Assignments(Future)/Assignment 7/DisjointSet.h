#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "LinkedList.h"
#endif
#ifndef METADATA_H
#define METADATA_H
#include "Metadata.h"
#endif

namespace DataStructure {
    class DisjointSet {
    public:
        LinkedList *objects;
        Metadata * metadata;
        DisjointSet(int x) {
            metadata = new Metadata(1);
            objects = new DataStructure::LinkedList(metadata);
            objects->insert(x);
        }

        ~DisjointSet() {
            delete metadata;
            delete objects;
        }

        static void Union(DisjointSet **set1, DisjointSet **set2) {
            if(!(*set1) || !(*set2)) return;
            DisjointSet *larger, *smaller;
            if((*set1)->metadata->length <= (*set2)->metadata->length) {
                larger = *set2;
                smaller = *set1;
            }
            else {
                larger = *set1;
                smaller = *set2;
            }

            // There can be 2 approaches now, one is to change meta nodes of every node
            // in the smaller set. Other is to insert new nodes in larger list with
            // values same as the ones in smaller list. Since both have O(n) complexity,
            // I've appended the smaller nodes in the bigger one.

            // Append smaller at end of larger
            LinkedList::LinkedListNode * currentAppendingNode = smaller->objects->HEAD;
            while(currentAppendingNode) {
                larger->objects->insert(currentAppendingNode->value);
                currentAppendingNode = currentAppendingNode->next;
            }

            // Update length of larger set
            larger->metadata->length = larger->metadata->length + smaller->metadata->length;

            // delete smaller one
            if(smaller == *set1) (*set1) = nullptr;
            else (*set2) = nullptr;
            delete smaller;
        }

        bool contains(int x) {
            return objects->contains(x);
        }

        int getRepresentativeElement() {
            if(objects->HEAD) return objects->HEAD->value;
            else return -1;
        }

        void traverse() {
            if(this == nullptr) return;
            LinkedList::LinkedListNode * currentNode = objects->HEAD;
            while(currentNode) {
                std::cout << currentNode->value << " ";
                currentNode = currentNode->next;
            }
            std::cout << std::endl;

        }
    };
}