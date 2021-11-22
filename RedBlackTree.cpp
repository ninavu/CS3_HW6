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
	// DO IT LAST
}

void RedBlackTree::RotateLeft(RBTNode* node){
	RBTNode* tmp = node->right;		// set a tmp node to the right of the grandparent
	node->right = tmp->left;		// tmp's left child now becomes the grandparent's right child
	
	/*
	if (node->right != nullptr){
		node->right->parent = node;
	}
	*/

	if (node->parent == nullptr){		// if node is the root, tmp node becomes the new root
		root = tmp;
		tmp->parent = nullptr;
		
	} else if (node == node->parent->left){		// switch the 
		node->parent->left = tmp;
	}
	
	tmp->left = node;			
	node->parent = tmp;
}

void RedBlackTree::RotateRight(RBTNode* node){
	RBTNode* tmp = node->left;		// a tmp node points to the middle value
	node->left = tmp->right;
	
	/*
	if (node->left != nullptr){
		node->left->parent = node;
	} */
	
	if (node->parent == nullptr){		// if node is the root, tmp node becomes the new root
		root = tmp;
		tmp->parent = nullptr;
	}
	
	tmp->right = node;			
	node->parent = tmp;
}

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
	
	if (Contains(n)){	// BST doesn't allow duplicate numbers
		throw invalid_argument("Node already exists in the tree!");	
	} 
	
	root = InsertNode(root, node);			// call a recursive function to keep adding nodes to the tree
	
	// exit if the parent of the new node is black/null
	
	// make sure node is not the root to avoid segmentation fault
	
	while (node != root && node->parent->color == COLOR_RED){		// CHECK WHETHER CURRENT NODE IS RED TOO?
		RBTNode* parent = node->parent;
		RBTNode* grandparent = parent->parent;
		RBTNode* uncle = new RBTNode;
		
		if (parent == grandparent->left){
			uncle = grandparent->right;

			if (uncle == nullptr) {
				if (node == parent->right){
					RotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				
				RotateRight(grandparent);
				grandparent->color = COLOR_RED;
				parent->color = COLOR_BLACK;
				cout << "grandparent color: " << RBTNodeToString(grandparent) << endl;
				cout << "parent color: " << RBTNodeToString(parent) << endl;
				//cout << "node color: " << RBTNodeToString(node) << endl;
				
			}
			
		} else if (parent == grandparent->right) {
			uncle = grandparent->left;
			
			if (uncle == nullptr) {
				
				RotateLeft(grandparent);
				grandparent->color = COLOR_RED;
				parent->color = COLOR_BLACK;
			}
		}
	}
	
	root->color = COLOR_BLACK;				// make sure root node is black
	AllNodes.push_back(node);
	numItems++;
	// if parent is red, check color of uncle (uncle = black (null) => rotate + recolor , uncle = red -> recolor
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
	
	int min = tmp->data;
	
	while (tmp->left != nullptr){
		tmp = tmp->left;
		min = tmp->data;
	}
	
	return min;
}

int RedBlackTree::GetMax(){
	RBTNode* tmp = root;
	
	if (tmp == nullptr){
		throw invalid_argument("Tree is empty! There's no maximum value!");	
	}
	
	int max = tmp->data; 
	
	while (tmp->right != nullptr){
		tmp = tmp->right;
		max = tmp->data;
	}
	
	return max;
}

int RedBlackTree::Size(){
	return numItems;
}

string RedBlackTree::RBTNodeToString(RBTNode* node) const{
	string s = " ";
	
	if (node->color == 0){
		s += "R";
	} else if (node->color == 1){
		s += "B"; 
	}
		
	s += to_string(node->data);
	s += " ";
	return s;
} 

string RedBlackTree::ToInfixString(RBTNode* node) const{
	string s = "";
	
	if (node == nullptr){
		return s;
	}
	
	if (node->left != nullptr){
		s += ToPrefixString(node->left);
	} 
	s += RBTNodeToString(node);
		
		
	if (node->right != nullptr){
		s += ToPrefixString(node->right);
	}
	
	return s;
}

string RedBlackTree::ToPrefixString(RBTNode* node) const{
	string s;
	
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
	string s;

	if (numItems == 0){
		return s;
	}
	
	if (node->left != nullptr){
		s += ToPrefixString(node->left);
	} 
	
	if (node->right != nullptr){
		s += ToPrefixString(node->right);
	}
	
	s += RBTNodeToString(node);

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
