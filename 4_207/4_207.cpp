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

struct Place {

	int id;
	string name;
	queue<pair<int, int>> id_dist;

	Place(string n, int identity) {
		name = n;
		id = identity;
	}
};


int main()
{

	int n;
	cin >> n;
	string place;
	vector<Place> nodes;
	vector<string> edges;
	for (int i = 0; i < n; i++) {
		getline(cin, place);
		nodes.push_back(Place(place, i));
	}

	int n_roads;
	cin >> n_roads;
	for (int i = 0; i < n_roads; i++) {
		string road;
		getline(cin, road);
		stringstream ss(road);
		string p1, p2, d1, d2 = "";
		getline(ss, p1, ':');
		getline(ss, p2, ' ');
		getline(ss, d1, ' ');
		
		if (getline(ss, d2)) {
			for (int j = 0; j < edges.size(); j++) {
				if(!)
			}
		}
	}





	


    return 0;
}

