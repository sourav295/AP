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
		
		for (graphInput; !graphInput.empty(); graphInput.pop()) {
			string input_line = graphInput.front();
			int noOfHigherNeighbours = (input_line.at(0));
			
			int first_neightbour = 2;
			int last_neightbour = noOfHigherNeighbours * 2;
			cout << input_line<<"\n";
			cout << noOfHigherNeighbours;
			for (int i = first_neightbour; i <= last_neightbour; i = i + 2) {//skipt the space as well
				cout << (input_line.at(i));
			}
			cout << "\n";
		}
		
	}


};



//queue<Country> all_countries;

void linkCountries(Country *a, Country *b) {
	(*a).insert_neighbour(b);
	(*b).insert_neighbour(a);
}




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