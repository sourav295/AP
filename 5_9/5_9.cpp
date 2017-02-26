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

int max(int a, int b);

const int limit_len = 20;

struct OperationStack {
	//1 - add
	//-1 - remove
	//2 - change
	//0 - match
	
	stack<pair<int, char>> op_char;

	void insert(int op, char ch) {
		
		//convert to change
		if (!op_char.empty() && op_char.top().first == 1 && op == -1) {
			char replacement = op_char.top().second;
			op_char.pop();
			op_char.push({ 2,  replacement });
			
		}//convert to change
		else if (!op_char.empty() && op_char.top().first == -1 && op == 1) {
			op_char.pop();
			op_char.push({ 2, ch });
		}
		else {
			op_char.push({ op, ch });
		}
	}


	string instruction(char *X, int m) {
		int index[limit_len];
		
		int offset = 0;//deviation due to add and remove

		for (int i = 0; i < m; i++) {
			int index = i + 1;


		}


	}

};


/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
void lcs(char *X, char *Y, int m, int n)
{
	int L[limit_len + 1][limit_len + 1];
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
	
	i = m;
	j = n;

	OperationStack op;

	while (!(i == 0 && j == 0))
	{
		if (i == 0) {
			op.insert(1, Y[j - 1]);
			j--;
			continue;
		}

		if (j == 0) {
			op.insert(-1, X[i - 1]);
			i--;
			continue;
		}

		if (X[i - 1] == Y[j - 1])
		{
			op.insert(0, X[i - 1]);
			i--; j--;
		}
		else if (L[i - 1][j] > L[i][j - 1]){
			op.insert(-1, X[i - 1]);
			i--;
		}
		else{
			op.insert(1, Y[j - 1]);
			j--;
		}
		
	}
	
	int x = 5;

}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
	return (a > b) ? a : b;
}

/* Driver program to test above function */
int main()
{
	char X[] = "abcde";
	char Y[] = "bcgfe";

	int m = strlen(X);
	int n = strlen(Y);

	lcs(X, Y, m, n);
	//printf("Length of LCS is %d\n", lcs(X, Y, m, n));

	return 0;
}
