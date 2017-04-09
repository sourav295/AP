// 548.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <inttypes.h>
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <math.h>
#include <stdint.h>
#include<string>
#include <sstream>
#include <limits>
using namespace std;


unsigned long long getFirstZero(unsigned long long n) {
	int i = 0;
	while (i < 66) {
		if (!(n & (1 << i))) {
			return 1 << i;
		}
		i++;
	}
	return 0;
}

unsigned long long getHighestSum(unsigned long long x, unsigned long long y) {
	unsigned long long xor, x_copy, sum;
	x_copy = x;
	int highest_hideFlip = -1; 
	xor = x ^ y;
	for (int i = 0; xor != 0; xor >>= 1, x >>= 1, i++) {//shift towards left
		bool change   = xor & 1;
		bool hideFlip = change && (x & 1);

		if (hideFlip){
			highest_hideFlip = i;
		}
		
	}
	
	unsigned long long noChange_mask = 0;
	if(highest_hideFlip > -1)
		noChange_mask = (1 << (highest_hideFlip+1)) - 1;
	//cout << noChange_mask << "\n";
	sum =  (x_copy & noChange_mask) | (y & (~noChange_mask));
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
		int pos = floor(log(b) / log(2));
		unsigned long long highest_precceding_multipleOf2 = (1 << pos);
		candidate1 = 0;
		candidate2 = 0;
		if (highest_precceding_multipleOf2  > a) {
			candidate1 =  2 * highest_precceding_multipleOf2 - 1;
		}
		candidate2 = getHighestSum(b-1, b);
		if (candidate1 > candidate2)
			cout << candidate1 << "\n";
		else
			cout << candidate2 << "\n";

	}
	
    return 0;
}

