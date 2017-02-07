#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
//#include <vector>
#include <utility>
#include <queue> 
#include<string>
#include <set>
#include <algorithm>
using namespace std;



struct Country
{
	int id = 0;
	int dist_src = 20;
	queue<int> all_neighbours;

	void insert_neighbour(int id) {
		//cout << (*neighbour).dist_src;
		all_neighbours.push(id);
	}

	Country(int identity) {
		id = identity;
	}

	Country() {}

	void displayNeighbours() {
		queue<int> temp = all_neighbours;
		for (temp; !temp.empty(); temp.pop()) {
			cout <<","<< temp.front();
		}
	}
	
};

struct CompareDistance {
	bool operator()(Country const & c1, Country const & c2) const {
		return c1.dist_src < c2.dist_src;
	}
}comparator_distance;

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
		(*a).insert_neighbour((*b).id);
		(*b).insert_neighbour((*a).id);
	}
	
	void connect(int c1_Id, int c2_Id) {
		linkCountries(&(countries[c1_Id-1]), &(countries[c2_Id-1]));
	}

	void readInputLine(string input, int curr_id) {
		int n = input.at(0) - '0';
		int len = input.length();
		int pos = 2;
		int hit = 0;
		
		if (curr_id == 18) {
			cout << "";
		}

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
			cout << "\n" << (i+1) << " "<< countries[i].dist_src;
			countries[i].displayNeighbours();
		}
	}
	

	int execute(int src_id, int dest_id) {
		
		countries[src_id-1].dist_src = 0;
		
		vector<Country> country_vec;
		for (int i = 0; i < 20; i++)
			country_vec.push_back(countries[i]);
		
		while (!country_vec.empty()) {
			//sort, extract min and pop front
			sort(country_vec.begin(), country_vec.end(), comparator_distance);
			Country u = (*country_vec.begin());
			
			if (u.id == dest_id)
				return u.dist_src;
			
			
			country_vec.erase(country_vec.begin());
			int potential_dist = u.dist_src + 1;
			
			for (u.all_neighbours; !u.all_neighbours.empty(); u.all_neighbours.pop()) {
				int v = u.all_neighbours.front();
				//find vector
				for (int i = 0; i < country_vec.size(); i++) {
					if (country_vec[i].id == v) {
						if (country_vec[i].dist_src > potential_dist) {
							country_vec[i].dist_src = potential_dist;
						}
						break;
					}
				}
			}
		}

		return NULL;
	}

};



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
	cout<< w.execute(2, 9);
	
	
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
|||||||||||||||||||||||||||||||||||||||||||||||||||||
priority_queue<Country, vector<Country>, CompareDistance> country_heap;
for (int i = 0; i < 20; i++)
country_heap.push(countries[i]);
//cout << country_heap.top().id;

while (!country_heap.empty()) {
//extract min
Country u = country_heap.top();
country_heap.pop();

queue<Country *> v_list = u.all_neighbours;
for (v_list; !v_list.empty(); v_list.pop()) {

Country *v = v_list.front();

int potential_dist = u.dist_src + 1;
if (potential_dist < (*v).dist_src)
(*v).dist_src = potential_dist;
}
}




*/