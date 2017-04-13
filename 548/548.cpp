// 548.cpp : Defines the entry point for the console application.
//

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
#include <cmath>
#include<math.h>
using namespace std;



unsigned long long getSeqOfOne(unsigned long long x, unsigned long long y) {
	
	//unsigned long long x = pow(10, 18);
	int closestHigherPower2 = floor(log(x) / log(2)) + 1;
	unsigned long long lower_lim = pow(2, closestHigherPower2 - 1);
	lower_lim--;
	if (lower_lim >= y) {
		unsigned long long res = (pow(2, closestHigherPower2));
		res--;
		return res;
	}
	else {
		return 0;
	}
	
}

unsigned long long getHighestSum(unsigned long long x, unsigned long long y) {
	unsigned long long bitsToChange, x_copy, sum;
	x_copy = x;
	int highest_hideFlip = -1;
	bitsToChange = x ^ y;
	for (int i = 0; bitsToChange != 0; bitsToChange >>= 1, x >>= 1, i++) {//shift towards left 
		bool change = bitsToChange & 1;
		bool hideFlip = change && (x & 1);
		if (hideFlip) {
			highest_hideFlip = i;
		}	
	}
	
	unsigned long long noChange_mask = 0;
	if (highest_hideFlip > -1)
			noChange_mask = (1 << (highest_hideFlip + 1)) - 1;
	//cout << noChange_mask << "\n"; 
	sum = (x_copy & noChange_mask) | (y & (~noChange_mask));
	return sum;
	
}



int main()
{
	
	
	unsigned long long a, b, candidate1, candidate2;
	string line;
	while (getline(cin , line)) {
		stringstream ss(line);
		ss >> a;
		ss >> b;
		if (a == b) {
			cout << a << "\n";
			continue;
		}
		
		
		candidate1 = 0;
		candidate2 = 0;
		
		candidate1 = getSeqOfOne(b, a);
		candidate2 = getHighestSum(b-1, b);
		if (candidate1 > candidate2)
			cout << setprecision(40)<<candidate1 << "\n";
		else
			cout << setprecision(40)<<candidate2 << "\n";

	}
	
    return 0;
}

