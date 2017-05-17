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

const int n_limit = 1299709;
bool  flag[n_limit + 1];
int   prime[n_limit + 1];

void getComposite(int n){
    
	for (int i = 0; i <= n_limit; i++) {
		flag[i] = true;
	}

    int  count = 0;
    for (int i = 2; true; i++){
		
		if (flag[i] == true){
			prime[count++] = i;
			if (n < i)
				break;
		}
					 
		for( int j=0 ; j<count  &&  i*prime[j] <= n_limit; j++)	{
			flag[i*prime[j]] = false;			    			    	                              
			if (i%prime[j] == 0)
				break;
		}
    }
}

int main()
{
	queue<int> input;
	int in, max_input;
	max_input = 0;
	while (cin >> in) {
		
		if (in == 0) {
			break;
		}


		if (in > max_input) {
			max_input = in;
		}
		
		input.push(in);
	}
	
	getComposite(max_input);

	for (input; !input.empty(); input.pop()) {
		in = input.front();
		int succeeding_prime, precceding_prime;
		for (int i = in; true; i++)
			if (flag[i]) {
				succeeding_prime = i;
				break;
			}
		for (int i = in; true; i--)
			if (flag[i]) {
				precceding_prime = i;
				break;
			}
		cout << succeeding_prime - precceding_prime << "\n";
	}

    return 0;
}

