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
#include <sstream>
#include <map>
using namespace std;

map<string, int> place_id;


const int n_limit = 100;

int sptSet[n_limit], dist[n_limit];
int college[n_limit][n_limit];
int backTrack[n_limit];

string place_array[n_limit];

int minDistance(int n)
{
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

void dijkstra(int src, int dest, int n)
{
	for (int i = 0; i < n; i++) {
		dist[i] = numeric_limits<int>::max();
		sptSet[i] = false;
	}

	dist[src] = 0;

	for (int count = 0; count < n; count++)
	{
		int u = minDistance(n);
		sptSet[u] = true;
		if (u == dest)
			return;

		for (int v = 0; v < n; v++)
			if (!sptSet[v] && college[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + college[u][v] < dist[v]) {
				dist[v] = dist[u] + college[u][v];
				backTrack[v] = u;
			}

	}

	
}



int main()
{
	int n, m;
	int dist1, dist2, indA, indB;


	while (cin >> n) {
		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				college[i][j] = 0;
		
		
		string place, link;
		cin >> place;
		for (int i = 0; i < n; i++) {
			place_id[place] = i;
			place_array[i] = place;
		}
		cin >> m;
		for (int i = 0; i < m; i++) {
			cin >> link;
			stringstream ss(link);
			ss >> place;
			ss >> dist1;
		
			indA = place_id[place.substr(0, place.find(":"))];
			indB = place_id[place.substr(place.find(":") + 1, place.length())];

			college[indA][indB] = dist1;
			if (ss >> dist2) {
				college[indB][indA] = dist2;
			}

		}
		dijkstra(place_id["office"], place_id["hall"], N);

	}
	
    return 0;
}

