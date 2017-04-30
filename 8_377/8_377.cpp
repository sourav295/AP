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

const int n_limit = 5002;
long long max_profit = 0;
int n_peopleToFire = 0;


struct Node {
	int cost;
	int id;
	vector<Node*> subordinates;

	Node(int c, int i) {
		cost = c;
		id = i;
	}

	Node(){}

};
vector<Node*> all_nodes(n_limit);

void findPeopleToFire(int u, int d, bool visited[], int path[], int &path_index, long long profit)
{
	visited[u] = true;
	path[path_index] = u;
	path_index++;

	if (u == d)
	{
		if (profit > max_profit) {
			max_profit = profit;
			n_peopleToFire = path_index - 2;
		}
	}
	else
	{
		for (int i = 0; i < all_nodes[u]->subordinates.size(); i++) {
			int id_subordinate = (all_nodes[u]->subordinates)[i]->id;
			if (!visited[id_subordinate]) {
				findPeopleToFire(id_subordinate, d, visited, path, path_index, profit + all_nodes[id_subordinate]->cost);
			}
		}
	}

	path_index--;
	visited[u] = false;
}


int main()
{
	
	int n, m, cost;
	int a, b;
	while (cin >> n >> m) {
		//all_nodes.clear();

		Node *start = new Node(0, 0);
		Node *end   = new Node(0, n+1);

		all_nodes[0]   = start;
		all_nodes[n+1] = end;

		for (int i = 1; i <= n; i++) {
			cin >> cost;
			Node *node = new Node(cost, i);
			all_nodes[i] = node;
			all_nodes[0]->subordinates.push_back(node);
		}

		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			all_nodes[a]->subordinates.push_back(all_nodes[b]);
		}
		//join end to all last ones
		for (int i = 1; i <= n; i++) {
			if(all_nodes[i]->subordinates.size() == 0)
				all_nodes[i]->subordinates.push_back(all_nodes[n+1]);
		}

		bool *visited = new bool[n+2];
		int *path = new int[n+2];
		int path_index = 0;
		for (int i = 0; i < n+2; i++)
			visited[i] = false;
		max_profit = 0;
		n_peopleToFire = 0;

		findPeopleToFire(0, n+1, visited, path, path_index, 0);
		cout << n_peopleToFire << " " << max_profit << "\n";
	}


    return 0;
}

