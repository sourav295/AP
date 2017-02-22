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

struct Chemical {
	queue<pair<int, int>> reactions;
	vector<int> results;

};



int minDistance(vector<int> dist, vector<bool> sptSet)
{
	int min = numeric_limits<int>::max();
	int min_index;

	int V = dist.size();

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min){
			min = dist[v];
			min_index = v;
		}

	return min_index;
}


void execute(vector<Chemical> chemicals, int src) {
	vector<int> dist;
	vector<bool> sptSet;
	
	int V = chemicals.size();

	for (int i = 0; i < V; i++) {
		dist.push_back(numeric_limits<int>::max());
		sptSet.push_back(false);
	}
	
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V; count++)
	{
		int u = minDistance(dist, sptSet);
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
	
	int res_n = chemicals[src].results.size();
	if (res_n % 2 != 0)
		cout << chemicals[src].results[res_n / 2];
	else
		cout << ((double)(chemicals[src].results[(res_n-1) / 2] + chemicals[src].results[(res_n) / 2]))/2;
	cout << "\n";

}





int main()
{
	string line;
	while (getline(cin, line)) {
		int n;
		stringstream ss(line);
		ss >> n;

		vector<Chemical> chemicals;
		for (int i = 0; i < n; i++)
			chemicals.push_back(Chemical());

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int heat;
				cin >> heat;
				chemicals[i].reactions.push({ j, heat });
			}
		}
		for (int i = 0; i < n; i++) {
			execute(chemicals, i);
		}
		getline(cin, line);
	}


    return 0;
}

