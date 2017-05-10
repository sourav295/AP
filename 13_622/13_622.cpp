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
/*
struct Edge;

int max_depth;
string final_answer;
int occurences = 0;
string dna_seq;

struct Node {

	map<char, Edge*> firstCharacter_Edge;

	Node() {

	}

	void insert_edge(int start, int end);
};



struct Edge {

	int start;
	int end;

	Node *nextNode;

	Edge(int s, int e) {
		start = s;
		end = e;
		
		nextNode = new Node();
	}

	void insert(int other_start, int other_end) {
		
		//copy the decendants of the node following this edge
		map<char, Edge*> temporary_map;
		map<char, Edge*>::iterator it;
		for (it = nextNode->firstCharacter_Edge.begin(); it != nextNode->firstCharacter_Edge.end(); it++)
		{
			temporary_map[it->first] = it->second;
		}
		

		int j = start;//this string
		int i;//other string being inserted
		for (i = other_start; i <= other_end && j <= end; i++, j++) {
			if (dna_seq[i] != dna_seq[j]) {
				break;
			}
		}
		
		//inserting new string related edge
		nextNode->insert_edge(i, dna_seq.length()-1);
		//remaining part of the base
		if (j <= end) {
			nextNode->insert_edge(j, end);
			//transfer all edges that were pointed from this node to the newly generated node that consists of a part of the previous string
			char newBranchBase_firstchar = dna_seq[j];
			for (it = temporary_map.begin(); it != temporary_map.end(); it++)
			{
				//next node that consists a part of this string -> over that edge to the next node -> restore the previous branches here
				nextNode->firstCharacter_Edge[newBranchBase_firstchar]->nextNode->firstCharacter_Edge[it->first] = it->second;
				nextNode->firstCharacter_Edge.erase(it->first);
			}
			end = j - 1;
		}
	}

	int getSize() {
		return end - start + 1;
	}
};


void Node::insert_edge(int start, int end) {
	char first_char = dna_seq[start];

	if (firstCharacter_Edge.count(first_char) == 0) {
		//not found
		Edge *newEdge = new Edge(start, end);
		firstCharacter_Edge[first_char] = newEdge;
	}
	else {
		firstCharacter_Edge[first_char]->insert(start, end);
	}
}

void search(Node *x, int depth, string ans) {
	
	if (x->firstCharacter_Edge.size() == 0)
		return;

	if (x->firstCharacter_Edge.size() > 1 && max_depth < depth) {
		occurences = x->firstCharacter_Edge.size();
		max_depth = depth;
		final_answer = ans;
	}else if (x->firstCharacter_Edge.size() > 1 && max_depth == depth && ans.compare(final_answer) < 0) {
		occurences = x->firstCharacter_Edge.size();
		final_answer = ans;
	}

	map<char, Edge*>::iterator it;
	for (it = x->firstCharacter_Edge.begin(); it != x->firstCharacter_Edge.end(); it++)
	{
		Edge *e = x->firstCharacter_Edge[it->first];
		search(e->nextNode, depth + e->getSize(), ans + dna_seq.substr(e->start, e->getSize()));
	}

}

int main() {

	int n;
	string line;
	cin >> n;
	getline(cin, line);
	for (int i = 0; i < n; i++) {

		getline(cin, line);
		dna_seq = line + "$";

		//dna_seq = "CAGTCAGG$";
		//dna_seq = "GKLGABXYGABMN$";
		int end = dna_seq.length() - 1;
		Node *base = new Node();
		for (int start = dna_seq.length() - 2; start >= 0; start--) {
			base->insert_edge(start, end);
		}
		max_depth = 0;
		occurences = 0;
		final_answer = "";
		search(base, 0, "");
		
		if (max_depth == 0)
			cout << "No repetitions found!\n";
		else
			cout << final_answer << " " << occurences << "\n";

	}
	

	return 0;
}
*/
const int n_limit = 100;

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