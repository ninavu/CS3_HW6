#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <climits>
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
		
		if (root->left != nullptr){
			root = root->left;
		}
		
		if (root->right != nullptr){
			root = root->right;
		}
	}
	
	//RBTNode root_copy = *root;		// copy the color, data, left, child, parent
	numItems = rbt.numItems;	
}

void RedBlackTree::RotateLeft(RBTNode* node){
	RBTNode* tmp = node->right;	
	node->right = tmp->left;			// open a new slot on the left and remove pointer from node to tmp
	
	if (node->parent == nullptr){		// if node is the root, tmp node becomes the new root
		root = tmp;
		tmp->parent = nullptr;
		
	} else if (node == node->parent->left){		
		node->parent->left = tmp;
		
	} else if (node == node->parent->right){		// switch the middle value with the parent
		node->parent->right = tmp;
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
		
	} else if (node == node->parent->right){		// switch the middle value with the parent
		node->parent->right = tmp;
		
	} else if (node == node->parent->left){
		node->parent->left = tmp;
	}
	
	tmp->right = node;			
	node->parent = tmp;
}

/* An Insert helper function that recursively calls itself 
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
		
		if (parent == grandparent->left){
			uncle = grandparent->right;

			if (uncle == nullptr || uncle->color == COLOR_BLACK) {
				if (node == parent->right){
					RotateLeft(parent);
					node = parent;						// change pointers after rotating before going into another rotation
					parent = node->parent;
				}
				
				RotateRight(grandparent);				// rotate and recolor when uncle is black
				grandparent->color = COLOR_RED;			
				parent->color = COLOR_BLACK;
				//cout << "grandparent : " << RBTNodeToString(grandparent) << endl;
				//cout << "parent: " << RBTNodeToString(parent) << endl;
				//cout << "node : " << RBTNodeToString(node) << endl;
				
			} else if (uncle->color == COLOR_RED){
				parent->color = COLOR_BLACK;			// only recolor when uncle is red
				uncle->color = COLOR_BLACK;
				grandparent->color = COLOR_RED;
			}
			
		} else if (parent == grandparent->right) {
			uncle = grandparent->left;
			
			if (uncle == nullptr || uncle->color == COLOR_BLACK) {
				if (node == parent->left){
					RotateRight(parent);
					node = parent;
					parent = node->parent;
				}
				
				RotateLeft(grandparent);
				grandparent->color = COLOR_RED;
				parent->color = COLOR_BLACK;
				
			} else if (uncle->color == COLOR_RED){
				parent->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				grandparent->color = COLOR_RED;
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
