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

int min(int a, int b);

const int limit_len = 20;

struct Operation {

	char operation, character;
	int position;

	Operation(char op, int pos, char ch) {
		operation = op;
		character = ch;
		position = pos;
	}

	void generate(int offset) {
		int index = offset + 1 + position;
		//string ch(1, character);

		cout << operation;
		if(operation == 'I')
			cout << setfill('0') << std::setw(2) << (1 + position);
		else
			cout << setfill('0') << std::setw(2) << index;
		cout << character;

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
			if (i == 0)
				L[i][j] = j;
			else if (j == 0)
				L[i][j] = i;

			else if (X[i - 1] == Y[j - 1])
				L[i][j] = L[i - 1][j - 1];

			else
				L[i][j] = min(	min(L[i - 1][j], L[i][j - 1]), L[i-1][j-1]) + 1;
		}
	}

	stack<Operation> command;
	int index = 0;

	i = m;
	j = n;
	while (!(i == 0 && j == 0))
	{
		if (X[i - 1] == Y[j - 1])
		{
			i--; j--;
		}
		else {

			if (i == 0) {
				command.push(Operation('I', i - 1, Y[j - 1]));
				j--;index++;
				continue;
			}

			if (j == 0) {
				command.push(Operation('D', i - 1, X[i - 1]));
				i--;index++;
				continue;
			}

			int top  = L[i - 1][j];
			int side = L[i][j - 1];
			int diag = L[i - 1][j - 1];

			if (diag <= side && diag <= top) {
				//change: position to change, the value to change to
				command.push(Operation('C', i - 1, Y[j - 1]));
				i--;j--;index++;
			}
			else if (side < top) {
				//insert: position to insert into, value to insert
				command.push(Operation('I', j - 1, Y[j - 1]));
				j--;index++;
			}
			else {
				//drop: position to drop, value to drop
				command.push(Operation('D', i - 1, X[i - 1]));
				i--;index++;
			}

		}
	}

	int offset = 0;
	string result = "";
	for (command; !command.empty(); command.pop()) {
		Operation op = command.top();
		
		if (op.operation == 'D') {
			op.generate(offset);
			offset--;
		}

		if (op.operation == 'I') {
			op.generate(offset);
			offset++;
		}

		if (op.operation == 'C') {
			op.generate(offset);
		}
	}
	
	cout << "E\n";

}

/* Utility function to get max of 2 integers */
int min(int a, int b)
{
	return (a < b) ? a : b;
}

/* Driver program to test above function */
int main()
{
	string line;
	while (getline(cin, line)) {
		stringstream ss(line);
		
		if (line.at(0) == '#')
			break;
		
		string source, goal;
		ss >> source;
		ss >> goal;

		char X[limit_len];
		char Y[limit_len];

		int m, n;
		m = source.length();
		n = goal.length();

		for (int i = 0; i < m; i++)
			X[i] = source.at(i);
		for (int i = 0; i < n; i++)
			Y[i] = goal.at(i);

		lcs(X, Y, m, n);
		
	}
	
	
	//
	//printf("Length of LCS is %d\n", lcs(X, Y, m, n));

	return 0;
}
