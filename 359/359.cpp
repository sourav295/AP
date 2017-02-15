#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <inttypes.h>
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
			memorySegment[count++] = MemorySegment((bitset<8>(input.front())).to_ulong());
			//memorySegment[count++] = MemorySegment(stoi(input.front(), nullptr, 2));
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
	string line;
	
	int count = 0;
	while (getline(cin, line))
	{
		count++;
		x.push(line);

		if (count == 32){
			//execute
			Memory m(x);
			m.start();
			cout << bitset<8>((unsigned)m.acc) << "\n";

			count = 0;
			x = queue<string>();

		}
		
	}
	

	

	
	
    return 0;
}

/*
	x.push("00111110");
	x.push("10100000");
	x.push("01010000");
	x.push("11100000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00111111");
	x.push("10000000");
	x.push("00000010");
	x.push("11000010");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("00000000");
	x.push("11111111");
	x.push("10001001");
	*/