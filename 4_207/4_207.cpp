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
#include <map>
using namespace std;

map<string, int> place_id;


const int n_limit = 201;

int sptSet[n_limit], dist[n_limit];
int college[n_limit][n_limit];
int backTrack[n_limit];

string place_array[n_limit];

int minDistance(int n)
{
	int min = numeric_limits<int>::max();
	int min_index = -1;

	for (int v = 0; v < n; v++) {
		if (sptSet[v] == false && dist[v] <= min) {

			min = dist[v];
			min_index = v;
		}
	}

	return min_index;
}

void dijkstra(int src, int dest, int n)
{
	for (int i = 0; i < n; i++) {
		dist[i] = numeric_limits<int>::max();
		sptSet[i] = false;
	}

	dist[src] = 0;

	for (int count = 0; count < n; count++)
	{
		int u = minDistance(n);
		sptSet[u] = true;
		if (u == dest)
			return;

		for (int v = 0; v < n; v++)
			if (!sptSet[v] && college[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + college[u][v] < dist[v]) {
				dist[v] = dist[u] + college[u][v];
				backTrack[v] = u;
			}

	}

	
}



int main()
{
	int n, m;
	int indA, indB;
	int distance;

	while (cin >> n) {
		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				college[i][j] = 0;
		
		
		string place, link;
		
		getline(cin, place);
		for (int i = 0; i < n; i++) {
			getline(cin, place);
			place_id[place] = i;
			place_array[i] = place;
		}
		cin >> m;
		getline(cin, link);
		for (int i = 0; i < m; i++) {
			getline(cin, link);
			
			int j = 0;
			while (!(isdigit(link.at(j + 1)) && link.at(j) == ' ')) {
				j++;
			}
			
			place = link.substr(0, j);
		
			stringstream ss_distance(link.substr(j+1, link.length()));
			ss_distance >> distance;
		
			indA = place_id[place.substr(0, place.find(":"))];
			indB = place_id[place.substr(place.find(":")+1, place.length())];

			if(college[indA][indB] == 0 || (college[indA][indB] > 0 && college[indA][indB] > distance))
				college[indA][indB] = distance;
			if (ss_distance >> distance) {
				if (college[indB][indA] == 0 || (college[indB][indA] > 0 && college[indB][indA] > distance))
					college[indB][indA] = distance;
			}

		}
		
		dijkstra(place_id["office"], place_id["hall"], n);

		int ans = dist[place_id["hall"]];

		string output1 = "";
		string output2 = "";

		int u = place_id["hall"];
		while (u != place_id["office"]) {
			output1 = " -> " + place_array[u] + output1;
			u      = backTrack[u];
		}
		output1 = "office" + output1;

		dijkstra(place_id["hall"], place_id["office"], n);
		ans+= dist[place_id["office"]];

		u = place_id["office"];
		while (u != place_id["hall"]) {
			output2 = " -> " + place_array[u] + output2;
			u = backTrack[u];
		}
		cout << ans << "\n" << output1 << output2 << "\n\n";
	}
	
    return 0;
}

