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


long long xstart, ystart, xend, yend, xleft, ytop, xright, ybottom;
pair<long long, long long> line_range_x;
pair<long long, long long> line_range_y;

struct Point
{
	double x;
	double y;

	Point(int ax, int ay) {
		x = ax;
		y = ay;
	}

	Point(){}
};


int orient(Point p, Point q, Point r)
{
	double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return 0;
	return (val > 0) ? 1 : -1; // clock or counterclock wise
}



bool inBetween(int lowerLim, int upperLim, int val) {
	if (val >= lowerLim && val <= upperLim)
		return true;
	return false;
}

bool inRangeOfLine(long long x[], long long y[]) {

	for(int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) {
			if (inBetween(line_range_x.first, line_range_x.second, x[i]) && inBetween(line_range_y.first, line_range_y.second, y[j]))
				return true;
		}

	return false;
}

bool inRangeOfRect(long long x[], long long y[]) {

	if (inBetween(x[0], x[1], xstart) && inBetween(y[0], y[1], ystart))
		return true;
	if (inBetween(x[0], x[1], xend) && inBetween(y[0], y[1], yend))
		return true;
	return false;
}

int main()
{
	int test;
	cin >> test;


	
	for (int t = 0; t < test; t++) {

		
		cin >> xstart >> ystart >> xend >> yend >> xleft >> ytop >> xright >> ybottom;


		line_range_x = { min(xstart, xend), max(xstart, xend)};
		line_range_y = { min(ystart, yend), max(ystart, yend)};
		
		long long rect_range_x[] = { min(xleft, xright), max(xleft, xright) };
		long long rect_range_y[] = { min(ytop, ybottom), max(ytop, ybottom) };

		if (inRangeOfLine(rect_range_x, rect_range_y) || inRangeOfRect(rect_range_x, rect_range_y)) {
			Point a(xstart, ystart);
			Point b(xend, yend);
			
			int sum = 0;

			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++) {
					Point c(rect_range_x[i], rect_range_y[j]);
					sum += orient(a, b, c);
				}

			if(sum == 4 || sum == -4)
				cout << "F\n";
			else
				cout << "T\n";

		}
		else {
			cout << "F\n";
		}

	}

	return 0;
}

