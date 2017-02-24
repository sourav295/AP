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
using namespace std;

const int limit_cents = 10000;
const int limit_denom = 100;

pair<int, int> minPayOUT(int denom[limit_denom], int n, int price) {

	int loss[limit_cents + 1];//loss would be negative
	int table[limit_cents + 1];

	loss[0] = 0;
	table[0] = 0;

	for (int i = 1; i <= price; i++){
		loss[i] = numeric_limits<int>::min();
		table[i]= numeric_limits<int>::max();
	}

	for (int i = 1; i <= price; i++) {
		for (int j = 0; j < n; j++) {
			if (i - denom[j] <= 0) {
				if(i - denom[j] > loss[i]){
					loss[i] = i - denom[j];
					table[i] = 1;
				}
			}
			else {
				int sub_loss = loss[i - denom[j]];
				if (sub_loss != numeric_limits<int>::min() && sub_loss > loss[i]) {
					loss[i]  = sub_loss;
					table[i] = table[i - denom[j]] + 1;
				}
				else if (sub_loss != numeric_limits<int>::min() && sub_loss == loss[i]) {
					if (table[i] > table[i - denom[j]] + 1)
						table[i] = table[i - denom[j]] + 1;
				}
			}
		}
	}

	return{ price - loss[price], table[price] };

}


int main()
{
	int t = 1;
	int n = 3;
	int price = 1600;

	int denom[limit_denom];

	cin >> t;
	for (int j = 0; j < t; j++) {

		cin >> price;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int d;
			cin >> d;
			denom[i] = d;
		}

		pair<int, int> res = minPayOUT(denom, n, price);
		cout << res.first << " " << res.second << "\n";
	}

	return 0;
}



/*
pair<int, int> minPayOUT(int price, vector<int> denominations) {

	if (price <= 0)
		return {price, 1 };

	vector<pair<int, int>> x;
	for (int i = 0; i < denominations.size(); i++) {
		x.push_back(minPayOUT(price - denominations[i], denominations));
	}

	int min_loss = numeric_limits<int>::min();
	int count	 = numeric_limits<int>::max();
	for (int i = 0; i < denominations.size(); i++) {
		if (x[i].first > min_loss) {
			min_loss = x[i].first;
			count = x[i].second;
		}
		else if(min_loss == x[i].first && count > x[i].second){
			count = x[i].second;
		}
	}
	return{ min_loss, count + 1 };
}

int main()
{
	int t = 1;
	int n = 3;
	int price = 1600;

	cin >> t;
	cin >> price;
	cin >> n;
	for (int j = 0; j < t; j++){
		vector<int> denom;
		for (int i = 0; i < n; i++) {
			int d;
			cin >> d;
			denom.push_back(d);
		}

		pair<int, int> res = minPayOUT(price, denom);
		cout << price - res.first << " " << res.second << "\n";
	}

    return 0;
}

*/