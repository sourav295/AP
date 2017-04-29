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

const int oprt_mask = (1 << 3) - 1;
const int oprd_mask = (1 << 5) - 1;

struct Instruction{
	unsigned int overall;
	unsigned int oprt;
	unsigned int oprd;

	Instruction(){}

	Instruction(unsigned int x){
		overall = x;
		oprt = (x >> 5) & oprt_mask;
		oprd = x & oprd_mask;
	}

	

}mem[n_limit];

bool run(Instruction i){
	switch (i.oprt)
	{
	case 0: mem[i.oprd] = Instruction(acc);
		break;
	case 1: acc = mem[i.oprd].overall;
		break;
	case 2: pc  = acc == 0 ? i.oprd : pc;
		break;
	case 3:
		break;
	case 4:acc = (acc == 0 ? 255 : acc - 1);
		break;
	case 5:acc = (acc == 255 ? 0 : acc + 1);
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
	pc = 0;
	while(!terminate){
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

	
	bitset<8> x;
	unsigned int y;
	while (cin >> x){
		//convert binary to int
		y = (unsigned int)x.to_ulong();

		mem[count] = Instruction(y);
		count++;


		if (count == 32){
			int res = execute();
			bitset<8> output(res);
			cout << output << "\n";
			
			count = 0;
			pc    = 0;
			acc   = 0;
			
		}
	}
	
    return 0;
}
