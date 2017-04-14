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
using namespace std;

const int m_limit = 100;
bool isIsolated[m_limit];

struct Point {
	int x, y;

	int determinant(Point other_point) {

	}

};

int main()
{
	int M, N;
	cin >> N;
	for (int n = 0; n < N; n++) {
		cin >> M;

		//clear array
		for (int m = 0; m < M; m++) {
			isIsolated[m] = true;
		}

		for (int m = 0; m < M; m++) {
			
		}

	}

    return 0;
}

