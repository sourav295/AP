// 278.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;


vector<int> acceptable_cycles_for_range(int cycle_time, int start_time, int end_time) {

	vector<int> results;
	
	int cn_max = floor(start_time / (2 * cycle_time));
	int cn_min = ceil((end_time + 5 - cycle_time) / (2 * cycle_time));

	for (int i = cn_min; i <= cn_max; i++)
		results.push_back(i);

	return results;

}



int execute(vector<int> cycleTime_queue) {

	int reference_cycleTime = cycleTime_queue.back();
	cycleTime_queue.pop_back();
	//choose a reference signal and check if it is valid for all
	for (int i = 1; i < 5; i++) {

		vector<int> common_cycles;

		int validTimeRange_start = reference_cycleTime * i * 2;//exclusive
		int validTimeRange_end   = validTimeRange_start + (reference_cycleTime - 5);//inclusive
	
		for (int j = 0; j < cycleTime_queue.size(); j++) {
			vector<int> acceptable = acceptable_cycles_for_range(cycleTime_queue[j], validTimeRange_start, validTimeRange_end);
			set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(common_cycles));

		}



		cout << "\n" << validTimeRange_start << " " << validTimeRange_end << "--" << cycle_range.size();


	}

	return 0;
}



int main()
{
	vector<int> cycleTime_queue;
	cycleTime_queue.push_back(19);
	cycleTime_queue.push_back(20);

	execute(cycleTime_queue);

	return 0;
}
