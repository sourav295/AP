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


unsigned long flag[(100000007 >> 6) + 1];

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
	
	for (i = 3; i <= n; i+=2) {
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
		return false;
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
			unsigned int p1, p2, n_pos, half_index;

			n_pos = n / 2;
			for (n_pos; n_pos < n; n_pos++) {
				if (checkPrime(n - n_pos) && checkPrime(n_pos)) {
					cout << n << " is the sum of " << n-n_pos<<" and " << n_pos<< ".\n";
					break;
				}
			}
		}
	}

	return 0;
}