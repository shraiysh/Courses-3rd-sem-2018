#include <stdio.h>
#include <stdlib.h>

// deleteNode() replaces node with successor if node has 2 children


struct BstreeNode {
    struct BstreeNode * left, * right, * parent;
    long long int number;
};

struct BstreeNode * newBstreeNode( long long int number ) {
    struct BstreeNode * myNewBSTNode = ( struct BstreeNode * ) malloc ( sizeof( struct BstreeNode ) );
    myNewBSTNode -> left = myNewBSTNode -> right = myNewBSTNode -> parent = NULL;
    myNewBSTNode -> number = number;
}

void insert( struct BstreeNode ** ROOT, long long int number ) {
    struct BstreeNode * parent = *ROOT;
    while( parent ) {
        if( number > parent -> number && parent -> right ) parent = parent -> right;
        else if( number < parent -> number && parent -> left ) parent = parent -> left;
        else if( number == parent -> number ) return;
        else break;
    }
    struct BstreeNode * newNode = newBstreeNode( number );
    newNode -> parent = parent;
    if( parent == NULL ) *ROOT = newNode;
    else if( parent -> number < number ) parent -> right = newNode;
    else if( parent -> number > number ) parent -> left = newNode;
}

struct BstreeNode * findElement( struct BstreeNode * ROOT, long long int number, int showPath ) {
    struct BstreeNode * currentNode = ROOT;
    while( currentNode ) {
        
        if( number > currentNode -> number ) {
            currentNode = currentNode -> right;
            if( showPath ) printf("1");
        }
        
        else if( number < currentNode -> number ) {
            currentNode = currentNode -> left;
            if( showPath ) printf("0");
        }
        
        else {
            if( showPath ) printf("\n");
            return currentNode;
        }
    }
    return NULL;
}

struct BstreeNode * findSuccessorForNode( struct BstreeNode * currentNode ) {    
    if( currentNode ) {
        struct BstreeNode * succ = NULL;
        // The enquired element exists in the BST. 
        // Case 1. It has a right child.
        if( currentNode -> right ) {
            // Keep going left on the right child.
            succ = currentNode -> right;
            while( succ -> left ) succ = succ -> left;
            return succ;
        }
        else {
            // Find node whose left subtree contains currentNode
            succ = currentNode;
            while( succ -> parent && succ -> parent -> left != succ ) succ = succ -> parent;
            return succ -> parent;
        }
    }
}

struct BstreeNode * findSuccessor( struct BstreeNode * ROOT, long long int number ) {

    if ( ROOT == NULL ) return NULL;
    
    struct BstreeNode * parent = ROOT;
    // Finding node in BST such that 
    // -> either that node has this number 
    // -> or that node is possible parent to the number
    while ( parent!=NULL ) {
        if( number > parent -> number && parent -> right ) parent = parent -> right;
        else if( number < parent -> number && parent -> left ) parent = parent -> left;
        else break;
    }
    if ( number >= parent -> number ) return findSuccessorForNode(parent);
    if ( number < parent -> number ) return parent;
}

void splice( struct BstreeNode * splicingNode ) {
    // Must have only one child and a parent.
    struct BstreeNode * child = splicingNode -> left ? splicingNode -> left : splicingNode -> right;
    child -> parent = splicingNode -> parent;
    if( splicingNode == splicingNode -> parent -> left ) child -> parent -> left = child;
    else if( splicingNode == splicingNode -> parent -> right ) child -> parent -> right = child;
    free(splicingNode);
}

void deleteNode( struct BstreeNode ** ROOT, long long int number) {

    // replaces node with successor if current node has 2 children

    struct BstreeNode * foundAt = findElement(*ROOT, number, 0);
    
    // 1. Not found in the tree
    if(!foundAt) return;

    // 2. Found and has no left or right children
    if( !( foundAt -> left ) && !( foundAt -> right ) ) {
        // 2a. Has no parent => it is root.
        if( !( foundAt -> parent ) ) *ROOT = NULL;              // New ROOT = NULL
        // 2b. It has a parent.
        else if ( foundAt == foundAt -> parent -> left ) foundAt -> parent -> left = NULL;
        else if ( foundAt == foundAt -> parent -> right ) foundAt -> parent -> right = NULL;
        free(foundAt);
        // Return the root.
    }
    // 3. Found and it has one child.
    else if ( ( foundAt -> left && !( foundAt -> right ) ) || ( foundAt -> right && !( foundAt -> left ) ) ) {
        // 3a. It has a parent. Then splice
        if ( foundAt -> parent ) splice( foundAt );
        // 3b. No parent => found at ROOT => new ROOT = child
        else *ROOT = foundAt -> left ? foundAt -> left : foundAt -> right;
    }

    // 4. Found and it has two children
    else {
        // Removing successor and then putting the value of successor in place of current node.
        struct BstreeNode * successor = findSuccessor( *ROOT, number );
        int tmp = successor ->number;
        deleteNode( ROOT, successor -> number);
        foundAt -> number = tmp;
    }
}

void traversal ( struct BstreeNode * ROOT ) {
    if( !ROOT ) return;
    printf( "%lld ", ROOT -> number );
    traversal ( ROOT -> left );
    traversal ( ROOT -> right );
}

void freeBstree(struct BstreeNode * ROOT) {
    if( !ROOT ) return;
    freeBstree( ROOT -> left);
    freeBstree( ROOT -> right);
    free( ROOT );
}

int main() {
    int digit;
    long long int number = 0;
    struct BstreeNode * ROOT = NULL;
    int state = ' ';
    while( ( digit = fgetc(stdin) ) != EOF ) {
        if( digit == 'N') {
            state = 'N';
            freeBstree(ROOT);
            ROOT = NULL;
        }
        else if( digit == 'P') {
            state = 'P';
            traversal(ROOT);
            printf("\n");
        }
        else if ( digit == 'S' || digit == '>' || digit == '+' || digit == '-')
            state = digit;
        else if ( digit == '\n' ) {
            if(number != 0) {
                if ( state == 'N' ) insert( &ROOT, number );
                else if ( state == 'S' &&  findElement( ROOT, number, 0 ) ) findElement( ROOT, number, 1 );
                else if ( state == 'S' && !findElement( ROOT, number, 0 ) ) printf( "-1\n" );
                else if ( state == '>' && findSuccessor( ROOT, number ) ) 
                    printf( "%lld\n", findSuccessor( ROOT, number ) -> number );
                else if ( state == '>' && !findSuccessor( ROOT, number ) ) printf( "-1\n" );
                else if ( state == '+' ) insert( &ROOT, number );
                else if ( state == '-' ) deleteNode( &ROOT, number );
            }
            number = 0;
            state = ' ';
        }
        else if ( digit == ' ' && number != 0 && state == 'N') {
            insert( &ROOT, number );
            number = 0;
        }
        else if(digit >= '0' && digit <= '9' ) number = number * 10 + digit - '0' ;
    }
    freeBstree(ROOT);
}