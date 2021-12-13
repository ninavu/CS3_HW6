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
	assert(rbt->ToInfixString() == " R12  B13  B15  B20 ");
	delete rbt;


	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	rbt->Insert(11);
	rbt->Insert(15);
	rbt->Insert(5);
	rbt->Insert(13);
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	delete rbt;
	
	rbt = new RedBlackTree();	
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(8);			// adding 8 nodes
	rbt->Insert(18);
	rbt->Insert(5);
	rbt->Insert(15);
	rbt->Insert(17);
	rbt->Insert(25);
	rbt->Insert(40);
	rbt->Insert(80);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == " B5  R8  B15  B17  B18  R25  B40  R80 ");
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);			// 17 nodes
	rbt->Insert(10);
	rbt->Insert(8);
	rbt->Insert(19);
	rbt->Insert(21);
	rbt->Insert(7);		
	rbt->Insert(0);
	rbt->Insert(13);
	rbt->Insert(54);
	rbt->Insert(28);
	rbt->Insert(2);
	rbt->Insert(9);
	rbt->Insert(11);
	rbt->Insert(20);
	rbt->Insert(5);
	rbt->Insert(15);
	rbt->Insert(14);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	
	try{
		rbt->Insert(19);
		assert(false);
		
		rbt->Insert(13);
		assert(false);
		
	} catch(const invalid_argument& e){
		
	}
	
	assert(rbt->ToInfixString() == " R0  B2  R5  B7  B8  R9  B10  B11  R12  R13  B14  R15  B19  R20  B21  R28  B54 ");
	
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
	//cout << "tree 2: "  << rbt2.ToPrefixString() << endl;
	
	assert(rbt1.Size() == rbt2.Size());
	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	//cout << "tree 1: "  << rbt1.ToPrefixString() << endl;
	//cout << "tree 2: "  << rbt2.ToPrefixString() << endl;
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());
	
	RedBlackTree rbt3 = RedBlackTree();
	rbt3.Insert(12);
	rbt3.Insert(10);
	rbt3.Insert(0);
	rbt3.Insert(11);
	rbt3.Insert(3);
	rbt3.Insert(9);
	rbt3.Insert(2);
	rbt3.Insert(7);
	rbt3.Insert(1);
	rbt3.Insert(4);
	rbt3.Insert(6);			// where copy constructor fails (part 1)
	rbt3.Insert(8);
	rbt3.Insert(37);
	rbt3.Insert(5);
	rbt3.Insert(72);
	rbt3.Insert(55);
	rbt3.Insert(90);
	rbt3.Insert(92);
	rbt3.Insert(20);
	rbt3.Insert(13);
	rbt3.Insert(57);
	rbt3.Insert(30);
	rbt3.Insert(64);
	rbt3.Insert(69);
	rbt3.Insert(50);
	rbt3.Insert(67);
	rbt3.Insert(99);
	rbt3.Insert(89);
	rbt3.Insert(33);

	assert(rbt3.ToPrefixString() == " B12  R7  B3  B1  R0  R2  B5  R4  R6  B10  B9  R8  B11  R55  B20  B13  R37  B30  R33  B50  B69  R64  B57  B67  R90  B72  R89  B92  R99 ");

	RedBlackTree rbt4 = RedBlackTree(rbt3);

	string s3 = rbt3.ToPrefixString();
	//cout << "s3: " << s3 << endl;
	string s4 = rbt4.ToPrefixString();
	//cout << "s4: " << s4 << endl;
	assert(rbt3.Size() == rbt4.Size());
	assert(s3 == s4);

	rbt3.Insert(200);
	assert(rbt3.ToPrefixString() != rbt4.ToPrefixString());


	cout << "PASSED!" << endl << endl;
}


void TestRemoveOneChild(){
	cout << "Testing Remove Node With One Child... " << endl;
	
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(19);
	rbt->Insert(14);
	
	rbt->Remove(19);
	assert(rbt->ToPrefixString() == " B14 ");
	
	rbt->Insert(9);
	rbt->Insert(5);
	rbt->Insert(11);
	rbt->Insert(2);
	rbt->Insert(7);
	rbt->Insert(6);
	rbt->Insert(3);
	assert(rbt->ToPrefixString() == " B9  R5  B2  R3  B7  R6  B14  R11 ");
	
	rbt->Remove(7);		//right left case
	assert(rbt->ToPrefixString() == " B9  R5  B2  R3  B6  B14  R11 ");
	
	rbt->Remove(14);
	assert(rbt->ToPrefixString() == " B9  R5  B2  R3  B6  B11 ");
	
	rbt->Remove(2);		// left right case
	assert(rbt->ToPrefixString() == " B9  R5  B3  B6  B11 ");
	
	rbt->Insert(0);
	rbt->Insert(16);
	rbt->Remove(3);		// left left case
	assert(rbt->ToPrefixString() == " B9  R5  B0  B6  B11  R16 ");
	
	rbt->Remove(11);	// right right case
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B9  R5  B0  B6  B16 ");

	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestRemoveTwoChildren(){
	cout << "Testing Remove Node With Two Children..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(19);
	rbt->Insert(14);
	rbt->Insert(10);
	
	rbt->Remove(14);
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B19  R10 ");

	rbt->Insert(5);
	rbt->Insert(9);
	rbt->Insert(3);
	rbt->Insert(7);
	rbt->Insert(15);
	rbt->Insert(12);
	rbt->Insert(11);
	rbt->Insert(14);
	rbt->Insert(13);
	assert(rbt->ToPrefixString() == " B10  B5  B3  B9  R7  B15  R12  B11  B14  R13  B19 ");

	rbt->Remove(12);		// delete red, replacement red
	cout << "rbt: " << rbt->ToPrefixString() << endl;	
	assert(rbt->ToPrefixString() == " B10  B5  B3  B9  R7  B15  R13  B11  B14  B19 ");
	
	rbt->Insert(16);
	rbt->Insert(25);
	cout << "rbt: " << rbt->ToPrefixString() << endl;
	
	rbt->Remove(19);		// delete black, replacement red
	cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B10  B5  B3  B9  R7  B15  R13  B11  B14  B25  R16 ");
	
	delete rbt;
	
	
	rbt = new RedBlackTree();
	rbt->Insert(9);
	rbt->Insert(5);
	rbt->Insert(15);
	rbt->Insert(1);
	rbt->Insert(7);
	rbt->Insert(3);
	rbt->Insert(10);
	rbt->Insert(25);
	rbt->Insert(22);
	rbt->Insert(27);
	assert(rbt->ToPrefixString() == " B9  R5  B1  R3  B7  R15  B10  B25  R22  R27 ");
	
	rbt->Remove(9);		// delete black, replacement black, black sibling has red children, 1 rotation
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B10  R5  B1  R3  B7  R25  B15  R22  B27 ");
	
	rbt->Remove(5);		// delete red, replacement black, black sibling, 2 rotations left right
	cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B10  R3  B1  B7  R25  B15  R22  B27 ");
	
	delete rbt;
	
	
	rbt = new RedBlackTree();
	rbt->Insert(7);
	rbt->Insert(3);
	rbt->Insert(18);
	rbt->Insert(10);
	rbt->Insert(22);
	rbt->Insert(8);
	rbt->Insert(11);
	rbt->Insert(26);  
	cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B7  B3  R18  B10  R8  R11  B22  R26 ");
	
	rbt->Remove(18);		// delete red, replacement black 
	cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B7  B3  R22  B10  R8  R11  B26 ");
	
	rbt->Remove(22);		// delete red, replacement black, black sibling has red children
	cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B7  B3  R10  B8  B26  R11 ");

	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestRemoveLeaf(){
	cout << "Testing Remove Leaf..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(7);
	rbt->Insert(20);
	rbt->Insert(30);
	assert(rbt->ToPrefixString() == " B10  B7  B20  R30 ");
	
	rbt->Remove(30);		// just delete the red node
	assert(rbt->ToPrefixString() == " B10  B7  B20 ");
	
	rbt->Insert(3);
	rbt->Insert(8);
	rbt->Insert(4);
	rbt->Insert(15);
	rbt->Insert(35);
	rbt->Insert(25);
	rbt->Insert(40);
	cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B10  R7  B3  R4  B8  R20  B15  B35  R25  R40 ");
	
	rbt->Remove(4);			// delete another red node 
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B10  R7  B3  B8  R20  B15  B35  R25  R40 ");
	
	rbt->Remove(15);		// delete black node, black sibling with red children
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B10  R7  B3  B8  R35  B20  R25  B40 ");
	
	rbt->Remove(40);		// delete black node, black sibling with red children, rotate left right
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B10  R7  B3  B8  R25  B20  B35 ");

	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(7);
	rbt->Insert(3);
	rbt->Insert(18);
	rbt->Insert(10);
	rbt->Insert(22);
	rbt->Insert(8);
	rbt->Insert(11);
	rbt->Insert(26);
	assert(rbt->ToPrefixString() == " B7  B3  R18  B10  R8  R11  B22  R26 ");
	
	rbt->Remove(3);		// delete black node, red sibling
	cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B18  R10  B7  R8  B11  B22  R26 ");
	
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(13);
	rbt->Insert(8);
	rbt->Insert(17);
	rbt->Insert(1);
	rbt->Insert(11);
	rbt->Insert(15);
	rbt->Insert(25);
	rbt->Insert(6);
	rbt->Insert(22);
	rbt->Insert(27);
	assert(rbt->ToPrefixString() == " B13  R8  B1  R6  B11  R17  B15  B25  R22  R27 ");
	
	rbt->Remove(11);		// delete black node, red sibling, 2 rotations left right
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B13  R6  B1  B8  R17  B15  B25  R22  R27 ");

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
	assert(rbt->Contains(35) == false);
	assert(rbt->Contains(22));
	assert(rbt->Contains(28) == false);
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;
	
	RedBlackTree *rbt = new RedBlackTree();
	
	try{
		rbt->GetMax(); 
		assert(false);
		
		rbt->GetMin(); 
		assert(false);
		
	} catch(const invalid_argument& e){
		
	}

	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->GetMax() == 55);
	assert(rbt->GetMin() == 12);
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(19);
	rbt->Insert(10);
	rbt->Insert(7);
	rbt->Insert(0);
	rbt->Insert(54);
	rbt->Insert(28);

	assert(rbt->GetMax() == 54);
	assert(rbt->GetMin() == 0);
	delete rbt;

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
	
	TestRemoveOneChild();
	TestRemoveTwoChildren();
	TestRemoveLeaf();
	
	//TestRemoveRandomTests();

	TestContains();
	TestGetMinimumMaximum();
	
	TestCopyConstructor();
	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
