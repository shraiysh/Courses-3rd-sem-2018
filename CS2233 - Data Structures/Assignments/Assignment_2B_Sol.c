#include <stdio.h>
#include <stdlib.h>

struct Digit {														// Stores one digit
	int value;
	struct Digit * next;
	struct Digit * prev;
};

struct Digit * new_digit(int value) {								// Contructor-like method to make a new digit struct
	struct Digit * my_digit = (struct Digit *)malloc(sizeof(struct Digit));
	my_digit->value = value;
	my_digit->prev = my_digit->next = NULL;
	return my_digit;
}

struct Number {														// Linked list for the number at a node
	struct Digit * HEAD;
	struct Digit * TAIL;
	int length;
};
struct Number * new_Number() {										// Constructor like method to make a new number(list)
	struct Number * my_Number = (struct Number *)malloc(sizeof(struct Number));
	my_Number->HEAD = my_Number->TAIL = NULL;
	my_Number->length = 0;
	return my_Number;
}

struct Bstree_Node {												// A binary search tree node
	struct Bstree_Node * parent, * left, * right;
	struct Number * my_Number;
};
struct Bstree_Node * new_Bstree_Node(struct Number * my_Number) {	// Constructor for a Binary Search Tree node
	struct Bstree_Node * my_Bstree_Node = (struct Bstree_Node *)malloc(sizeof(struct Bstree_Node));
	my_Bstree_Node->parent = my_Bstree_Node->right = my_Bstree_Node->left = NULL;
	my_Bstree_Node->my_Number = my_Number;
}

void free_Number(struct Number * my_Number) {
	// To free memory of a list(number)
	if(my_Number -> HEAD == NULL) return;
	struct Digit * current_digit = my_Number -> HEAD, *next_digit;
	while(current_digit != NULL) {
		next_digit = current_digit->next;
		free(current_digit);
		current_digit = next_digit;
	}
	my_Number -> HEAD = NULL;
	my_Number -> length = 0;
}

void insert_digit_in_Number(struct Number * my_Number, int value, int ignore_zero) {
	// Insert in a list(number) at the start(HEAD)
	if(my_Number -> HEAD == NULL)  {
		if(value == 0 && ignore_zero) return;
		my_Number -> TAIL = my_Number -> HEAD = new_digit(value);
	}
	else {
		struct Digit * my_new_digit = new_digit(value);
		my_new_digit -> next = my_Number -> HEAD;
		my_Number -> HEAD -> prev = my_new_digit;
		my_Number -> HEAD = my_new_digit;
	}
	my_Number -> length = my_Number -> length + 1;
}

void display_Number(struct Number * my_Number, char end) {
	// Used to print the number in the list as a natural number with `end` as the end character.
	struct Digit * current_digit = my_Number -> TAIL;
	while(current_digit!=NULL) {
		printf("%d", current_digit -> value);
		current_digit = current_digit -> prev;
	}
	printf("%c", end);
}

int compare(struct Number * num1, struct Number * num2) {
	// Compare 2 numbers. 
	// -> Return 1  if list1 > list2
	// -> Return -1 if list1 < list2
	// -> Return 0  if list1 = list2
	if(num1 -> length > num2 -> length) return 1;
	if(num1 -> length < num2 -> length) return -1;
	// Now, the lengths are same.
	struct Digit * num1_digit = num1->TAIL, * num2_digit = num2->TAIL;
	// Started with TAIL as the number is stored with MSB at TAIL
	while(num1_digit != NULL && num2_digit != NULL) {
		if(num1_digit -> value != num2_digit -> value)  {
			break;
		}
		num1_digit = num1_digit ->prev;
		num2_digit = num2_digit ->prev;
	}
	if(!num1_digit) {			// Both will be null simultaneously and so, reached the end without difference
		return 0;
	}
	return (num1_digit -> value > num2_digit -> value) ? 1 : -1;
}

struct Number * number_clone(struct Number * my_Number) {
	// returns a clone of the list
	struct Number * clone = new_Number();
	struct Digit * current_digit = my_Number -> TAIL;
	while(current_digit != NULL) {
		insert_digit_in_Number(clone, current_digit->value, 1);
		current_digit = current_digit -> prev;
	}
	return clone;
}

struct Bstree_Node * insert_bst(struct Bstree_Node * ROOT, struct Number * my_Number) {
	// Inserts a number in the BST
	struct Number * clone = number_clone(my_Number);
	struct Bstree_Node * my_new_node = new_Bstree_Node(clone);
	struct Bstree_Node * current_Node = ROOT;
	int cmp;
	while(current_Node != NULL) {
		cmp = compare(current_Node -> my_Number, my_Number);
		if(cmp == 1 && current_Node -> left != NULL) {
			current_Node = current_Node -> left;
		}
		else if(cmp == -1 && current_Node -> right != NULL) {
			current_Node = current_Node -> right;
		}
		else if(cmp == 0){
			// Number already exists.
			return ROOT;
		}
		else break;
	}
	if(ROOT == NULL) {
		return my_new_node;
	}
	my_new_node -> parent = current_Node;
	if(cmp == 1) {
		current_Node -> left = my_new_node;
	}
	else if(cmp == -1) {
		current_Node -> right = my_new_node;
	}
	return ROOT;		// Updated in case the tree was empty.
}

void free_bstree(struct Bstree_Node * ROOT) {
	// Frees the BST
	if(ROOT == NULL) return;
	free_bstree(ROOT -> left);
	free_bstree(ROOT -> right);
	if(ROOT->my_Number) free_Number(ROOT -> my_Number);
	if(ROOT->my_Number) free(ROOT -> my_Number);
	free(ROOT);
	ROOT = NULL;
}
void find_path(struct Bstree_Node * ROOT, struct Number * my_Number) {
	// Finds path to a number as a list(number) without ignoring start zeroes.
	if(ROOT == NULL) return;
	struct Number * path = new_Number();
	struct Bstree_Node * current_Node = ROOT;
	int cmp, found = 0;
	while(current_Node != NULL) {
		cmp = compare(current_Node -> my_Number, my_Number);
		if(cmp == 1 && current_Node -> left != NULL) {
			current_Node = current_Node -> left;
			insert_digit_in_Number(path, 0, 0);
		}
		else if(cmp == -1 && current_Node -> right != NULL) {
			current_Node = current_Node -> right;
			insert_digit_in_Number(path, 1, 0);
		}
		else if(cmp == 0){
			found = 1;
			display_Number(path, '\n');
			break;
		}
		else break;
	}
	if(!found) printf("-1\n");
	free_Number(path);
	free(path);
}

void pre_order_traverse(struct Bstree_Node * ROOT) {
	// Pre-order traversal of BSTree
	if(ROOT == NULL) return;
	display_Number(ROOT->my_Number, ' ');
	pre_order_traverse(ROOT -> left);
	pre_order_traverse(ROOT -> right);
}

int main() {
	int digit, Number_extracted = 0, state = ' ';
	struct Bstree_Node * ROOT = NULL;
	struct Number * my_Number = new_Number();
	while((digit = fgetc(stdin)) != EOF) {
		if(digit == 'S') {
			state = 'S';
		}
		else if(digit == 'P') {
			state = 'P';
		}
		else if(digit == 'N') {
			state = 'N';
			free_bstree(ROOT);
			ROOT = NULL;
		}
		else if(digit == ' ' && Number_extracted) {
			// Happens only when state is 'N' because, for this to happen, at least one space after one number is needed.
			if(state == 'N') {
				// Insert the number in BST
				ROOT = insert_bst(ROOT, my_Number);
			}
			free_Number(my_Number);
		}
		else if(digit >= '0' && digit <= '9') {
			insert_digit_in_Number(my_Number, digit - '0', 1);
			Number_extracted = 1;
		}
		else if(digit == '\n') {
			if(state == 'N') {
				ROOT = insert_bst(ROOT, my_Number);
			}
			else if(state == 'S') {
				find_path(ROOT, my_Number);
			}
			else if(state = 'P') {
				pre_order_traverse(ROOT);
				printf("\n");
			}
			free_Number(my_Number);
			Number_extracted = 0;
		}
	}
	free_bstree(ROOT);
	// free(ROOT);
	free_Number(my_Number);
	free(my_Number);
	return (0);
}