#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <bitset>
#include <queue> 
using namespace std;

struct MemorySegment{

	uint8_t instruction;
	uint8_t content;

	MemorySegment(uint8_t segment) {
		
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


	void display() {
		cout << "\n";
		for (uint8_t i = 0; i < len; i++)
			cout << unsigned(memorySegment[i].instruction)<<" " << unsigned(memorySegment[i].content) << " \n";
	}
	
	void interpretInstruction(uint8_t index) {

		uint8_t instr = memorySegment[index].instruction;
		
		switch (unsigned(instr))
		{
		case 0:
			cout << "0";
			break;
		case 1:
			cout << "1";
			break;
		case 2:
			cout << "2";
			break;
		case 3:
			cout << "3";
			break;
		case 4:
			cout << "4";
			break;
		case 5:
			cout << "5";
			break;
		case 6:
			cout << "6";
			break;
		case 7:
			cout << "7";
			break;
		default:
			break;
		}

	}

};

int main()
{
	queue<string> x;
	x.push("01100000");
	x.push("00000001");
	Memory m(x);
	m.display();

	
	m.interpretInstruction(0);

	

    return 0;
}

