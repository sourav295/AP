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
#include <bitset>
#include <math.h>
#include <fstream>
using namespace std;

const unsigned long long n_limit = numeric_limits<unsigned long long>::max();
bitset<64> flag(n_limit / 64);


int main()
{
	cout << flag[0];
	/*
	unsigned long long x = 123;
	unsigned long long d = pow(x, 2);
	int times = log(n_limit) / log(x);
	x = pow(x, 4);

	for (int i = 4; i <= times; i += 2, x = x*d) {
		cout << i << "-"<<x << "\n";
	}
	*/
    return 0;
}

