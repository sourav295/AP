#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <stack>
#include <limits>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <map>
using namespace std;


enum Character_Enum {
	ch_space,
	ch_operator,
	ch_operand
};

Character_Enum getCharacterCategory(char ch) {
	if (ch == '&' || ch == '+' || ch == '!')
		return ch_operator;
	else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return ch_operand;
	return ch_space;
}

bool evaluate(char operand_1, char operand_2, char operator_1) {
	bool result;
	switch (operator_1) {
	case '&':
		result = operand_1 & operand_2;
		return result;
	case '+':
		result = operand_1 + operand_2;
		return result;
	case '!':
		result = !operand_1;
		return result;
	}
}

int getPriority(char operator_ch) {
	switch (operator_ch) {
	case '(':
	case ')':
		return -1;
	case '+':
		return 0;
	case '&':
		return 1;
	case '!':
		return 2;
	}
}

bool getPrecedence(char operator_1, char operator_2) {
	return getPriority(operator_1) >= getPriority(operator_2);
}

stack<char> operand_stack;
stack<char> operator_stack;

void popEvaluatePush() {
	char a, b;
	char operator_ch = operator_stack.top();
	operator_stack.pop();

	if (operator_ch == '!')
	{
		a = operand_stack.top();
		operand_stack.pop();
		operand_stack.push(evaluate(a, a, operator_ch));
	}

	else
	{
		a = operand_stack.top();
		operand_stack.pop();
		
		b = operand_stack.top();
		operand_stack.pop();
		
		operand_stack.push(evaluate(a, b, operator_ch));
	}
}

bool execute(string exp) {
	

	for (unsigned int i = 0; i < exp.length(); i++)
	{
		char incoming_character = exp[i];

		if (incoming_character == ' ')
			continue;
		if (getCharacterCategory(incoming_character) == ch_operand)
			operand_stack.push(incoming_character);
		else if (incoming_character == '(')
			operator_stack.push(incoming_character);
		else if (incoming_character == ')'){
			while (operator_stack.top() != '(') {
				popEvaluatePush();
			}
			operator_stack.pop();
		}
		else if (getCharacterCategory(incoming_character)==ch_operator){
			while (!operator_stack.empty() && getPrecedence(operator_stack.top(), incoming_character)){
				popEvaluatePush();
			}
			operator_stack.push(incoming_character);
		}
	}


	while (!operator_stack.empty()){
		popEvaluatePush();
	}

	return operand_stack.top();


}


void clearStack() {
	while (!operand_stack.empty())
		operand_stack.pop();
	while (!operator_stack.empty())
		operator_stack.pop();
}

int main()
{
	string exp;
	while (getline(cin, exp)) {
		clearStack();
		cout << (execute(exp) ? "YES" : "NO") << "\n";
	}

	return 0;
}

/*




bool returnprecedenceOfOperators(char opp1, char opp2)
{
char op1 = opp1;
char op2 = opp2;

int w1 = returnBooleanpriority(op1);
int w2 = returnBooleanpriority(op2);

if (w1 > w2 || w1 == w2)
{
return true;
}

else
{
return false;
}

}


int evaluate_Boolean_Expression(string exp)
{
string evaluated_expression = "";
stack<char> mystack_Operands;
stack<char> mystack_BooleanOperators;

for (unsigned int i = 0; i < exp.length(); i++)
{
char c = exp[i];

if (c == ' ')
{
continue;
}

if (checkforBooleanOperand(c))
{
mystack_Operands.push(c);
}

else if (c == '(')
{
mystack_BooleanOperators.push(c);
}


else if (c == ')')
{
while (mystack_BooleanOperators.top() != '(')

{

char oper = mystack_BooleanOperators.top();
mystack_BooleanOperators.pop();

if (oper == '!')
{
char a = mystack_Operands.top();
mystack_Operands.pop();
mystack_Operands.push(evaluate_BooleanOperation(a, a, oper));
}

else
{
char a = mystack_Operands.top();
mystack_Operands.pop();
char b = mystack_Operands.top();
mystack_Operands.pop();
mystack_Operands.push(evaluate_BooleanOperation(a, b, oper));
}


}
mystack_BooleanOperators.pop();

}

else if (checkforBooleanOperator(c))
{
while (!mystack_BooleanOperators.empty() && returnprecedenceOfOperators(mystack_BooleanOperators.top(), c))
{

char oper = mystack_BooleanOperators.top();
mystack_BooleanOperators.pop();

if (oper == '!')
{
char a = mystack_Operands.top();
mystack_Operands.pop();
int val = evaluate_BooleanOperation(a, a, oper);
mystack_Operands.push(val);
}

else
{
char a = mystack_Operands.top();
mystack_Operands.pop();
char b = mystack_Operands.top();
mystack_Operands.pop();
int val = evaluate_BooleanOperation(a, b, oper);
mystack_Operands.push(val);
}


}
mystack_BooleanOperators.push(c);
}


}


while (!mystack_BooleanOperators.empty())
{


char oper = mystack_BooleanOperators.top();
mystack_BooleanOperators.pop();

if (oper == '!')
{
char a = mystack_Operands.top();
mystack_Operands.pop();
mystack_Operands.push(evaluate_BooleanOperation(a, a, oper));

}

else
{
char a = mystack_Operands.top();
mystack_Operands.pop();
char b = mystack_Operands.top();
mystack_Operands.pop();
mystack_Operands.push(evaluate_BooleanOperation(a, b, oper));
}



}

return mystack_Operands.top();

}

int main()

{

string line;

while (getline(cin, line) && line.at(0) != '\0')
{
bool value = evaluate_Boolean_Expression(line);

if (value)
{
printf("%s\n", "YES");
}
else
{
printf("%s\n", "NO");
}


}


return 0;
}

*/