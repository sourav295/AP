#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <set>
#include <algorithm>
using namespace std;



struct Chamber {
	int id;

	//State variables
	bool involved_in_graph = false;
	bool has_incoming = false;

	bool updated = false;
	bool taken = false;
	int  benefit;

	Chamber* next;
	
	Chamber(int identity) {
		id = identity;
		//involved_in_graph = true;
	}
	Chamber(){}
};

int calculate_benefit(Chamber *c) {

	if ((*c).updated)
		return (*c).benefit;
	if ((*c).taken)
		return 0;

	(*c).taken = true;
	(*c).benefit = calculate_benefit((*c).next) + 1;
	(*c).updated = true;

	return (*c).benefit;
}



int execute(int a, int b, int c, int n) {

	vector<Chamber> chambers;
	for (int i = 0; i < n; i++) {
		chambers.push_back(Chamber(i));
	}

	//set next pointers
	for (int i = 0; i < chambers.size(); i++) {
		if (chambers[i].involved_in_graph)
			continue;

		Chamber *root = &(chambers[i]);
		do {
			(*root).involved_in_graph = true;

			int id = (*root).id;
			int next_id = (a*id*id + b*id + c)%n;
			(*root).next = &(chambers[next_id]);
			
			root = (*root).next;
			if(id != next_id)
				(*root).has_incoming = true;


		} while (!(*root).involved_in_graph);
	}

	//identify starting points
	queue<Chamber *> starting_pointers;
	for (int i = 0; i < chambers.size(); i++) {
		if (!chambers[i].has_incoming)
			starting_pointers.push(&(chambers[i]));
	}

	//recurr till all updated
	for (starting_pointers; !starting_pointers.empty(); starting_pointers.pop()) {
		cout <<"\n"<< (*starting_pointers.front()).id << " "<< calculate_benefit(starting_pointers.front());
	}
	
	return starting_pointers.size();
	

}





int main()
{
	cout << execute(1, 1, 1, 5);
	/*
	string blank;

	int t;//number of test cases
	cin >> t;

	for (int i = 0; i < t; i++) {
		getline(cin, blank);

		int a, b, c, n;
		cin >> a >> b >> c >> n;
		
	}
	*/

    return 0;
}

