#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <bitset>
#include <queue> 

using namespace std;

const int n_limit = 32;
unsigned int pc, acc;

const int oprt_mask = (1 << 5) + (1 << 6) + (1 << 7);
const int oprd_mask = (1 << 5) - 1;

struct Instruction{
	unsigned int overall;
	unsigned int oprt;
	unsigned int oprd;

	Instruction(){}

	Instruction(int x){
		overall = x;
		oprt = x & oprt_mask;
		oprd = x & oprd_mask;
	}

	

}mem[n_limit];

bool run(Instruction i){
	switch (i.oprt)
	{
	case 0: mem[i.oprd] = Instruction(acc);
		break;
	case 1: acc = i.overall;
		break;
	case 2: pc  = acc == 0 ? i.oprd : pc;
		break;
	case 3:
		break;
	case 4:acc--;
		break;
	case 5:acc++;
		break;
	case 6:pc = i.oprd;
		break;
	case 7:return true;
		break;


	default:
		break;
	}

	return false;
}

int execute(){
	bool terminate = false;
	while(!terminate){
		pc = 0;
		Instruction inst = mem[pc];
		pc++;
		terminate = run(inst);
		
	}
	return acc;
}

int main()
{
	int count = 0;
	pc = 0;
	acc = 0;

	

	unsigned int x, y;
	while (cin >> x){
		//convert binary to int
		y = 0;
		for (int i = 0; i < 8; i++){
			if ((x >> i) & 1)
				y += (1 << i);
		}

		mem[count] = Instruction(y);
		count++;


		if (count == 32){
			
			
			int res = execute();
			//convert to binary
			count = 0;
			pc    = 0;
			acc = 0;
			
		}
	}
	
    return 0;
}
