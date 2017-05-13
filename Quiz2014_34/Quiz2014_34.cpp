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
#include <map>
using namespace std;

const int n_lim = 200;
const int m_lim = 2000;

int A[n_lim];
int B[n_lim];

int lowest_cost = numeric_limits<int>::max();

struct extra {
	int a, b, c;
};

vector<extra> pair_cost;

void search(bool cat[], int i, int cost, int N, int M) {

	int costA = cost + A[i];
	int costB = cost + B[i];

	if (i == N - 1) {
		cat[i] = 0;
		for (int j = 0; j < M; j++) {
			if (cat[pair_cost[j].a] != cat[pair_cost[j].b]) {
				costA += pair_cost[j].c;
			}
		}

		cat[i] = 1;
		for (int j = 0; j < M; j++) {
			if (cat[pair_cost[j].a] != cat[pair_cost[j].b]) {
				costB += pair_cost[j].c;
			}
		}

		if (min(costA, costB) < lowest_cost) {
			lowest_cost = min(costA, costB);
		}

		return;
	}


	if (costA < lowest_cost) {
		cat[i] = 0;
		search(cat, i + 1, costA, N, M);
	}

	if (costB < lowest_cost) {
		cat[i] = 1;
		search(cat, i + 1, costB, N, M);
	}

	return;

}

int main()
{
	int N, M;
	while (cin >> N >> M) {
		
		pair_cost.clear();
		
		for (int i = 0; i < N; i++)
		{
			cin >> A[i] >> B[i];
		}

		for (int i = 0; i < M; i++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			extra e;
			e.a = a;
			e.b = b;
			e.c = c;

			pair_cost.push_back(e);
		}

		bool cat[n_lim];
		lowest_cost = numeric_limits<int>::max();
		for (int i = 0; i < N; i++)
			cat[i] = 0;


		search(cat, 0, 0, N, M);
		cout << lowest_cost << "\n";

	}
    return 0;
}

