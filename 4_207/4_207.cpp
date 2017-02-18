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
using namespace std;

struct Place {

	int id;
	string name;
	vector<pair<int, int>> id_dist;

	Place(string n, int identity) {
		name = n;
		id = identity;
	}
};

int minDistance(vector<int> dist, vector<bool> sptSet)
{
	// Initialize min value
	int min = numeric_limits<int>::max();
	int min_index;

	for (int v = 0; v < dist.size(); v++)
		if (sptSet[v] == false && dist[v] <= min){
			min = dist[v]; 
			min_index = v;
		}

	return min_index;
}


stack<Place> execute(vector<Place> &nodes, int index_src, int index_dest, int &distance) {
	int n = nodes.size();

	vector<int> dist;
	vector<bool> sptSet;
	vector<int> preceeding_id;
	for (int i = 0; i < n; i++){
		dist.push_back(numeric_limits<int>::max());
		sptSet.push_back(false);
		preceeding_id.push_back(0);
	}
	dist[index_src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < n ; count++)
	{
		int u = minDistance(dist, sptSet);
		sptSet[u] = true;

		if (u == index_dest) {
			distance = dist[u];
			stack<Place> path;
			int currentId = u;

			while (currentId != index_src) {
				path.push(nodes[currentId]);
				currentId = preceeding_id[currentId];
			}

			path.push(nodes[currentId]);

			return path;
		}
		
		Place p = nodes[u];
		
		//Relaxation
		for (int k = 0; k < p.id_dist.size(); k++) {
			int other_nodeId = p.id_dist[k].first;
			int dist_toNode  = p.id_dist[k].second;

			if (!sptSet[other_nodeId] && dist[u] != numeric_limits<int>::max() && dist[u] + dist_toNode < dist[other_nodeId]) {
				dist[other_nodeId] = dist[u] + dist_toNode;
				preceeding_id[other_nodeId] = u;
			}

		}
	}

	stack<Place> empty;
	return empty;

}



int main()
{
	bool first = true;
	string start = "office";
	string end = "hall";

	string input;
	while(getline(cin, input)){

		if (first)
			first = false;
		else
			cout << "\n";
		
		int n;
		stringstream node_count(input);
		node_count >> n;
	
		string place;
		int index_src = 0;
		int index_dest = 0;

		//getline(cin, place);//blank
	
		vector<Place> nodes;
		for (int i = 0; i < n; i++) {
			getline(cin, place);
			nodes.push_back(Place(place, i));

			if (!place.compare(start))
				index_src = i;
			if (!place.compare(end))
				index_dest = i;
		}
	
		int n_roads;
		cin >> n_roads;

		getline(cin, place);//blank

		for (int i = 0; i < n_roads; i++) {
			string road;
			getline(cin, road);
		
			int indexOfDigit = -1;
			for (int j = 0; j < road.length(); j++)
			{
				if (isdigit(road.at(j)))
				{
					indexOfDigit = j;
					break;
				}
			}
			string places = road.substr(0, indexOfDigit - 1);
			string num = road.substr(indexOfDigit, road.length() - indexOfDigit);
		
			stringstream ss_places(places);
			stringstream ss_nums(num);
			string p1 = "";
			string p2 = "";
			int d1;
			int d2;

			getline(ss_places, p1, ':');
			getline(ss_places, p2);
		
			int index_p1 = 0;
			int index_p2 = 0;
			bool found_p1 = false;
			bool found_p2 = false;

			for (int j = 0; j < n; j++) {
				if (!found_p1 && !p1.compare(nodes[j].name)) {
					index_p1 = j;
					found_p1 = true;
				}
				if (!found_p2 && !p2.compare(nodes[j].name)){
					index_p2 = j;
					found_p2 = true;
				}

				if (found_p1 && found_p2)
					break;
			}
		
		
			ss_nums >> d1;
		
			if (ss_nums >> d2) {
				//bi-directional
				nodes[index_p2].id_dist.push_back({ index_p1, d2 });
			}
			nodes[index_p1].id_dist.push_back({index_p2, d1});

		}

		int distance_to = 0;
		int distance_fro = 0;
		stack<Place> path_to  = execute(nodes, index_src, index_dest, distance_to);
		stack<Place> path_fro = execute(nodes, index_dest, index_src, distance_fro);
		
		cout << distance_to + distance_fro<<"\n";
		cout << path_to.top().name;
		path_to.pop();
		while (!path_to.empty()) {
			cout << " -> " << path_to.top().name;
			path_to.pop();
		}
		path_fro.pop();
		while (!path_fro.empty()) {
			cout << " -> " << path_fro.top().name;
			path_fro.pop();
		}
		cout << "\n";
	
	}
    return 0;
}

