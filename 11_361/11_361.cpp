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
#include <math.h>
#include <fstream>
#include <map>
#include <set>
using namespace std;

unsigned long long int max_base = 65536;
unsigned long long int n_limit = 18446744073709551615;

const double log10_nLimit = log10(n_limit);



bool  flag[64 + 1];
int   prime[64 + 1];
int composite_dict[64];

void getComposite() {

	for (int i = 0; i <= 64; i++) {
		flag[i] = true;
	}

	int  count = 0;
	for (int i = 2; i <= 64; i++) {

		if (flag[i] == true) {
			prime[count++] = i;
		}

		for (int j = 0; j<count && i*prime[j] <= 64; j++) {
			flag[i*prime[j]] = false;
			if (i%prime[j] == 0)
				break;
		}
	}

	count = 0;
	for (int i = 0; i <= 64; i++) {
		if (!flag[i])
			composite_dict[count++] = i;
	}
}



set<unsigned long long int> superPower_set;

unsigned long long number_sq(unsigned long long n) {
	return n*n;
}

unsigned long long number_power(unsigned long long base, int exp)
{
	if (!exp) {
		return 1;
	}
	else if ((exp & 1)) {
		return base * number_power(base, exp - 1);
	}
	else {
		return number_sq(number_power(base, exp >>= 1));
	}
}

int main(){
	
	getComposite();

	unsigned long long int i, j;
	
	for (i = 2; i< max_base; i++) {
		double maxRange_inverseExpo = (log10_nLimit / log10(i));
		for (j = 0; composite_dict[j] < maxRange_inverseExpo; j++) {
			superPower_set.insert(number_power(i, composite_dict[j]));
		}
	}

	cout << 1 << "\n";

	for (set<unsigned long long int>::iterator it = superPower_set.begin(); it != superPower_set.end(); it++)
	{
		cout << *it << "\n";
	}

	return 0;
}