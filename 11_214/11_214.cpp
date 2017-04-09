#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <stack>
#include <limits>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

bool isPrime(unsigned long int x) {
	unsigned long int x_half = x / 2;
	bool isPreime = true;
	
	for (int i = 2; i < x_half; i++)
		if (x%i == 0)
			return false;
	return true;
}


int main()
{
	unsigned long int x, y, lower_prime, upper_prime;
	while (cin >> x) {
		if (x == 0)
			break;
		if (isPrime(x)) {
			cout << 0 << "\n";
		}
		else {
			if(x%2 == 0){
				x += 1;
			}

			for (y = x; true; y+=2) {
				if (isPrime(y)){
					upper_prime = y;
					break;
				}
			}
			for (y = x-2; true; y-=2) {
				if (isPrime(y)) {
					lower_prime = y;
					break;
				}
			}
			cout << upper_prime - lower_prime << "\n";
		}



	}


    return 0;
}

