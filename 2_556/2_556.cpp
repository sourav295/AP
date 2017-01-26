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

	bool operator==(const OperandState other) const { return ((other.getOperand()) == operand); }

};

class State {

	vector<OperandState> constrained_operands;
	


	

};





void insert_operand(stack<char>& operator_stack, stack<int>& operand_stack, int o) {

	
}


void insert_operator(stack<char>& operator_stack, stack<int>& operand_stack, char op) {

	
}



int main()
{

	


	return 0;
}

