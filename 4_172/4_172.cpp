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

const int n_limit = 506;
int n;

int sptSet[n_limit], dist[n_limit];
int park[n_limit][n_limit];

int minDistance()
{
	// Initialize min value
	int min = numeric_limits<int>::max();
	int min_index = -1;

	for (int v = 0; v < n; v++) {
		if (sptSet[v] == false && dist[v] <= min) {
			
			min = dist[v];
			min_index = v;
		}
	}

	return min_index;
}

int dijkstra(int src, int dest, bool excld_direct = false)
{
	for (int i = 0; i < n; i++) {
		dist[i] = numeric_limits<int>::max();
		sptSet[i] = false;
	}

	dist[src] = 0;

	for (int count = 0; count < n; count++)
	{
		int u = minDistance();

		if (u == -1)
			return 0;

		sptSet[u] = true;

		if (u == dest)
			return dist[dest];

		for (int v = 0; v < n; v++)
			if (!sptSet[v] && park[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + park[u][v] < dist[v] ) {
				if((!excld_direct) || (excld_direct && !(u == src && v == dest)))
					dist[v] = dist[u] + park[u][v];
			}
				
	}

	return numeric_limits<int>::max();
}

int main()
{
	string line;
	int count = 1;
	int r;

	while (cin >> n >> r) {
		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				park[i][j] = 0;

		for (int i = 0; i < r; i++) {
			int a, b, d;
			cin >> a >> b >> d;

			park[a][b] = d;
			park[b][a] = d;

			
		}
		int dest = n - 1;

		int res = dijkstra(0, dest, true);

		for (int i = 0; i < n; i++) {
			if (park[0][i] > 0 && i != dest) {
				int potential = park[0][i] + dijkstra(i, dest);
				if (potential < res)
					res = potential;
			}

		}


		cout << "Set #" << count++ << "\n";
		if(res != numeric_limits<int>::max()){
			cout << res << "\n";
		}
		else {
			cout << "?\n";
		}

	}


	
	return 0;
}

