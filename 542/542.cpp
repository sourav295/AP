// 278.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;

int calculateGreenTime_start(int time_period, int cycle_no) {
	return 2 * cycle_no * time_period;
}

int calculateGreenTime_end(int time_period, int cycle_no) {
	return (2 * cycle_no * time_period) + (time_period - 5);
}

/*
bool isIntersecting(int this_time_period, int this_cycle_no, int other_time_period, int other_cycle_no) {
	int this_start = calculateGreenTime_start(this_time_period, this_cycle_no);
	int this_end   = calculateGreenTime_end(this_time_period, this_cycle_no);

	int other_start = calculateGreenTime_start(other_time_period, other_cycle_no);
	int other_end   = calculateGreenTime_end(other_time_period, other_cycle_no);

	if (((this_start <= other_start) && (other_start < this_end)) || ((other_start <= this_start) && (this_start < other_end))) {
		return true;
	}

	return false;
}
*/
bool isIntersecting(int this_time_period, int this_cycle_no, int other_start_time, int other_end_time) {
	int this_start = calculateGreenTime_start(this_time_period, this_cycle_no);
	int this_end = calculateGreenTime_end(this_time_period, this_cycle_no);

	if (((this_start <= other_start_time) && (other_start_time < this_end)) || ((other_start_time <= this_start) && (this_start < other_end_time))) {
		return true;
	}

	return false;
}


int main()
{
	

	return 0;
}

