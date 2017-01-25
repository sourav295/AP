#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <utility>
#include <stack> 
using namespace std;


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




int evaluate(char o1, char op, char o2) {

	if (op == '+')
		return o1 + o2;
	else
		return o1 * o2;
}

void insert_operand(stack<int>& stack_var, char o) {

	stack_var.push(o);
}

void insert_operator(stack<char>& operator_stack, stack<int>& operand_stack, char op) {
	
	if (op == '+' && operator_stack.top() == '*') {
		//insertion of a lower precedence character. Since we need to pop until there is a lower precedence character at top, we have to empty the stack as [+] is the lowest one
		while(!operator_stack.empty()){
			int o1 = operand_stack.top();
			operand_stack.pop();
			int o2 = operand_stack.top();
			operand_stack.pop();
			operand_stack.push(evaluate(o1, 
										operator_stack.top(),
										o2)
			);

			operator_stack.pop();
		}

		operator_stack.push(op);

	}

	//op = '*' && top = '*'
	//when empty



	operator_stack.push(op);
}

void printStackState(stack<char>& dump) {
	for (dump; !dump.empty(); dump.pop())
		cout << dump.top() << '\n';
}

int main()
{
	stack<char> operator_stack;
	stack<int>  operand_stack;
	char line[] = "4+5*3+5";

	for (int i = 0; line[i] != '\0'; i++)
		if (line[i] == '+' || line[i] == '*')
			insert_operator(operator_stack, operand_stack, line[i]);
		else
			insert_operand(operand_stack, parseAsInt(line[i]));

	
	//printStackState(operator_stack);
	
	
	

    return 0;
}

