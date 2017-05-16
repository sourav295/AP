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
#include <stdlib.h>
using namespace std;

const int n_limit = 5002;

map<int, bool> nodeId_existinDJ;
int A[n_limit];

void Union(int element1, int element2);
void UnionSet(int set1, int set2);
int Find(int element);

int Find(int element) {
	if (A[element] < 0)
		return element;
	else
		return Find(A[element]);
}

void Union(int element1, int element2) {
	int root1 = Find(element1);
	int root2 = Find(element2);
	if (A[root1] < A[root2])
		UnionSet(root1, root2);
	else
		UnionSet(root2, root1);
}

void UnionSet(int set1, int set2) {
	A[set1] += A[set2];
	A[set2] = set1;
}


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

pair<long long, int> findPeopleToFire(int u, bool visited[] )//returns profit realized and no. of people fired
{
	if (!nodeId_existinDJ[u]) {
		return { 0, 0 };
	}


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
	while (1) {
		cin >> n >> m;
		//idCost_cache.clear();
		

		for (int i = 1; i <= n; i++) {
			cin >> cost;
			Node *node = new Node(cost, i);
			all_nodes[i] = node;
		}

		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			all_nodes[a]->subordinates.push_back(all_nodes[b]);
		}
		
		for (int j = 1; j <= n; j++)
			A[j] = -1;

		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < all_nodes[i]->subordinates.size(); j++) {
				int neighbouring_i= (all_nodes[i]->subordinates)[j]->id;
				if(Find(i)!=Find(neighbouring_i))
					Union(i, neighbouring_i);
			}
		}

		int count_dj = 0;
		queue<int> roots;
		for (int j = 1; j <= n; j++)
			if (A[j] < 0) {
				count_dj++;
				roots.push(j);
			}

		long long sum_profit = 0;
		int sum_fired = 0;

		for (roots; !roots.empty(); roots.pop()) {

			nodeId_existinDJ.clear();
			for (int i = 1; i <= n; i++)
				nodeId_existinDJ[i] = false;

			for (int i = 1; i <= n; i++) {
				if (Find(i) == roots.back()) {
					nodeId_existinDJ[i] = true;
				}
			}

			long long max_profit = 0;
			int min_fired = 0;

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

			if (max_profit > 0) {
				sum_profit += max_profit;
				sum_fired += min_fired;
			}

		}

		cout << (sum_fired) << " " << (sum_profit) << ("\n");

		break;
	}


    return 0;
}

