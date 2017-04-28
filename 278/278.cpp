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

const int n_limit = 1000;
int input[n_limit];

int main()
{
	int c, n, sum, count;
	cin >> c;
	for (int i = 0; i < c; i++){
		cin >> n;
		sum = 0;
		count = 0;
		for (int j = 0; j < n; j++){
			cin >> input[j];
			sum += input[j];
		}

		for (int j = 0; j < n; j++){
			if (n*input[j] > sum)
				count++;
		}
		printf("%.3lf%%\n", (float)count*100 / n);
	}
	

	return 0;
}

//