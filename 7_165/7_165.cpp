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
#include<math.h>
using namespace std;


const int n_limit = 1000;


int X[n_limit], Y[n_limit];
int graph[n_limit][n_limit];


int minDistance(int dist[], bool sptSet[], int n)
{
	// Initialize min value
	int min = numeric_limits<int>::max();
	int min_index;

	for (int v = 0; v < n; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

int dijkstra(int n)
{
	int dist[n_limit];
	bool sptSet[n_limit];
	for (int i = 0; i < n; i++){
		dist[i] = numeric_limits<int>::max();
		sptSet[i] = false;
	}

	dist[0] = 0;
	for (int count = 0; count < n; count++)
	{
		int u = minDistance(dist, sptSet, n);
		sptSet[u] = true;

		if (u == 1) {
			return dist[u];
		}
			

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < n; v++)
			if (!sptSet[v] && graph[u][v] && dist[u] != numeric_limits<int>::max()) {
				int max_fromIncoming = graph[u][v] > dist[u] ? graph[u][v] : dist[u];
				
				if (dist[v] == numeric_limits<int>::max()) {
					dist[v] = max_fromIncoming;
				}
				else if (max_fromIncoming < dist[v]) {
					dist[v] = max_fromIncoming;
				}
			}
	}

	return 0;
}




int main()
{
	string line;
	int test = 1;
	while (true) {
		int N;
		cin >> N;

		if (N == 0)
			break;

		for (int i = 0; i < N; i++) {
			int x, y;
			cin >> x >> y;
			X[i] = x;
			Y[i] = y;
		}

		getline(cin, line);
		getline(cin, line);

		int count = 0;
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++) {
				int d = pow(X[i] - X[j], 2) + pow(Y[i] - Y[j], 2);
				graph[i][j] = d;
				graph[j][i] = d;
			}
				//edges[count++] = Edge(i, j, pow(X[i] - X[j], 2) + pow(Y[i] - Y[j], 2));

		if (test > 1)
			cout << "\n";

		cout << "Scenario #" << test++ << "\n";
		printf("Frog Distance = %.3f\n", sqrt(dijkstra(N)));

	}





	return 0;
}

