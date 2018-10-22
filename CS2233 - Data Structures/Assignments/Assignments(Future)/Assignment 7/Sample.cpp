#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H
#include "DisjointSet.h"
#endif

#include <string>
#include <sstream>

using namespace DataStructure;
using namespace std;

void getInput(istringstream * stream, int * a) {
    string temp;
    (*stream) >> temp;
    (*a) = stoi(temp);
}

int getSetIndex(DisjointSet ** sets, int size, int x) {
    for(int i=1;i<size;i++) {
        if(sets[i] && sets[i]->contains(x))
            return i;
    }
    return -1;
}

int main() {

    DisjointSet ** sets = new DisjointSet*[0];
    int size=0;
    while(!cin.eof()) {
        string input_line;
        getline(cin, input_line);
        if(input_line.length() == 0) break; 
        char state = input_line[0];
        istringstream myStream(input_line.substr(1));
        int a,b,i, setA, setB;
        int set;
        switch(state) {
            case 'N':
                for(int i=1;i<size;i++) {
                    delete sets[i];
                }
                delete[] sets;

                getInput(&myStream, &size);

                sets = new DisjointSet*[++size];    // increasing size by 1 to make indices 1 based.
                for(int i = 1; i < size; i++)
                    sets[i] = new DisjointSet(i);
                break;

            case '?':
                getInput(&myStream, &a);
                getInput(&myStream, &b);
                
                for(i=1;i<size;i++) {
                    DisjointSet * currentSet = sets[i];
                    if(currentSet && currentSet->contains(a) && currentSet->contains(b)) {
                        std::cout << "1" << std::endl;
                        break;
                    }
                    else if(currentSet && currentSet->contains(a) || currentSet->contains(b)) {
                        std::cout << "0" << std::endl;
                        break;
                    }
                }
                if(i==size) {
                    std::cout << "-1" << std::endl;
                }
                break;
            case 'S':

                getInput(&myStream, &a);
                set = getSetIndex(sets, size, a);
                if(set!=-1)
                    std::cout << sets[set]->getRepresentativeElement() << std::endl;
                else
                    std::cout << "None contains the element" << std::endl;
                break;

            case 'U':

                getInput(&myStream, &a);
                getInput(&myStream, &b);
                setA = getSetIndex(sets, size, a);
                setB = getSetIndex(sets, size, b);

                // Either they are already in the same set, or they do not exist!
                if(setA == -1 || setB == -1 || setA == setB) break;

                DisjointSet::Union(&sets[setA], &sets[setB]);
                
                std::cout << "Traversing all sets" << std::endl;
                for(int i=1;i<size;i++) {
                    if(sets[i]) {
                        std::cout << "i=" << i << ":";
                        sets[i]->traverse();
                    }
                }
                break;
            case 'R':
                getInput(&myStream, &a);
                std::cout << "Get the rank bro!" << std::endl;
        }
    }
    // free the sets.
    for(int i=1;i<size; i++) {
        if(sets[i]) delete sets[i];
    }
    delete[] sets;
}