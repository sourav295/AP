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
using namespace std;


long long calcKey(long n)
{


	bool two_is_a_factor = false;
	bool other_factor    = false;
	long latest_factor   = 0;
	long long key        = 0;

	while (n % 2 == 0){
		n = n / 2;
		two_is_a_factor = true;
		latest_factor   = 2;
	}
	if (two_is_a_factor)
		key += 2;

	for (int i = 3; i <= n; i = i + 2)
	{
		other_factor = false;
		while (n%i == 0){
			other_factor = true;
			n = n / i;
		}

		if(other_factor){
			latest_factor = i;
			key += latest_factor;
		}
	}

	return (2 * latest_factor) - (key);

}

void compare(long n1, long n2) {
	if (calcKey(n1) > calcKey(n2))
		cout << "a\n";
	else
		cout << "b\n";
}

int main()
{
	long a, b;
	while (cin >> a >> b) {
		if (a == 0 && b == 0)
			break;
		compare(a, b);
	}
    return 0;
}

