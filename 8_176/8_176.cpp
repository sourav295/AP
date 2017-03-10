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

const int n_limit = 100;
const int max_bandwith = 1000;

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

	parent_list[start] =  -2;
	currentPathCapacity[start] = max_bandwith;

	while (!q.empty()) {

		int u = q.front();
		q.pop();

		for (int v = 0; v < n; v++) {
			if (graph[u][v] && parent_list[v] == -1 && capacities[u][v] - flow_passed[u][v] > 0) {
				parent_list[v] = u;
				currentPathCapacity[v] = min(currentPathCapacity[u], capacities[u][v] - flow_passed[u][v]);

				if (u == end) {
					return currentPathCapacity[v];
				}
				q.push(v);
			}
		}
	}
}

int maxFlow(int start, int end, int n) {

	int maxFlow = 0;
	while (true) {
		int flow = bfs(start, end, n);


	}
}


int main()
{
    return 0;
}

