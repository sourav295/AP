// 548.cpp : Defines the entry point for the console application.
//

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
#include <cmath>
#include<math.h>
using namespace std;





int main()
{
	
	
	unsigned long long a, b, c, b_copy;
	string line;
	while (getline(cin , line)) {
		stringstream ss(line);
		ss >> a;
		ss >> b;
		if (a == b) {
			cout << a << "\n";
			continue;
		}
		
		b_copy = b;

		int furthest_mutilation = -1;
		int count = 0;
		while (b > 0) {
			bool a_last = a & 1;
			bool b_last = b & 1;
			if (a_last != b_last)
				furthest_mutilation = count;
			count++;
			
			a = a >> 1;
			b = b >> 1;
		}
		
		c = (1 << (furthest_mutilation + 1)) - 1;

		cout << (b_copy|c) <<"\n";

	}
	
    return 0;
}

