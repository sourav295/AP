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

char x[100001];

int main()
{
	string input;
	while (getline(cin, input)) {

		int n = input.length();
		//strcpy(x, input.c_str());
		string x = input;
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
				if (palBegin > -1)
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

	}

    return 0;
}

