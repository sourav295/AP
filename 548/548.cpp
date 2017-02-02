// 548.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


struct cardOperation {
	bool showCard;//false -> hide card
	int  position;//position in the bits
};


unsigned long long max_intermediate_sum(unsigned long long a, unsigned long long b) {
	
	if (a == b)
		return a;

	//init
	unsigned long long maxShown = 0;
	unsigned long long currShown;

	for (unsigned long long i = a; i < b; i++) {
		unsigned long long curr = i;
		unsigned long long next = i + 1;
		//cout << "\n=============\n" << curr << "=>" << next << "\n";
		unsigned long long bits = i ^ (i + 1);
		
		currShown = i;
		
		vector<cardOperation> operation_list;
		// searches for the flip positions
		int binary_pos = 0;
		while (bits) {
			if (bits & 1) {
				//requried to operate on this card
				cardOperation task;
				task.position = binary_pos;
				task.showCard = !(curr & 1);

				operation_list.push_back(task);
			}
			
			bits >>= 1;
			curr >>= 1;
			binary_pos++;
		}

		//Utilize as Stack
		while (!operation_list.empty())
		{
			cardOperation op = operation_list.back();
			operation_list.pop_back();

			//execute operation
			//cout << "\n" << op.showCard << " position:" << op.position;
			if (op.showCard)
				currShown += (1 << op.position);
			else
				currShown -= (1 << op.position);

			if (currShown > maxShown)
				maxShown = currShown;

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
	
	queue<unsigned long long> results;

	while (scanf("%llu %llu", &a, &b) != EOF) {
		results.push(max_intermediate_sum(a, b));
		//printf("%llu\n", max_intermediate_sum(a, b));
	}
	
	for (results;!results.empty(); results.pop()){
		printf("%llu\n", results.front());
	}


    return 0;
}

