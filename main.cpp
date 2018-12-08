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
	cout << "1 to update , 2 to SP, 3 to display" << endl;
	while (true) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			string option;
			cout << "edit or remove or add" << endl;
			cin >> option;
			city.update_graph(option);
		}
		else if (opt == 2) {
			city.apply_dijkstra();
			city.apply_floyd();
			string a, b;
			cin >> a >> b;
			city.get_shortestPath(a, b);
		}
		else {
			city.display_graph();
		}
	}
	return 0;
}