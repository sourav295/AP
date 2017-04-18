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


const int n_limit = 300;
bool  visited[n_limit], sptSet[n_limit], dist[n_limit];
bool  chamber[n_limit][n_limit];
int a, b, c, n;


int minDistance()
{
	// Initialize min value
	int min = numeric_limits<int>::max();
	int min_index;

	for (int v = 0; v < n; v++)
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}

	return min_index;
}




int dijkstra(int src)
{
	int max_coins = 0;
	for (int i = 0; i < n; i++) {
		dist[i] = 0;
		sptSet[i] = false;
	}

	int count = 0;
	int v = src;
	while (!sptSet[v]) {
		count++;
		sptSet[v] = true;
		v = (a*v*v + b*v + c) % n;
	}

	return count;
}

void connect(int v) {
	int next = (a*v*v + b*v + c) % n;
	
	chamber[v][next] = true;
	

}

int execute() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			chamber[i][j] = false;
	}

	for(int i = 0; i < n; i++)
		connect(i);
	
	int max_coins = 0;
	for (int i = 0; i < n; i++) {
		int res = dijkstra(i);
		if (res > max_coins) {
			max_coins = res;
		}
	}

	return max_coins;
}


int main()
{
	
	
	int n_test;
	cin >> n_test;

	string blank;

	for (int i = 0; i < n_test; i++) {
		getline(cin, blank);
		
		cin >> a >> b >> c >> n;
		cout << execute() << "\n";
	}
	
    return 0;
}

