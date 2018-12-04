#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
using namespace std;

int main() {
	cout << "Enter list of towns" << endl;
	cout << "press 1 if you finished " << endl;
	cout << "Enter the Name of the name of the town each in a row " << endl;
	int n = 1;
	string town;
	map<int, string> graph_data;
	do {
		cin >> town;
		graph_data[n++] = town;
	} while (town[0]!='1');

	return 0;
}