#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <utility>
#include <stack> 
#include <queue>
#include <ctype.h>
#include <string>

using namespace std;

bool isIncomingPrecedenceHigher(char incoming_symbol, stack<char> &eval) {

	if (eval.empty() || eval.top() == '(')
		return true;

	char stack_top_value = eval.top();

	switch (incoming_symbol)
	{

	case('*'):
	case('/'):
		if (stack_top_value == '+' || stack_top_value == '-')
			return true;
		return false;
	default:
		return false;
	}
}


string convertToPostFix(queue<char> input) {

	string output = "";
	stack<char> eval;

	for (input; !input.empty(); input.pop()) {
		
		char incoming_operator = input.front();
		
		//incoming character is a number
		if (isdigit(incoming_operator)) {
			output.push_back(incoming_operator);
		}
		//=========================================
		//Incoming element is a operator
		//incoming character is of higher precedence than stack top(), also manages the case of empty stack!!
		else if (isIncomingPrecedenceHigher(incoming_operator, eval)) {
			eval.push(incoming_operator);
			continue;
		}
		//special case - handles brace operators
		else if (incoming_operator == '(') {
			eval.push(incoming_operator);
		}
		else if (incoming_operator == ')') {
			while (eval.top() != '(') {
				output.push_back(eval.top());
				eval.pop();
			}
			//remove left brace
			eval.pop();
		}
		//incoming character is of lower precendence
		else {
			//achieve the state where the incoming has the highest precedence, keep popping till then
			while (isIncomingPrecedenceHigher(incoming_operator, eval)) {
				output.push_back(eval.top());
				eval.pop();
			}
			//coveted state achieved
			eval.push(incoming_operator);
		}
	}

	//extract remaining operator
	for(eval; !eval.empty(); eval.pop())
		output.push_back(eval.top());



	return output;
}

//() * / + -

int main()
{


	queue<char> input_queue;
	input_queue.push('2');
	input_queue.push('*');
	input_queue.push('(');
	input_queue.push('3');
	input_queue.push('-');
	input_queue.push('4');
	input_queue.push(')');
	input_queue.push('/');
	input_queue.push('5');

	cout << convertToPostFix(input_queue);

	/*
	stack<char> test;
	test.push('*');
	cout << isIncomingPrecedenceHigher('+', test);
	*/



    return 0;
}
/*

A summary of the rules follows:

1. Print operands as they arrive.

2. If the stack is empty or contains a left parenthesis on top, push the incoming operator onto the stack.

3. If the incoming symbol is a left parenthesis, push it on the stack.

4. If the incoming symbol is a right parenthesis, pop the stack and print the operators until you see a left parenthesis. Discard the pair of parentheses.

5. If the incoming symbol has higher precedence than the top of the stack, push it on the stack.

6. If the incoming symbol has equal precedence with the top of the stack, use association. If the association is left to right, pop and print the top of the stack and then push the incoming operator. If the association is right to left, push the incoming operator.

7. If the incoming symbol has lower precedence than the symbol on the top of the stack, pop the stack and print the top operator. Then test the incoming operator against the new top of stack.

8. At the end of the expression, pop and print all operators on the stack. (No parentheses should remain.)




*/

