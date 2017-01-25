#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <utility>
#include <stack> 
using namespace std;

//////////////////////////////////////////////
void printStackState(stack<char> dump) {
	for (dump; !dump.empty(); dump.pop())
		cout << dump.top() << '\t';
}

void printStackState(stack<int> dump) {
	for (dump; !dump.empty(); dump.pop())
		cout << dump.top() << '\t';
}
//TESTING

///////////////////////////////////////////////


int parseAsInt(char o) {

	switch (o)
	{
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	case '(':
		return -1;
	case ')':
		return -2;

	default:
		return o-'0';
	}

}



int evaluate(int o1, char op, int o2) {

	if (op == '+')
		return o1 + o2;
	else
		return o1 * o2;
}

int extract_and_evaluate(stack<char>& operator_stack, stack<int>& operand_stack) {
	int o1 = operand_stack.top();
	operand_stack.pop();
	int o2 = operand_stack.top();
	operand_stack.pop();
	
	return evaluate(o1, operator_stack.top(), o2);
}



void insert_operand(stack<char>& operator_stack, stack<int>& operand_stack, int o) {

	// handles ')'
	if (o == -2) {
		while (true) {
			int res = extract_and_evaluate(operator_stack, operand_stack);
			operator_stack.pop();
			
			bool doExit = false;
			if (operand_stack.top() == -1) {
				doExit = true;
				operand_stack.pop();//remove -1
			}

			operand_stack.push(res);
			if (doExit)
				break;
		}

		return;
	}

	operand_stack.push(o);
	
}


void insert_operator(stack<char>& operator_stack, stack<int>& operand_stack, char op) {
	
	//2 cases where we need to extract and evaluate
	if (op == '+' && !operator_stack.empty() && operator_stack.top() == '*') {//Need to extract
		while(!operator_stack.empty()){
			insert_operand(operator_stack, operand_stack, extract_and_evaluate(operator_stack, operand_stack) );
			operator_stack.pop();
		}
		operator_stack.push(op);//push new oprator
		return;
	}

	if (op == '*' && !operator_stack.empty() && operator_stack.top() == '*') {
		while (!operator_stack.empty() && operand_stack.top() == '+') {
			insert_operand(operator_stack, operand_stack, extract_and_evaluate(operator_stack, operand_stack) );
			operator_stack.pop();
		}
		operator_stack.push(op);
		return;
	}
	//no manipulation required, just push
	operator_stack.push(op);

}



int main()
{

	stack<char> operator_stack;
	stack<int>  operand_stack;
	char line[] = "(4+5)*3+5";

	
	for (int i = 0; line[i] != '\0'; i++){
		if (line[i] == '+' || line[i] == '*') {
			insert_operator(operator_stack, operand_stack, line[i]);
			cout << "==============\nInsert " << line[i] << ": ";printStackState(operator_stack);cout << "<>";printStackState(operand_stack);cout << "\n";
		}
		else{
			insert_operand(operator_stack, operand_stack, parseAsInt(line[i]));
			cout << "==============\nInsert " << line[i] << ": ";printStackState(operator_stack);cout << "<>";printStackState(operand_stack);cout << "\n";
		}
	}



	while (!operator_stack.empty()) {
		insert_operand(operator_stack, operand_stack, extract_and_evaluate(operator_stack, operand_stack));
		operator_stack.pop();
		
	}
	
	//printStackState(operator_stack);
	
	cout << "\n\n";
	printStackState(operand_stack);
	

    return 0;
}

