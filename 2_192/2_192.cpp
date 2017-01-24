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

	static TreeNode* initalize(int weight, int distance_to_parent) {
		struct TreeNode *newNode = (struct TreeNode*) malloc(sizeof(struct TreeNode));
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->weight = weight;
		newNode->distance_to_parent = distance_to_parent;

		return newNode;
	}

};

void construct_tree(queue<InputLine>& input_queue, TreeNode* parent) {

	InputLine input_line = input_queue.front();
	input_queue.pop();

	
	TreeNode* leftChild = TreeNode::initalize(input_line.weight_left, input_line.distance_left);
	parent->left = leftChild;

	TreeNode* rightChild = TreeNode::initalize(input_line.weight_right, input_line.distance_right);
	parent->right = rightChild;
	
	
	if (input_line.weight_left == 0) {
		//has a left child
		construct_tree(input_queue, leftChild);
	}

	if (input_line.weight_right == 0) {
		//has a right child
		construct_tree(input_queue, rightChild);
	}

}


//<isBalanced, weight of subtree >
pair <bool, int> isBalanced(TreeNode* parent) {





	return make_pair(true, 3);

}



int main()
{
	queue<InputLine> input_queue;
	
	TreeNode* root_fulcrum = TreeNode::initalize(0, 0);
	input_queue.push(InputLine(1, 6, 3, 2));

	construct_tree(input_queue, root_fulcrum);
	cout << ((root_fulcrum->right->right->right) == NULL);

	return 0;
}

/* == TEST CASE ==
TreeNode* root_fulcrum = TreeNode::initalize(0, 0);
input_queue.push(InputLine(0, 2, 0, 4));
input_queue.push(InputLine(0, 3, 0, 1));
input_queue.push(InputLine(1, 1, 1, 1));
input_queue.push(InputLine(2, 4, 4, 2));
input_queue.push(InputLine(1, 6, 3, 2));

construct_tree(input_queue, root_fulcrum);

cout<< (root_fulcrum->right->right->weight);
*/