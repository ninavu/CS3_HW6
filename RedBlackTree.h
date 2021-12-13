#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_DOUBLE_BLACK 2

#include <iostream>	

using namespace std;

struct RBTNode {
	int data;
	unsigned short int color = COLOR_RED;		// new node added will always be red
	RBTNode* parent = nullptr;
	RBTNode* right = nullptr;
	RBTNode* left = nullptr;		// null nodes are black
	bool null = false;
};

class RedBlackTree {
	public:
		RedBlackTree();  	//simple constructor
		RedBlackTree(const RedBlackTree& rbt);			//copy constructor
		~RedBlackTree();	//destructor
		
		void Insert(int num);
		void Remove(int num);
		bool Contains(int num);
		
		int GetMin();
		int GetMax();
		int Size();
		
		string ToInfixString() const { return ToInfixString(root); };
		string ToPrefixString() const { return ToPrefixString(root); };
		string ToPostfixString() const { return ToPostfixString(root); };
		string RBTNodeToString(RBTNode* n) const;

		
	private: 
		string ToInfixString(RBTNode* n) const;
		string ToPrefixString(RBTNode* n) const;
		string ToPostfixString(RBTNode* n) const;
		
		RBTNode* InsertNode(RBTNode* r, RBTNode* n);
		RBTNode* FindNode(RBTNode* r, int n);
		RBTNode* MinNode(RBTNode* snode);
		
		RBTNode* ConvertNull(RBTNode* null);
		void DeleteNull(RBTNode* null);
		
		void SwitchParent(RBTNode* dnode, RBTNode* rnode);
		void FixDoubleBlack(RBTNode* node);
		
		void RotateLeft(RBTNode* n);
		void RotateRight(RBTNode* n);
		void DeleteNode(RBTNode* n);
		
		unsigned long long int numItems;
		RBTNode *root;	
};


#endif
