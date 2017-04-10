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
//const int n_limit = 1000000000;
vector<pair<int, int>> researved(c_limit);
vector<int> rowBeingJudged(c_limit + 2);
int possibilities;

int calc_possibilities(int start, int end) {

	if (end - start >= 3)
		return end - start - 2;//minus 1 to find the gaps, another minus one to find the combinations
	else
		return 0;
}


int main()
{
	int n_test;
	int n, m, c;
	cin >> n_test;
	for (int test = 0; test < n_test; test++) {

		cin >> n >> m >> c;
		possibilities = 0;

		int input, n_uniqueRows;
		for (int i = 0; i < c; i++) {
			cin >> input;
			researved[i] = { input, 0 };
		}
		for (int i = 0; i < c; i++) {
			cin >> input;
			researved[i] = { researved[i].first, input };
		}

		sort(researved.begin(), researved.begin() + c);

		int i = 0;
		int j = 0;
		int current_row = 0;
		n_uniqueRows = 0;

		possibilities = 0;
		while (i < c) {
			//new row
			n_uniqueRows++;
			current_row = researved[i].first;

			j = 0;
			rowBeingJudged[j++] = 0;
			while (true) {
				rowBeingJudged[j++] = researved[i++].second;
				if (researved[i].first != current_row) {
					rowBeingJudged[j++] = m + 1;
					break;
				}
			}
			for (int k = 0; k < j - 1; k++) {
				possibilities += calc_possibilities(rowBeingJudged[k], rowBeingJudged[k + 1]);
			}
		}
		possibilities += (m - 1)*(n - n_uniqueRows);

		cout << "Case #"<<test<<": "<<possibilities<<"\n";



	}


	
    return 0;
}

