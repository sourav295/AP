#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
//#include <utility>
#include <stack> 
using namespace std;


class Operand {

	char symbol;
	
public:
	Operand(char sym) {
		symbol = sym;
	}

	const char getSymbol() const{
		return symbol;
	}

	bool operator==(const Operand other) const { return ((other.getSymbol()) == symbol); }

};

class OperandState
{
	Operand operand = NULL;
	bool state;

public:
	
	OperandState(Operand op, bool val) {
		operand = op;
		state = val;
	}

	const Operand getOperand() const {
		return operand;
	}

	const Operand getState() const {
		return state;
	}

	bool operator==(const OperandState other) const { return ((other.getOperand()) == operand) && (other.getState()==state); }

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

