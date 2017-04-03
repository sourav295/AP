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

void loadDest(long dest) {
	int i;
	for (i = 0; i < n_limit; ++i) {  // assuming a 32 bit int
		endNumber[i]   = dest & (1 << i) ? 1 : 0;
	}
}

void loadSrc(long src) {
	int i;


	for (i = 0; i < n_limit; ++i) {  // assuming a 32 bit int
		startNumber[i] = src & (1 << i) ? 1 : 0;
	}
}


int main()
{
	loadDest(8);
	loadSrc(7);
	cout << startNumber[0];

	int sig_bit = n_limit - 1;

	for (int i = sig_bit; i >= 0; i--) {
		if (startNumber[i] == true) {
			sig_bit = i;
			break;
		}
	}





	int x = 10;
	/*
	uint64_t a, b, c, d;
	while (cin >> a >> b) {
		
		c = a ^ b;
		d = 0;

		int i = 0;
		while (c >>= 1) {
			d += (1 << i);
			i++;
		}
		printf("%" PRIu64 "\n", (d | b));
		//printf("%llu\n", );
	}
	*/
    return 0;
}

