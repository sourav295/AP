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
using namespace std;

typedef struct Junction Junction;

struct Link {
	Junction *neightbour;
	int distance;

	Link(Junction *x, int dist) {
		neightbour = x;
		distance = dist;
	}

};

struct Junction {

	queue<Link> neighbours;
	int id;
	int distance_src;
	
	Junction(int identity) {
		id = identity;
		distance_src = numeric_limits<int>::max();
	}

	Junction(){}

	bool operator()(Junction const &a, Junction const &b) const { return a.distance_src > b.distance_src; }

};


bool sortHelper(Junction i, Junction j) { return (i.distance_src > j.distance_src); }

int main()
{
	int n,r;
	int test_number = 0;
	while (cin >> n >> r) {
		test_number++;
		
		vector<Junction> priority_queue;

		//create junctions 
		for (int i = 0; i < n; i++) {
			priority_queue.push_back(Junction(i));
		}
		
		//link the junctions 
		for (int i = 0; i < r; i++) {
			int start, end, dist = 0;
			
			cin >> start >> end >> dist;

			priority_queue[start].neighbours.push(
				Link(&(priority_queue[end]), dist)
			);

			priority_queue[end].neighbours.push(
				Link(&(priority_queue[start]), dist)
			);
		}

		//init src
		priority_queue[0].distance_src = 0;

		/*
		while (!priority_queue.empty()) {
			cout << "\n" << priority_queue.back().id;
			queue<Link> links = priority_queue.back().neighbours;

			
			for (links; !links.empty(); links.pop())
				cout << ",  " << (*(links.front().neightbour)).id<< " " << links.front().distance ;
			priority_queue.pop_back();
		}*/
				
		//djikstra
		int results = 0;
		while (!priority_queue.empty()) {
			sort(priority_queue.begin(), priority_queue.end(), sortHelper);

			Junction *junction = &(priority_queue.back());

			int curr_distance = (*junction).distance_src;
			queue<Link> extracted_links = (*junction).neighbours;
			
			if ((*junction).id == (n - 1)) {
				results = (*junction).distance_src;
				break;
			}

			priority_queue.pop_back();

			for (extracted_links; !extracted_links.empty(); extracted_links.pop()) {
				Link link = extracted_links.front();
				Junction *j = link.neightbour;
				int distance = link.distance;//distance till the neightbour
				
				int potential_distance = curr_distance + distance;
				//cout << (*j).id<< " P"<< potential_distance<< " "<< ", ";
				if ((*j).distance_src > potential_distance)
					(*j).distance_src = potential_distance;

			}
		}
		
		cout << "Set #" << test_number<<"\n";
		cout <<results<<"\n";
	}
	
	return 0;
}

