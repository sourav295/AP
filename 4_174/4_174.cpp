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
	int min = numeric_limits<int>::max(), min_index;

	for (int v = 0; v < n; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}


void execute(int n, vector<City> map, int src_id, int dest_id, vector<int> tax) {

	//dijkstra
	vector<int> dist;
	vector<bool> sptSet;
	vector<int> preceedingId;//for backtracking

	for (int i = 0; i < n; i++){
		dist.push_back(numeric_limits<int>::max());
		sptSet.push_back(false);
		preceedingId.push_back(0);
	}

	dist[src_id-1] = 0;

	for (int i = 0; i < n; i++) {

		int u = minDistance(dist, sptSet, n);
		sptSet[u] = true;

		if (dest_id - 1 == u) {
			//backtrack
			stack<int> path;
			int current = dest_id;
			
			while (src_id != current) {
				path.push(current);
				current = preceedingId[current - 1];
			}

			cout << "From " << src_id << " to " << dest_id << " :\n";
			cout << "Path: "<<src_id;
			for (path; !path.empty(); path.pop())
				cout << "->" << path.top();
			cout << "\nTotal cost : " << dist[u]<<"\n";

			cout << "\n";
			break;
		}

		City c = map[u];
		for (c.neighbours; !c.neighbours.empty(); c.neighbours.pop()) {
			pair<int, int> id_dist = c.neighbours.front();
			int id = id_dist.first;//opposite end (relaxation)
			int d  = id_dist.second;//distance to the opposite end

			if (!sptSet[id - 1] && d != -1) {
				if (id == dest_id && (dist[u] + d) < dist[id - 1]) {
					dist[id - 1] = (dist[u] + d);
					preceedingId[id - 1] = u + 1;//u+1 => id
				}
				else if((dist[u] + d + tax[id - 1]) < dist[id - 1]){
					dist[id - 1] = (dist[u] + d + tax[id - 1]);
					preceedingId[id - 1] = u + 1;//u+1 => id
				}			
			}
		}

	}

	
}


int main()
{
	int M = 0;// no of cases
	string line;

	cin >> M;

	getline(cin, line);
	getline(cin, line);

	for (int case_no = 0; case_no < M; case_no++) {

		vector<City> map;
		vector<int> tax;

		int n = numeric_limits<int>::max();//number of columns
		int row_number = 0;
		do {
			
			getline(cin, line);
			map.push_back(
				cityFactory((row_number+1), line, n)//adjust row limit based on the column limit
			);
			row_number++;
		} while (row_number < n);

		for (int i = 0; i < n; i++) {
			int tax_instance;
			cin >> tax_instance;
			tax.push_back(tax_instance);
		}
		
		getline(cin, line);
			
		while (getline(cin, line) && line!="") {
			stringstream ss(line);
			int a, b;
			ss >> a;
			ss >> b;
			execute(n, map, a, b, tax);
		}	
	}



    return 0;
}

