#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}


void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30); // leak here
	rbt->Insert(15);
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(40);
	rbt->Insert(55); // Right Right
	assert(rbt->ToPrefixString() == " B40  R30  R55 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(40);
	rbt->Insert(35); // Right Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B35  R30  R40 ");
	delete rbt;
	
	//cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10);	// left left
	rbt->Insert(5);		// add left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  B10  R5  B30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(25);
	rbt->Insert(40);	// balanced case
	rbt->Insert(10);	// add left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B25  R10  B40 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(10);
	rbt->Insert(20);	// left right
	rbt->Insert(40);	// add right
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B20  B10  B30  R40 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(10);
	rbt->Insert(40);	// balanced case
	rbt->Insert(20);	// add left right
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B10  R20  B40 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(20);
	rbt->Insert(30);
	rbt->Insert(40);	// right right
	rbt->Insert(50);	// add right
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B20  B40  R50 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(25);
	rbt->Insert(40);	// balanced case
	rbt->Insert(45);	// add right
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B25  B40  R45 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(20);
	rbt->Insert(30);	// right left
	rbt->Insert(40);	// add left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B20  B10  B30  R40 ");
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(10);
	rbt->Insert(40);	// balanced case
	rbt->Insert(35);	// add right left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B10  B40  R35 ");
	delete rbt;
	
	//cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);		// balanced case
	rbt->Insert(10);		// add left
	rbt->Insert(25);		// add left right -> no change since parent is black
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);		// balanced case
	rbt->Insert(10);		// add left
	rbt->Insert(5);			// add left left -> parent is red
	assert(rbt->ToPrefixString() == " B30  B10  R5  R15  B45 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(20);
	rbt->Insert(45);		// balanced case
	rbt->Insert(10);		// add left
	rbt->Insert(15);		// add left right -> parent is red
	assert(rbt->ToPrefixString() == " B30  B15  R10  R20  B45 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(20);
	rbt->Insert(40);		// balanced case
	rbt->Insert(50);		// add right
	rbt->Insert(55);		// add right right -> parent is red
	assert(rbt->ToPrefixString() == " B30  B20  B50  R40  R55 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(20);
	rbt->Insert(40);		// balanced case
	rbt->Insert(50);		// add right
	rbt->Insert(45);		// add right left -> parent is red
	assert(rbt->ToPrefixString() == " B30  B20  B45  R40  R50 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(25);
	rbt->Insert(20);	// left left
	rbt->Insert(15);	// add left
	rbt->Insert(10);
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B25  B15  R10  R20  B30 ");
	delete rbt;
	
	//cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);
	
	//cout << "result: "  << rbt.ToInfixString() << endl;
	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "more random tests: " << endl;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);	
	rbt1.Insert(9);		// balanced case
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);
	cout << "tree 2: "  << rbt2.ToPrefixString() << endl;

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	cout << "tree 1: "  << rbt1.ToPrefixString() << endl;
	cout << "tree 2: "  << rbt2.ToPrefixString() << endl;
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}


void TestContains(){
	cout << "Testing Contains..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));
	delete rbt;

	
	cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}


void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	cout << "TESTS MISSING" << endl << endl;

	cout << "PASSED!" << endl << endl;
}


int main(){

	
	TestSimpleConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();

	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
