#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <utility>
#include <stack>
#include<string>
#include<sstream>
#include<ctype.h>
#include <stdlib.h>
using namespace std;

int main() {
	
	int n, t;
	cin >> t;
	while (t--) {
		cin >> n;
		cout << (n <= 2 ? 0 : n-2) << "\n";
	}

	return 0;
}