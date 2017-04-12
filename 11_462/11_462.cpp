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
using namespace std;

const long n_limit = 100000000 + 1;
bool  flag[n_limit + 1];
long  prime[n_limit + 1];

long count_prime;
long primeNumbers_calculated;


void getPrime(long n) {
	
	if (n <= primeNumbers_calculated)
		return;
	else
		primeNumbers_calculated = n;//new value



	for (long i = 2; i <= n; i++) {

		if (flag[i] == true) {
			prime[count_prime++] = i;
		}

		for (long j = 0; j<count_prime && i*prime[j] <= n; j++) {
			flag[i*prime[j]] = false;
			if (i%prime[j] == 0)
				break;
		}
	}
}

int main()
{
	primeNumbers_calculated = 0;
	count_prime = 0;
	for (long i = 0; i <= n_limit; i++) {
		flag[i] = true;
	}

	queue<long> input;
	long in;
	long half_input, best_p1;
	
	long p1, p2;
	while (cin >> in) {
		getPrime(in);
		half_input = in / 2;


		best_p1 = -1;
		//check special case, p1 = 1
		if (flag[in - 1]) {
			best_p1 = 1;
		}

		for (long i = 0; prime[i] <= half_input; i++) {
			
			p1 = prime[i];
			p2 = in - prime[i];
			if (flag[p2]) {
				//checks if p2 is indeed a prime number
				best_p1 = p1;
			}
		}
		
		if (best_p1 == -1) {
			cout <<in<<" is not the sum of two primes!\n";
		}
		else {
			cout <<in<<" is the sum of "<<best_p1<<" and "<<in - best_p1<<".\n";
		}

	}

	
	return 0;
}

