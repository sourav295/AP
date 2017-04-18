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

const int n_limit = 501;
int n;

int sptSet[n_limit], dist[n_limit];
int park[n_limit][n_limit];

int minDistance()
{
	// Initialize min value
	int min = numeric_limits<int>::max();
	int min_index;

	for (int v = 0; v < n; v++)
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}

	return min_index;
}

int dijkstra(int src, int dest)
{
	for (int i = 0; i < n; i++) {
		dist[i] = numeric_limits<int>::max();
		sptSet[i] = false;
	}

	dist[src] = 0;

	for (int count = 0; count < n; count++)
	{
		int u = minDistance();
		sptSet[u] = true;

		if (u == dest)
			return dist[dest];

		for (int v = 0; v < n; v++)
			if (!sptSet[v] && park[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + park[u][v] < dist[v])
				dist[v] = dist[u] + park[u][v];
	}

	return 0;
}

int main()
{
	string line;
	int count = 1;
	int r;

	while (cin >> n >> r) {
		for (int i = 0; i < r; i++) {
			int a, b, d;
			cin >> a >> b >> d;

			if (a == 0 && b == n - 1)
				continue;

			park[a][b] = d;
			park[b][a] = d;
			
		}

		int res = dijkstra(0, n - 1);
		cout << "Set #" << count++ << "\n";
		if(res != numeric_limits<int>::max() && res != 0){
			cout << res << "\n";
		}
		else {
			cout << "?\n";
		}

	}


	
	return 0;
}

