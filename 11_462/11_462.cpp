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
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <bitset>
using namespace std;

const unsigned long last_prime = 100000007;
const unsigned long n_sqrt = 10001;

//6 signifies 2^6 that is 64, 64 since int provides a space of 32 bits and even numbers can be ignored.
//Therefore, the entire range is broken into sets of 64 bits
int flag[(100000007 >> 6) + 1];
//unsigned int *prime = new unsigned int[no_prime];

unsigned int index_to_value(unsigned int index) {
	if (index == 0)
		return 1;
	if (index == 1)
		return 2;
	
	return 2 * index - 1;
}

unsigned int value_to_index(unsigned int value) {//eliminate the need of even numbers
	if (value == 1)
		return 0;
	if (value == 2)
		return 1;

	return (value + 1) / 2;
}

void setAsComposite(unsigned long x) {
	flag[(x >> 6)] |= (1 << (
								(x & 63) >> 1
							) 
						);
}

bool isComposite(unsigned long x) {
	return	flag[(x >> 6)] & (1 <<	(
										(x & 63) >> 1
									)
							);
}

void createPrimeArray(unsigned int n) {

	unsigned long i, j;
	

	//i = 1 contains 2
	
	for (i = 3; i <= n_sqrt; i+=2) {
		if (!isComposite(i)) {
			for (j = i*i; j <= n; j += (i<<1)) {
				setAsComposite(j);
			}
		}
	}

}

bool checkPrime(unsigned long x) {
	if (x == 1 || x == 2)
		return true;
	else if (x % 2 == 0)
		return true;
	else return !isComposite(x);

}


int main()
{
	unsigned int n;
	createPrimeArray(100000007);

	while(cin >> n){
		//n = input.front();
		
		if (n == 0 || n == 1) {
			cout << n << " is not the sum of two primes!\n";
			continue;
		}

		if (n & 1){
			//number is odd
			if (checkPrime(n-2))
				if(n-2 != 1)
					cout << n << " is the sum of " << "2 and " << n - 2 << ".\n";
				else
					cout << n << " is the sum of " << "1 and 2"<< ".\n";
			else
				cout << n << " is not the sum of two primes!\n";
		}
		else{
			unsigned int p1, p2, n_half, half_index;

			n_half = n / 2;
			if (!(n_half & 1))//even
				n_half++;
			half_index = value_to_index(n_half);

			for (unsigned int i = half_index; i < n; i++){
				p2 = index_to_value(i);
				p1 = n - p2;
				if (checkPrime(p1) && checkPrime(p2)){
					cout << n << " is the sum of " << p1 << " and " << p2 << ".\n";
					break;
				}
			}
		}
	}

	return 0;
}