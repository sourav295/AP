#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <set>
#include <stack>
#include <limits>
#include<math.h>
#include <sstream>
using namespace std;

const int limit_n = 100;
const int limit_m = 10000;



int minDistance(int dist[], bool sptSet[], int V)
{
	int min = numeric_limits<int>::max();
	int min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}

	return min_index;
}


void execute(int **cities, int n) {

	int dist[limit_n];
	bool sptSet[limit_n];
	int results[limit_n];

	for (int i = 0; i < n; i++)
		results[i] = 0;

	for (int src = 0; src < n; src++) {

		for (int i = 0; i < n; i++) {
			dist[i] = numeric_limits<int>::max();
			sptSet[i] = false;
		}
		
		dist[src] = 0;

		// Find shortest path for all vertices
		for (int count = 0; count < n; count++)
		{
			int u = minDistance(dist, sptSet, n);
			sptSet[u] = true;
			
			results[src] += dist[u];
			//RELAX---------------
			for (int w = 0; w < n; w++) {
				if (!sptSet[w] && cities[u][w] > 0 && dist[u] != numeric_limits<int>::max() && dist[u] + cities[u][w] < dist[w]) {
					dist[w] = dist[u] + cities[u][w];
				}
			}
		}

		

	}

	int min = numeric_limits<int>::max();
	int index;
	for (int src = 0; src < n; src++) {
		if (results[src] < min) {
			min = results[src];
			index = src;
		}
	}

	cout << index + 1<<"\n";
}





int main()
{
	string line;
	//int chemicals[limit_n][limit_n];

	int **cities = new int*[limit_n];
	for (int i = 0; i < limit_n; i++)
		cities[i] = new int[limit_n];

	while (getline(cin, line)) {
		int n;
		int m;
		stringstream ss(line);
		ss >> n;
		ss >> m;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cities[i][j] = 0;

		for (int i = 0; i < m; i++) {
			int u, w, distance;
			cin >> u >> w >> distance;
			u--;
			w--;
			cities[u][w] = distance;
			cities[w][u] = distance;
		}
		execute(cities, n);
		getline(cin, line);
	}

    return 0;
}

