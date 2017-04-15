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



/*
struct Point
{
	long long x;
	long long y;

	Point(int ax, int ay) {
		x = ax;
		y = ay;
	}

	Point(){}
};

struct Line {
	Point p, q;

	Line(Point ap, Point aq) {
		p = ap;
		q = aq;
	}
	Line(){}
};

Line rect[rect_n_sides];
Line objective;


bool sameSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

int orient(Point p, Point q, Point r)
{
	long long val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return 0;
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool doIntersect(Line a, Line b)
{
	Point p1 = a.p;
	Point q1 = a.q;
	Point p2 = b.p;
	Point q2 = b.q;

	int o1 = orient(p1, q1, p2);
	int o2 = orient(p1, q1, q2);
	int o3 = orient(p2, q2, p1);
	int o4 = orient(p2, q2, q1);

	if (o1 != o2 && o3 != o4)
		return true;

	if (o1 == 0 && sameSegment(p1, p2, q1)) return true;
	if (o2 == 0 && sameSegment(p1, q2, q1)) return true;
	if (o3 == 0 && sameSegment(p2, p1, q2)) return true;
	if (o4 == 0 && sameSegment(p2, q1, q2)) return true;

	return false;
}
*/


const int rect_n_sides = 4;
float distance(int ax1, int ay1, int ax2, int ay2) {
	float x_diffsq = pow(ax1 - ax2, 2);
	float y_diffsq = pow(ay1 - ay2, 2);
	return sqrt(x_diffsq + y_diffsq);
}

struct Line {
	long long x1, y1, x2, y2;

	float dist;

	Line(int ax1, int ay1, int ax2, int ay2) {
		x1 = ax1;
		x2 = ax2;
		y1 = ay1;
		y2 = ay2;

		dist = distance(x1, y1, x2, y2);
	}
	Line() {}

	long long reltivePosition(Line other) {
		long long x3 = other.x1;
		long long x4 = other.x2;
		long long y3 = other.y1;
		long long y4 = other.y2;

		long long first_angle = (x2*y3 - x3*y2) - x1*(y3 - y2) + y1*(x3 - x2);
		long long second_angle = (x2*y4 - x4*y2) - x1*(y4 - y2) + y1*(x4 - x2);

		return first_angle * second_angle;
	}

}rect[rect_n_sides];

Line objective;

float maxDistancebtwLines(Line l1, Line l2) {

	vector<pair<int, int>> all_points;
	all_points.push_back({ l1.x1, l1.y1 });
	all_points.push_back({ l1.x2, l1.y2 });
	all_points.push_back({ l2.x1, l2.y1 });
	all_points.push_back({ l2.x2, l2.y2 });

	sort(all_points.begin(), all_points.begin() + 4);

	return distance(all_points[0].first, all_points[0].second, all_points[3].first, all_points[3].second);
}



bool isIntersecting(Line l1, Line l2) {

	long long rel_pos1 = l1.reltivePosition(l2);
	long long rel_pos2 = l2.reltivePosition(l1);
	if ((rel_pos1 <= 0 && rel_pos2 <= 0) && !(rel_pos1 == 0 && rel_pos2 == 0))//one of them can be 0, not both
		return true;

	bool distance_ok = (maxDistancebtwLines(l1, l2) < (l1.dist + l2.dist));
	//bool are_colinear = isColinear(l1, l2);

	if (rel_pos1 == 0 && rel_pos2 == 0 && distance_ok) {
		return true;
	}
	return false;
}

// Driver program to test above functions
int main()
{
	int test;
	cin >> test;
	
	for (int t = 0; t < test; t++) {

		long long xstart, ystart, xend, yend, xleft, ytop, xright, ybottom;
		cin >> xstart >> ystart >> xend >> yend >> xleft >> ytop >> xright >> ybottom;


		objective = Line(xstart, ystart, xend, yend);

		rect[0] = Line(xleft, ytop          , xright, ytop     );
		rect[1] = Line(xleft, ytop          , xleft , ybottom  );
		rect[2] = Line(xright, ybottom      , xright, ytop     );
		rect[3] = Line(xright, ybottom      , xleft, ybottom   );

		bool liesInside_1 = xstart >= xleft && ystart >= ybottom && xstart <= xright && ystart <= ytop;
		bool liesInside_2 = xend >= xleft && yend >= ybottom && xend <= xright && yend <= ytop;

		if (liesInside_1 || liesInside_2) {
			cout << "T\n";
			continue;
		}
		
		bool intersect = false;
		for (int i = 0; i < rect_n_sides; i++) {
			if (isIntersecting(objective, rect[i])) {
				intersect = true;
				break;
			}
		}
		if (intersect) {
			cout << "T\n";
			continue;
		}
	
		cout << "F\n";

	}

	return 0;
}

