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

struct Junction {

	
	int id;
	
	queue<pair<int, int>> neighbours;//id-distance
	
	Junction(int identity) {
		id = identity;
	}

};

int minDistance(vector<int> dist, vector<bool> sptSet, int n)
{
	int min = numeric_limits<int>::max(), min_index;

	for (int v = 0; v < n; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}


void execute(vector<Junction> all_junctions) {

	//dijkstra
	vector<int> dist;
	vector<bool> sptSet;

	int n = all_junctions.size();

	for (int i = 0; i < n; i++) {
		dist.push_back(numeric_limits<int>::max());
		sptSet.push_back(false);
	}

	dist[0] = 0;

	for (int i = 0; i < n; i++) {

		int u = minDistance(dist, sptSet, n);
		sptSet[u] = true;

		if (u == n - 1) {
			cout << dist[u]<<"\n";
			break;
		}
	

		Junction j = all_junctions[u];
		for(j.neighbours; !j.neighbours.empty(); j.neighbours.pop()){
			pair<int, int> id_dist = j.neighbours.front();
			int id = id_dist.first;
			int d = id_dist.second;

			if (!sptSet[id] && dist[u] + d < dist[id])
				dist[id] = dist[u] + d;
		}

	}

}



int main()
{
	string line;
	while (getline(cin, line)) {

		stringstream ss(line);
		int n, r;
		ss >> n;
		ss >> r;

		vector<Junction> all_junctions;
		for (int i = 0; i < n; i++)
			all_junctions.push_back(Junction(i));

		for (int i = 0; i < r; i++) {
			int a, b, dist;
			cin >> a >> b >> dist;
			all_junctions[a].neighbours.push({ b, dist });
			all_junctions[b].neighbours.push({ a, dist });
		}

		execute(all_junctions);

		getline(cin, line);
	}
	
	return 0;
}

