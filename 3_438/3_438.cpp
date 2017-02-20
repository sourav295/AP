#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <utility>
#include <stack>
#include<string>
#include<sstream>
#include<ctype.h>
#include <stdlib.h>
using namespace std;

int main()
{
	int n_samples;
	cin >> n_samples;

	for (int i = 0; i < n_samples; i++) {
		int n;
		cin >> n;
		if (n == 0 || n == 1)
			cout << 0 << "\n";
		else if (n % 2 == 0)
			cout << n / 2 << "\n";
		else
			cout << (n - 1) / 2 << "\n";
	}

    return 0;
}

