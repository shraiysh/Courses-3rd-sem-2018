#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

namespace DataStructure {
    class RedBlackTree {

        class Node {
        public:
            int value;
            char color;
            Node *left, *right, *parent;

            Node(int value, Node *NIL) {
                this->value = value;
                color = 'R';
                left = right = parent = NIL;
            }
            Node(int value, char color, Node *NIL) {
                this->value = value;
                this->color = color;
                left = right = parent = NIL;
            }
        };

        

        void fixInsert(Node *Z) {
            if(ROOT->color == 'R') {
                ROOT->color = 'B'; 
                return;
            }

            // Other case if prop 4 is violated by z and it's parent alone
            if(Z->color == 'R' && Z->parent->color == 'R') {
                Node *uncle = getUncle(Z);
                if(uncle->color == 'R') {
                    // When uncle exists, parent and grandparent exist.
                    // Case 1. Uncle is red. Color parent and uncle black and grandparent:red
                    Z->parent->color = uncle->color = 'B';
                    Z->parent->parent->color = 'R';
                    fixInsert(Z->parent->parent);
                    return;
                }

                bool isLeftLeftChild = (Z->parent!=NIL) && (Z->parent->parent!=NIL) &&
                                    (Z == Z->parent->left) && (Z->parent == Z->parent->parent->left);
                bool isRightRightChild = (Z->parent!=NIL) && (Z->parent->parent!=NIL) &&
                                    (Z == Z->parent->right) && (Z->parent == Z->parent->parent->right);
                bool isRightOfLeftChild = (Z->parent!=NIL && Z->parent->parent!=NIL) &&
                                    (Z == Z->parent->right && Z->parent == Z->parent->parent->left);
                bool isLeftOfRightChild = (Z->parent!=NIL && Z->parent->parent!=NIL) &&
                                        (Z == Z->parent->left && Z->parent == Z->parent->parent->right);

                if(uncle->color == 'B' && isLeftLeftChild) {
                    Z->parent->color = 'B';
                    Z->parent->parent->color = 'R';
                    rightRotation(Z->parent->parent);
                }

                if(uncle->color == 'B' && isRightRightChild) {
                    Z->parent->color = 'B';
                    Z->parent->parent->color = 'R';
                    leftRotation(Z->parent->parent);
                }

                if(uncle->color == 'B' && isRightOfLeftChild) {
                    Z = Z->parent;
                    leftRotation(Z);
                    fixInsert(Z);
                }

                if(uncle->color == 'B' && isLeftOfRightChild) {
                    Z = Z->parent;
                    rightRotation(Z);
                    fixInsert(Z);
                }
            }
        }

        void RBdelete(Node *Z) {
            Node *Y = Z, *X;
            char Y_original_color = Y->color;
            if(Z->left == NIL) {
                std::cout << "Left child is NIL. Hoping right is not!" << std::endl;
                X = Z->right;
                RBTransplant(Z, Z->right);
            }
            else if(Z->right == NIL) {
                std::cout << "Right child is NIL, left is not." << std::endl;
                X = Z->left;
                RBTransplant(Z, Z->left);
            }
            else {
                std::cout << "Both are not NULL" << std::endl;
                Node *Y = findSuccessor(Z);
                Y_original_color = Y->color;
                X = Y->right;
                if(Y->parent == Z) {
                    if(X->parent!=Y)std::cout << "X->parent=" << X->parent << ", Y=" << Y << std::endl;
                    X->parent = Y;
                }
                else {
                    RBTransplant(Y, Y->right);
                    Y->right = Z->right;
                    Y->right->parent = Y;
                }
                RBTransplant(Z, Y);
                Y->left = Z->left;
                Y->left->parent = Y;
                Y->color = Z->color;
            }
            std::cout << "Simple delete completed" << std::endl;
            detailedTraverse("\t");
            if(Y_original_color == 'B') {
                RBDeleteFixup(X);
            }
            std::cout << "After deletion: NIL = " << NIL->value << NIL->parent << NIL->left << NIL->right << std::endl;
        }

        void RBTransplant(Node *U, Node *V) {
            // This is similar to splice.
            if(U->parent == NIL) {
                ROOT = V;
            }
            else if (U == U->parent->left)
                U->parent->left = V;
            else U->parent->right = V;
            V->parent = U->parent;
        }

        void RBDeleteFixup(Node *X) {
            while(X != ROOT && X->color == 'B') {
                std::cout << "--------------------------\nX=" << X->value << std::endl;
                if(X == X->parent->left) {
                    std::cout << "X is left child" << std::endl;
                    Node *W = X->parent->right;
                    if(W->color == 'R') {
                        std::cout << "Case 1" << std::endl;
                        W->color = 'B';
                        X->parent->color = 'R';
                        leftRotation(X->parent);
                        W = X->parent->right;
                    }
                    if(W->left->color == 'B' && W->right->color == 'B') {
                        std::cout << "Case 2" << std::endl;
                        W->color = 'R';
                        X = X->parent;
                    }
                    else {
                        if(W->right->color == 'B') {
                            std::cout << "Case 3" << std::endl;
                            W->left->color = 'B';
                            W->color = 'R';
                            rightRotation(W);
                            W = X->parent->right;
                        }
                        std::cout << "Case 4" << std::endl;
                        W->color = X->parent->color;
                        X->parent->color = 'B';
                        W->right->color = 'B';
                        leftRotation(X->parent);
                        X = ROOT;
                    }
                }
                else {
                    std::cout << "X is right child" << std::endl;
                    Node *W = X->parent->left;
                    if(W->color == 'R') {
                        std::cout << "Case 1" << std::endl;
                        W->color = 'B';
                        X->parent->color = 'R';
                        rightRotation(X->parent);
                        W = X->parent->left;
                    }
                    if(W->right->color == 'B' && W->left->color == 'B') {
                        std::cout << "Case 2" << std::endl;
                        W->color = 'R';
                        X = X->parent;
                    }
                    else {
                        if(W->left->color == 'B') {
                            std::cout << "Case 3" << std::endl;
                            W->right->color = 'B';
                            W->color = 'R';
                            leftRotation(W);
                            W = X->parent->left;
                        }
                        std::cout << "Case 4" << std::endl;
                        W->color = X->parent->color;
                        X->parent->color = 'B';
                        W->left->color = 'B';
                        rightRotation(X->parent);
                        X = ROOT;
                    }
                }
            }
            std::cout << "Coloring last X Black" << std::endl;
            X->color = 'B';
        }

        void deleteTree(Node *ROOT) {
            if(ROOT == NIL) return;
            deleteTree(ROOT->left);
            deleteTree(ROOT->right);
            delete ROOT;
        }

    public:
        Node *ROOT;
        Node *NIL;

        RedBlackTree() {
            NIL = new Node(-1, nullptr);
            NIL->color = 'B';
            ROOT = NIL;
        }
        ~RedBlackTree() {
            deleteTree(ROOT);
            delete NIL;
        }

        void customInsert(int value, char color) {
            Node *newNode = new Node(value, color, NIL);

            // Here, the tree is not empty. Finding parent where this new node comes.
            Node *requiredParent = ROOT;
            while(requiredParent!=NIL) {

                if(requiredParent->value == value) return; // Already exists
                
                if(requiredParent->value > value && requiredParent->left!=NIL)
                    requiredParent = requiredParent->left;
                
                else if(requiredParent-> value < value && requiredParent->right!=NIL)
                    requiredParent = requiredParent->right;

                else break; // Does not exist and parent is found.
            }
            
            newNode->parent = requiredParent;

            // If tree is empty, color ROOT black.
            if(requiredParent == NIL) ROOT = newNode;

            // If not, inserting at apt position.
            else if(requiredParent->value > value) requiredParent->left = newNode;
            else requiredParent->right = newNode;
        }

        void insert(int value) {
            Node *newNode = new Node(value, NIL);

            // Here, the tree is not empty. Finding parent where this new node comes.
            Node *requiredParent = ROOT;
            while(requiredParent!=NIL) {

                if(requiredParent->value == value) return; // Already exists
                
                if(requiredParent->value > value && requiredParent->left!=NIL)
                    requiredParent = requiredParent->left;
                
                else if(requiredParent-> value < value && requiredParent->right!=NIL)
                    requiredParent = requiredParent->right;

                else break; // Does not exist and parent is found.
            }
            
            newNode->parent = requiredParent;

            // If tree is empty, color ROOT black.
            if(requiredParent == NIL) ROOT = newNode;

            // If not, inserting at apt position.
            else if(requiredParent->value > value) requiredParent->left = newNode;
            else requiredParent->right = newNode;

            fixInsert(newNode);
            std::cout << "Insert " << value << std::endl;
            detailedTraverse("\t");
        }

        void traverse() {
            std::cout << "\nTraversing" << std::endl;
            traverse(this->ROOT);
            std::cout << std::endl;
        }

        void traverse(Node *ROOT) {
            if(ROOT==NIL) return;
            traverse(ROOT->left);
            std::cout << ROOT->value << ":" << ROOT->color << " ";
            traverse(ROOT->right);
        }

        void detailedTraverse(std::string initSpace) {
            std::cout << std::endl;
            std::cout << initSpace << "Detailed Traversal => ROOT=" << ROOT->value << std::endl;
            detailedTraverse(ROOT, initSpace);
            std::cout << std::endl;
        }

        void detailedTraverse(Node *ROOT, std::string initSpace) {
            if(ROOT == NIL || (ROOT->left == NIL && ROOT->right == NIL)) return;
            detailedTraverse(ROOT->left, initSpace);
            std::cout << initSpace << "\t" << ROOT->left->value << "(" << ROOT->left->color << ")";
            std::cout << initSpace << "\t<-\t" << ROOT->value << "(" << ROOT->color << ")" << "\t->\t";
            std::cout << initSpace << ROOT->right->value << "(" << ROOT->right->color << ")";
            std::cout << initSpace << std::endl;
            detailedTraverse(ROOT->right, initSpace);
        }

        Node *findSuccessor(int x) {
            Node *found = findElement(x);
            if(found)
                return findSuccessor(found);
            else {
                insert(x);
                found = findSuccessor(x);
                RBdelete(x);
                return found;
            }
        }

        Node *findSuccessor(Node *currentNode) {
            if(currentNode != NIL) {
                Node *succ = NIL;
                // The enquired element exists in the BST. 
                // Case 1. It has a right child.
                if(currentNode->right != NIL) {
                    // Keep going left on the right child.
                    succ = currentNode->right;
                    while(succ->left != NIL) succ = succ->left;
                    return succ;
                }
                else {
                    // Find node whose left subtree contains currentNode
                    succ = currentNode;
                    while(succ->parent != NIL && succ->parent->left != succ) succ = succ->parent;
                    return succ->parent;
                }
            }
        }

        void leftRotation(int x) {
            leftRotation(findElement(x));
        }

        void rightRotation(int x) {
            rightRotation(findElement(x));
        }

        void leftRotation (Node *X) {
            if (X == NIL || (X->right) == NIL) return;
            Node *Y = X->right;
            Node *A = X->right, *B = Y->left, *C = Y->right, *P = X->parent;
            Y->left = X;
            X->parent = Y;
            X->right = B;
            if (B != NIL) B->parent = X;
            Y->parent = P;
            if (P != NIL) {
                if(P->right == X) P->right = Y;
                else P->left = Y;
            }
            else ROOT = Y;
        }

        void rightRotation(Node *X) {
            if (X == NIL || (X->left) == NIL) return;
            Node *Y = X->left;
            Node * A = X->left, * B = Y->right, * C = Y->left, * P = X->parent;
            Y->right = X;
            X->parent = Y;
            X->left = B;
            if (B != NIL) B->parent = X;
            Y->parent = P;
            if (P != NIL) {
                if(P->left == X) P->left = Y;
                else P->right = Y;
            }
            else ROOT = Y;
        }

        Node *getUncle(Node *Z) {
            if(Z->parent!=NIL && Z->parent->parent!=NIL) {
                if(Z->parent == Z->parent->parent->left) return Z->parent->parent->right;
                else return Z->parent->parent->left;
            }
            return NIL;
        }

        Node *getSibling(Node *Z) {
            if(Z == NIL || Z->parent == NIL) return NIL;
            if(Z == Z->parent->left) return Z->parent->right;
            else return Z->parent->left;
        }

        Node *findElement(int x) {
            return findElement(x, false);
        }

        Node *findElement(int x, bool showPath) {
            std::string path = "";
            Node * currentNode = ROOT;
            while(currentNode!=NIL) {
                if(x > currentNode->value) {
                    path += "1";
                    currentNode = currentNode->right;
                }
                else if(x < currentNode->value) { 
                    path += "0";
                    currentNode = currentNode->left;
                }
                else {
                    if(showPath) {
                        // std::cout << "Found." << std::endl;
                        // std::cout << "Path: " << path << ", color: " << currentNode->color << std::endl;
                        std::cout << path << " " << currentNode->color << std::endl;
                    }
                    return currentNode;
                }
            }
            if(showPath) {
                std::cout << "-1" << std::endl;
            }
            return NIL;
        }

        void showChildren(int x) {
            Node *found = findElement(x);
            if(found == NIL) return;

            if(found->left == NIL) std::cout << "L B ";
            else std::cout << found->left->value << " " << found->left->color << " ";
            
            if(found->right == NIL) std::cout << "L B";
            else std::cout << found->right->value << " " << found->right->color;

            std::cout << std::endl;
        }

        void preOrderTraversal() {
            preOrderTraversal(ROOT);
            std::cout << std::endl;
        }

        void preOrderTraversal(Node *ROOT) {
            if(ROOT == NIL) return;
            preOrderTraversal(ROOT->left);
            std::cout << ROOT->value << " ";
            preOrderTraversal(ROOT->right);
        }

        void RBdelete(int z) {
            Node *Z = findElement(z);
            if(Z!=NIL)
                RBdelete(Z);
            delete Z;
            std::cout << "Deleting " << z << std::endl;
            detailedTraverse("\t");
        }
    };
}