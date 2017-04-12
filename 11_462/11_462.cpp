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
using namespace std;

const long n_limit = 100000000 + 1;
const long bit_size = 64;
const long bins = (n_limit/bit_size) + 1;

bitset<bit_size> flag[bins];
long primeNumbers_calculated;

long count_prime = 0;

void updateFlag(long pos, bool value) {
	(flag[(pos / bit_size)])[(pos % bit_size)] = value;
}

bool getFlag(long pos) {
	return (flag[(pos / bit_size)])[(pos % bit_size)];
}


void getPrime(long n) {
	
	if (n <= primeNumbers_calculated)
		return;
	else
		primeNumbers_calculated = n;//new value
	
	for (long i = 0; i <= n; i++) {
		updateFlag(i, true);
	}

	for (long i = 2; i <= n; i++) {
		if (getFlag(i)) {
			count_prime++;
		}
		long k = 0;//number of prime numbers utilized in calculation 2..count
		
		for (long j = 2; i*j <= n; j++) {
			if (!getFlag(j))
				continue;
			//j is a prime number
			k++;
			updateFlag(i*j, false);
			if (i%j == 0 || k == count_prime)
				break;
		}
	}
	updateFlag(1, true);
}

int main()
{

	
	primeNumbers_calculated = 0;
	

	long in;
	long half_input, best_p1;
	
	while (cin >> in) {
		getPrime(in);
		half_input = in / 2;

		bool found = false;
		for (long i = half_input; i >= 1; i--) {
			if (getFlag(i) && getFlag(in - i)) {
				found = true;
				cout << in << " is the sum of " << i << " and " << in - i<< ".\n";
				break;
			}
		}
		if(!found)
			cout << in << " is not the sum of two primes!\n";

	}
	
	return 0;
}

