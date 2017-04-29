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

		if (u == -1)
			return 0;

		sptSet[u] = true;

		if (u == dest)
			return dist[dest];

		for (int v = 0; v < n; v++)
			if (!sptSet[v] && park[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + park[u][v] < dist[v] && !(u == src && v == dest)) {
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
		
		int minDirect_d = numeric_limits<int>::max();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				park[i][j] = 0;

		for (int i = 0; i < r; i++) {
			int a, b, d;
			cin >> a >> b >> d;

			park[a][b] = d;
			park[b][a] = d;

			if (a == 0 && b == n - 1 && d < minDirect_d) {
				minDirect_d = d;
			}

		}
		int dest = n - 1;

		int candidate1 = numeric_limits<int>::max();
		if (minDirect_d < candidate1) {//there is a link between src and dest
			int minlink_intermediate = candidate1;
			for (int i = 0; i < n; i++) {
				if (park[0][i] > 0 && park[0][i] < minlink_intermediate)
					minlink_intermediate = park[0][i];
			}
			candidate1 = minDirect_d + 2 * minlink_intermediate;
		}

		
		int res = dijkstra(0, dest);
		cout << "Set #" << count++ << "\n";
		if((res != numeric_limits<int>::max() && res != 0) || candidate1 != numeric_limits<int>::max()){
			cout << (res < candidate1 ? res:candidate1) << "\n";
		}
		else {
			cout << "?\n";
		}

	}


	
	return 0;
}

