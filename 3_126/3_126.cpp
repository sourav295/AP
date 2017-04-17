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
using namespace std;

const int n = 20;
bool world[n][n];
int dist[n];
bool sptSet[n];

pair<int, int> input[100];
int output[100];

bool srcExist(int srcId, int lastInputIndex) {
	bool ex = false;
	for (int i = 0; i < lastInputIndex; i++)
		if (input[i].first == srcId)
			return true;
	return false;
}


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




int dijkstra(int src)
{	
	for (int i = 0; i < n; i++){
		dist[i] = numeric_limits<int>::max();
		sptSet[i] = false;
	}
	
	dist[src] = 0;

	for (int count = 0; count < n; count++)
	{
		int u = minDistance();
		sptSet[u] = true;
		
		for (int v = 0; v < n; v++)
			if (!sptSet[v] && world[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + world[u][v] < dist[v])
				dist[v] = dist[u] + 1;
	}

	return 0;
}

void clearWorld() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			world[i][j] = false;
}


int main() {
	int count = 0;
	int test  = 0;

	string line;
	clearWorld();

	int N, x, y;

	while (getline(cin, line)) {
		
		stringstream ss(line);
		int n_neightbours;
		ss >> n_neightbours;

		int neightbour;
		for (int i = 0; i < n_neightbours; i++) {
			ss >> neightbour;
			neightbour--;
			world[neightbour][count] = true;
			world[count][neightbour] = true;
		}


		count++;
		if (count == n - 1) {
			
			count = 0;

			cin >> N;
			for (int i = 0; i < N; i++) {
				cin >> x >> y;
				x--;
				y--;
				input[i] = { x, y };
			}

			for (int i = 0; i < n; i++) {
				if (srcExist(i, N)) {
					dijkstra(i);
					for (int j = 0; j < n; j++) {
						if (input[j].first == i)
							output[j] = dist[input[j].second];
					}
				}
			}
			
			cout << "Test Set #" << ++test << "\n";
			for (int i = 0; i < N; i++) {
				printf("%2d to %2d: %2d\n", input[i].first + 1, input[i].second + 1, output[i]);
			}
			getline(cin, line);
			clearWorld();
		}
	}



}


