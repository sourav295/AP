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

//int graph[limit_n][limit_n];
//int res[limit_n];


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
	if (A[root1] < A[root2]) //root1 has more member		
		UnionSet(root1, root2);	
	else		
		UnionSet(root2, root1);
}

void UnionSet(int set1, int set2) {
	A[set1] += A[set2]; // A[ root of set ] is negative, and its
	A[set2] = set1;     // magnitude is the num of members
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
		for (int i = 0; i < m; i++) {
			int a, b, ppa;
			cin >> a >> b >> ppa;
			edges[i] = Edge(a-1, b-1, ppa);
			
			if (ppa > max_ppa)
				max_ppa = ppa;
		}

		qsort(edges, m, sizeof(Edge), compareEdge);
		
		for (int i = 0; i < m; i++) {
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

	int z = 5;
    return 0;
}




/*
int minKey(int key[], bool mstSet[], int n)
{
int min = numeric_limits<int>::max();
int min_index;
for (int v = 0; v < n; v++)
if (mstSet[v] == false && key[v] < min){
min = key[v];
min_index = v;
}

return min_index;
}


void primMST(int n)
{
int parent[limit_n];
int key[limit_n];
bool mstSet[limit_n];

for (int i = 0; i < n; i++){
key[i] = numeric_limits<int>::max();
mstSet[i] = false;
}

key[0] = 0;
parent[0] = -1;

for (int count = 0; count < n - 1; count++)
{
int u = minKey(key, mstSet, n);
mstSet[u] = true;
for (int v = 0; v < n; v++)
if (graph[u][v]!=0 && mstSet[v] == false && graph[u][v] <  key[v]){
parent[v] = u;
key[v] = graph[u][v];
}
}


for (int i = 1; i < n; i++) {
res[i-1] = graph[i][parent[i]] * (-1);
}

qsort(res, n-1, sizeof(int), compareInt);

int total = 0;
int count = 0;
float prev_avg = 0;
float new_avg = 0;

for (int i = 0; i < n - 1; i++) {
total += res[i];
count = i + 1;

new_avg = float(total) / count;
if (new_avg > prev_avg) {
prev_avg = new_avg;
}
else {
cout << count + 1;
break;
}

}

}
*/