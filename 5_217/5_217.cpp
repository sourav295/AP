#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <stack>
#include <limits>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

int coins[] = { 1, 5, 10, 25, 50 };

const int limit_change = 7489;
const int n_coins = 5;



int main()
{
	int T[n_coins][limit_change + 1];
	vector<int> input_change;

	string line;
	while (getline(cin, line)) {
		stringstream ss(line);

		int change;
		ss >> change;

		input_change.push_back(change);
	}

	int max_change = 0;
	int n = input_change.size();

	for (int i = 0; i < n; i++) {
		if (max_change < input_change[i])
			max_change = input_change[i];
	}

	for (int i = 0; i < n_coins; i++) {
		for (int j = 0; j <= max_change; j++) {
			if (j == 0)
				T[i][j] = 1;
			else if (i == 0)
				T[i][j] = 1;
			else if (j >= coins[i])
				T[i][j] = T[i - 1][j] + T[i][j - coins[i]];
			else
				T[i][j] = T[i - 1][j];
		}
	}

	for (int i = 0; i < n; i++) {
		cout << T[n_coins - 1][input_change[i]]<<"\n";
	}

    return 0;
}

