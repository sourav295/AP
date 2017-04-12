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
	long half_input;
	
	while (cin >> in) {
		getPrime(in);
		half_input = in / 2;
		for (long i = 0; prime[i] <= half_input; i++) {
			cout << prime[i] << "(" << in - prime[i] << ")\t";
		}
		cout << "\n";
	
	}

	
	return 0;
}

