#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <set>
#include <algorithm>
#include <limits>
#include <sstream>
using namespace std;

const int n_limit = 105;
int cost[n_limit][n_limit];
int lvl[n_limit], sptSet[n_limit], dist[n_limit], minLvl[n_limit];

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



int dijkstra(int src, int V, int M)
{
	for (int i = 0; i < V; i++) {
		dist[i] = numeric_limits<int>::max();
		sptSet[i] = false;
		minLvl[i] = numeric_limits<int>::max();
	}

	dist[src] = 0;
	minLvl[src] = lvl[1];//destination monster

	for (int count = 0; count < V; count++)
	{
		int u = minDistance(V);
		sptSet[u] = true;

		if (u == 1)
			return dist[u];
		
		for (int v = 0; v < V; v++)
			if (!sptSet[v] && cost[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + cost[u][v] < dist[v] && abs(lvl[v] - minLvl[u])<=M ) {
				dist[v]   = dist[u] + cost[u][v];
				minLvl[v] = lvl[v] < minLvl[u] ? lvl[v] : minLvl[u];
			}
	}

	return -1;
}

int main()
{
	int M, N;
	int P, L, X;
	int T, V;


	while (cin >> M >> N) {
		for (int i = 1; i <= N; i++) {
			cin >> P >> L >> X;
			
			cost[0][i] = P;
			lvl[i] = L;

			for (int j = 0; j < X; j++) {
				cin >> T >> V;
				cost[T][i] = V;
			}
		}

		for (int i = 1; i <= N; i++) {
			if (abs(lvl[1] - lvl[i]) > M)
				for (int j = 0; j <= N; j++) {
					cost[i][j] = 0;
					cost[j][i] = 0;
				}
		}

		cout << dijkstra(0, N + 1, M) <<"\n";
	}


    return 0;
}

