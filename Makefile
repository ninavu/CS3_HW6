all:
	g++ --std=c++14 -Wall RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt
	g++ --std=c++14 -Wall RedBlackTree.cpp SpeedTest.cpp -o st
