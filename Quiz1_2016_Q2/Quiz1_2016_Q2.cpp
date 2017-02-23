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
using namespace std;

const int n_limit = 100;

int search(int r, int c, int N, int M, bool **space) {
	//uncheck current box
	space[r][c] = false;

	int sum = 1;//including this
	//check left
	if (c - 1 >= 0 && space[r][c - 1])
		sum += search(r, c - 1, N, M, space);
	//check right
	if (c + 1 < M && space[r][c + 1])
		sum += search(r, c + 1, N, M, space);
	//check bottom
	if (r + 1 < N && space[r + 1][c])
		sum += search(r + 1, c, N, M, space);
	//check top
	if (r - 1 >= 0 && space[r - 1][c])
		sum += search(r - 1, c, N, M, space);

	return sum;

}



int main()
{
	bool **space = new bool*[n_limit];
	for (int i = 0; i < n_limit; i++)
		space[i] = new bool[n_limit];
	pair<int, int> starts[n_limit];

	int N, M, K;
	string line;

	while (getline(cin, line)) {
		stringstream ss(line);

		ss >> N;
		ss >> M;
		ss >> K;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				space[i][j] = false;

		for (int k = 0; k < K; k++) {
			int r, c;
			cin >> r >> c;
			r--;
			c--;
			space[r][c] = true;
			starts[k] = { r, c };
		}

		if(K > 0)
			getline(cin, line);

		int max = 0;
		int res = 0;
		for (int k = 0; k < K; k++) {
			res = search(starts[k].first, starts[k].second, N, M, space);
			if (res > max)
				max = res;
		}
		cout << max << "\n";
	}

    return 0;
}

