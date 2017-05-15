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
using namespace std;


const int n_limit = 105;
const int m_limit = 105*104/2;
int A[n_limit];

struct Edge {

	int indexA, indexB, ppa;

	Edge(int a, int b, int dist) {
		indexA = a;
		indexB = b;
		ppa = dist;
	}

	Edge() {}

}edges[m_limit];

int compareEdge(const void * a, const void * b)
{
	return ((*(Edge*)a).ppa - (*(Edge*)b).ppa);
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



int main()
{
	
	while(1) {
		int n, m;
		cin >> n >> m;

		if (n == 0 && m == 0)
			break;

		for (int j = 0; j < m; j++) {
			int u, v, c;
			cin >> u >> v >> c;
			edges[j] = Edge(u-1, v-1, c);
		}

		qsort(edges, m, sizeof(Edge), compareEdge);

		int min_slimness = numeric_limits<int>::max();
		bool isAdmissionable = false; // only admissionable if n-1 edges are selected

		for (int i = 0; i < m; i++) {
			

			for (int j = 0; j < n; j++)
				A[j] = -1;

			int max_weight = numeric_limits<int>::min();
			int min_weight = numeric_limits<int>::max();

			int n_edgesSelected = 0;

			for (int j = i; j < m; j++) {
				Edge e = edges[j];
				if (Find(e.indexA) != Find(e.indexB)) {
					Union(e.indexA, e.indexB);
					n_edgesSelected++;

					if (e.ppa > max_weight)
						max_weight = e.ppa;
					if (e.ppa < min_weight)
						min_weight = e.ppa;
				}

				if (n_edgesSelected == n - 1 && (max_weight - min_weight) < min_slimness) {
					min_slimness = max_weight - min_weight;
					isAdmissionable = true;
					break;
				}
			}
		}
		cout << (isAdmissionable ? min_slimness : -1) << "\n";
	}



	return 0;
}

