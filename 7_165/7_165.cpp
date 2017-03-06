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
#include <algorithm>
#include <iomanip>
#include <cmath>
#include<math.h>
using namespace std;


const int n_limit = 1000;
const int m_limit = 49500;
int A[n_limit];

int X[n_limit], Y[n_limit];
int graph[n_limit][n_limit];


struct Edge {

	int indexA, indexB;
	unsigned int ppa;

	Edge(int a, int b, unsigned int dist) {
		indexA = a;
		indexB = b;
		ppa = dist;
	}

	Edge() {}

}edges[m_limit];

int compareEdge(const void * a, const void * b)
{
	if ((*(Edge*)a).ppa > (*(Edge*)b).ppa)
		return +1;
	else
		return -1;
}


void Union(int element1, int element2);
void UnionSet(int set1, int set2);
int Find(int element);

int Find(int element) {
	if (A[element] < 0)
		return element;
	else
		return Find(A[element]);
}

void Union(int element1, int element2) {
	int root1 = Find(element1);
	int root2 = Find(element2);
	if (A[root1] < A[root2])
		UnionSet(root1, root2);
	else
		UnionSet(root2, root1);
}

void UnionSet(int set1, int set2) {
	A[set1] += A[set2];
	A[set2] = set1;
}

int minDistance(int dist[], bool sptSet[], int n)
{
	// Initialize min value
	int min = numeric_limits<int>::max();
	int min_index;

	for (int v = 0; v < n; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

int dijkstra(int n)
{
	int dist[n_limit];
	int parent[n_limit];
	bool sptSet[n_limit];
	for (int i = 0; i < n; i++){
		dist[i] = numeric_limits<int>::max();
		sptSet[i] = false;
	}

	dist[0] = 0;
	for (int count = 0; count < n; count++)
	{
		int u = minDistance(dist, sptSet, n);
		sptSet[u] = true;

		if (u == 1) {
			//complete
			int max = numeric_limits<int>::min();
			int cur = u;
			int par = parent[u];
			while (0 != cur) {
				if (dist[cur] - dist[par] > max)
					max = dist[cur] - dist[par];
				cur = par;
				par = parent[cur];
			}
			
			return max;
		}
			

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < n; v++)
			if (!sptSet[v] && graph[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + graph[u][v] < dist[v]) {
				dist[v] = dist[u] + graph[u][v];
				parent[v] = u;
			}
	}

	return 0;
}




int main()
{
	string line;
	int test = 1;
	while (true) {
		int N;
		cin >> N;

		if (N == 0)
			break;

		for (int i = 0; i < N; i++) {
			int x, y;
			cin >> x >> y;
			X[i] = x;
			Y[i] = y;
		}

		getline(cin, line);
		getline(cin, line);

		int count = 0;
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++)
				edges[count++] = Edge(i, j, pow(X[i] - X[j], 2) + pow(Y[i] - Y[j], 2));

		for (int i = 0; i < N; i++)
			A[i] = -1;

		qsort(edges, count, sizeof(Edge), compareEdge);

		for (int i = 0; i < count; i++) {
			Edge e = edges[i];
			if (Find(e.indexA) != Find(e.indexB)) {
				Union(e.indexA, e.indexB);
			}

			//search complete
			if (Find(0) == Find(1)) {
				int root = Find(0);
				int hop_count = 0;
				
				for (int j = 0; j < N; j++)
					for (int k = 0; k < N; k++)
						graph[j][k] = 0;

				for (int j = 0; j <= i; j++) {
					int root = Find(0);
					
					Edge e = edges[j];
					if (root == Find(j)) {
						graph[e.indexA][e.indexB] = e.ppa;
						graph[e.indexB][e.indexA] = e.ppa;
					}
				}

				if (test > 1)
					cout << "\n";

				cout << "Scenario #" << test++ << "\n";
				printf("Frog Distance = %.3f\n", sqrt(dijkstra(N)));

				break;
			}


		}

	}





	return 0;
}

