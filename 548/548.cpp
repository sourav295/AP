// 548.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <inttypes.h>
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <stdint.h>
using namespace std;

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
	
	
	/*
	unsigned long long max_change = start;
	int max_sig = sig_start > sig_end ? sig_start : sig_end;
	for (int i = max_sig; i >= 0; i--) {
		//difference[i] = startNumber[i] ^ endNumber[i];
		if (startNumber[i] ^ endNumber[i]) {
			if (!startNumber[i]) {
				//show number
				max_change += (1 << i);
			}
			else {
				break;
			}
		}
	}
	*/
	return add_one() + start;
}




int main()
{
	
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


    return 0;
}

