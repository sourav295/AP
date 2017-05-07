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

const unsigned int last_prime = 100000007;
const unsigned int no_prime   = 5761456;

bool  *flag = new bool[(100000007 + 1)/2];
unsigned int *prime = new unsigned int[no_prime];

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

void createPrimeArray(unsigned int n) {

	unsigned int i, j;
	fill(flag, flag + (n*sizeof(bool)+1)/2, true);

	//i = 1 contains 2
	/*
	for (i = 3; i <= n_sqrt; i+=2) {
		if (flag[value_to_index(i)]) {
			for (j = i*i; j <= n; j += 2*val) {
				flag[value_to_index(j)] = false;
			}
		}
	}
	
	*/

	unsigned int  count = 0;		   //total number found now
	for (i = 3; i <= n; i+=2) {
		if (flag[value_to_index(i)] == true)
			prime[count++] = i;     //not filtered, then prime
									// prime[j], the j-th prime	
		for( j=0 ; j<count  &&  i*prime[j] <= n ; j++)	{
		flag[value_to_index(i*prime[j])] = false;   //i*prime[j] is filtered. 					    			    	                              
		if (i%prime[j] == 0)
			break;
		}
	}

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
			if (flag[value_to_index(n - 2)])
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
				if (flag[value_to_index(p1)] && flag[value_to_index(p2)]){
					cout << n << " is the sum of " << p1 << " and " << p2 << ".\n";
					break;
				}
			}
		}
	}

	return 0;
}