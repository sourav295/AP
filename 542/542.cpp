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
#include <map>
#include <stdlib.h>
using namespace std;

const int n_limit = 100;

struct Signal {

	int id;
	int time_period;

	Signal(int i, int tp ) {
		id = i;
		time_period = tp;
	}

	pair<bool, int> isGreen(int time) {

		int upperLim = time / (2 * time_period);//remove numbers after decimal
		float lowerLim = (float)(time - time_period + 5) / (2 * time_period);

		return{ lowerLim < upperLim, upperLim};
	}

	pair<int, int> getTimeBound(int i) {

		float lower = 2 * i * time_period;
		float upper = lower + time_period - 5 - 1;

		return { lower, upper };

	}


	Signal() {}
};

int compareSignals(const void * a, const void * b)
{
	return ((*(Signal*)a).time_period - (*(Signal*)b).time_period);
}

Signal signals[n_limit];

bool inInterval(pair<int, int> &bounds, Signal newSignal) {

	pair<bool, int> lower_boundCmp = newSignal.isGreen(bounds.first);
	pair<bool, int> upper_boundCmp = newSignal.isGreen(bounds.second);

	bool isIntersecting = (lower_boundCmp.first || upper_boundCmp.first);
	if (isIntersecting) {




	}
	else
		return false;

}


void execute(int n) {
	//ref is the first signal
	int ref = 0;
	float ref_lim = (float)5 * 60 * 60 / (2 * signals[ref].time_period);


	for (int i = 1; i <= ref_lim; i++) {
		signals[ref].getTimeBound(i);


	}

}

bool hasThreeZeros(string line) {
	stringstream ss(line);
	int a, b, c;
	ss >> a;
	ss >> b;
	ss >> c;
	return a == 0 && b == 0 && c == 0;

}

int main()
{
	string line;
	int count = 0;
	while (1) {

		getline(cin, line);

		if (hasThreeZeros(line)) {
			break;
		}


		stringstream ss(line);

		int input;
		while (ss >> input) {
			if (input == 0) {
				qsort(signals, count, sizeof(Signal), compareSignals);
				execute(count);
				count = 0;
			}
			else {
				signals[count++] = Signal(count, input);
			}

		}


	}

	return 0;
}
