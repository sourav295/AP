// 548.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;



int len_to_represent(int value) {
	//CITATION: http://stackoverflow.com/questions/680002/find-out-number-of-bits-needed-to-represent-a-positive-integer-in-binary
	int count = 0;
	while (value > 0) {
		count++;
		value = value >> 1;
	}
	return count;
}


bool add_remove(int curr, int position) {
	//returns 0 for remove and 1 for add.
	int count = 0;
	int bits = curr;
	int bitValue = 0;
	while (bits && count <= position) {
		bitValue = (bits & 1);
		
		bits >>= 1;
		count++;
	}

	if (!bitValue)
		return 1; // prev: 0, need to show the card
	else
		return 0; // prev: 1, need to add the card
}



int main()
{
	
	
	
	int a = 7;
	int b = 8;

	int lenArray = b - a + 1;

	int *isShown = new int[lenArray];
	for (int i = 0; i < lenArray; i++)
		isShown[i] = 0;
	
	//init
	int maxShown = a;
	int currShown = a;

	for (int i = a; i < b; i++) {
		int curr = i;
		int next = i + 1;

		int binary_diff = a ^ (a + 1);
		int bits = binary_diff;
		

		int reprLen = len_to_represent(binary_diff); //representation length
		bool *posToFlip = new bool[reprLen];

		// searches for the flip positions
		int count = 0;
		while (bits) {
			posToFlip[count] = (bits & 1);
			cout << (bits & 1);
			bits >>= 1;
			count++;
		}
		cout << "\n" << "curr: " << next;
		cout << "\n";

		for (int j = (reprLen - 1); j >= 0; j--) {
			bool toFlip = posToFlip[j];
			
			if (toFlip) {
				int card = 1 << j;//calculates 2 to the power j by bit manipulation

				if (add_remove(curr, j)) {
					//SHOW THE CARD
					cout << j << " " << card << "\n";
					currShown += card;
					if (currShown > maxShown)
						maxShown = currShown;
				}
				else {
					//HIDE THE CARD
					currShown -= card;
				}
			}
		}


	}
	cout << maxShown;

    return 0;
}

