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


const int rect_n_sides = 4;


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

// Driver program to test above functions
int main()
{
	int test;
	cin >> test;
	
	for (int t = 0; t < test; t++) {

		int xstart, ystart, xend, yend, xleft, ytop, xright, ybottom;
		cin >> xstart >> ystart >> xend >> yend >> xleft >> ytop >> xright >> ybottom;


		objective = Line(Point(xstart, ystart), Point(xend, yend));

		rect[0] = Line(Point(xleft, ytop), Point(xright, ytop));
		rect[1] = Line(Point(xleft, ytop), Point(xleft, ybottom));
		rect[2] = Line(Point(xright, ybottom), Point(xright, ytop));
		rect[3] = Line(Point(xright, ybottom), Point(xleft, ybottom));

		bool liesInside_1 = xstart >= xleft && ystart >= ybottom && xstart <= xright && ystart <= ytop;
		bool liesInside_2 = xend >= xleft && yend >= ybottom && xend <= xright && yend <= ytop;

		if (liesInside_1 || liesInside_2) {
			cout << "T\n";
			continue;
		}
		
		bool intersect = false;
		for (int i = 0; i < rect_n_sides; i++) {
			if (doIntersect(objective, rect[i])) {
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

