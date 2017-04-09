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
		candidate2 = (b - 1) + getFirstZero(b - 1);
		if (candidate1 > candidate2)
			cout << candidate1 << "\n";
		else
			cout << candidate2 << "\n";



	}

    return 0;
}

