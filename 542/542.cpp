// 278.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;





class Signal {
	int time_period;
public:
	
	Signal(int period) {
		time_period = period;
	}
	
	int calculateGreenTime_start(int cycle_no) {
		return 2 * cycle_no * time_period;
	}

	int calculateGreenTime_end(int cycle_no) {
		return (2 * cycle_no * time_period) + (time_period - 5);
	}

	//get the cycle number for a specific number
	//Null if it is not green
	int getGreenLightCycleNumber(int time_now) {

		//Green light condition
		/*
		k is the cycle number.
		time_now belongs to [ 2(timee_period)(k) , 2(timee_period)(k) + (time_period - 5) )
		Given everything other parameter, k should existd
		*/

		float k1 = ((float)time_now - ((float)time_period - 5)) / (2 * (float)time_period);
		float k2 = (float)time_now / (2 * (float)time_period);


		int k;
		if (ceil(k1) <= floor(k2))
			k = ceil(k1);//k exist
		else
			k = NULL;

		return k;
	}

};


int main()
{

	vector<Signal> signals;
	
	Signal s (30);
	Signal s1(25);
	Signal s2(35);
	signals.push_back(s);
	signals.push_back(s1);
	signals.push_back(s2);

	int cycle_limit = 5 * 60 * 60 / (10 * 2); // 5hrs divided by min cycle size


	bool simultaneously_green = false;
	int success_time = 0;
	for (int cycle = 1; cycle <= cycle_limit; cycle++) {
		Signal base_signal = signals[0];

		int start_time = base_signal.calculateGreenTime_start(cycle);
		int end_time = base_signal.calculateGreenTime_end(cycle);

		for (int time_now = start_time; time_now < end_time; time_now++) {
			
			bool interim_simultaneously_green = true;
			for (std::vector<int>::size_type i = 1; i != signals.size(); i++) {
				int cycle_intersection = signals[i].getGreenLightCycleNumber(time_now);

				interim_simultaneously_green = cycle_intersection && interim_simultaneously_green;

				if (!interim_simultaneously_green) {
					break;
				}
			}

			//-- condtion met
			if (interim_simultaneously_green) {
				simultaneously_green = true;
				success_time = time_now;
				break;
			}
		}

		if (simultaneously_green)
			break;
	}

	cout << success_time;

	
	return 0;
}

