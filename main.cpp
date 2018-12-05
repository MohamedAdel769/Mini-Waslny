#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <string>
using namespace std;

vector< vector<pair<int, long long> > > adjlist;
vector <int> source;
vector<long long> cost;
priority_queue<pair<long long, int>> pq;


void Path(int **next, int i, int j) {
	if (i == j)
		cout << i << " ";
	else if (next[i][j] == -1)
		cout << "no path" << endl;
	else {
		Path(next, i, next[i][j]);
		cout << j << " ";
	}
}


int main() {
	cout << "Enter list of towns" << endl;
	cout << "press 1 if you finished " << endl;
	cout << "Enter the Name of the town each in a row " << endl;
	int n = 1;
	string town;
	map<string, int> graph_data;
	map<int, string> graph_data2;
	do {
		cin >> town;
		graph_data[town] = n;
		graph_data2[n++] = town;
	} while (town[0] != '1');
	graph_data.erase("1");
	cout << "Enter the distance between towns " << endl;
	string A, B;
	int A_ID, B_ID;
	long long distance;
	long long **floyd = new long long*[n];
	for (int i = 1; i < n; i++)
		floyd[i] = new long long[n];
	int **next = new int*[n];
	for (int i = 1; i < n; i++)
		next[i] = new int[n];
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++)
			floyd[i][j] = i != j ? 1e17 : 0;
	}
	adjlist.resize(n);
	source.resize(n);
	cost.assign(n, 1e17);
	while (true) {
		cin >> A >> B >> distance;
		if (A == "null")
			break;
		A_ID = graph_data[A], B_ID = graph_data[B];
		adjlist[A_ID].push_back({ B_ID, distance });
		adjlist[B_ID].push_back({ A_ID, distance });
		floyd[A_ID][B_ID] = distance;
		floyd[B_ID][A_ID] = distance;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			if (floyd[i][j] == 1e17)
				next[i][j] = -1;
			else
				next[i][j] = i;
		}
	}
	for (int k = 1; k < n; k++) {
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < n; j++) {
				if (floyd[i][k] + floyd[k][j] < floyd[i][j]) {
					floyd[i][j] = floyd[i][k] + floyd[k][j];
					next[i][j] = next[k][j];
				}
			}
		}
	}
	source[1] = 1;
	cost[1] = 0;
	pq.push({ 0,1 });
	while (!pq.empty()) {
		int town = pq.top().second;
		pq.pop();
		for (int i = 0; i < adjlist[town].size(); i++) {
			int child = adjlist[town][i].first;
			int childW = adjlist[town][i].second;
			if (childW + cost[town] < cost[child]) {
				cost[child] = childW + cost[town];
				source[child] = town;
				pq.push({ -1 * cost[child], child });
			}
		}
	}
	int option;
	cout << "Enter 1 to display graph data, 2 to get shortest path between two towns, 3 to delete graph, 4 to edit graph, 5 to exit" << endl;
	while (true) {
		cin >> option;
		if (option == 5)
			break;
		if (option == 2) {
			cout << "enter two towns to get shortest path between them" << endl;
			while (true) {
				cin >> A >> B;
				if (A == "null" || B == "null")
					break;
				if (graph_data[A] == 1) {
					stack<int> st;
					int x = source[graph_data[B]];
					st.push(graph_data[B]);
					for (int i = 1; i < n; i++) {
						st.push(x);
						if (x == graph_data[A] || x == source[x])
							break;
						x = source[x];
					}
					while (!st.empty()) {
						cout << st.top() << " ";
						st.pop();
					}
					cout << endl;
					cout << "Path cost = " << cost[graph_data[B]] << endl;
				}
				else {
					Path(next, graph_data[A], graph_data[B]);
					cout << endl << "Path cost = " << floyd[graph_data[A]][graph_data[B]] << endl;
				}
			}
		}
		else if (option == 1) {
			cout << "The Towns:";
			for (auto it : graph_data)
				cout << it.first << " ";
			cout << endl;
			cout << "Distance between towns:" << endl;
			for (int i = 1; i < n; i++) {
				for (int j = 0; j < adjlist[i].size(); j++) {
					cout << graph_data2[i] << " " << graph_data2[adjlist[i][j].first] << " " << adjlist[i][j].second << endl;
				}
			}
		}
	}
	return 0;
}