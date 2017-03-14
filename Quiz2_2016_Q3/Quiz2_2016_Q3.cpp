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

const int max_coord = 50;
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


void generateNode(int a, int cost) {
	graph[2 * a][2 * a + 1]		 = true;
	capacities[2 * a][2 * a + 1] = cost;
}


void connect(int a, int b, int d) {
	graph[2 * a + 1][2 * b] = true;
	graph[2 * b + 1][2 * a] = true;

	capacities[2 * a + 1][2 * b] = d;
	capacities[2 * b + 1][2 * a] = d;

}



int main()
{
	int M, W;

	while (true) {
		cin >> M >> W;
		if (M == 0 && W == 0)
			break;

		int n = 2 * M;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				graph[i][j] = false;
				flow_passed[i][j] = 0;
				capacities[i][j] = 0;
			}
		}

		generateNode(0, numeric_limits<int>::max());//K's machine
		generateNode(M - 1, numeric_limits<int>::max());//Central server

		int M_id, W_a, W_b, cost;
		for (int i = 0; i < M - 2; i++) {
			cin >> M_id >> cost;
			generateNode(M_id - 1, cost);
		}

		for (int i = 0; i < W; i++) {
			cin >> W_a >> W_b >> cost;
			connect(W_a - 1, W_b - 1, cost);
		}

		cout << maxFlow(0, 2 * (M - 1) + 1, n) << "\n";
	}


    return 0;
}

