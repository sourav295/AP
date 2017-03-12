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

const int limit_cat  = 20;
const int limit_prob = 1000;
const int limit_size = limit_cat + limit_prob + 2;//the last 2 is for src and dest

bool graph[limit_size][limit_size];

int capacities[limit_size][limit_size];
int flow_passed[limit_size][limit_size];

int parent_list[limit_size];
int currentPathCapacity[limit_size];

enum NodeType {src, cat, prob, dest};

int addressMapper(int index, NodeType type, int n_cat, int n_prob) {
//maps the index in the node to the graph
	switch (type) {
	case src:
		return 0;
	case dest:
		return n_cat + n_prob + 1;
	case cat:
		return index;
	case prob:
		return n_cat + index;
	}
}



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
	int n_cat, n_prob;
	
	while (true) {
		cin >> n_cat >> n_prob;

		int n = n_cat + n_prob + 2;

		int sum_cap = 0;

		if (n_cat == 0 && n_prob == 0)
			break;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				graph[i][j] = false;
				flow_passed[i][j] = 0;
				capacities[i][j] = 0;
			}
		}

		int cat_size, prob_size, category_index, problem_index, dest_index;
		//join source to category
		for (int i = 1; i <= n_cat; i++) {
			cin >> cat_size;

			sum_cap += cat_size;

			graph[0][i]		 = true;
			graph[i][0] = true;
			capacities[0][i] = cat_size;
		}

		//join category to problem
		for (int i = 1; i <= n_prob; i++) {
			cin >> prob_size;
			problem_index = addressMapper(i, prob, n_cat, n_prob);
			for (int j = 1; j <= prob_size; j++) {
				//j is the problem index
				cin >> category_index;
			
				graph[category_index][problem_index]	  = true;
				graph[problem_index][category_index]      = true;
				
				capacities[category_index][problem_index] = 1;
			}
		}

		//join problem to sink
		dest_index = addressMapper(0, dest, n_cat, n_prob);
		for (int i = 1; i <= n_prob; i++) {
			problem_index = addressMapper(i, prob, n_cat, n_prob);

			graph[problem_index][dest_index] = true;
			graph[dest_index][problem_index] = true;

			capacities[problem_index][dest_index] = 1;
		}

		cout << (maxFlow(0, dest_index, n) == sum_cap) << "\n";
	}
	

    return 0;
}

