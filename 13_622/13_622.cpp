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
#include <unordered_map>
using namespace std;

class DNA_Node
{
public:
	char c;
	unordered_map<char, DNA_Node*> children;
	
	DNA_Node(char character) {
		c = character;
	}


};

void insertDNASeq(DNA_Node* root, string str)
{
	if (str.empty()) return;

	DNA_Node* child;
	if (root->children.count(str[0]) == 0) {
		child = new DNA_Node(str[0]);
		(root->children)[str[0]] = child;
	}
	else {
		child = root->children[str[0]];
	}

	insertDNASeq(child, str.substr(1));
}


int main()
{
	DNA_Node* root = new  DNA_Node('%');

	string str = "banana$";

	for (int i = 0; i < str.length() - 1; i++) {
		insertDNASeq(root, str.substr(i));
	}


    return 0;
}

