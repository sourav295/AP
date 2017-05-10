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

const int max_coord = 100;
const int n_limit   = (2* max_coord) + 10;//2 more for source and destination

vector<pair<int, int>> coordinates(max_coord);
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
	graph[2 * a][2 * a + 1] = true;
	capacities[2 * a][2 * a + 1] = cost;
}

void connect(int a, int b, int d) {
	graph[2 * a + 1][2 * b] = true;
	graph[2 * b + 1][2 * a] = true;

	capacities[2 * a + 1][2 * b] = d;
	capacities[2 * b + 1][2 * a] = d;

}

void clear(int n) {
	int dimension = 2 * n + 5;

	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			graph[i][j] = false;
			flow_passed[i][j] = 0;
			capacities[i][j] = 0;
		}
	}

}


int main()
{
	int L, W, n, d;
	int x, y;

	int test_count = 1;
	while (true) {
		cin >> L >> W >> n >> d;
		
		if (L == 0 && W == 0 && n == 0 && d == 0)
			break;
		
		clear(n);

		int north_id	= 0;
		int south_id	= n+1;
		int four_d_sq	= 4*d*d;

		generateNode(north_id, numeric_limits<int>::max());
		generateNode(south_id, numeric_limits<int>::max());

		for (int i = 0; i <n; i++) {
			cin >> x >> y;
			coordinates[i] = { y , x };//sort by y and then x
		}
		
		int u, v;
		sort(coordinates.begin(), coordinates.begin() + n);
		for (int i = 0; i <n; i++) {
			u = i + 1;
			int u_x = coordinates[i].second;
			int u_y = coordinates[i].first;


			generateNode(u, 1);


			if (u_y + d >= W)
				connect(u, north_id, 1);
			if (u_y - d <= 0)
				connect(south_id, u, 1);

			for (int j = i + 1; j < n; j++) {
				v = j + 1;
				int v_x = coordinates[j].second;
				int v_y = coordinates[j].first;
				
				int dist_sq = pow((u_x - v_x), 2) + pow((u_y - v_y),2);
				if (dist_sq < four_d_sq) {
					connect(u, v, 1);
				}
			}
		}
		cout << "Case "<< test_count++ <<": "<< maxFlow(south_id, north_id, 2 * n + 4) << "\n";
	}

	return 0;
}

