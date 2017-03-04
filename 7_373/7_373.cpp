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


const int n_limit = 1000;
const int m_limit = 25000;
int A[n_limit];
bool accepted[n_limit];
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



int main()
{
	
	while(true) {
		int n, m;
		cin >> n >> m;

		if (n == 0 && m == 0)
			break;

		for (int j = 0; j < m; j++) {
			int u, v;
			unsigned int c;
			cin >> u >> v >> c;
			edges[j] = Edge(u, v, c);
		}

		qsort(edges, m, sizeof(Edge), compareEdge);

		for (int i = 0; i < n_limit; i++)
			accepted[i] = false;

		for (int j = 0; j < n; j++)
			A[j] = -1;

		int max_val = numeric_limits<int>::min();
		for (int j = 0; j < m; j++) {
			Edge e = edges[j];
			if (Find(e.indexA) != Find(e.indexB)) {
				Union(e.indexA, e.indexB);
				accepted[j] = true;
			}
		}

		cout << "Case #" << i << ": " << max_val*(-1) << "\n";
	}



	return 0;
}

