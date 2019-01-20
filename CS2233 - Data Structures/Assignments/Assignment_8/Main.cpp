#define IOSTREAM
#include <iostream>
#include "RedBlackTree.h"
#define STRING
#include <sstream>
#include <string>
using namespace std;

bool isNumber(string s) { 
    for (int i = 0; i < s.length(); i++) 
        if (isdigit(s[i]) == false) 
            return false; 
  
    return true; 
} 

bool getInput(istringstream * stream, int * a) {
    // A utility function to get input from console.
    string temp;
    if((*stream) >> temp && isNumber(temp) && ((*a)=stoi(temp)))
        return true;

    (*a)=-1;    // For invalid inputs, give -1
    return false;
}

int main() {
    DataStructure::RedBlackTree *myRedBlackTree = new DataStructure::RedBlackTree();
    while(!cin.eof()) {
        std::cout << "---------------------" << std::endl;
        string input_line;
        getline(cin, input_line);
        std::cout << "Input: " << input_line << std::endl;
        if(!input_line.length()) break;
        char state = input_line[0];
        istringstream myStream(input_line.substr(1));
        int a,b,c;

        switch(state) {
            
            case 'N':
            delete myRedBlackTree;
            myRedBlackTree = new DataStructure::RedBlackTree();
            while(getInput(&myStream, &a)) myRedBlackTree->insert(a);
            myRedBlackTree->detailedTraverse("");
            break;

            case '+':
            if(getInput(&myStream, &a)) myRedBlackTree->insert(a);
            break;

            case '>':
            if(getInput(&myStream, &a)) std::cout << myRedBlackTree->findSuccessor(a)->value;
            break;

            case '-':
            if(getInput(&myStream, &a)) myRedBlackTree->RBdelete(a);
            break;

            case 'S':
            if(getInput(&myStream, &a)) myRedBlackTree->findElement(a, true);
            break;

            case 'C':
            if(getInput(&myStream, &a)) myRedBlackTree->showChildren(a);
            break;

            case 'P':
            if(getInput(&myStream, &a)) myRedBlackTree->preOrderTraversal();
            break;

            default:
            std::cout << "Case not handled!" << std::endl;
        }
        state = ' ';
    }
    delete myRedBlackTree;
}