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

const int n_limit = 5002;


struct Node {
	long int cost;
	int id;
	vector<Node*> subordinates;

	Node(int c, int i) {
		cost = c;
		id = i;
	}

	Node(){}

};

vector<Node*> all_nodes(n_limit);

pair<long long, int> findPeopleToFire(int u, bool visited[])//returns profit realized and no. of people fired
{
	
	visited[u] = true;

	long long sum_profit = all_nodes[u]->cost;
	int n_fired = 1;
	for (int i = 0; i < all_nodes[u]->subordinates.size(); i++) {
		int id_subordinate = (all_nodes[u]->subordinates)[i]->id;
		if (!visited[id_subordinate]) {
			pair<long long, int> profitNuser_pair = findPeopleToFire(id_subordinate, visited);
			
			sum_profit += profitNuser_pair.first;
			n_fired += profitNuser_pair.second;
		}
	}

	return { sum_profit, n_fired };
}

void clearVisited(bool visited[], int n) {
	for (int j = 0; j < n + 2; j++)
		visited[j] = false;
}

int main()
{
	
	int n, m, cost;
	int a, b;
	while (cin >> n >> m) {
		
		//idCost_cache.clear();
		long long max_profit = 0;
		int min_fired = 0;


		for (int i = 1; i <= n; i++) {
			cin >> cost;
			Node *node = new Node(cost, i);
			all_nodes[i] = node;
		}

		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			all_nodes[a]->subordinates.push_back(all_nodes[b]);
		}
		
		for (int i = 1; i <= n; i++) {
			bool *visited = new bool[n + 2];
			clearVisited(visited, n);
			pair<long long, int> profitNuser_pair = findPeopleToFire(i, visited);

			long long sum_profit = profitNuser_pair.first;
			int n_fired = profitNuser_pair.second;

			if (sum_profit > max_profit) {
				max_profit = sum_profit;
				min_fired = n_fired;
			}
			else if (sum_profit == max_profit && n_fired < min_fired) {
				min_fired = n_fired;
			}
		}
		
		cout << min_fired << " " << max_profit << "\n";
		
	}


    return 0;
}

