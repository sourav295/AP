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
#include <math.h>
using namespace std;

const int m_limit = 100;
bool isIsolated[m_limit];


float distance(int ax1, int ay1, int ax2, int ay2) {
	float x_diffsq = pow(ax1 - ax2, 2);
	float y_diffsq = pow(ay1 - ay2, 2);
	return sqrt(x_diffsq + y_diffsq);
}

struct Line{
	int x1, y1, x2, y2;

	float dist;

	Line(int ax1, int ay1, int ax2, int ay2) {
		x1 = ax1;
		x2 = ax2;
		y1 = ay1;
		y2 = ay2;

		dist = distance(x1, y1, x2, y2);
	}
	Line() {}

	int reltivePosition(Line other) {
		int x3 = other.x1;
		int x4 = other.x2;
		int y3 = other.y1;
		int y4 = other.y2;

		int first_angle  = (x2*y3 - x3*y2) - x1*(y3 - y2) + y1*(x3 - x2);
		int second_angle = (x2*y4 - x4*y2) - x1*(y4 - y2) + y1*(x4 - x2);

		return first_angle * second_angle;
	}

}all_lines[m_limit];

float maxDistancebtwLines(Line l1, Line l2) {

	vector<pair<int, int>> all_points;

	all_points.push_back({ l1.x1, l1.y1 });
	all_points.push_back({ l1.x2, l1.y2 });
	all_points.push_back({ l2.x1, l2.y1 });
	all_points.push_back({ l2.x2, l2.y2 });

	sort(all_points.begin(), all_points.end());

	return distance(all_points[0].first, all_points[0].second, all_points[3].first, all_points[3].second);
}

bool isColinear(Line l1, Line l2) {

	vector<pair<int, int>> all_points;

	all_points.push_back({ l1.x1, l1.y1 });
	all_points.push_back({ l1.x2, l1.y2 });
	all_points.push_back({ l2.x1, l2.y1 });
	all_points.push_back({ l2.x2, l2.y2 });

	sort(all_points.begin(), all_points.end());

	return ((all_points[3].second - all_points[2].second) * (all_points[2].first - all_points[0].first) == (all_points[2].second - all_points[0].second) * (all_points[3].first - all_points[2].first));
}

bool checkBoundary(Line l1, Line l2) {
	if (l1.x1 == l2.x1 && l1.y1 == l2.y1)
		return true;
	if (l1.x1 == l2.x2 && l1.y1 == l2.y2)
		return true;
	if (l1.x2 == l2.x1 && l1.y2 == l2.y1)
		return true;
	if (l1.x2 == l2.x2 && l1.y2 == l2.y2)
		return true;
	return false;
}



bool isIntersecting(Line l1, Line l2) {
	
	if (checkBoundary(l1, l2))
		return true;

	int rel_pos1 = l1.reltivePosition(l2);
	int rel_pos2 = l2.reltivePosition(l1);
	if ((rel_pos1 <= 0 && rel_pos2 <= 0) && !(rel_pos1 == 0 && rel_pos2 == 0))//one of them can be 0, not both
		return true;

	bool distance_ok  = (maxDistancebtwLines(l1, l2) < (l1.dist + l2.dist));
	//bool are_colinear = isColinear(l1, l2);

	if (rel_pos1 == 0 && rel_pos2 == 0 && distance_ok) {
		return true;
	}
	return false;
}


int main()
{
	int M, N;
	int x1, y1, x2, y2;

	
	cin >> N;
	for (int n = 0; n < N; n++) {
		cin >> M;

		//clear array
		for (int m = 0; m < M; m++) {
			isIsolated[m] = true;
		}

		for (int m = 0; m < M; m++) {
			cin >> x1 >> y1 >> x2 >> y2;
			all_lines[m] = Line(x1, y1, x2, y2);
		}

		for (int i = 0; i < M; i++) {
			for (int j = i + 1; j < M; j++) {
				
				if (isIntersecting(all_lines[i], all_lines[j])) {
					isIsolated[i] = false;
					isIsolated[j] = false;
				}
			}
		}
		int count = 0;
		for (int i = 0; i < M; i++) {
			if (isIsolated[i]) {
				count++;
			}
		}
		cout << count << "\n";
	}
    return 0;
}

