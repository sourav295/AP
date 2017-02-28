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
using namespace std;

const int limit_n = 1001;
int L[limit_n + 1][limit_n + 1];

int lcs(char X[limit_n], char Y[limit_n], int m, int n)
{
	int i, j;

	for (i = 0; i <= m; i++)
	{
		for (j = 0; j <= n; j++)
		{
			if (i == 0 || j == 0)
				L[i][j] = 0;

			else if (X[i - 1] == Y[j - 1])
				L[i][j] = L[i - 1][j - 1] + 1;

			else
				L[i][j] = max(L[i - 1][j], L[i][j - 1]);
		}
	}

	return L[m][n];
}





int main()
{
	string line;
	char X[limit_n], Y[limit_n];
	int m, n;

	int t;
	cin >> t;

	getline(cin, line);

	for (int i = 0; i < t; i++) {
		getline(cin, line);
		m = line.length();
		for (int j = 0; j < m; j++)
			X[j] = line.at(j);

		getline(cin, line);
		n = line.length();
		for (int j = 0; j < n; j++)
			Y[j] = line.at(j);

		int l = lcs(X, Y, m, n);
		cout << m + n - l << "\n";
	}

	return 0;
}

