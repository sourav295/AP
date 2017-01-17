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

		
				
	}

	/*
	for (int i = 0; i < n; i++)
	{
		printf("%.3lf%%\n", results[i]);
	}
	*/
	return 0;
}

