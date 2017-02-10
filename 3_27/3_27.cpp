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

		} while (!(*root).involved_in_graph);
	}

	int max = 0;
	int curr = 0;

	for (int i = 0; i < chambers.size(); i++) {
		curr = calculate_benefit(&(chambers[i]));
		if (curr > max)
			max = curr;
	}
	
	
	return max;
	

}


int main()
{
	int n_test;
	cin >> n_test;

	string blank;

	for (int i = 0; i < n_test; i++) {
		getline(cin, blank);
		int a, b, c, n;
		cin >> a >> b >> c >> n;
		cout << execute(a, b, c, n) << "\n";
	}

    return 0;
}

