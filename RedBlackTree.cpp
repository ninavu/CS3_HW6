#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "RedBlackTree.h"

using namespace std;

RedBlackTree::RedBlackTree(){
	root = nullptr;
	numItems = 0;
}

RedBlackTree::RedBlackTree(const RedBlackTree& rbt){
	
	while (root != nullptr){
		root->data = rbt.root->data;
		root->color = rbt.root->color;
		//root->parent = nullptr;
		
		if (rbt.root->left != nullptr){
			root->left = rbt.root->left;
		}
		
		if (rbt.root->right != nullptr){
			root->right = rbt.root->right;
		}
	}
	
	// copy the color, data, left, child, parent
	numItems = rbt.numItems;	
}

void RedBlackTree::RotateLeft(RBTNode* node){
	RBTNode* tmp = node->right;	
	node->right = tmp->left;			// open a new slot on the left and remove pointer from node to tmp
	
	if (node->parent == nullptr){		// if node is the root, tmp node becomes the new root
		root = tmp;
		tmp->parent = nullptr;
		
	} else {
		tmp->parent = node->parent;
		
		if (node == node->parent->left){		
			tmp->parent->left = tmp;
			
		} else if (node == node->parent->right){		// switch the middle value with the parent
			tmp->parent->right = tmp;
		}
	}
	
	tmp->left = node;			
	node->parent = tmp;
}

void RedBlackTree::RotateRight(RBTNode* node){
	RBTNode* tmp = node->left;		// a tmp node points to the middle value
	node->left = tmp->right;		// open a new slot on the right and remove pointer from node to tmp

	if (node->parent == nullptr){		// if node is the root, tmp node becomes the new root
		root = tmp;
		tmp->parent = nullptr;
		
	} else {
		tmp->parent = node->parent;
		
		if (node == node->parent->left){		
			tmp->parent->left = tmp;
			
		} else if (node == node->parent->right){		// switch the middle value with the parent
			tmp->parent->right = tmp;
		}
	}
	
	tmp->right = node;			
	node->parent = tmp;
}

/* A private Insert helper function that recursively calls itself 
 * to add new nodes into the tree that match the properties of 
 * a binary search tree */
RBTNode* RedBlackTree::InsertNode(RBTNode* r, RBTNode* node){

	if (r == nullptr){
		r = node;

	} else {
	
		if (node->data < r->data){
			r->left = InsertNode(r->left, node);
			r->left->parent = r;
			
		} else if (node->data > r->data){
			r->right = InsertNode(r->right, node);
			r->right->parent = r;
		}
	}
	
	return r;
} 

void RedBlackTree::Insert(int n){

	RBTNode* node = new RBTNode;
	node->data = n;
	
	if (Contains(n)){						// BST doesn't allow duplicate numbers
		throw invalid_argument("Node already exists in the tree!");	
	} 
	
	root = InsertNode(root, node);			// call a recursive function on root to keep traversing the tree and adding new nodes
	
	// exit if the parent of the new node is black/null, otherwise move on to the balancing steps
	while (node != root && node->parent->color == COLOR_RED){		// make sure node is not the root to avoid segmentation fault
		RBTNode* parent = node->parent;
		RBTNode* grandparent = parent->parent;
		RBTNode* uncle = new RBTNode;
		
		if (parent == grandparent->left){				// set uncle depends on the parent's position
			uncle = grandparent->right;

			if (uncle == nullptr || uncle->color == COLOR_BLACK) {		// rotate and recolor when uncle is black
				if (node == parent->right){
					RotateLeft(parent);					// rotate the parent with the left right case
					node = parent;						// change pointers after rotating before going into another rotation
					parent = node->parent;
				}
				
				RotateRight(grandparent);				// rotate the grandparent with the left left/left right case
				grandparent->color = COLOR_RED;			
				parent->color = COLOR_BLACK;
				//cout << "grandparent node: " << RBTNodeToString(grandparent) << endl;
				//cout << "parent node: " << RBTNodeToString(parent) << endl;
				
			} else if (uncle->color == COLOR_RED){
				parent->color = COLOR_BLACK;			// only recolor when uncle is red
				uncle->color = COLOR_BLACK;
				grandparent->color = COLOR_RED;
				node = grandparent;						// make sure the property is maintained up to the root
			}
			
		} else if (parent == grandparent->right) {			// mirror case
			uncle = grandparent->left;
			
			if (uncle == nullptr || uncle->color == COLOR_BLACK) {
				if (node == parent->left){
					RotateRight(parent);				// rotate the parent with the right left case
					node = parent;
					parent = node->parent;
				}
				
				RotateLeft(grandparent);				// rotate the grandparent with the right right/right left case
				grandparent->color = COLOR_RED;
				parent->color = COLOR_BLACK;
				
			} else if (uncle->color == COLOR_RED){
				parent->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				grandparent->color = COLOR_RED;
				node = grandparent;
			}
		}
	}
	
	root->color = COLOR_BLACK;				// make sure root node is always black
	numItems++;
}

bool RedBlackTree::Contains(int n){
	RBTNode* tmp = root;
	
	while (tmp != nullptr){
		if (tmp->data == n){
			return true;
			
		} else if (tmp->data > n){
			tmp = tmp->left;
			
		} else {
			tmp = tmp->right;
		}
	}
	return false;
}

int RedBlackTree::GetMin(){
	RBTNode* tmp = root;
	
	if (tmp == nullptr){
		throw invalid_argument("Tree is empty! There's no minimum value!");	
	}
	
	while (tmp->left != nullptr){
		tmp = tmp->left;
	}
	
	return tmp->data;
}

int RedBlackTree::GetMax(){
	RBTNode* tmp = root;
	
	if (tmp == nullptr){
		throw invalid_argument("Tree is empty! There's no maximum value!");	
	} 
	
	while (tmp->right != nullptr){
		tmp = tmp->right;
	}
	
	return tmp->data;
}

int RedBlackTree::Size(){
	return numItems;
}

string RedBlackTree::RBTNodeToString(RBTNode* node) const{
	string s = " ";
	
	if (node->color == COLOR_RED){
		s += "R";
	} else if (node->color == COLOR_BLACK){
		s += "B"; 
	}
		
	s += to_string(node->data);
	s += " ";
	return s;
} 

string RedBlackTree::ToInfixString(RBTNode* node) const{
	string s = "";

	if (node != nullptr){
		
		if (node->left != nullptr){
			s += ToInfixString(node->left);
		} 
		
		s += RBTNodeToString(node);
		
		if (node->right != nullptr){
			s += ToInfixString(node->right);
		}
	}
	
	return s;
}

string RedBlackTree::ToPrefixString(RBTNode* node) const{
	string s = "";
	
	if (node != nullptr){
		
		s += RBTNodeToString(node);
		
		if (node->left != nullptr){
			s += ToPrefixString(node->left);
		} 
		
		if (node->right != nullptr){
			s += ToPrefixString(node->right);
		}
	}

	return s;
}

string RedBlackTree::ToPostfixString(RBTNode* node) const{
	string s = "";
	
	if (node != nullptr){
		
		if (node->left != nullptr){
			s += ToPostfixString(node->left);
		} 
		
		if (node->right != nullptr){
			s += ToPostfixString(node->right);
		}
		
		s += RBTNodeToString(node);
	}

	return s;
}

void RedBlackTree::DeleteNode(RBTNode* node){
		
	if (node != nullptr){
		
		if (node->left != nullptr){
			DeleteNode(node->left);
		} 
		
		if (node->right != nullptr){
			DeleteNode(node->right);
		}
		
		delete node;
	}
}

RedBlackTree::~RedBlackTree(){
	DeleteNode(root);
}
