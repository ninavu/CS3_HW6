#include <cstdlib>
#include <ctime>
#include "RedBlackTree.h"

using namespace std;


int main(){

	// create a simulated 3.7 million ID number system.
	const int N = 3700000;

	clock_t start = clock();
	RedBlackTree rbt = RedBlackTree();
	for(int i = 0; i < N; i++){
		rbt.Insert(i);
	}
	clock_t stop = clock();

	double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
	cout << "Collected " << rbt.Size() << " ID numbers in " << (duration) << " seconds." << endl;

	// Your code goes here to simulate leaving / joining
	int leaving = 0;
	int joining = 0;
	
	clock_t begin, end;
	
	while (joining < 5){
		
		begin = clock();
		int num_ID = rand();
		
		try {
		rbt.Insert(num_ID);
		end = clock();
		
		} catch(const invalid_argument& e){
			
		}
	
		joining++;
		double time_joined = (static_cast<double>(end - begin));
		cout << "Insert the new ID number " << num_ID << " takes " << (time_joined) << " seconds." << endl;
	}
	
	while (leaving < 5){
		
		begin = clock();
		int num_ID = rand();
		
		try {
		rbt.Remove(num_ID);
		end = clock();
		
		} catch(const invalid_argument& e){
			
		}
	
		leaving++;
		double time_left = (static_cast<double>(end - begin));
		cout << "Remove an ID number " << num_ID << " takes " << (time_left) << " seconds." << endl;
	}


	return 0;
}
