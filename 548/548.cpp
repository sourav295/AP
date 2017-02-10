// 548.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#include <inttypes.h>
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <stdint.h>
using namespace std;

int main()
{
	
	uint64_t a, b, c, d;
	while (cin >> a >> b) {
		
		c = a ^ b;
		d = 0;

		int i = 0;
		while (c >>= 1) {
			d += (1 << i);
			i++;
		}
		printf("%" PRIu64 "\n", (d | b));
		//printf("%llu\n", );
	}
	
    return 0;
}

