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

struct Chemical {
	queue<pair<int, int>> reactions;
	vector<int> results;

};

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


double execute(Chemical chemicals[], int src, int n) {
	int dist[limit_n];
	bool sptSet[limit_n];
	
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

		chemicals[src].results.push_back(dist[u]);
		
		Chemical c = chemicals[u];
		for (c.reactions; !c.reactions.empty(); c.reactions.pop()) {
			int id = c.reactions.front().first;
			int h = c.reactions.front().second;
			if (!sptSet[id] && dist[u] != numeric_limits<int>::max() && dist[u] + h < dist[id])
				dist[id] = dist[u] + h;
		}	
	}

	sort(chemicals[src].results.begin(), chemicals[src].results.end());
	
	int res_n = n;
	if (res_n % 2 != 0)
		return chemicals[src].results[res_n / 2];
	else
		return ((double)(chemicals[src].results[(res_n-1) / 2] + chemicals[src].results[(res_n) / 2]))/2;
}





int main()
{
	string line;
	queue<double> res;
	
	Chemical chemicals[limit_n];
	
	while (getline(cin, line)) {
		int n;
		stringstream ss(line);
		ss >> n;

		
		for (int i = 0; i < n; i++)
			chemicals[i] = Chemical();

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int heat;
				cin >> heat;
				chemicals[i].reactions.push({ j, heat });
			}
		}
		for (int i = 0; i < n; i++) {
			res.push(execute(chemicals, i, n));
		}
		getline(cin, line);
	}
	for (res; !res.empty(); res.pop()) {
		cout << res.front() << "\n";
	}

    return 0;
}

