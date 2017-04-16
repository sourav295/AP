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

const int n_limit = 512;

struct Point {
	int x, y;
	Point(int ax, int ay) {
		x = ax;
		y = ay;
	}
	Point(){}


}points[n_limit], p0;

vector<Point> pointStack;
vector<pair<int, int>> input(n_limit);

int getOrientation(int ax1, int ay1, int ax2, int ay2, int ax3, int ay3) {
	long long x1, x2, x3, y1, y2, y3;
	x1 = ax1;
	y1 = ay1;
	
	x2 = ax2;
	y2 = ay2;
	
	x3 = ax3;
	y3 = ay3;
	long long orientation = (x2*y3 - x3*y2) - x1*(y3 - y2) + y1*(x3 - x2);
	if (orientation < 0)
		return -1;//clockwise
	else if (orientation > 0)
		return 1;//anticlockwise;
	else
		return 0;
}

int compare(const void *vp1, const void *vp2)
{
	Point *p1 = (Point *)vp1;
	Point *p2 = (Point *)vp2;

	int o = getOrientation(p0.x, p0.y, (*p1).x, (*p1).y, (*p2).x, (*p2).y);
	
	return (o > 0) ? -1 : 1;
}

bool doPop(int i) {
	int x1, x2, x3, y1, y2, y3;
	x1 = pointStack[pointStack.size() - 2].x;//next to top
	y1 = pointStack[pointStack.size() - 2].y;//next to top

	x2 = pointStack[pointStack.size() - 1].x;//top
	y2 = pointStack[pointStack.size() - 1].y;//top

	x3 = points[i].x;
	y3 = points[i].y;

	int o = getOrientation(x1, y1, x2, y2, x3, y3);
	return o < 0;
}



int main()
{
	int K, N, x, y, minus1;
	
	cin >> K;
	cout << K;

	for (int k = 0; k < K; k++) {
		input.clear();
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> x >> y;
			input.push_back({ y,x });
			//points[i] = Point(x, y);
		}
		if (input[0] == input[N - 1]) {
			input.pop_back();
			N--;
		}


		cin >> minus1;

		sort(input.begin(), input.begin() + N);
		for (int i = 0; i < N; i++) {
			points[i] = Point(input[i].second, input[i].first);
		}
		p0 = points[0];
		qsort(&points[1], N - 1, sizeof(Point), compare);

		pointStack.clear();
		for (int i = 0; i < 3; i++) {
			pointStack.push_back(points[i]);
		}

		for (int i = 3; i < N; i++) {
			while (doPop(i)) {
				pointStack.pop_back();
			}
			pointStack.push_back(points[i]);
		}

		cout << pointStack.size() + 1 << "\n";
		for (int i = 0; i < pointStack.size(); i++) {
			cout << pointStack[i].x << " " << pointStack[i].y << "\n";
		}
		cout << p0.x << " " << p0.y << "\n";

		if (k != K - 1) {
			cout << "-1\n";
		}
	}



    return 0;
}

