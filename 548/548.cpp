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
/*
const int n_limit = 66;

bool startNumber[n_limit];
bool endNumber[n_limit];
bool difference[n_limit];
int sig_start, sig_end;

bool one_binary[n_limit];

unsigned long long  add_one() {

	bool c = false;
	int max_indexChange= 0;
	for (int i = 0; i <= sig_end + 1; i++) {
		startNumber[i] = endNumber[i];//increment the start number by 1

		if (c && !endNumber[i])
			max_indexChange = i;

		bool val = ((endNumber[i] ^ one_binary[i]) ^ c); // c is carry
		c = ((endNumber[i] & one_binary[i]) | (endNumber[i] & c)) | (one_binary[i] & c);
		


		endNumber[i] = val;//increment the end number by 1
	}

	sig_start = sig_end;
	if (endNumber[sig_end + 1])
		sig_end++;

	return 1 << max_indexChange;
}

int convertToBinary(unsigned long long n, bool arr[], int pos)
{
	int p;
	if (n / 2 != 0) {
		arr[pos] = n % 2;
		p = convertToBinary(n / 2, arr, pos + 1);
	}
	else {
		arr[pos] = n % 2;
		p = pos;
	}

	return p;
}

unsigned long long getMaxDiff(unsigned long long start) {
	
	
	
	return add_one() + start;
}


*/

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

	

	/*
	one_binary[0] = true;
	unsigned long long a, b;
	while (cin >> a >> b) {
		if (a == b){
			cout << a << "\n";
			continue;
		}

		sig_end = convertToBinary(a, endNumber, 0);
		
		unsigned long long max = 0;
		for (unsigned long long i = a; i < b; i++) {

			unsigned long long res = getMaxDiff(i);
			if (res > max)
				max = res;
		}

		for (int i = 0; i <= sig_end; i++)
			endNumber[i] = false;

		cout << max << "\n";
	}
	*/

    return 0;
}

