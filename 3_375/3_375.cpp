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
using namespace std;


const int max_cap = 25;
const int n_bucks = 4;
const int n = max_cap*max_cap;

bool ingredient[n][n];
bool hasTarget[n];
bool visited[n];
int dist[n];
bool sptSet[n];

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

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a%b);
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
		/*
		if(T % gcd(gcd(gcd(cap[0], cap[1]), cap[2]), cap[3]) != 0) {
			cout << "-1\n";
			continue;
		}*/

		transition(state);
		cout << dijkstra(0, latest_id) << "\n";


	}


}


