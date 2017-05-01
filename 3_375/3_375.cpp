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

	void addState(array<int, 4> new_state) {
		if (!existInMap(new_state)) {
			Node * newNode = new Node(new_state);
			next.push_back(newNode);

			all_states[new_state] = newNode;
			all_nodes.push_back(newNode);

			for (int i = 0; i < n_bucks; i++)
				if (new_state[i] == T) {
					newNode->target = true;
					cout << "T";
				}

			if(!(newNode->target))
				constructGraph(newNode);
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

	array<int, 4> new_state;
	for (int i = 0; i < n_bucks; i++) {
		if (n->can_fill(i)) {
			new_state = n->copyState();
			new_state[i] = capacities[i];
			n->addState(new_state);
		}
		
		if (n->can_empty(i)) {
			new_state = n->copyState();
			new_state[i] = 0;
			n->addState(new_state);
		}

		for (int j = 0; j < n_bucks; j++) {
			if (i == j)
				continue;
			
			int measure = n->can_pour(i, j);
			if (measure > 0) {
				new_state = n->copyState();
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
		all_nodes[u]->visited == true;

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

	T = 4;
	capacities = { 1, 2, 3, 5 };
	constructGraph(initial);
	minimumDistance = numeric_limits<int>::max();
	dijkstra();
	cout << minimumDistance;

	cout << "!";

	return 0;
}


/*
const int max_cap = 25;
const int n_bucks = 4;
const int n = max_cap*max_cap;

bool ingredient[n][n];
bool hasTarget[n];
bool visited[n];
int dist[n];
bool sptSet[n];


struct Node{


};

int cap[n_bucks];

int T;
map<string, int> state_loc;
int latest_id;

int minDistance(int V)
{
	// Initialize min value
	int min = numeric_limits<int>::max();
	int min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}

	return min_index;
}




int dijkstra(int src, int V)
{
	for (int i = 0; i < V; i++) {
		dist[i] = numeric_limits<int>::max();
		sptSet[i] = false;
	}

	dist[src] = 0;

	for (int count = 0; count < V; count++)
	{
		int u = minDistance(V);
		sptSet[u] = true;

		if (hasTarget[u])
			return dist[u];

		for (int v = 0; v < V; v++)
			if (!sptSet[v] && ingredient[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + ingredient[u][v] < dist[v])
				dist[v] = dist[u] + ingredient[u][v];
	}

	return -1;
}

void clearingredient() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ingredient[i][j] = false;
}


int getId(vector<int> s) {
	string stateString = "";
	for (int i = 0; i < n_bucks; i++) {
		if (s[i] / 10 == 0)
			stateString += "0";
		
		stateString += s[i];
	}
	
	if (state_loc.find(stateString) == state_loc.end())
		state_loc[stateString] = latest_id++;

	return state_loc[stateString];
}


bool can_fill(vector<int> s, int bucket) {
	return s[bucket] < cap[bucket];
}

bool can_empty(vector<int> s, int bucket) {
	return s[bucket] > 0;
}

int can_pour(vector<int> s, int from, int to) {
	int measure = s[from] < (cap[to] - s[to]) ? s[from] : (cap[to] - s[to]);
	return measure;
}

void transition(vector<int> s) {
	int id = getId(s);
	if (visited[id])
		return;
	visited[id] = true;

	
	for (int i = 0; i < n_bucks; i++) {
		if (s[i] == T) {
			hasTarget[id] = true;
			return;
		}
	}


	vector<int> temp;

	for (int i = 0; i < n_bucks; i++) {
		if (can_fill(s, i)) {
			temp = s;
			temp[i] = cap[i];
			
			ingredient[id][getId(temp)] = true;

			transition(temp);
		}

		if(can_empty(s, i)) {
			temp = s;
			temp[i] = 0;
			
			ingredient[id][getId(temp)] = true;

			transition(temp);
		}
	}

	for(int i = 0; i < n_bucks; i++)
		for (int j = 0; j < n_bucks; j++) {
			if (i != j && can_pour(s, i, j) > 0) {
				int m = can_pour(s, i, j);
				
				temp = s;
				temp[i] -= m;
				temp[j] += m;
				
				ingredient[id][getId(temp)] = true;

				transition(temp);
			}
		}

}

int main() {
	int id;
	while (cin >> cap[0] >> cap[1] >> cap[2] >> cap[3] >> T) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				ingredient[i][j] = false;
			visited[i] = false;
			hasTarget[i] = false;
		}
		latest_id = 0;
		state_loc.clear();

		vector<int> state(n_bucks);
		int max_cap = 0;
		for (int i = 0; i < n_bucks; i++) {
			if (cap[i] > max_cap) {
				max_cap = cap[i];
			}
		}

		if (max_cap < T) {
			cout << "-1\n";
			continue;
		}
		

		transition(state);
		cout << dijkstra(0, latest_id) << "\n";


	}


}


*/