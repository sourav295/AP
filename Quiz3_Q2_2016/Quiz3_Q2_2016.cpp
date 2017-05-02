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

struct suffix {

	int index;
	string suff;

	suffix(){}

};

vector<suffix> suffixes(1000000);

int cmp(suffix a, suffix b)
{
	return a.suff.compare(b.suff) < 0 ? 1 : 0;
}

string buildSuffixArray(string txt, int n, int L)
{
	struct suffix ;

	int count = 0;
	for (int i = 0; i < n; i++)
	{
		
		string suffix_txt = txt.substr(i);
		if (suffix_txt.length() >= L) {
			suffixes[i].index = i;
			suffixes[i].suff = suffix_txt;
			count++;
		}
	}

	string minString = suffixes[0].suff;
	for (int i = 0; i < count; i++) {
		if (suffixes[i].suff.compare(minString) < 0) {
			minString = suffixes[i].suff;
		}
	}


	return minString.substr(0, L);
}


int main()
{
	string line, x;
	int L;
	while (getline(cin, line)) {
		stringstream ss(line);
		ss >> x;
		ss >> L;
		cout << buildSuffixArray(x, x.length(), L) << "\n";


	}
	


    return 0;
}

