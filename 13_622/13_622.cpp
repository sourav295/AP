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



string dna_seq;

struct Edge {

	int start;
	int end;

	Edge* next;

	Edge(int s, int e) {
		start = s;
		end = e;
		next = NULL;
	}
};





int main() {

	dna_seq = "GATTACA$";
	Edge e(0, dna_seq.length());
	cout << (e.next == NULL);

	return 0;
}




/*
int max_depth = 0;
int occurences = 0;
string output;


class DNA_Node
{
public:
	char c;
	map<char, DNA_Node*> children;
	
	DNA_Node(char character) {
		c = character;
	}
};



void insertDNASeq(DNA_Node* root, string str, int depth, string entireString)
{
	if (str.empty()) return;

	DNA_Node* child;
	if (root->children.count(str[0]) == 0) {
		child = new DNA_Node(str[0]);
		(root->children)[str[0]] = child;

		if (depth > max_depth && root->children.size() >= 2) {
			max_depth = depth;
			occurences = 2;
			output = entireString.substr(0, max_depth);
		}
		else if(depth == max_depth && root->children.size() >= 2){
			
			string potential = entireString.substr(0, max_depth);
			if(output.compare(potential) == 0)
				occurences++;
			else {
				if (output.compare(potential) > 0) {
					//replace
					occurences == 2;
					output = potential;
				}
			}

		}

	}
	else {
		child = root->children[str[0]];
	}

	depth++;

	insertDNASeq(child, str.substr(1), depth, entireString);
}


int main()
{
	
	int n;
	string line, str;
	cin >> n;
	getline(cin, line);
	for (int i = 0; i < n; i++) {

		getline(cin, line);
		DNA_Node* root = new  DNA_Node('%');

		str = line + "$";

		max_depth = 0;
		occurences = 0;
		output = "";

		for (int i = 0; i < str.length() - 1; i++) {
			insertDNASeq(root, str.substr(i), 0, str.substr(i));
		}

		if (max_depth == 0)
			cout << "No repetitions found!\n";
		else
			cout << output << " " << occurences<<"\n";

	}
	
	
	
	
	
	

    return 0;
}

*/