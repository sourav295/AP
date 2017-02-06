#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <set>
using namespace std;

struct Country
{
	int id = 0;
	int dist_src = 0;
	queue<Country *> all_neighbours;

	void insert_neighbour(Country *neighbour) {
		//cout << (*neighbour).dist_src;
		all_neighbours.push(neighbour);
	}

	Country(int identity) {
		id = identity;
	}

	Country() {}

	void displayNeighbours() {
		for (all_neighbours; !all_neighbours.empty(); all_neighbours.pop()) {
			Country *x = all_neighbours.front();
			cout <<"(" <<(*x).id<<"," << (*x).dist_src << ")";
		}
	}

};



struct World {

	Country countries[20];

	World() {
		for (int i = 0; i < 20; i++) {
			countries[i] = (Country(i + 1));
		}
	}

	Country findCountryById(int id) {
		return countries[id - 1];
	}

	void constructGraph(queue<string> graphInput) {
		
		int curr_id = 1;
		for (graphInput; !graphInput.empty(); graphInput.pop()) {
			//cout << graphInput.front() << "\n";
			readInputLine(graphInput.front(), curr_id);
			curr_id++;
			//cout << "\n=======\n";
		}
		
	}

	void linkCountries(Country *a, Country *b) {
		(*a).insert_neighbour(b);
		(*b).insert_neighbour(a);
	}
	
	void connect(int c1_Id, int c2_Id) {
		Country c1 = findCountryById(c1_Id);
		Country c2 = findCountryById(c2_Id);

		linkCountries(&c1, &c2);
	}

	void readInputLine(string input, int curr_id) {
		int n = input.at(0) - '0';
		int len = input.length();
		int pos = 2;
		int hit = 0;
		
		while (pos < len && hit < n) {
			if (isdigit(input.at(pos))) {
				hit++;
				if ((pos+1) < len && isdigit(input.at(pos + 1))) {
					connect(curr_id, ((input.at(pos) - '0') * 10 + (input.at(pos + 1) - '0')));
					pos++;
				}
				else{
					connect(curr_id, ((input.at(pos) - '0')));
				}
			}
			pos++;
		}
	}

	
	void display() {
		for (int i = 0; i < 20; i++) {
			cout << "\n" << (i+1);
			Country x = countries[i];
			(x).displayNeighbours();
		}
	}

};



//queue<Country> all_countries;






int main()
{
	queue<string> graphInput;
	graphInput.push("1 3");
	graphInput.push("2 3 4");
	graphInput.push("3 4 5 6");
	graphInput.push("1 6");
	graphInput.push("1 7");
	graphInput.push("2 12 13");
	graphInput.push("1 8");
	graphInput.push("2 9 10");
	graphInput.push("1 11");
	graphInput.push("1 11");
	graphInput.push("2 12 17");
	graphInput.push("1 14");
	graphInput.push("2 14 15");
	graphInput.push("2 15 16");
	graphInput.push("1 16");
	graphInput.push("1 19");
	graphInput.push("2 18 19");
	graphInput.push("1 20");
	graphInput.push("1 20");

	World w;
	w.constructGraph(graphInput);
	w.display();

    return 0;
}

/*

Country c1;
Country c2;

linkCountries(&c1, &c2);

Country * cTemp = c2.all_neighbours.front();

cout << &c1 << " " << cTemp << "\n";

cTemp = c1.all_neighbours.front();

cout << &c2 << " " << cTemp;


*/