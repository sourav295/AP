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
using namespace std;




const int n_limit = 100;



enum CellStage{
	SIMPLE,
	FULLYGROWN,
	MUTAGENIC,
	MUTANT

};

void print_cell(CellStage ans) {
	switch (ans)
	{
	case SIMPLE:
		cout << "SIMPLE";
		break;
	case FULLYGROWN:
		cout << "FULLY-GROWN";
		break;
	case MUTAGENIC:
		cout << "MUTAGENIC";
		break;
	case MUTANT:
		cout << "MUTANT";
		break;
	default:
		break;
	}

	cout << "\n";
}

CellStage check(int start, int end, char cell[]) {
	int length_cell = end - start + 1;

	if (length_cell == 1) {
		if (cell[start] == 'A')
			return SIMPLE;
		else 
			return MUTANT;
	}
	else if (cell[end - 1] == 'A' && cell[end] == 'B') {
		CellStage nestedCell = check(start, end - 2, cell);

		return nestedCell == MUTANT ? MUTANT : FULLYGROWN;
	}
	else if (cell[start] == 'B' && cell[end] == 'A') {
		CellStage nestedCell = check(start+1, end-1, cell);

		return nestedCell == MUTANT ? MUTANT : MUTAGENIC;
	}
	else {
		return MUTANT;
	}

}


int main()

{
	char cell[n_limit];
	int N;
	string line;
	cin >> N;

	while (N--) {
		cin >> line;
		for (int i = 0; i < line.length(); i++) {
			cell[i] = line[i];
		}

		print_cell(check(0, line.length() - 1, cell));

	}

	


	return 0;
}