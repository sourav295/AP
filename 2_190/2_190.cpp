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
		//cout<< input.front() << "\n";
		//incoming character is a number
		if (isdigit(input.front())) {
			output.push_back(input.front());
		}
		//=========================================
		//Incoming element is a operator
		//incoming character is of higher precedence than stack top(), also manages the case of empty stack!!
		else if (eval.empty() || isIncomingPrecedenceHigher(input.front(), eval)) {
			eval.push(input.front());
			continue;
		}

		//incomin



	}

	return output;
}

//() * / + -

int main()
{


	queue<char> input_queue;
	input_queue.push('2');
	input_queue.push('*');
	input_queue.push('3');
	input_queue.push('-');
	input_queue.push('4');
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

