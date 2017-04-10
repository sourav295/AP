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

vector<bool> hasOnePower, shownInOutput;


int main()
{
	unsigned long long n_limit = 1;
	for (int i = 1; i <= 64; i++) {
		n_limit <<= 1;
		cout <<i << " "<< n_limit << "\n";
	}

    return 0;
}

