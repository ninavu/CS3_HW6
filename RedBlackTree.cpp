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
	numItems = rbt.numItems;
	
	if (rbt.root == nullptr){		// if rbt is empty, root is always null
		root = nullptr;
		
	} else {
	
		root = new RBTNode;						// initiate the root since it is currently null, or else seg fault
		root->data = rbt.root->data;			// copy non-pointer elements from the root if rbt is not empty
		root->color = rbt.root->color;
		
		RBTNode* tmp = rbt.root;				// create tmp nodes to separate the original pointers
		RBTNode* tmp_copy = root;
		
		while (tmp != nullptr){
			RBTNode* cur = new RBTNode;			// create a new cur node to traverse the whole tree
			
			if (tmp->left != nullptr && tmp_copy->left == nullptr){
				
				cur->data = tmp->left->data;		// copy non-pointer elements
				cur->color = tmp->left->color;
				tmp_copy->left = cur;				// copy the whole non-pointer elements into tmp_copy
				cur->parent = tmp_copy;				// mark parent-child relationship between 2 pointers	
				
				tmp = tmp->left;					// update tmp and tmp_copy to keep traversing the left side
				tmp_copy = tmp_copy->left;
				
			} else if (tmp->right != nullptr && tmp_copy->right == nullptr){	// mirror case: traverse the tree and copy the right side
				
				cur->data = tmp->right->data;
				cur->color = tmp->right->color;
				tmp_copy->right = cur;
				cur->parent = tmp_copy;
				
				tmp = tmp->right;
				tmp_copy = tmp_copy->right;
				
			} else {		// if there's no left and right nodes left, keep going up 1 level until tmp->parent is null
				
				tmp = tmp->parent;				
				tmp_copy = tmp_copy->parent;
			}
		}
	}
}


void RedBlackTree::RotateLeft(RBTNode* node){
	RBTNode* tmp = node->right;	
	node->right = tmp->left;			// open a new slot on the left and remove pointer from node to tmp
	
	if (node->right != nullptr){		// when there's a left child of tmp, point it directly to the node instead
		node->right->parent = node;
		//cout << "node-right: " << RBTNodeToString(node->right) << endl;
	} 
	
	if (node->parent == nullptr){		// if node is the root, tmp node becomes the new root
		root = tmp;
		tmp->parent = nullptr;
		
	} else {									// create new parent-child relationship
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
	
	if (node->left != nullptr){		// when there's a right child of tmp, point it directly to the node instead
		node->left->parent = node;
		//cout << "node-left: " << RBTNodeToString(node->left) << endl;
	} 

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
	if (Contains(n)){						// BST doesn't allow duplicate numbers
		throw invalid_argument("Node already exists in the tree!");	
	} 
	
	RBTNode* node = new RBTNode;
	node->data = n;
	
	root = InsertNode(root, node);			// call a recursive function to keep traversing the tree from the root and adding new nodes
	
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
					node = parent;						// change pointers after the first rotation before going into another rotation
					parent = node->parent;
				}
				
				RotateRight(grandparent);				// rotate the grandparent with the left left/left right case
				grandparent->color = COLOR_RED;			
				parent->color = COLOR_BLACK;
				//cout << "grandparent node: " << RBTNodeToString(grandparent) << endl;
				//cout << "parent node: " << RBTNodeToString(parent) << endl;
				
			} else if (uncle->color == COLOR_RED){
				parent->color = COLOR_BLACK;			// when uncle is red, only recolor
				uncle->color = COLOR_BLACK;				// push blackness down onto parent and uncle
				grandparent->color = COLOR_RED;
				node = grandparent;						// make sure the property is maintained up to the root
			}
			
		} else if (parent == grandparent->right) {		// mirror case
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

/* Remove BST: 
 * search for the node -> 3 cases: 0 child, 1 child, 2 children
 * 0 child -> just get rid of it
 * 1 child -> replace the child with the deleted node
 * 2 child -> recursion: in order successor (right, all the way to the left) : replace the data with the root
 */
 
/* A private helper function that finds the nodes in the tree 
 * in the right position
 */
RBTNode* RedBlackTree::FindNode(RBTNode* r, int n){
	RBTNode* tmp = r;
	
	while (tmp != nullptr){
		if (tmp->data == n){
			return tmp;
			
		} else if (tmp->data > n){
			tmp = tmp->left;
			
		} else {
			tmp = tmp->right;
		}
	}
	return nullptr;
}


void RedBlackTree::SwitchParent(RBTNode* dnode, RBTNode* rnode){
	
	if (dnode == root){		// if dnode is the root (has no parent), then rnode becomes the new root
		root = rnode;
		
	} else if (dnode == dnode->parent->left){			// whether dnode is the right or left child
		dnode->parent->left = rnode;
		
	} else if (dnode == dnode->parent->right){
		dnode->parent->right = rnode;
	}
	
	rnode->parent = dnode->parent;		// assign dnode's parent to rnode's parent
}


void RedBlackTree::FixDoubleBlack(RBTNode* node){
	

}


void RedBlackTree::Remove(int n){
	
	if (Contains(n) == false){						// cannot remove node that doesn't exist
		throw invalid_argument("Node doesn't exist in the tree!");	
	} 
	
	RBTNode* del_node = FindNode(root, n);		// node to be deleted
	RBTNode* rep_node = new RBTNode;			// replacement node	
	cout << "del node: " << RBTNodeToString(del_node) << endl;
	
	/* the deleted node either has one child or no child: 
	 * one child: the replacement node becomes that child
	 * no child: the replacement node can be any child since both children are nullptr/black
	 */
	if (del_node->left == nullptr){					// deleted node has no left child
		
		rep_node = del_node->right;
		cout << "rep node: " << RBTNodeToString(rep_node) << endl;
		SwitchParent(del_node, rep_node);	
		
	} else if (del_node->right == nullptr){			// deleted node has no right child
		rep_node = del_node->left;
		cout << "rep node: " << RBTNodeToString(rep_node) << endl;
		SwitchParent(del_node, rep_node);			
	}
	
	/*
	if (rep_node == root || rep_node->color == COLOR_RED){
		rep_node->color = COLOR_BLACK;
	}
	

	if (rep_node->color == COLOR_BLACK || del_node->color == COLOR_BLACK){
		//double black situation
		rep_node->color = COLOR_DOUBLE_BLACK;
		//fix double black
	} */
	
	if (rep_node->color == COLOR_RED){			// should add rep_node == root as well?
		rep_node->color = COLOR_BLACK;	
	}
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


/* A private destructor helper function that recursively calls itself 
 * to delete all the nodes - NOT COMPLETE */
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
