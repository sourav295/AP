#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <utility>
#include <stack>
#include<string>
#include<sstream>
#include<ctype.h>
#include <stdlib.h>
using namespace std;


struct Int_Bracket {

	bool isInt;//true == integer, otherwise (
	int value = 0;

	Int_Bracket(int v) {
		value = v;
		isInt = true;
	}

	Int_Bracket() {
		isInt = false;
	}


	static Int_Bracket evaluate(Int_Bracket o1, char op, Int_Bracket o2) {

		if (op == '+')
			return Int_Bracket(o1.value + o2.value);
		else
			return Int_Bracket(o1.value * o2.value);
	}


};


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

	default:
		return o-'0';
	}

}


bool higherIncomingPrecedence(char incoming_symbol, char stackTop_symbol) {

	if (incoming_symbol == '*' && stackTop_symbol == '+')
		return true;
	return false;
}


int main()
{

	
	
	string line;
	
	while (getline(cin, line)) {
		stack<char>  operator_stack;
		stack<Int_Bracket>  operand_stack;
		
		
		stringstream ss(line);
		char c;
		while (ss >> c) {
			if (c == '(') {
				operand_stack.push(Int_Bracket());
			}
			else if (c == ')') {
				bool terminate = false;
				while (!terminate) {
					char op = operator_stack.top();
					operator_stack.pop();

					Int_Bracket i1 = operand_stack.top();
					operand_stack.pop();
					Int_Bracket i2 = operand_stack.top();
					operand_stack.pop();

					if (operand_stack.top().isInt == false) {
						operand_stack.pop();//remove bracket
						terminate = true;
					}

					operand_stack.push(
						Int_Bracket::evaluate(i1, op, i2)
					);
				}
			}
			else if (isalnum(c)){
				operand_stack.push(Int_Bracket(parseAsInt(c)));
			}
			else{
				
				while (!operator_stack.empty() && !higherIncomingPrecedence(c, operator_stack.top())) {
					char op = operator_stack.top();
					operator_stack.pop();

					Int_Bracket i1 = operand_stack.top();
					operand_stack.pop();
					Int_Bracket i2 = operand_stack.top();
					operand_stack.pop();

					operand_stack.push(
						Int_Bracket::evaluate(i1, op, i2)
					);
				}
				operator_stack.push(c);
			}
		}

		while (!operator_stack.empty()) {
			char op = operator_stack.top();
			operator_stack.pop();

			Int_Bracket i1 = operand_stack.top();
			operand_stack.pop();
			Int_Bracket i2 = operand_stack.top();
			operand_stack.pop();

			operand_stack.push(
				Int_Bracket::evaluate(i1, op, i2)
			);
		}
		

		stringstream ss1;
		int ans = operand_stack.top().value;

		ss1 << std::hex << ans;
		string res(ss1.str());

		cout << res;
	}
	


    return 0;
}

