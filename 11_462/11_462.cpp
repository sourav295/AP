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

bool  *flag = new bool[100000000];
unsigned long int *prime = new unsigned long int[5761455];

void createPrimeArray(unsigned long int n) {
	
	for (unsigned long int i = 0; i <= n; i++) {
		flag[i] = true;
	}

	unsigned long int count = 0;		   //total number found now
	for (unsigned long int i = 2; i <= n; i++) {
		if (flag[i] == true)
			prime[count++] = i;     //not filtered, then prime
									// prime[j], the j-th prime	
		for(unsigned long int j=0 ; j<count  &&  i*prime[j] <= n ; j++)	{
			flag[i*prime[j]] = false;   //i*prime[j] is filtered. 					    			    	                              
			if (i%prime[j] == 0)
				break;
		}
	}
}



int main()
{
	unsigned long int n;

	createPrimeArray(100000000);

	while(cin >> n){
		//n = input.front();
		
		if (n == 0 || n == 1) {
			cout << n << " is not the sum of two primes!\n";
			continue;
		}

		
		
		if (n & 1){
			//number is odd
			if (flag[n - 2])
				if(n-2 != 1)
					cout << n << " is the sum of " << "2 and " << n - 2 << ".\n";
				else
					cout << n << " is the sum of " << "1 and 2"<< ".\n";
			else
				cout << n << " is not the sum of two primes!\n";
		}
		else{
			unsigned long int p1, p2;
			for (unsigned long int i = n / 2; i < n; i++){
				p2 = i;
				p1 = n - p2;
				if (flag[p1] && flag[p2]){
					cout << n << " is the sum of " << p1 << " and " << p2 << ".\n";
					break;
				}
			}
		}
	}

	return 0;
}