#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <set>
#include <algorithm>
#include <sstream>
#include <limits>
#include <iomanip>
#include <map>
#include <array>
using namespace std;

const int n_bucks = 4;
int T;
array<int, 4> capacities = { 0, 0, 0, 0 };

struct Node;
void constructGraph(Node *n);

map<array<int, 4>, Node*> all_states;
vector<Node*> all_nodes;

int minimumDistance = numeric_limits<int>::max();

bool existInMap(array<int, 4> t) {
	return !(all_states.count(t) == 0);
}

struct Node {
	int state[n_bucks];
	bool visited;
	bool target = false;

	vector<Node*> next;

	int distance;

	Node(array<int, 4> s) {
		for (int i = 0; i < n_bucks; i++) {
			state[i] = s[i];
		}
		distance = numeric_limits<int>::max();
		visited = false;
	}

	bool can_fill(int bucket_id) {
		return state[bucket_id] < capacities[bucket_id];
	}

	bool can_empty(int bucket_id) {
		return state[bucket_id] > 0;
	}

	int can_pour( int from, int to) {
		int measure = state[from] < (capacities[to] - state[to]) ? state[from] : (capacities[to] - state[to]);
		return measure;
	}

	array<int, 4> copyState() {
		array<int, 4> new_state = { 0, 0, 0 , 0 };
		for (int i = 0; i < n_bucks; i++)
			new_state[i] = state[i];
		return new_state;
	}

	void relax(array<int, 4> new_state) {
		if (distance + 1 < all_states[new_state]->distance)
			all_states[new_state]->distance = distance + 1;
	}


	void addState(array<int, 4> new_state) {
		if (!existInMap(new_state)) {
			Node * newNode = new Node(new_state);

			all_states[new_state] = newNode;
			all_nodes.push_back(newNode);

			relax(new_state);

			for (int i = 0; i < n_bucks; i++)
				if (new_state[i] == T) {
					newNode->target = true;
					if (newNode->distance < minimumDistance)
						minimumDistance = newNode->distance;
				}

			if (!all_states[new_state]->target)
				constructGraph(all_states[new_state]);
		}
		else {
			relax(new_state);
		}

		next.push_back(all_states[new_state]);
	}


};



int minDistance()
{
	// Initialize min value
	int min = numeric_limits<int>::max();
	int min_index;

	for (int i = 0; i < all_nodes.size(); i++) {
		if (all_nodes[i]->visited == false && all_nodes[i]->distance <= min) {
			min = all_nodes[i]->distance;
			min_index = i;
		}

	}

	return min_index;
}



void constructGraph(Node *n) {
	if (n->distance > minimumDistance)
		return;
	
	for (int i = 0; i < n_bucks; i++) {
		if (n->can_fill(i)) {
			array<int, 4> new_state = n->copyState();
			new_state[i] = capacities[i];
			n->addState(new_state);
		}
	}

	for (int i = 0; i < n_bucks; i++) {
		if (n->can_empty(i)) {
			array<int, 4> new_state = n->copyState();
			new_state[i] = 0;
			n->addState(new_state);
		}
	}

	for (int i = 0; i < n_bucks; i++) {
		for (int j = 0; j < n_bucks; j++) {
			if (i == j)
				continue;
			
			int measure = n->can_pour(i, j);
			if (measure > 0) {
				array<int, 4> new_state = n->copyState();
				new_state[i] -= measure;
				new_state[j] += measure;
				n->addState(new_state);
			}
		}
	}

}

int dijkstra()
{
	for (int count = 0; count < all_nodes.size(); count++)
	{
		int u = minDistance();
		all_nodes[u]->visited = true;

		if (all_nodes[u]->distance > minimumDistance)
			continue;

		if (all_nodes[u]->target && (all_nodes[u]->distance) < minimumDistance)
			minimumDistance = (all_nodes[u]->distance);

		for (int i = 0; i < all_nodes[u]->next.size(); i++) {
			Node *v = all_nodes[u]->next[i];
			if (v->visited == false && all_nodes[u]->distance != numeric_limits<int>::max() && all_nodes[u]->distance + 1 < v->distance)
				v->distance = all_nodes[u]->distance + 1;
		}
	}

	return -1;
}

int main() {

	array<int, 4> initial_arr = { 0, 0, 0, 0 };
	Node *initial = new Node(initial_arr);
	initial->distance = 0;
	
	all_states[initial_arr] = initial;
	all_nodes.push_back(initial);

	T = 20;
	capacities = { 22, 23, 5, 25 };
	minimumDistance = numeric_limits<int>::max();
	constructGraph(initial);
	
	if (minimumDistance == numeric_limits<int>::max())
		cout << -1;
	else {
		dijkstra();
		cout << minimumDistance;
	}



	return 0;
}

