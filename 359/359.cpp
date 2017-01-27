#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <bitset>
#include <queue> 
using namespace std;

struct MemorySegment{

	uint8_t value;

	uint8_t instruction;
	uint8_t content;

	MemorySegment(uint8_t segment) {
		
		value = segment;

		instruction = 0;
		content = 0;
		
		//extract content
		uint8_t count = 0;
		for (segment; count < 5; segment = segment >> 1){
			//content[count++] = segment & 1;
			if (segment & 1)
				content += (1 << count);
			count++;
		}
		
		count = 0;
		for (segment; count < 3; segment = segment >> 1) {
			//instruction[count++] = segment & 1;
			if (segment & 1)
				instruction += (1 << count);
			count++;
		}
	}
	
	MemorySegment() {

	}


};


struct Memory{

	MemorySegment memorySegment[32];
	uint8_t len;

	uint8_t counter;
	uint8_t acc;
	
	Memory(queue<string> input) {
		
		counter = 0;
		acc = 0;

		uint8_t count = 0;
		for (input; !input.empty(); input.pop())
			memorySegment[count++] = MemorySegment(stoi(input.front(), nullptr, 2));
		len = count;
	};

	void start() {
		bool terminate = false;
		do {
			executeInstruction(counter, terminate);
		} while (!terminate);
	}
	
	void executeInstruction(uint8_t &index, bool &terminate) {

		//FETCH INSTRUCTION
		uint8_t instr = memorySegment[index].instruction;
		uint8_t cont  = memorySegment[index].content;

		//INCREMENT COUNTER
		index++;
		
		//EXCUTE INSTRUCTION
		switch (unsigned(instr))
		{
		case 0://STA
			memorySegment[cont] = MemorySegment(acc);
			break;
		case 1://LDA
			acc = memorySegment[cont].value;
			break;
		case 2://BEQ
			if (acc == 0)
				index = cont;
			break;
		case 3://NOP
			break;
		case 4://DEC
			acc--;
			break;
		case 5://INC
			acc++;
			break;
		case 6://JMP
			index = cont;
			break;
		case 7://HLT
			terminate = true;
			break;
		default:
			break;
		}

	}


	void display() {
		cout << "\n";
		for (uint8_t i = 0; i < len; i++)
			cout << unsigned(memorySegment[i].instruction) << " " << unsigned(memorySegment[i].content) << " \n";
	}
};

int main()
{
	queue<string> x;
	x.push("01100000");
	x.push("00000001");
	Memory m(x);
	m.display();

	bool terminate = false;
	m.executeInstruction(0, terminate);

	

    return 0;
}

