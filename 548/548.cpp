// 548.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <inttypes.h>
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <stdint.h>
using namespace std;

const int n_limit = 64;

bool startNumber[n_limit];
bool endNumber[n_limit];
bool difference[n_limit];


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
	
	int sig_start = convertToBinary(start, startNumber, 0);
	int sig_end = convertToBinary(start + 1, endNumber, 0);
	
	unsigned long long max_change = start;
	int max_sig = sig_start > sig_end ? sig_start : sig_end;
	for (int i = max_sig; i >= 0; i--) {
		//difference[i] = startNumber[i] ^ endNumber[i];
		if (startNumber[i] ^ endNumber[i]) {
			if (!startNumber[i]) {
				//show number
				max_change += unsigned long long(1 << i);
			}
			else {
				break;
			}
		}
	}
	return max_change;
}


int main()
{
	

	unsigned long long a, b;
	while (cin >> a >> b) {
		if (a == b){
			cout << a << "\n";
			continue;
		}
		unsigned long long max = 0;
		for (unsigned long long i = a; i < b; i++) {
			unsigned long long res = getMaxDiff(i);
			if (res > max)
				max = res;
		}
		cout << max << "\n";
	}


    return 0;
}

