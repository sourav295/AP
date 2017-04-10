#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include <string>
#include <stack>
#include <limits>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;


const int c_limit = 47;
vector<pair<int, int>> researved(c_limit);




int main()
{
	int c = 10;
	int input, emptySeat_streak;
	for (int i = 0; i < c; i++) {
		cin >> input;
		researved[i] = { input, 0 };
	}
	for (int i = 0; i < c; i++) {
		cin >> input;
		researved[i] = { researved[i].first, input };
	}
	sort(researved.begin(), researved.begin() + c);

	int previous_row = 0;
	for (int i = 0; i < c; i++) {
				
		if (researved[i].first > previous_row) {
			//new row
			emptySeat_streak =  
		}
		else {

		}
	}

    return 0;
}

