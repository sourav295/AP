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

bitset<100000000> prime;

void createPrimeArray(long int n){
	for (long int p = 2; p*p <= n; p++)
	{
		// If prime[p] is not changed, then it is a prime
		if (prime[p] == false)
		{
			// Update all multiples of p
			for (int i = p * 2; i <= n; i += p)
				prime[i] = true;
		}
	}
}

bool isPrime(long int n){
	return !prime[n];
}


int main()
{
	long int n, max_n;
	queue<long int> input;

	max_n = 0;
	while (cin >> n){
		if (n > max_n)
			max_n = n;
		input.push(n);
	}
	createPrimeArray(max_n);

	for (input; !input.empty(); input.pop()){
		n = input.front();
		if (n & 1){
			//number is odd
			if (isPrime(n - 2))
				cout << n << " is the sum of " << "2 and " << n - 2 << ".\n";
			else
				cout << n << " is not the sum of two primes!\n";
		}
		else{
			long int p1, p2;
			for (long int i = n / 2; i <= n; i++){
				p2 = i;
				p1 = n - p2;
				if (isPrime(p1) && isPrime(p2)){
					cout << n << " is the sum of " << p1 << " and " << p2 << ".\n";
					break;
				}
			}
		}
	}

	return 0;
}