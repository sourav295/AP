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

const int n_limit = 102;

struct Point {
	int x, y;
	Point(int ax, int ay) {
		x = ax;
		y = ay;
	}
	Point(){}

	

}points[n_limit], p0;

Point point_copy[n_limit], hull_points[n_limit];


bool selected[n_limit];
vector<Point> pointStack;
vector<pair<int, int>> input(n_limit);

int dist_square(Point p1, Point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y);
}

int getTriArea(Point origin, Point v1, Point v2) {

	int ax = v1.x - origin.x;
	int ay = v1.y - origin.y;

	int bx = v2.x - origin.x;
	int by = v2.y - origin.y;

	int res  = abs(ax*by - bx*ay)/2;
	
	return res;

}

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
	if (o == 0)
		if(dist_square(p0, *p2) >= dist_square(p0, *p1))
			return 1;
		else
			return -1;
	
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

int comparePoints(const void *vp1, const void *vp2)
{
	Point *p1 = (Point *)vp1;
	Point *p2 = (Point *)vp2;

	// Find orientation
	if ((*p1).y == (*p2).y) {
		if ((*p1).x >= (*p2).x)
			return -1;
		else 
			return +1;
	}

	if ((*p1).y >= (*p2).y)
		return +1;
	else
		return -1;
}

double getArea_intoTwo(Point p[], int n_ver) {
	float area = 0.0f;

	for (int i = 0; i < n_ver - 1; i++)
		area += p[i].x * p[i + 1].y - p[i + 1].x * p[i].y;

	area += p[n_ver - 1].x * p[0].y - p[0].x * p[n_ver - 1].y;

	area = abs(area);

	return area;
}

int main()
{
	int K, N, x, y, minus1;
	
	K =1;
	while(true) {
		cin >> N;
		int N_copy = N;
		if (N == 0)
			break;

		input.clear();
		for (int i = 0; i < N; i++) {
			cin >> x >> y;
			input.push_back({ y,x });
			//points[i] = Point(x, y);
		}
		

		sort(input.begin(), input.begin() + N);

		for (int i = 0; i < N; i++) {
			points[i] = Point(input[i].second, input[i].first);
			selected[i] = true;
		}

		p0 = points[0];
		qsort(&points[1], N - 1, sizeof(Point), compare);
		for (int i = 0; i < N; i++)
			point_copy[i] = points[i];

		
		int m = 1;
		int first_i;
		for (int i = 1; i<N; i++)
		{
			first_i = i;
			while (i < N - 1 && getOrientation(p0.x, p0.y, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y) == 0)
				i++;
			points[m++] = points[first_i];
		}
		N = m;

		
		m = 0;
		for (int i = 0; i + 1 < N; i++) {
			Point p_1 = points[i];
			Point p_2 = points[i + 1];
			int j = i + 2;
			while (j < N && getOrientation(p_1.x, p_1.y, p_2.x, p_2.y, points[j].x, points[j].y) == 0) {
				selected[j - 1] = false;
				j++;
			}
			i = j - 2;
		}


		for (int i = 0; i < N; i++) {
			if (selected[i]) {
				points[m++] = points[i];
			}
		}
		N = m;
		
		

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

		int counter_hull = 0;
		for (pointStack;!pointStack.empty(); pointStack.pop_back()) {
			hull_points[counter_hull++] = pointStack.back();
		}

		float hull_area = getArea_intoTwo(hull_points, counter_hull);
		float polygon_area = getArea_intoTwo(point_copy, N_copy);
		float result = (1 - (polygon_area / hull_area))*100;


		cout << "Tile #" << K++;
		cout << "\nWasted Space = ";
		printf("%.2lf %%\n\n", (float)result);
		
		
	}



    return 0;
}

