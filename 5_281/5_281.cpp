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
using namespace std;

const int max_weight = 30;
const int max_number = 1000;
const int max_group = 100;

int K[max_number + 1][max_weight + 1];

void knapSack(int W, int wt[], int val[], int n)
{
	int i, w;
	
	for (i = 0; i <= n; i++)
	{
		for (w = 0; w <= W; w++)
		{
			if (i == 0 || w == 0)
				K[i][w] = 0;
			else if (wt[i - 1] <= w)
				K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
			else
				K[i][w] = K[i - 1][w];
		}
	}
}



int main()
{
	int wt[max_number];
	int val[max_number];
	int mw[max_group];

	int T, N, P, W, G, MW;
	cin >> T;

	for (int t = 0; t < T; t++) {
		cin >> N;
		
		for (int n = 0; n < N; n++) {
			cin >> P >> W;
			val[n] = P;
			wt[n] = W;
		}
		
		//get group information
		cin >> G;
		int max_wt = 0;
		for (int g = 0; g < G; g++) {
			cin >> MW;
			if (max_wt < MW)
				max_wt = MW;
			mw[g] = MW;
		}

		int sum = 0;
		knapSack(max_wt, wt, val, N);
		for (int g = 0; g < G; g++)
			sum += K[N][mw[g]];

		cout << sum << "\n";
	}

    return 0;
}

