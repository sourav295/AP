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
#include <ctype.h>
#include <map>
#include <iomanip>


using namespace std;


const int n_lines = 5000;
const int n_words_in_line = 200;
const int n_dist_word = 5000;

int max_wordSize = -1;

vector<string> all_words;
map<string, bool> unique_words;

char smallest_word = int('a') - 1;

void countSort(int exp)
{
	string output[n_dist_word]; // output array
	int count[27] = { 0 };
	int i;

	for (i = 0; i < all_words.size(); i++)
		count[(all_words[i])[exp] - 'a' + 1]++;

	for (i = 1; i < 27; i++)
		count[i] += count[i - 1];

	for (i = all_words.size() - 1; i >= 0; i--)
	{
		output[count[(all_words[i])[exp] - 'a' + 1] - 1] = (all_words[i]);
		count[(all_words[i])[exp] - 'a' + 1]--;
	}

	for (i = 0; i < all_words.size(); i++)
		all_words[i] = output[i];
}

void radixsort()
{
	for (int i = 0; i < all_words.size(); i++) {
		for (int j = all_words[i].length();j < max_wordSize; j++) {
			all_words[i].push_back(smallest_word);
		}
	}

	for (int exp = max_wordSize - 1; exp >= 0; exp--)
		countSort(exp);

	
}



int main()
{
	string line;
	string word;
	
	while (getline(cin, line)) {
		int i = 0;
		while(i < line.length()) {
			if (!isalpha(line[i])) {
				i++;
				continue;
			}
			int start = i;
			int end = i;
			while (isalpha(line[end])) {
				line[end] = tolower(line[end]);
				end++;
			}
			i = end;

			word = line.substr(start, end - start);
			if (unique_words.count(word) == 0) {
				int len = word.length();
				if (max_wordSize < len)
					max_wordSize = len;

				unique_words[word] = true;
				all_words.push_back(word);
			}
			
		}
		
	}
	radixsort();
	
	for (int i = 0; i < all_words.size(); i++) {
		int j = 0;
		while (j < all_words[i].length() && isalpha((all_words[i])[j])) {
			cout << (all_words[i])[j];
			j++;
		}
		cout << "\n";
	}

			


    return 0;
}

