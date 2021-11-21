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
	
	if (node->right != nullptr){
		node->right->parent = node;
	}
	
	
	
	
}

void RedBlackTree::RotateRight(RBTNode* node){
	RBTNode* tmp = node->left;		// a tmp node points to the middle value
	//node->left = tmp->right;
	
	/*
	if (node->left != nullptr){
		node->left->parent = node;
	} */
	
	if (node->parent == nullptr){		// if node is the root, tmp node becomes the new root
		root = tmp;
	}
	
	tmp->right = node;
	node->parent = tmp;
	
}

RBTNode* RedBlackTree::InsertNode(RBTNode* r, RBTNode* node){
	numItems++;
	
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
	root->color = COLOR_BLACK;				// mark root node black
	
	// exit if the parent of the new node is black/null
	
	// make sure node is not the root to avoid segmentation fault
	
	while (node != root && node->parent->color == COLOR_RED){		// CHECK WHETHER CURRENT NODE IS RED TOO?
		RBTNode* parent = node->parent;
		RBTNode* grandparent = parent->parent;
		RBTNode* uncle = new RBTNode;
		
		if (parent == grandparent->left){
			uncle = grandparent->right;
			
			if (uncle->color == COLOR_BLACK){
				
				RotateRight(grandparent);
				
			} else if (uncle->color == COLOR_RED){
				
			}
			
		} else if (parent == grandparent->right) {
			uncle = grandparent->left;
		}
	}
	
	
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
	int min = INT_MAX;
	
	while (tmp != nullptr){
		min = tmp->data;
		tmp = tmp->left;
	}
	
	return min;
}

int RedBlackTree::GetMax(){
	RBTNode* tmp = root;
	int max = 0; 
	
	while (tmp != nullptr){
		max = tmp->data;
		tmp = tmp->right;
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
	
	if (numItems == 0){
		return s;
		
	} else {
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

string RedBlackTree::ToPrefixString(RBTNode* node) const{
	string s;

	if (numItems == 0){
		return s;
		
	} else {
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
	} else {
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

RedBlackTree::~RedBlackTree(){
	
}
