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

const int m_limit = 100;
bool isIsolated[m_limit];

struct Line{
	int x1, y1, x2, y2;

	Line(int ax1, int ay1, int ax2, int ay2) {
		x1 = ax1;
		x2 = ax2;
		y1 = ay1;
		y2 = ay2;
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

bool isIntersecting(Line l1, Line l2) {
	if (l1.reltivePosition(l2) <= 0 && l2.reltivePosition(l1) <= 0)
		return true;
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

