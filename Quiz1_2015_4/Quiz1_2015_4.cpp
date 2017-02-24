#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <set>
#include <stack>
#include <limits>
#include<math.h>
#include <sstream>
using namespace std;

const int limit_n = 10000;

int importance[limit_n];
int boss[limit_n];

bool checkBoss(int i, int j) {
	return boss[j] != i && boss[i] != j;
}

void search(int n) {

	int imp[limit_n + 1];
	int parent[limit_n + 1];
	
	for (int i = 1; i <= n; i++)
		imp[i] = numeric_limits<int>::min();

	imp[0] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i - 1; j++) {
			int sub_importance = imp[j];
			if (checkBoss(i,j) && imp[j] != numeric_limits<int>::min() && imp[j] + importance[i] > imp[i]){
				//check if parent is related to boss
				int p = j;
				bool con = false;
				while (p != 0) {
					if (!checkBoss(i, parent[p]))
						con = true;
					p = parent[p];
				}

				if (con)
					continue;

				imp[i] = imp[j] + importance[i];
				parent[i] = j;
			}
		}
	}

	int max = numeric_limits<int>::min();
	for (int i = 0; i <= n; i++)
		if (max < imp[i])
			max = imp[i];

	cout << max << "\n";
}


int main()
{
	

	importance[0] = 0;
	boss[0] = 0;

	string line;
	while (getline(cin, line)) {
		stringstream ss(line);
		int n;
		ss >> n;
		
		for (int i = 1; i <= n; i++) {
			boss[i] = 0;
		}
		
		for (int i = 1; i <= n; i++) {
			int imp;
			cin >> imp;
			importance[i] = imp;
		}

		for (int i = 1; i <= n - 1; i++) {
			int u, v;
			cin >> u >> v;
			boss[v] = u;
		}
		search(n);
		getline(cin, line);
	}

    return 0;
}

