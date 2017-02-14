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


struct City {

	int id;
	queue<pair<int, int>> neighbours;//id-distance

	City(int identity, queue<int> distances) {
		id = identity;
		for (int i = 1; i <= distances.size(); distances.pop()) {
			neighbours.push({ i, distances.front() });
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


int main()
{
	int M = 0;// no of cases

	cin >> M;

	for (int case_no = 0; case_no < M; case_no++) {

		vector<City> map;

		int n;//number of columns
		int row_number = 0;
		do {
			string line;
			getline(cin, line);
			map.push_back(
				cityFactory(row_number, line, n)//adjust row limit based on the column limit
			);		
		} while (row_number < n);


		int x = 5;
		int y = 10;

	}



    return 0;
}

