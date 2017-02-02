// 278.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
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

		float k1 = ((float)time_now - ((float)time_period - 5 - 1)) / (2 * (float)time_period);//exclusion of the ending
		float k2 = (float)time_now / (2 * (float)time_period);


		int k;
		if (ceil(k1) <= floor(k2))
			k = ceil(k1);//k exist
		else
			k = NULL;

		return k;
	}

};

int calculateWait(vector<Signal> signals) {
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

	return success_time;
}
/*
void execute(vector<Signal> signals) {
	int success_time = calculateWait(signals);

	int seconds = success_time;
	int minutes = seconds / 60;
	int hours = minutes / 60;

	if((hours > 5) || (hours == 5 && ((seconds%60) > 0|| (minutes%60) > 0)))
		printf("%s\n", "Signals fail to synchronise in 5 hours");
	else
		printf("%02d:%02d:%02d\n", hours, (minutes % 60), (seconds % 60));

}
*/

bool isTerminatingLine(char line[], int max) {
	int continuousZeros = 0;
	for (int i = 0; i < max; i++) {
		char c = line[i];


		if (isdigit(c)) {
			if ((c - '0') == 0)
				continuousZeros++;
			else
				return false;
		
			if (continuousZeros == 3)
				return true;
		
		}
	}

	return false;
}


int main()
{
	const int max = 100;
	queue<int> results;
	
	vector<Signal> signals;
	
	while(true){
		int temp = 0;
		char string[max] = { 0 };
		cin.getline(string, max, '\n');

		if (isTerminatingLine(string, max))
			break;
		
		for (int i = 0; i < max; i++) {
		
			if (!isdigit(string[i])) {
				if (temp != 0) {
					Signal s(temp);
					signals.push_back(s);
				}
				temp = 0;
			}
			else {
				int num = (int)(string[i] - '0');
				if (temp == 0 && num == 0){
					//execute(signals);
					results.push(calculateWait(signals));
					signals.clear();
					break;
				}
				temp = (temp * 10) + num;
			}
		}
	}
	
	for (results; !results.empty(); results.pop()) {
		int success_time = results.front();

		int seconds = success_time;
		int minutes = seconds / 60;
		int hours = minutes / 60;

		if ((hours > 5) || (hours == 5 && ((seconds % 60) > 0 || (minutes % 60) > 0)))
			printf("%s\n", "Signals fail to synchronise in 5 hours");
		else
			printf("%02d:%02d:%02d\n", hours, (minutes % 60), (seconds % 60));


	}

	/*
	vector<Signal> signals;
	
	Signal s (30);
	Signal s1(25);
	Signal s2(35);
	signals.push_back(s);
	signals.push_back(s1);
	signals.push_back(s2);

	
	int success_time = calculateWait(signals);

	if (success_time == 0) {
		printf("%s", "Replace with custom text");
	}
	else {
		int seconds = success_time;
		int minutes = seconds / 60;
		int hours = minutes / 60;

		printf("%02d:%02d:%02d\n", hours, (minutes % 60), (seconds % 60));

	}
	*/
	return 0;
}

