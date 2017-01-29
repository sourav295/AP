#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
//#include <utility>
#include <stack> 
using namespace std;


struct OperandState
{
	char operand;
	bool state;
	OperandState(char op, bool val) {
		operand = op;
		state = val;
	}
	bool operator==(const OperandState other) const { return ((other.operand) == operand) && (other.state==state); }

};

class State {

	vector<OperandState> constrained_operands;

public:
	bool checkConstraint(OperandState otherState) {
			
	}

	

};





void insert_operand(stack<char>& operator_stack, stack<int>& operand_stack, int o) {

	
}


void insert_operator(stack<char>& operator_stack, stack<int>& operand_stack, char op) {

	
}



int main()
{


	return 0;
}

