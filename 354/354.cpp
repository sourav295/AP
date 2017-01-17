// 278.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main()
{
	const int cardNumberLen = 16;
	const int cardNumberSeg = 4;
	int n;
	scanf("%d", &n);
	


	for (int i = 0; i<n; i++)
	{
		bool isValid = true;
		
		int *creditCardNumber  = new int[cardNumberLen];
		int *cardSegments      = new int[cardNumberSeg];
		//read 4 segments
		scanf("%d %d %d %d", &cardSegments[0], &cardSegments[1], &cardSegments[2], &cardSegments[3]);

		int cardNumberPos = 0;

		//Iterate over segments to create card number array
		for (int j = 0; j < cardNumberSeg; j++)
		{
			int card_segment = cardSegments[j];
			
			do {
				int digit = card_segment % 10;
				//populate card number to operate on
				creditCardNumber[cardNumberPos] = digit;
				cardNumberPos++;

				card_segment /= 10;
			} while (card_segment > 0);
		}

		for (int j = 0; j < cardNumberLen; j++)
		{
			printf("%d", creditCardNumber[j]);
		}
				
	}

	/*
	for (int i = 0; i < n; i++)
	{
		printf("%.3lf%%\n", results[i]);
	}
	*/
	return 0;
}

