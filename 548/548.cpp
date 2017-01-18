// 548.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;


//Length taken to represent a given integer as a binary
int len_to_represent(int value) {
	//CITATION: http://stackoverflow.com/questions/680002/find-out-number-of-bits-needed-to-represent-a-positive-integer-in-binary
	int count = 0;
	while (value > 0) {
		count++;
		value = value >> 1;
	}
	return count;
}

//Decides if card has to be removed or placed...
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
	
	if (!bitValue || ( count - 1 ) < position)
		return 1; // prev: 0, need to show the card, second condition accounts for the binary representation smaller in size than the position, which means it needs to be added...
	else
		return 0; // prev: 1, need to add the card
}

int max_intermediate_sum(int a, int b) {
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
		//cout << "\n=============\n" << curr << "=>" << next << "\n";
		int binary_diff = i ^ (i + 1);
		int bits = binary_diff;


		int reprLen = len_to_represent(binary_diff); //representation length
		bool *posToFlip = new bool[reprLen];

		// searches for the flip positions
		int count = 0;
		while (bits) {
			posToFlip[count] = (bits & 1);
			//cout << (bits & 1);
			bits >>= 1;
			count++;
		}


		for (int j = (reprLen - 1); j >= 0; j--) {
			bool toFlip = posToFlip[j];

			if (toFlip) {
				int card = 1 << j;//calculates 2 to the power j via bit manipulation
				//cout << "\ncard" << card;

				if (add_remove(curr, j)) {
					//SHOW THE CARD
					//cout << "add";
					currShown += card;
					if (currShown > maxShown)
						maxShown = currShown;
				}
				else {
					//HIDE THE CARD
					//cout << "remove";
					currShown -= card;
				}
			}
		}


	}
	return maxShown;

}


int main()
{
	//cout << "\nFINAL RESULT: " << max_intermediate_sum(6, 8);
	


	printf("%d\n", max_intermediate_sum(6, 8));


    return 0;
}

