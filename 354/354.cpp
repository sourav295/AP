// 278.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;


int main()
{
	const int cardNumberLen = 16;
	const int cardNumberSeg = 4;

	int n;
	scanf("%d", &n);
	
	bool *results = new bool[n];


	for (int i = 0; i<n; i++)
	{
		bool isValid = true;
		
		int *creditCardNumber  = new int[cardNumberLen];
		int *cardSegments      = new int[cardNumberSeg];
		//read 4 segments
		scanf("%d %d %d %d", &cardSegments[0], &cardSegments[1], &cardSegments[2], &cardSegments[3]);

		//construct int array of the four segments
		for (int j = 0; j < cardNumberSeg; j++){
			int cardSegmentValue = cardSegments[j];
			for (int k = 0; k < 4; k++){
				creditCardNumber[((j + 1)*4 ) - ( k + 1 )] = cardSegmentValue % 10;
				cardSegmentValue /= 10;
			}
		}
		
		//card number output verification
		/*
		for (int j = 0; j < cardNumberLen; j++) {
			cout << creditCardNumber[j];
		}
		*/

		//Checking algorithm
		bool isEvenPos  = true;
		int sumOfDigits = 0;
		for (int j = 0; j < cardNumberLen; j++) {
			
			int digit = creditCardNumber[j];
			if (isEvenPos) {
				//split and add
				int double_digit = digit * 2;
				sumOfDigits += (double_digit % 10) + (double_digit / 10);
			}
			else {
				sumOfDigits += digit;
			}

			isEvenPos = (!isEvenPos);
		}

		// set final result
		if (sumOfDigits % 10 == 0)
			results[i] = true;
		else
			results[i] = false;

	}

	
	for (int i = 0; i < n; i++)
	{
		string output = "Invalid";
		if (results[i])
			output = "Valid";

		printf("%s\n", output.c_str());
	}
	
	return 0;
}

