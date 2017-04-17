#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include <string.h>
#include <string>
#include <stack>
#include <limits>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

//char* x     = new char[100001 * 2 + 1];
//int* result = new int[100001 * 2 + 1];

char x[100001 * 2 + 1];
int result[100001 * 2 + 1];

vector<int> PrefixFunction(string S) {
	vector<int> p(S.size());
	int j = 0;
	for (int i = 1; i < (int)S.size(); i++) {
		while (j > 0 && S[j] != S[i])
			j = p[j - 1];

		if (S[j] == S[i])
			j++;
		p[i] = j;
	}
	return p;
}



int preprocess(int n)
{
	int len = 0;
	result[0]  = 0;
	int i   = 1;
	while (i < n)
	{
		if (x[i] == x[len])
		{
			len++;
			result[i] = len;
			i++;
		}
		else
		{
			if (len != 0){
				len = result[len - 1];
			}
			else{
				result[i] = 0;
				i++;
			}
		}
	}

	return result[n - 1];
}




int main()
{
	string input;
	while (getline(cin, input)) {

		int n = input.length();
		x[n] = '$';
		for (int i = 0; i < n; i++) {
			//post sentinel 
			x[n + 1 + i] = input[i];
			//pre sentinel
			x[n - 1 - i] = input[i];
		}

		

		int max_postFixPalindrome = preprocess(2*n + 1);
		cout << input;
		for (int i = n - max_postFixPalindrome - 1; i >= 0; i--)
			cout << input[i];
		cout << "\n";


		/*
		int i, j;

		i = 0;
		j = n - 1;

		bool found = false;
		int palBegin = -1;
		for (i, j; i < j; i++) {

			if (x[i] == x[j]) {
				if (found == false)
					palBegin = i;
				found = true;
				j--;
			}else {
				//reset
				if (palBegin > -1 && x[palBegin] == x[palBegin + 1])
					i = palBegin;
				j = n - 1;
				found = false;
			}
		}

		if (!found)
			palBegin = n - 1;

		cout << input;
		for (i = palBegin - 1; i >= 0; i--)
			cout << x[i];
		cout << "\n";
		*/
	}

    return 0;
}

