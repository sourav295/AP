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

