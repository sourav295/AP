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
using namespace std;


const int limit_n = 1000;



int minDistance(int dist[], bool sptSet[], int V)
{
	int min = numeric_limits<int>::max();
	int min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min){
			min = dist[v];
			min_index = v;
		}

	return min_index;
}


void execute(int **chemicals, int n) {
	
	int dist[limit_n];
	bool sptSet[limit_n];
	int results[limit_n];

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
			//chemicals[src][u] = dist[u];
			results[u] = dist[u];
			//RELAX---------------
			//Chemical c = chemicals[u];
			for (int k = 0; k < n; k++) {
				int id = k;
				int h = chemicals[u][k];
				if (!sptSet[id] && dist[u] != numeric_limits<int>::max() && dist[u] + h < dist[id]) {
					dist[id] = dist[u] + h;
				}
			}
		}

		sort(results, results + n);
		if (n % 2 != 0)
			cout << results[n / 2] << "\n";
		else
			cout << ((double)(results[(n - 1) / 2] + results[(n) / 2])) / 2 << "\n";
	}	
}





int main()
{
	string line;
	//int chemicals[limit_n][limit_n];
	
	int **chemicals = new int*[limit_n];
	for (int i = 0; i < limit_n; i++)
		chemicals[i] = new int[limit_n];
	
	while (getline(cin, line)) {
		int n;
		stringstream ss(line);
		ss >> n;

		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				unsigned short heat;
				cin >> heat;
				chemicals[i][j] = heat;
			}
		}
		execute(chemicals, n);
		getline(cin, line);
	}

    return 0;
}

