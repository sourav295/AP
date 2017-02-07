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

int fallen_dominos;

struct Domino {
	
	
	int id;
	int upright = true;
	queue<Domino *> following_dominos;

	Domino(int identity) {
		id = identity;
	}
	Domino(){}


	static vector<Domino> create(int n) {
		vector<Domino> domino_vector;
		for (int i = 1; i <= n; i++)
			domino_vector.push_back(Domino(i));
		return domino_vector;
	}

	void drop() {
		if (!upright)
			return;

		upright = false;
		fallen_dominos++;
		
		for (following_dominos; !following_dominos.empty(); following_dominos.pop()) {
			Domino *to_fall = (following_dominos.front());
			(*to_fall).drop();
		}

	}

};


int main()
{
	int n_test;
	cin >> n_test;
	
	for (int i = 0; i < n_test; i++) {
		int n, m, l;
		cin >> n >> m >> l;
		
		vector<Domino> domino_vector = Domino::create(n);
		
		for (int j = 0; j < m; j++) {
			int x, y;
			cin >> x >> y;
			domino_vector[x - 1].following_dominos.push(&(domino_vector[y - 1]));
			//Domino *c = domino_vector[x - 1].following_dominos.front();
			//cout << (*c).id;
		}

		fallen_dominos = 0;
		for (int k = 0; k < l; k++) {
			int z;
			cin >> z;
			domino_vector[z - 1].drop();
		}
		cout << fallen_dominos << "\n";

	}
	
	
	return 0;
}

