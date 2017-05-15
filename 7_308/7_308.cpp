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
	return min(abs(a - b), 10 - abs(a - b));
	
}

int distance(int A[], int B[]){
	int distance = 0;
	for(int i = 0; i < 4; i++){
		distance += diff(A[i], B[i]);
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
		vector<int> input_keys;
		int N;
		int count = 0;
		cin >> N;

		
		for (int j = 0; j < N; j++) {
			int key;
			cin >> key;
			input_keys.push_back(key);
			//edges[count++] = Edge(0, key, 0, count + 1);//connect to 0000
		}
		//interconnections
		for (int j = 0; j < N; j++)
			for (int k = j + 1; k < N; k++)
				edges[count++] = Edge(input_keys[j], input_keys[k], j, k);
				//edges[count++] = edges[j].generateEdgeOnIndexB(edges[k]);

		qsort(edges, count, sizeof(Edge), compareEdge);
		//MST
		for (int j = 0; j < N; j++)
			A[j] = -1;

		int total_rolls = 0;
		for (int j = 0; j < count; j++){
			Edge e = edges[j];
			if (Find(e.keyA_id) != Find(e.keyB_id)) {
				Union(e.keyA_id, e.keyB_id);
				total_rolls += e.ppa;
			}
		}

		int min_weightFrom0 = numeric_limits<int>::max();
		for (int j = 0; j < N; j++) {
			Edge e(0, input_keys[j], 0, 0);
			if (e.ppa < min_weightFrom0)
				min_weightFrom0 = e.ppa;
		}
		
		cout << total_rolls + min_weightFrom0 << "\n";
		
	}
	

	return 0;
}

