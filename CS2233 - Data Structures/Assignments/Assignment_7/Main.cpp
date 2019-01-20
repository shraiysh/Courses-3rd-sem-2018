#include <iostream>
#include "Forest.h"
#include <string>
#include <sstream>

using namespace std;

void getInput(istringstream * stream, int * a) {
    string temp;
    if((*stream) >> temp && ((*a)=stoi(temp)))
        return;

    (*a)=-1;
    std::cout << "Invalid input!" << std::endl;
}

int main() {
    Forest *myForest = new Forest(0);
    while(!cin.eof()) {
        string input_line;
        getline(cin, input_line);
        if(!input_line.length()) break;
        char state = input_line[0];
        istringstream myStream(input_line.substr(1));
        int a,b,c;

        switch(state) {
            case 'N':
                getInput(&myStream, &a);
                
                if(a < 0) break;

                delete myForest;
                
                myForest = new Forest(a);
                break;

            case '?':
                getInput(&myStream, &a);
                getInput(&myStream, &b);
                c = 0;

                if(a < 1 || b < 1 || a > myForest->size || b > myForest->size) 
                    c = -1;
                else if(myForest->getRepresentative(a) == myForest->getRepresentative(b))
                    c = 1;
                else 
                    c = 0;

                std::cout << c << std::endl;
                break;

            case 'U':
                getInput(&myStream, &a);
                getInput(&myStream, &b);
                if(a >= 1 && a <= myForest->size && b >= 0 && b <= myForest->size)
                    myForest->unionSet(a,b);
                break;

            case 'S':
                getInput(&myStream, &a);
                if(a >= 1 && a <= myForest->size)
                    b = myForest->getRepresentative(a);
                else b = -1;
                std::cout << b << std::endl;
                break;

            case 'R':
                getInput(&myStream, &a);
                if(a >= 1 && a <= myForest->size)
                    b = myForest->sets[a]->rank;
                else
                    b = -1;
                std::cout << b << std::endl;
        }
        state = ' ';
    }
    delete myForest;
}