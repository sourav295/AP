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
int min_val = 0;


int A[limit_n];
//Edge edges[limit_n];

int graph[limit_n][limit_n];
/*
int compareEdge(const void * a, const void * b)
{
	return ((*(Edge*)b).ppa - (*(Edge*)a).ppa);
}*/

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

	if (A[set1] < min_val)
		min_val = A[set1];

}

int main()
{
	int n, m;

	while (true) {
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				graph[i][j] = 0;


		if (n == 0 && m == 0)
			break;

		for (int i = 0; i < n; i++)
			A[i] = -1;

		int min_ppa = numeric_limits<int>::max();
		for (int i = 0; i < m; i++) {
			int a, b, ppa;
			cin >> a >> b >> ppa;

			int negative_ppa = ppa* (-1);

			graph[a - 1][b - 1] = negative_ppa;

			if (min_ppa > negative_ppa)
				min_ppa = negative_ppa;

			
			/*
			if (ppa > max_ppa) {
				//restart
				count   = 0;
				max_ppa = ppa;
			}
			
			if (ppa == max_ppa) {
				edges[count] = Edge(a - 1, b - 1, ppa);
				count++;
			}*/
		}

		min_val = 0;

		int count = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (graph[i][j] == min_ppa){
					if (Find(i) != Find(j))
						Union(i, j);
				}

		//qsort(edges, count, sizeof(Edge), compareEdge);
		/*
		for (int i = 0; i < count; i++) {
			Edge e = edges[i];
			if(Find(e.indexA) != Find(e.indexB))
				Union(e.indexA, e.indexB);
		}
		

		int min = 0;
		for (int i = 0; i < n; i++) {
			if (min > A[i])
				min = A[i];
		}*/

		cout << min_val*(-1) << "\n";
	}

    return 0;
}
