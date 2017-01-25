#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <utility>
#include <stack> 
using namespace std;


struct available_options
{
	bool can_be_false;
	bool can_be_true;

	available_options() {
		can_be_false = true;
		can_be_true = true;
	}
};


class Operand {

	char symbol;
	available_options availability;

	Operand(char sym) {
		symbol = sym;
		availability = available_options();
	}

	static available_options generateOptions(Operand op1,) {

	}
};

class Operator {

	char 

};





void insert_operand(stack<char>& operator_stack, stack<int>& operand_stack, int o) {

	
}


void insert_operator(stack<char>& operator_stack, stack<int>& operand_stack, char op) {

	
}



int main()
{

	


	return 0;
}

