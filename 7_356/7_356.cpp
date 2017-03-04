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

const int limit_n = 500;


struct Edge {

	int indexA, indexB, ppa;

	Edge(int a, int b, int dist) {
		indexA = a;
		indexB = b;
		ppa = dist;
	}

	Edge() {}

};


int A[limit_n];
Edge edges[limit_n*limit_n];

int compareEdge(const void * a, const void * b)
{
	return ((*(Edge*)b).ppa - (*(Edge*)a).ppa);
}

void Union(int element1, int element2);
void UnionSet(int set1, int set2);
int Find(int element);


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

int Find(int element) {
	if (A[element] < 0)
		return element;
	else
		return Find(A[element]);
}



int main()
{
	int n, m;

	while (true) {
		cin >> n >> m;
		if (n == 0 && m == 0)
			break;

		for (int i = 0; i < n; i++)
			A[i] = -1;

		int max_ppa = 0;
		int count = 0;
		for (int i = 0; i < m; i++) {
			int a, b, ppa;
			cin >> a >> b >> ppa;
			
			if (ppa > max_ppa) {
				//restart
				count   = 0;
				max_ppa = ppa;
			}
			
			if (ppa == max_ppa) {
				edges[count] = Edge(a - 1, b - 1, ppa);
				count++;
			}
		}

		qsort(edges, count, sizeof(Edge), compareEdge);
		
		for (int i = 0; i < count; i++) {
			Edge e = edges[i];
			if (Find(e.indexA) != Find(e.indexB) && e.ppa == max_ppa)
				Union(e.indexA, e.indexB);
		}

		int min = 0;
		for (int i = 0; i < n; i++) {
			if (min > A[i])
				min = A[i];
		}

		cout << min*(-1) << "\n";
	}

    return 0;
}
