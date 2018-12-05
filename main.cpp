#include"Graph.h"
using namespace std;

int main() {
	Graph city;
	while (true) {
		string town;
		cin >> town;
		if (town == "null")
			break;
		city.add_town(town);
	}
	string A, B;
	int A_ID, B_ID;
	int distance;
	while (true) {
		cin >> A;
		if (A == "null")
			break;
		cin >> B >> distance;
		city.add_distance(A, B, distance);
	}
	city.apply_dijkstra();
	city.apply_floyd();
	while (true) {
		cin >> A;
		if (A == "null")
			break;
		cin >> B;
		city.get_shortestPath(A, B);
	}
	return 0;
}