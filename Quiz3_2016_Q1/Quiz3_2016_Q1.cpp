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
#include <math.h>

using namespace std;

const int N = 2;
const int m = 1000003;

void matrix_mult_modular(int a[N][N], int b[N][N])
{
	int mul[N][N];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			mul[i][j] = 0;
			for (int k = 0; k < N; k++)
				mul[i][j] += (a[i][k] * b[k][j])%m;
		}
	}

	// storing the muliplication resul in a[][]
	for (int i = 0; i<N; i++)
		for (int j = 0; j<N; j++)
			a[i][j] = (mul[i][j])%m;  // Updating our matrix
}




void matrix_fastpower(int A[N][N], int n) { //(A^n)%m
	int ans[N][N];
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			ans[i][j] = 0;


	for (int i = 0;i<N;i++)
		ans[i][i] = 1;
	while (n) {
		if (n & 1)
			matrix_mult_modular(ans, A);//ans=(ans*A)%m;
		matrix_mult_modular(A, A); //A=(A*A)%m;
		n = n >> 1;
	}
	for (int i = 0; i<N; i++)
		for (int j = 0; j<N; j++)
			A[i][j] = (ans[i][j]) % m;  // Updating our matrix
}

int main()
{
	int f0, f1, fn;

	f0 = 1;
	f1 = 1;


	int X[N][N] = { {1, 1},{1, 0} };
	int n = 5;
	matrix_fastpower(X, n - 1);

	cout << (f1*X[0][0] + f0*X[0][1]) % m;

    return 0;
}

