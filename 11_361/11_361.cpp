#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <queue> 
#include <string>
#include <stack>
#include <limits>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <fstream>
#include <map>
using namespace std;

const unsigned long long x_lim = (unsigned long long)18446744073709551615;
const unsigned long long x_lim_by_4 = x_lim >> 2;//x*2^2 <= 2^64 - 2^0




void setAsSuperPower(unsigned long x) {
	x = x - 2;
	flag[(x >> 6)] |= (
							1 << (x & 63) 
					  );
}

bool isSuperPower(unsigned long x) {
	x = x - 2;
	return	flag[(x >> 6)] & (
								1 << (x & 63) 
							 );
}


int main()
{
	for (unsigned long long i = 2; i <= x_lim; i++) {
		if (!isSuperPower(i)) {
			unsigned long long j    = i;
			unsigned long long j_sq = i*i;

			while(j <= x_lim)

		}
	}
	
	
    return 0;
}

