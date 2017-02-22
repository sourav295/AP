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

struct Chemical {
	vector<pair<int, int>> reactions;


};


int main()
{
	string line;
	while (getline(cin, line)) {
		int n;
		vector<Chemical> chemicals;
		for (int i = 0; i < n; i++)
			chemicals.push_back(Chemical());

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int heat;
				chemicals[i].reactions.push_back({ j, heat });
			}
		}
	}


    return 0;
}

