#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <set>
#include <stack>
#include <limits>
#include<math.h>
#include <sstream>
using namespace std;

int main()
{
	string line;

	while (getline(cin, line)) {
		stringstream ss(line);

		unsigned int H, U, D, F;
		ss >> H;
		ss >> U;
		ss >> D;
		ss >> F;

		

		unsigned day = 1;

		double pos = 0;
		while (true) {
			double trav_today = U*pow(F, day - 1) / pow(100, day - 1);
			trav_today -= D;

			if (trav_today < 0) {
				cout << "failed on day " << day + 1 <<"\n";
				break;
			}

			pos += trav_today;
			if (pos + D >= H) {
				cout << "succeeded on day " << day << "\n";
				break;
			}

			day++;
		}




	}


    return 0;
}

