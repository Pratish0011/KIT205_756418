#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

// create an empty bst
BST new_bst() {
	BST temp;
	temp.root = NULL;
	return temp;
}

// recursive function to find a value and return the containing node
BSTNodePtr find_bst_node(BSTNodePtr self, int n) {
	if (self == NULL || (n == self->data_item)) { /* not present, or here */
		return self;
	}
	else if (n < self->data_item) {
		return find_bst_node(self->left, n);
	}
	else {
		return find_bst_node(self->right, n);
	}
}

// find a value in the tree and return the node
BSTNodePtr find_bst(BST* self, int n) {
	return find_bst_node(self->root, n);
}

// recursive function to insert a value
BSTNodePtr insert_bst_node(BSTNodePtr self, int n) {
	if (self == NULL) { /* found where to put it*/
		self = malloc(sizeof * self);
		if (self == NULL) {
			printf("Memory allocation failed!\n");
			exit(1);
		}
		self->data_item = n;
		self->left = self->right = NULL;
	}
	else if (n < self->data_item) {
		self->left = insert_bst_node(self->left, n);
	}
	else if (n > self->data_item) {
		self->right = insert_bst_node(self->right, n);
	}
	return self;
}

// insert a value into the tree
void insert_bst(BST* self, int n) {
	self->root = insert_bst_node(self->root, n);
}

// helper function for delete
BSTNodePtr min_node(BSTNodePtr self) {
	BSTNodePtr current = self;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

// recursive function to delete a value
BSTNodePtr delete_bst_node(BSTNodePtr self, int n) {
	if (self != NULL) {
		if (n == self->data_item) { // found item 
			if (self->left != NULL && self->right != NULL) {
				// two child case 
				BSTNodePtr successor = min_node(self->right);
				self->data_item = successor->data_item;
				self->right = delete_bst_node(self->right, self->data_item);
			}
			else { // one or zero child case 
				BSTNodePtr to_free = self;
				if (self->left) {
					self = self->left;
				}
				else {
					self = self->right;
				}
				free(to_free);
			}
		}
		else if (n < self->data_item) {
			self->left = delete_bst_node(self->left, n);
		}
		else {
			self->right = delete_bst_node(self->right, n);
		}
	}
	return self;
}

// delete a value from the tree
void delete_bst(BST* self, int n) {
	self->root = delete_bst_node(self->root, n);
}

// recursive function to print in order
void print_in_order_bst_node(BSTNodePtr self) {
	if (self == NULL) {
		printf("_");
	}
	else {
		printf("(");
		print_in_order_bst_node(self->left);
		printf(" %d ", self->data_item);
		print_in_order_bst_node(self->right);
		printf(")");
	}
}

// print the tree in order
void print_in_order_bst(BST* self) {
	print_in_order_bst_node(self->root);
}

// recursive function to detroy all node
void destroy_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		destroy_bst_node(self->left);
		self->left = NULL;
		destroy_bst_node(self->right);
		self->right = NULL;
		free(self);
	}
}

// destroy the tree
void destroy_bst(BST* self) {
	destroy_bst_node(self->root);
	self->root = NULL;
}



void bst_adhoc_test() {
	BST tree = new_bst();
	int quit = 0;
	int data;
	while (quit == 0) {
		printf("Enter some data: ");
		if (scanf("%d", &data) != 1) {
			printf("Invalid input!\n");
			break;
		}
		if (data != 0) {
			insert_bst(&tree, data);
		}
		else {
			quit = 1;
		}
	}
	print_in_order_bst(&tree);
	printf("\n");
}


// Pre order: root -> left -> right
void print_pre_order_bst_node(BSTNodePtr self) {
	if (self == NULL) {
		printf("_");
	}
	else {
		printf("(");
		printf(" %d ", self->data_item);
		print_pre_order_bst_node(self->left);
		print_pre_order_bst_node(self->right);
		printf(")");
	}
}

void print_pre_order_bst(BST* self) {
	print_pre_order_bst_node(self->root);
}

// Post order: left -> right -> root
void print_post_order_bst_node(BSTNodePtr self) {
	if (self == NULL) {
		printf("_");
	}
	else {
		printf("(");
		print_post_order_bst_node(self->left);
		print_post_order_bst_node(self->right);
		printf(" %d ", self->data_item);
		printf(")");
	}
}

void print_post_order_bst(BST* self) {
	print_post_order_bst_node(self->root);
}




// recursive helper
int height_bst_node(BSTNodePtr self) {
	if (self == NULL) {
		return 0;
	}
	int left_height = height_bst_node(self->left);
	int right_height = height_bst_node(self->right);

	if (left_height > right_height)
		return left_height + 1;
	else
		return right_height + 1;
}

// public function
int height_bst(BST* self) {
	return height_bst_node(self->root);
}


void bst_test() {
	BST tree = new_bst();

	printf("=== BST Unit Tests ===\n\n");

	// Test insert
	printf("Testing insert...\n");
	insert_bst(&tree, 5);
	insert_bst(&tree, 3);
	insert_bst(&tree, 7);
	insert_bst(&tree, 1);
	insert_bst(&tree, 4);

	printf("In order (expected: 1 3 4 5 7): ");
	print_in_order_bst(&tree);
	printf("\n");

	printf("Pre order: ");
	print_pre_order_bst(&tree);
	printf("\n");

	printf("Post order: ");
	print_post_order_bst(&tree);
	printf("\n");

	// Test height
	printf("\nTesting height (expected 3): %d\n", height_bst(&tree));

	// Test find
	printf("\nTesting find...\n");
	printf("Find 3 (expected found): %s\n", find_bst(&tree, 3) != NULL ? "Found" : "Not Found");
	printf("Find 9 (expected not found): %s\n", find_bst(&tree, 9) != NULL ? "Found" : "Not Found");

	// Test delete
	printf("\nTesting delete...\n");
	delete_bst(&tree, 3);
	printf("After deleting 3: ");
	print_in_order_bst(&tree);
	printf("\n");

	// Test destroy
	destroy_bst(&tree);
	printf("\nTree destroyed successfully\n");
	printf("Root is NULL: %s\n", tree.root == NULL ? "Yes" : "No");
}