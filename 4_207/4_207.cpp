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
	getline(cin, place);//blank
	
	vector<Place> nodes;
	vector<string> edges;
	for (int i = 0; i < n; i++) {
		getline(cin, place);
		nodes.push_back(Place(place, i));
	}
	cout << "Done";

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
		string p1, p2 = "";
		int d1, d2;

		getline(ss_places, p1, ':');
		getline(ss_places, p2);
		
		int index_p1, index_p2 = 0;
		for (int j = 0; j < n; j++) {
			if (!p1.compare(nodes[j].name))
				index_p1 = j;
			if (!p2.compare(nodes[j].name))
				index_p2 = j;
		}
		
		
		ss_nums >> d1;
		
		if (ss_nums >> d2) {
			//bi-directional
			nodes[index_p2].id_dist.push({ index_p1, d2 });
		}
		nodes[index_p1].id_dist.push({index_p2, d1});

	}



    return 0;
}

