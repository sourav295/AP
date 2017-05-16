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
using namespace std;

const int max_coord = 100 + 4;
const int n_limit = (2 * max_coord);//2 more for source and destination

bool graph[n_limit][n_limit];

int capacities[n_limit][n_limit];
int flow_passed[n_limit][n_limit];

int parent_list[n_limit];
int currentPathCapacity[n_limit];

int bfs(int start, int end, int n) {

	for (int i = 0; i < n; i++) {
		parent_list[i] = -1;
		currentPathCapacity[i] = 0;
	}

	queue<int> q;
	q.push(start);

	parent_list[start] = -2;
	currentPathCapacity[start] = numeric_limits<int>::max();

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < n; v++) {
			if (graph[u][v] && parent_list[v] == -1) {
				if (capacities[u][v] - flow_passed[u][v] > 0) {
					parent_list[v] = u;
					currentPathCapacity[v] = min(currentPathCapacity[u], capacities[u][v] - flow_passed[u][v]);

					if (v == end) {
						return currentPathCapacity[v];
					}
					q.push(v);
				}
			}
		}
	}

	return 0;

}

int maxFlow(int start, int end, int n) {

	int maxFlow = 0;
	while (true) {
		int flow = bfs(start, end, n);
		if (flow == 0) {
			break;
		}
		maxFlow += flow;
		int u = end;
		while (u != start) {
			int v = parent_list[u];
			flow_passed[v][u] += flow;
			flow_passed[u][v] -= flow;
			u = v;
		}

	}

	return maxFlow;
}


int distance_sq(pair<int, int> a, pair<int, int> b) {
	return (pow(a.first - b.first, 2) + pow(a.second - b.second, 2));

}

int main()
{
	int L, W, N, d;
	vector<pair<int, int>> input;
	int n_case = 1;

	while (true) {
		cin >> L >> W >> N >> d;
		input.clear();
		if (L == 0 && W == 0 && N == 0 && d == 0)
			break;

		for (int i = 0; i < 2 * N + 2; i++) {
			for (int j = 0; j < 2 * N + 2; j++) {
				graph[i][j] = false;
				flow_passed[i][j] = 0;
				capacities[i][j] = 0;
			}
		}

		int sount_index = 2*N + 1;
		int north_index = 2*N;
		int four_d_sqr  = 4*d*d;

		

		for (int i = 0; i < N; i++) {
			int x, y;
			cin >> x >> y;
			
			input.push_back({ x, y });

			graph[2*i][2 * i + 1] = true;
			capacities[2 * i][2 * i + 1] = 1;


			if (y <= d) {
				graph[north_index][2 * i] = true;
				capacities[north_index][2 * i] = 1;

			}
				
			if (W - y <= d) {
				graph[2 * i + 1][sount_index] = true;
				capacities[2 * i + 1][sount_index] = 1;
			}

		}

		for(int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				if (distance_sq(input[i], input[j]) <= four_d_sqr) {
					graph[2 * i + 1][2 * j] = true;
					capacities[2 * i + 1][2 * j] = 1;
				}
			}

		cout << "Case " << n_case++ << ": "<<maxFlow(north_index, sount_index, sount_index + 1) << "\n";
	}


	return 0;
}

