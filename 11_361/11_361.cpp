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
using namespace std;

vector<unsigned long long> x;
map<unsigned long long, bool> dict;

int main()
{
	unsigned long long n = (1 << 64) - 1;
	

	x.push_back(1);
	
	
	unsigned long long i = 0;
	unsigned long long prod = 0;
	unsigned long long diff = 0;
	unsigned long long lim = 0;

	for (i = 2; i <= n; i++) {
		if (!dict.count(i)) {
			diff = i*i;
			prod = diff * diff;

			lim = n / diff;

			while (prod < n) {
				x.push_back(prod);
				dict[prod] = true;
				cout << prod << "\n";

				if (prod > lim)// in this case it will cross the limit
					break;

				prod *= diff;
			}
		}
	}

    return 0;
}

