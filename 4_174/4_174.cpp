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
using namespace std;


struct City {

	int id;
	queue<pair<int, int>> neighbours;//id-distance

	City(int identity, queue<int> distances) {
		id = identity;

		int i = 1;
		for (distances; !distances.empty(); distances.pop()) {
			neighbours.push({ i, distances.front() });
			i++;
		}
	}
};


City cityFactory(int id, string line, int &n) {
	stringstream ss(line);
	int distance;
	queue<int> distances;
	while (ss >> distance) {
		distances.push(distance);
	}

	n = distances.size();

	return City(id, distances);

}

int minDistance(vector<int> dist, vector<bool> sptSet, int n)
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < n; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}


void execute(int n, vector<City> map, int src_id, int dest_id) {

	//dijkstra
	vector<int> dist;
	vector<bool> sptSet;
	vector<int> preceedingId;

	for (int i = 0; i < n; i++){
		dist.push_back(INT_MAX); 
		sptSet.push_back(false);
		preceedingId.push_back(0);
	}

	dist[src_id-1] = 0;

	for (int i = 0; i < n; i++) {

		int u = minDistance(dist, sptSet, n);
		sptSet[u] = true;

		if (dest_id - 1 == u) {
			cout << dist[u];
			break;
		}

		City c = map[u];
		for (c.neighbours; !c.neighbours.empty(); c.neighbours.pop()) {
			pair<int, int> id_dist = c.neighbours.front();
			int id = id_dist.first;
			int d  = id_dist.second;

			if (!sptSet[id - 1] && (dist[u] + d) < dist[id - 1] && d != -1) {
				dist[id - 1] = (dist[u] + d);
				preceedingId[id - 1] = u + 1;//u+1 => id
			}
		}

	}

	stack<int> path;
	//do backtrack
}


int main()
{
	int M = 0;// no of cases
	string line;

	cin >> M;

	getline(cin, line);

	for (int case_no = 0; case_no < M; case_no++) {

		vector<City> map;

		int n = INT_MAX;//number of columns
		int row_number = 0;
		do {
			
			getline(cin, line);
			map.push_back(
				cityFactory((row_number+1), line, n)//adjust row limit based on the column limit
			);
			row_number++;
		} while (row_number < n);
	
		execute(n, map, 1, 3);
	}



    return 0;
}

