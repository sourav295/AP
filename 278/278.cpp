// 278.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main()
{
    
	
	int n;
	scanf("%d", &n);
	
	float *results = new float[n];

	for (int i = 0; i<n; i++)
	{
		int sample_count;
		scanf("%d", &sample_count);
		
		//Create blank array of user Input
		int *grades = new int[sample_count];
		
		//populate array with user input
		int sumGrades = 0;
		for (int j = 0; j < (sample_count); j++) 
		{
			int temp;
			scanf("%d", &temp);
			grades[j] = temp;
			sumGrades += temp;
		}

		int memberCountAboveAvg = 0;
		
		//count members above the average grade
		for (int j = 0; j < (sample_count); j++)
		{
			//condition to be above average
			if (sumGrades < (sample_count * grades[j]))
			{
				memberCountAboveAvg++;
			}
		}

		results[i] = ( (float)memberCountAboveAvg * 100 )/ (float)sample_count;


	}

	for (int i = 0; i < n; i++)
	{
		printf("%.3lf%%\n", results[i]);
	}

	return 0;
}

