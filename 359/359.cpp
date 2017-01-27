#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <bitset>
#include <queue> 
using namespace std;

struct MemorySegment{

	bitset<3> instruction;
	bitset<5> content;

	MemorySegment(uint8_t segment) {
		
				
		//extract content
		uint8_t count = 0;
		for (segment; count < 5; segment >> 1){
			content[count++] = segment & 1;
			cout << (segment & 1) << "\n";
		}
		count = 0;
		for (segment; count < 3; segment >> 1) {
			instruction[count++] = segment & 1;
			cout << (segment & 1) << "\n";
		}

		cout << instruction[2] << instruction[1] << instruction[0];

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
			//memorySegment[count++] = MemorySegment(stoi(input.front(), nullptr, 2));
		len = count;
	};

	/*
	void display() {
		cout << "\n";
		for (uint8_t i = 0; i < len; i++)
			cout << unsigned(memorySegment[i])<<", ";
	}
	*/
	

};


int main()
{
	//queue<string> x;
	//x.push("00000000");
	//x.push("00000001");
	//Memory m(x);
	//m.display();

	
	MemorySegment x = MemorySegment((stoi("11111110", nullptr, 2)));
	//cout<< x.instruction[0];



    return 0;
}

