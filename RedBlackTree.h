#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#define COLOR_RED 0
#define COLOR_BLACK 1

#include <iostream>	
#include <vector>

using namespace std;

struct RBTNode {
	int data;
	unsigned short int color = COLOR_RED;		// new node added will be red
	RBTNode* parent = nullptr;
	RBTNode* right = nullptr;
	RBTNode* left = nullptr;		// null nodes are black
};

class RedBlackTree {
	public:
		RedBlackTree();  //simple constructor
		RedBlackTree(const RedBlackTree& rbt);			//copy constructor
		~RedBlackTree();
		
		void Insert(int num);
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
		void RotateLeft(RBTNode* n);
		void RotateRight(RBTNode* n);
		void DeleteNode(RBTNode* n);
		
		unsigned long long int numItems;
		RBTNode *root;	
		vector<RBTNode*> AllNodes;
};


#endif
