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


const int n_limit = 500;
const int m_limit = (n_limit*n_limit + n_limit)/2 + 5; //(n*n-1)/2 with n = 500
int A[n_limit];


int diff(int a, int b){
	if(b-a <= 10 - b + a)
		return b - a;
	else
		return 10- b + a;
	
}

int distance(int A[], int B[]){
	int distance = 0;
	for(int i = 0; i < 4; i++){
		if(A[i] <= B[i]){
			distance += diff(A[i], B[i]);
		}else{
			distance += diff(B[i], A[i]);
		}
	}
	
	return distance;
}


struct Edge {

	int keyA, keyB;
	int keyA_id, keyB_id;

	int indexA[4];
	int indexB[4];
	int ppa;

	Edge(int a, int b, int A_id, int B_id) {
		keyA = a;
		keyB = b;

		keyA_id = A_id;
		keyB_id = B_id;

		for (int i = 3; i >= 0; i--) {
			indexA[i] = a%10;
			indexB[i] = b%10;
			
			a /= 10;
			b /= 10;
		}
		
		ppa = distance(indexA, indexB);
	}

	Edge generateEdgeOnIndexB(Edge other) {
		return Edge(keyB, other.keyB, keyB_id, other.keyB_id);
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
	int T;
	cin >> T;
	
	for (int test = 0; test < T; test++) {
		int N;
		int count = 0;
		int maxdist_connectedToZero = 0;
		int sumdist_connectedToZero = 0;
		cin >> N;

		
		for (int j = 0; j < N; j++) {
			int key;
			cin >> key;
			edges[count++] = Edge(0, key, 0, count + 1);//connect to 0000
		}
		//interconnections
		for (int j = 0; j < N; j++)
			for (int k = j+1; k < N; k++)
				edges[count++] = edges[j].generateEdgeOnIndexB(edges[k]);

		qsort(edges, count, sizeof(Edge), compareEdge);
		//MST
		for (int j = 0; j < N + 1; j++)
			A[j] = -1;

		int total_rolls = 0;
		for (int j = 0; j < count; j++){
			Edge e = edges[j];
			if (Find(e.keyA_id) != Find(e.keyB_id)) {
				Union(e.keyA_id, e.keyB_id);

				if (e.keyA_id == 0 || e.keyB_id == 0) {
					sumdist_connectedToZero += e.ppa;
					if (e.ppa > maxdist_connectedToZero)
						maxdist_connectedToZero = e.ppa;
				}
			
				total_rolls += e.ppa;
			}
		}

		//find maximum depth of the graph

		//find out a way to roll across the tree
		cout << total_rolls + sumdist_connectedToZero - maxdist_connectedToZero << "\n";
		
	}
	

	return 0;
}

