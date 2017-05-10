#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include <string.h>
#include <string>
#include <stack>
#include <limits>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <map>
using namespace std;

const int n_limit = 1005;

int cmp(string a, string b)
{
	return a.compare(b) < 0 ? 1 : 0;
}



int occurences;
int max_similarity;
string answer;

int getSimilarity(string a, string b) {
	int similarity = 0;
	for (int i = 0; i < min(a.length(), b.length()); i++) {
		if (a[i] == b[i])
			similarity++;
		else
			return similarity;
	}
	return similarity;
}

int main() {

	string suffixArray[n_limit];
	int t;
	string line;
	cin >> t;
	getline(cin, line);
	for (int test = 0; test < t; test++) {
		getline(cin, line);

		occurences = 0;
		max_similarity = 0;
		
		int n = line.length();
		for (int i = 0; i < n; i++) {
			string sub_string = line.substr(i);
			suffixArray[i] = sub_string;
		}

		sort(suffixArray, suffixArray + n, cmp);

		int i, j;
		i = 0;
		while (i < n) {
			j = i + 1;
			
			//ith is the reference and first check if it can exceed the max_similarity
			if (j < n) {
				int similarity = getSimilarity(suffixArray[i], suffixArray[j]);

				if (similarity > max_similarity) {
					max_similarity = similarity;
					answer = suffixArray[i].substr(0, max_similarity);
					occurences = 2;


					//check for more occurences
					j++;
					while (j < n) {
						if (getSimilarity(answer, suffixArray[j]) == max_similarity)
							occurences++;
						else
							break;
						j++;
					}
				}
			}
			i++;
		}
		if(max_similarity==0)
			cout << "No repetitions found!\n";
		else
			cout << answer << " " << occurences << "\n";

	}


	return 0;
}