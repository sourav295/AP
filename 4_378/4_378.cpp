#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <set>
#include <algorithm>
#include <limits>
#include <sstream>
using namespace std;

const int n_limit = 105;
int cost[n_limit][n_limit];
int lvl[n_limit];


int destination;
int min_cost;



void getCost(int u, int d, bool visited[], int path[], int &indx, int min_lvl ,int M, int N, int cost_intermediate) {
	visited[u] = true;
	path[indx] = u;
	min_lvl    = min(min_lvl, lvl[u]);
	
	indx++;

	if (u == destination) {
		//find cost
		int v = destination;
		int total_cost = cost_intermediate;
		if (total_cost < min_cost) {
			min_cost = total_cost;
		}
	}
	else {
		for (int v = 0; v <= N; v++) {
			if (cost[u][v] > 0 && !visited[v] && (lvl[v] - min_lvl <= M) && cost_intermediate + cost[u][v] < min_cost) {
				getCost(v, d, visited, path, indx, min_lvl, M, N, cost_intermediate + cost[u][v]);
			}
		}
	}

	indx--;
	visited[u] = false;
}



int main()
{
	int M, N;
	int P, L, X;
	int T, V;


	while (cin >> M >> N) {
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N; j++) {
				cost[i][j] = 0;
			}
			lvl[i] = 0;
		}
		
		for (int i = 1; i <= N; i++) {
			cin >> P >> L >> X;
			
			cost[0][i] = P;
			lvl[i] = L;

			for (int j = 0; j < X; j++) {
				cin >> T >> V;
				cost[T][i] = V;
			}
		}

		destination = 1;
		min_cost = numeric_limits<int>::max();
		
		bool visited[n_limit];
		int  path[n_limit];
		for (int i = 0; i < n_limit; i++) {
			visited[i] = false;
			path[i] = 0;
		}

		int index = 0;
		int cost_intermediate = 0;
		lvl[0] = lvl[1];
		getCost(0, destination, visited, path, index, numeric_limits<int>::max(), M, N, cost_intermediate);
		cout << min_cost << "\n";	
	}

    return 0;
}

