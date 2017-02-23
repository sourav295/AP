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
	vector<pair<int, int>> reactions;
	vector<pair<bool, int>> results;

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


void execute(vector<Chemical> chemicals, int n) {
	
	for (int src = 0; src < n; src++){
	
		int dist[limit_n];
		bool sptSet[limit_n];
		int backtracker[limit_n];
	
		for (int i = 0; i < n; i++) {
			dist[i] = numeric_limits<int>::max();
			sptSet[i] = false;
		}
	
		dist[src] = 0;

		// Find shortest path for all vertices
		for (int count = 0; count < n; count++)
		{
			if (chemicals[src].results[count].first == true)
				continue;
		
			int u = minDistance(dist, sptSet, n);
			sptSet[u] = true;

			//backtrack and update----------------------------------------------
			int dest = u;
			int d = dest;
			while (d != src) {
				int s = backtracker[d];
				while (s != src) {
					chemicals[s].results[d] = { true, dist[d] - dist[s] };
					s = backtracker[s];
				}
				d = backtracker[d];
			}
			chemicals[src].results[dest] = { true, dist[dest] };
			//-------------------------------------------------------------------
		
			//RELAX---------------
			Chemical c = chemicals[u];
			for (int k =0; k < c.reactions.size(); k++) {
				int id = c.reactions[k].first;
				int h = c.reactions[k].second;
				if (!sptSet[id] && dist[u] != numeric_limits<int>::max() && dist[u] + h < dist[id]){
					dist[id] = dist[u] + h;
					backtracker[id] = u;
				}
			}
			//---------------------
		}
		
	}

	for (int i = 0; i < n; i++) {
		sort(chemicals[i].results.begin(), chemicals[i].results.end());
		int res_n = n;
		if (res_n % 2 != 0)
			cout << chemicals[i].results[res_n / 2].second << "\n";
		else
			cout << ((double)(chemicals[i].results[(res_n - 1) / 2].second + chemicals[i].results[(res_n) / 2].second)) / 2 << "\n";
	}
		 
	
	
}





int main()
{
	string line;
	queue<double> res;
	
	
	
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
				chemicals[i].reactions.push_back({ j, heat });
				chemicals[i].results.push_back({ false, 0 });
			}
		}
		execute(chemicals, n);
		getline(cin, line);
	}

    return 0;
}

