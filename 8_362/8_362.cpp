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

const int max_coord = 100;
const int n_limit   = (2* max_coord + 1) + 2;//2 more for source and destination

pair<int, int> coordinates[max_coord];
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

int main()
{
	int L, W, n, d;
	int x, y;
	while (true) {
		cin >> L >> W >> n >> d;
		if (L == 0 && W == 0 && n == 0 && d == 0)
			break;

		int north_id	= 0;
		int south_id	= (2 * n);
		int d_sq		= d*d;

		for (int i = 1; i <=n; i++) {
			cin >> x >> y;
			if (y + d >= W) {
				//connect to north
				graph[i][north_id] = true;
				graph[north_id][i] = true;

				capacities[north_id][i] = 1;
			}

			if (y - d <= 0) {
				//connect to south
				graph[i][south_id] = true;
				graph[south_id][i] = true;

				capacities[south_id][i] = 1;
				capacities[i][south_id] = 1;
			}

			coordinates[i - 1] = { y , x };//sort by y and then x
		}

		sort(begin(coordinates), end(coordinates));
		for (int i = 0; i < n; i++) {
			int u_x = coordinates[i].second;
			int u_y = coordinates[i].first;

			for (int j = i + 1; j < n; j++) {
				int v_x = coordinates[j].second;
				int v_y = coordinates[j].first;

				//check if out of range
				if (v_y > u_y + d)
					break;

				if (v_x > u_x + d)
					continue;

				//check if actually in range
				int dist = (u_x - v_x)*(u_x - v_x) - (u_x - v_x)*(u_x - v_x);



			}


		}



	}


    return 0;
}

