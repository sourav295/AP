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





bool* createPrimeArray(long int n) {
	bool  *flag = new bool[n];
	long int *prime = new long int[n];
	
	for (long int i = 0; i <= n; i++) {
		flag[i] = true;
	}

	int  count = 0;		   //total number found now
	for (long int i = 2; i <= n; i++) {
		if (flag[i] == true)
			prime[count++] = i;     //not filtered, then prime
									// prime[j], the j-th prime	
		for(long int j=0 ; j<count  &&  i*prime[j] <= n ; j++)	{
			flag[i*prime[j]] = false;   //i*prime[j] is filtered. 					    			    	                              
			if (i%prime[j] == 0)
			break;
		}
	}

	return flag;
}



int main()
{
	long int n;

	

	while(cin >> n){
		//n = input.front();
		bool *flag = createPrimeArray(n);
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
			long int p1, p2;
			for (long int i = n / 2; i <= n; i++){
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