#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <utility>
#include <queue> 
using namespace std;


//pair <int, int> p = std::make_pair(1, 2);
//cout << p.first << " " << p.second << std::endl;

struct InputLine {
	int weight_left;
	int distance_left;
	int weight_right;
	int distance_right;

	InputLine(int wl, int dl, int wr, int dr) {
		weight_left		= wl;
		distance_left	= dl;
		weight_right	= wr;
		distance_right	= dr;
	}

};


struct TreeNode {
	int weight;        
	int distance_to_parent;
	TreeNode *left;			// Pointer to the left subtree.
	TreeNode *right;		// Pointer to the right subtree.

};

void construct_tree(int wl, int dl, int w2, int d2) {



}

TreeNode* construct_root() {
	struct TreeNode *rootNode = (struct TreeNode*) malloc(sizeof(struct TreeNode));
	
	rootNode->weight = 0;
	rootNode->distance_to_parent = 0;

	return rootNode;
}

void connect_left(TreeNode *parent, int w, int d) {

}

void connect_right(TreeNode *parent, int w, int d) {

}


int main()
{

	TreeNode* root_fulcrum = construct_root();

	cout << root_fulcrum->distance_to_parent;


	return 0;
}

