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

struct Edge;


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
		for (i = other_start; i <= other_end, j <= end; i++, j++) {
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

int search(Node *x, int depth) {
	if (x->firstCharacter_Edge.size() == 0)
		return depth;

	map<char, Edge*>::iterator it;
	for (it = x->firstCharacter_Edge.begin(); it != x->firstCharacter_Edge.end(); it++)
	{
		Edge *e = x->firstCharacter_Edge[it->first];
		search(e->nextNode, e->getSize());
	}

}

int main() {

	//dna_seq = "CAGTCAGG$";
	dna_seq = "GKLGABXYGABMN$";
	int end = dna_seq.length() - 1;
	Node *base = new Node();
	for (int start = dna_seq.length() - 2; start >= 0; start--) {
		base->insert_edge(start, end);
	}
	

	cout << 5;

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