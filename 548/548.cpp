// 548.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;


//Length required to represent a given integer as binary
int len_to_represent(unsigned long long value) {
	int count = 0;
	while (value > 0) {
		count++;
		value = value >> 1;
	}
	return count;
}

//Decides if the card has to be removed or shown (bit converts to -> 1/0)...
//position is the location of the bit being flipped
//curr is the number
bool add_remove(unsigned long long curr, int position) {
	//returns 0 for remove and 1 for add.
	int count = 0;
	int bitValue = 0;
	while (curr && count <= position) {
		bitValue = (curr & 1);
		curr >>= 1;
		count++;
	}
	
	if (!bitValue || ( count - 1 ) < position)
		return 1; // prev: 0, need to show the card, second condition accounts for the binary representation smaller in size than the position, which means it needs to be added...
	else
		return 0; // prev: 1, need to add the card
}

unsigned long long max_intermediate_sum(unsigned long long a, unsigned long long b) {
	
	//init
	unsigned long long maxShown = a;
	unsigned long long currShown = a;

	for (unsigned long long i = a; i < b; i++) {
		unsigned long long curr = i;
		unsigned long long next = i + 1;
		//cout << "\n=============\n" << curr << "=>" << next << "\n";
		unsigned long long binary_diff = i ^ (i + 1);
		unsigned long long bits = binary_diff;


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
				unsigned long long card = 1 << j;//calculates 2 to the power j via bit manipulation
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
	//printf("%llu\n", max_intermediate_sum(6, 8));
	//printf("%llu\n", max_intermediate_sum(35, 38));
	unsigned long long a, b;
	
	while (scanf("%llu %llu", &a, &b) != EOF) {
		printf("%llu\n", max_intermediate_sum(a, b));
	}
	


    return 0;
}

