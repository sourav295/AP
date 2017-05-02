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

struct suffix
{
	char *suff;
};

struct suffix suffixes[1000000];

int cmp(struct suffix a, struct suffix b)
{
	return strcmp(a.suff, b.suff) < 0 ? 1 : 0;
}

void buildSuffixArray(string txt, int n, int L)
{
	
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		string x = txt.substr(i);
		if (x.length > L) {
			suffixes[i].suff = &x[0];
			count++;
		}
	}

	sort(suffixes, suffixes + count, cmp);

	
	for (int i = 0; i < L; i++)
		cout << (suffixes[0].suff[i]);
	cout << "\n";
}



int main()
{
	string line, x;
	int L;
	while (getline(cin, line)) {
		stringstream ss(line);
		ss >> x;
		ss >> L;
		buildSuffixArray(x, x.length(), L);


	}
	


    return 0;
}

