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

/* Insert function takes roughly 1-2 seconds to process */
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
		
		if (parent == grandparent->left){				// set uncle depends on the parent's position
			RBTNode* uncle = grandparent->right;

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
			RBTNode* uncle = grandparent->left;
			
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


/* A private helper function that finds the nodes in the tree 
 * in the right position */
RBTNode* RedBlackTree::FindNode(RBTNode* r, int n){
	
	if (Contains(n) == false){						// cannot remove node that doesn't exist
		throw invalid_argument("Node doesn't exist in the tree!");	
	} 
	
	RBTNode* tmp = r;
	
	while (tmp->data != n){
		if (tmp->data > n){
			tmp = tmp->left;
			
		} else {
			tmp = tmp->right;
		}
	}
	return tmp;
}


RBTNode* RedBlackTree::MinNode(RBTNode* snode){
	
	if (snode == nullptr){
		throw invalid_argument("Tree is empty! There's no minimum value!");	
	}
	
	while (snode->left != nullptr){
		snode = snode->left;
	}
	
	return snode;
}


void RedBlackTree::SwitchParent(RBTNode* dnode, RBTNode* rnode){
	
	if (dnode == root){		// if dnode is the root (has no parent), then rnode becomes the new root
		root = rnode;
		
	} else if (dnode == dnode->parent->left){			// whether dnode is the right or left child
		dnode->parent->left = rnode;
		
	} else if (dnode == dnode->parent->right){
		dnode->parent->right = rnode;
	}
	
	if (rnode != nullptr){
		rnode->parent = dnode->parent;		// assign dnode's parent to rnode's parent
	}
}


RBTNode* RedBlackTree::ConvertNull(RBTNode* node){
	
	RBTNode* tmp = new RBTNode;
	node = tmp;
	node->null = true;
	node->color = COLOR_BLACK;
	return node;
}

/* //Delete all the null nodes - segmentation fault
void RedBlackTree::DeleteNull(RBTNode* r){
	
	RBTNode* tmp = r;

	if (tmp != nullptr){
		
		if (tmp->left != nullptr){
			DeleteNull(tmp->left);		
		} 
		
		if (tmp->right != nullptr){
			DeleteNull(tmp->right);
		}
		
		if (tmp->null == true){
			
			tmp = tmp->parent;
			if (tmp->left->null == true){
				tmp->left = nullptr;
			} else if (tmp->right->null == true){
				tmp->right = nullptr;
			}
		}
	}	
}
*/

void RedBlackTree::FixDoubleBlack(RBTNode* node){
	
	RBTNode* parent = node->parent;
	//cout << "node: " << RBTNodeToString(node) << endl;
	//cout << "parent: " << RBTNodeToString(parent) << endl;
	
	while (node != root && node->color == COLOR_DOUBLE_BLACK){
		
		if (node == parent->left){
			RBTNode* sibling = parent->right;
			//cout << "sibling right: " << RBTNodeToString(sibling) << endl;
			
			if (sibling->color == COLOR_RED){
				parent->color = COLOR_RED;
				sibling->color = COLOR_BLACK;
				RotateLeft(parent);
				
			} else if (sibling->color == COLOR_BLACK){
				
				if (sibling->left == nullptr){
					sibling->left = ConvertNull(sibling->left);
				}
				
				if (sibling->right == nullptr){
					sibling->right = ConvertNull(sibling->right);
				}
				
				if (sibling->left->color == COLOR_BLACK && sibling->right->color == COLOR_BLACK){
					sibling->color = COLOR_RED;
					//cout << "sibling black children" << endl;
					
					
					if (parent->color == COLOR_RED){
						parent->color = COLOR_BLACK;
					} else {
						parent->color = COLOR_DOUBLE_BLACK;
					}
					node = parent;					// move the double black up to the parent
					
				} else {
					
					if (sibling->right->color == COLOR_BLACK){	
						sibling->left->color = COLOR_BLACK;
						sibling->color = COLOR_RED;
						RotateRight(sibling);			
						sibling = parent->right;
					}
					//cout << "sibling red children" << endl;
					sibling->color = parent->color;
					sibling->right->color = COLOR_BLACK;			// since node is the left ch
					parent->color = COLOR_BLACK;
					RotateLeft(parent);
					break;
				}
			}
			
		} else if (node == node->parent->right){
			RBTNode* sibling = node->parent->left;
			//cout << "sibling left: " << RBTNodeToString(sibling) << endl;
			
			if (sibling->color == COLOR_RED){
				parent->color = COLOR_RED;
				sibling->color = COLOR_BLACK;
				RotateRight(parent);
				
			} else if (sibling->color == COLOR_BLACK){
				
				if (sibling->left == nullptr){
					sibling->left = ConvertNull(sibling->left);
				}
				
				if (sibling->right == nullptr){
					sibling->right = ConvertNull(sibling->right);
				}
				
				if (sibling->left->color == COLOR_BLACK && sibling->right->color == COLOR_BLACK){
					sibling->color = COLOR_RED;
					//cout << "sibling black children" << endl;
					
					if (parent->color == COLOR_RED){
						parent->color = COLOR_BLACK;
					} else {
						parent->color = COLOR_DOUBLE_BLACK;
					}
					node = parent;					// move the double black up to the parent
					
				} else {
			
					if (sibling->left->color == COLOR_BLACK){
						sibling->right->color = COLOR_BLACK;
						sibling->color = COLOR_RED;
						RotateLeft(sibling);
						sibling = parent->left;		// since node is the right child
					}
					sibling->color = parent->color;
					parent->color = COLOR_BLACK;
					sibling->left->color = COLOR_BLACK;
					RotateRight(parent);
					break;
				}
			}	
		}
	}
	
	node->color = COLOR_BLACK;		// eject double-blackness out of root node
}

/* Remove function takes roughly 1-2 seconds to process */
void RedBlackTree::Remove(int n){
			
	RBTNode* del_node = FindNode(root, n);				// node to be deleted
	int del_color = del_node->color;
	RBTNode* rep_node;			// replacement node	
	
	//cout << "del node: " << RBTNodeToString(del_node) << endl;
	 
	if (del_node->left == nullptr){					// deleted node has no left child or no child 
		
		rep_node = del_node->right;

		if (del_color == COLOR_BLACK && rep_node == nullptr){
			rep_node = ConvertNull(rep_node);
			rep_node->parent = del_node->parent;
		}
		
		SwitchParent(del_node, rep_node);			// call the function to set del_node's parent to rep_node's parent
		
	} else if (del_node->right == nullptr){			// deleted node has no right child
		rep_node = del_node->left;
		SwitchParent(del_node, rep_node);		
			
	} else {			// deleted node has 2 children
		
		RBTNode* successor = MinNode(del_node->right);		// delete the inorder successor node instead
		rep_node = successor->right;
		del_color = successor->color;
		//cout << "actual del node: " << RBTNodeToString(successor) << endl;
		
		if (successor->color == COLOR_BLACK && rep_node == nullptr){
			rep_node = ConvertNull(rep_node);
			successor->right = rep_node;
		}			
		
		if (successor->parent == del_node && rep_node != nullptr){
			rep_node->parent = successor;
			//cout << "rep node parent" << RBTNodeToString(rep_node) << endl;
			
		} else if (successor->parent != del_node){
			
			//cout << "rep node successor" << endl;
			SwitchParent(successor, rep_node);			// move rep_node into the successor place
			successor->right = del_node->right;		
			successor->right->parent = successor;
		}
		
		SwitchParent(del_node, successor);			// replace del_node with successor
		successor->left = del_node->left;			// the successor is always to the right -> always connect everything on the left
		del_node->left->parent = successor;
		successor->color = del_node->color;			// takes the color of the node being deleted
		//cout << "successor after: " << RBTNodeToString(successor) << endl;
	}

	if (del_color == COLOR_BLACK && rep_node->color == COLOR_BLACK){
		rep_node->color = COLOR_DOUBLE_BLACK;	
		//cout << "fix double black " << endl;
		FixDoubleBlack(rep_node);
		
	} else if (rep_node == nullptr) {
		return;
		
	} else {	// del_node is red & rep_node is red or null				
		rep_node->color = COLOR_BLACK;	
		//cout << "fix color " << endl;
	}
	
	//DeleteNull(root);
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
	return MinNode(root)->data;
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
	
	if (node->null == true){
		return "";
	}
	
	string s = " ";
	
	if (node->color == COLOR_RED){
		s += "R";
	} else if (node->color == COLOR_BLACK){
		s += "B"; 
	} else {
		s+= "DB";
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
 * to delete all the nodes */
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

// node struct: make an id number, a global variable each 
// assign id number, print it, print the id number deleting

RedBlackTree::~RedBlackTree(){
	DeleteNode(root);
}
