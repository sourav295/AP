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

int max_word = -1;//'z' - 'a' + 1;
map<string, bool> uniqueWords;

struct Word{
	int w[n_words_in_line];
	string text;

	Word(string x) {
		text = x;
		int n = x.length();
		for (int i = 0; i < n; i++) {
			w[i] = tolower(x[i]) - 'a';
			text[i] = tolower(x[i]);
		}
		for (int i = n; i < n_words_in_line; i++) {
			w[i] = max_word;
		}
	}
	Word() {}
};


vector<Word> allwords;
int pos = 0;
bool isAlphabeticallySmaller(const Word& x, const Word& y) { return x.w[pos]< y.w[pos]; }

int main()
{
	string line;
	string word;
	int max_wordSize = 0;
	while (getline(cin, line)) {
		
		int i = 0;
		while(i < line.length()) {
			if (!isalnum(line[i])) {
				i++;;
				continue;
			}
			int start = i;
			int end = i;
			while (isalnum(line[end])) {
				end++;
			}
			i = end;

			word = line.substr(start, end - start);
			if (max_wordSize < word.length())
				max_wordSize = word.length();

			if (uniqueWords.find(word) == uniqueWords.end()) {
				allwords.push_back(Word(word));
				uniqueWords[word] = true;
			}
		}
		
	}
	
	for (pos = max_wordSize - 1; pos >= 0; pos--)
		sort(allwords.begin(), allwords.end(), isAlphabeticallySmaller);
	
	for (int i = 0; i < allwords.size(); i++)
		cout << allwords[i].text << "\n";
		//if(i == 0 || (i > 0 && allwords[i].text != allwords[i-1].text))
			


    return 0;
}

