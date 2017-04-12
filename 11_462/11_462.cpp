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
const long largestPrime = 5761455;


const long bit_size = 64;
const long bins = (n_limit/bit_size) + 1;

bitset<bit_size> flag[bins];
long prime[largestPrime];

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

	count_prime = 0;
	for (long i = 2; i <= n; i++) {
		if (getFlag(i)) {
			prime[count_prime++] = i;
		}
		
		for (int j = 0; j<count_prime && i*prime[j] <= n; j++) {
			updateFlag(i*prime[j], false);   //i*prime[j] is filtered. 					    			    	                              
			if (i%prime[j] == 0)
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
	
	queue<long> input;
	long max_input = 0;
	while (cin >> in) {
		
		

		if (in > max_input)
			max_input = in;
		input.push(in);

		

	}
	getPrime(max_input);

	for (input; !input.empty(); input.pop()) {
		long in = input.front();
		half_input = in / 2;

		bool found = false;
		long best;
		for (long i = 0; prime[i] <= half_input && i < count_prime; i++) {
			if (getFlag(in - prime[i])) {
				found = true;
				best = prime[i];
			}
		}

		if (found) {
			cout << in << " is the sum of " << best << " and " << in - best << ".\n";
		}
		else {
			cout << in << " is not the sum of two primes!\n";
		}
	}


	
	return 0;
}

