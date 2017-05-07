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
bool flag[50000001];
//bool  *flag = new bool[50000001];
//bitset<100000001>  flag;
//vector<bool> flag(100000000/2 + 1, true);
unsigned int *prime = new unsigned int[5761455];

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

	unsigned int i, j, val_sq, val;
	unsigned int n_sqrt_index = value_to_index((unsigned int)pow(n, 0.5) + 1);

	unsigned int n_lim = value_to_index(n);
	for (i = 0; i <= n_lim; i++) {
		flag[i] = true;
	}

	//i = 1 contains 2
	for (i = 1; i <= n_sqrt_index; i++) {
		if (flag[i]) {

			unsigned int val = index_to_value(i);
			if (val&1) {
				val_sq = val*val;
				for (j = val_sq; j <= n; j += val) {
					if (j & 1)
						flag[value_to_index(j)] = false;
				}
			}
		}
	}
	


	/*
	unsigned int count = 0;		   //total number found now
	for (unsigned int i = 2; i <= n; i++) {
		if (flag[i] == true)
			prime[count++] = i;     //not filtered, then prime
									// prime[j], the j-th prime	
		for(unsigned int j=0 ; j<count  &&  i*prime[j] <= n ; j++)	{
			flag[i*prime[j]] = false;   //i*prime[j] is filtered. 					    			    	                              
			if (i%prime[j] == 0)
				break;
		}
	}*/
}

int main()
{
	unsigned int n;
	cout << numeric_limits<int>::max();
	

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