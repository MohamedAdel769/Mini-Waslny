#include "Graph.h"



void Graph::print_path(int **next, int i, int j)
{
	if (i == j)
		cout << graph_data[i] << " ";
	else if (next[i][j] == -1)
		cout << "no path found" << endl;
	else {
		print_path(next, i, next[i][j]);
		cout << graph_data[j] << " ";
	}
}

Graph::Graph()
{
	NumberOfNodes = 1;
}

void Graph::add_town(string Tname)
{
	graph_data[NumberOfNodes] = Tname;
	towns_data[Tname] = NumberOfNodes++;
	adjlist.resize(NumberOfNodes);
	source.resize(NumberOfNodes);
}

void Graph::add_distance(string tA, string tB, int dist)
{
	int tA_ID = towns_data[tA], tB_ID = towns_data[tB];
	adjlist[tA_ID].push_back({ tB_ID, dist });
	adjlist[tB_ID].push_back({ tA_ID, dist });
}

void Graph::apply_dijkstra()
{
	cost.assign(NumberOfNodes, 1e17);
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
}

void Graph::apply_floyd()
{
	floyd = new int*[NumberOfNodes];
	next = new int*[NumberOfNodes];
	for (int i = 1; i < NumberOfNodes; i++) {
		floyd[i] = new int[NumberOfNodes];
		next[i] = new int[NumberOfNodes];
	}
	for (int i = 1; i < NumberOfNodes; i++) {
		for (int j = 1; j < NumberOfNodes; j++)
			floyd[i][j] = i != j ? 1e9 : 0;
	}
	for (int i = 1; i < NumberOfNodes; i++) {
		for (int j = 0; j < adjlist[i].size(); j++) {
			floyd[i][adjlist[i][j].first] = adjlist[i][j].second;
			floyd[adjlist[i][j].first][i] = adjlist[i][j].second;
		}
	}
	for (int i = 1; i < NumberOfNodes; i++) {
		for (int j = 1; j < NumberOfNodes; j++) {
			next[i][j] = floyd[i][j] == 1e9 ? -1 : i;
		}
	}
	for (int k = 1; k < NumberOfNodes; k++) {
		for (int i = 1; i < NumberOfNodes; i++) {
			for (int j = 1; j < NumberOfNodes; j++) {
				if (floyd[i][k] + floyd[k][j] < floyd[i][j]) {
					floyd[i][j] = floyd[i][k] + floyd[k][j];
					next[i][j] = next[k][j];
				}
			}
		}
	}
}

void Graph::get_shortestPath(string A, string B)
{
	if (towns_data[A] == 1) {
		stack<int> path;
		int curr_town = source[towns_data[B]];
		path.push(towns_data[B]);
		for (int i = 1; i < NumberOfNodes; i++) {
			path.push(curr_town);
			if (curr_town == source[curr_town])
				break;
			curr_town = source[curr_town];
		}
		while (!path.empty()) {
			int T_ID = path.top();
			cout << graph_data[T_ID] << " ";
			path.pop();
		}
		cout << endl;
		cout << "This path costs = " << cost[towns_data[B]] << endl;
	}
	else {
		print_path(next, towns_data[A], towns_data[B]);
		cout << endl << "This path costs = " << floyd[towns_data[A]][towns_data[B]] << endl;
	}
}

void Graph::display_graph()
{
	if (!towns_data.empty()) {
		cout << "Towns: ";
		for (auto it : towns_data) {
			cout << it.first << " ";
		}
		cout << endl;
		cout << "Distances:" << endl;
		for (int i = 1; i < NumberOfNodes; i++) {
			if (graph_data.find(i) != graph_data.end()) {
				for (int j = 0; j < adjlist[i].size(); j++) {
					cout << graph_data[i] << " " << graph_data[adjlist[i][j].first] << " " << adjlist[i][j].second << endl;
				}
			}
		}
	}
	else
		cout << "The graph is empty" << endl;
}

void Graph::delete_graph()
{
	graph_data.clear();
	towns_data.clear();
	adjlist.clear();
	source.clear();
	cost.clear();
	NumberOfNodes = 1;
}

void Graph::update_graph(string option)
{
	if (option == "add") {
		string newTown;
		cout << "Enter the new town(s)" << endl;
		while (true) {
			cin >> newTown;
			if (newTown == "null")
				break;
			add_town(newTown);
		}
		cout << "want to add distance between other towns?" << endl;
		string A, B;
		int dist;
		while (true) {
			cin >> A;
			if (A == "null")
				break;
			cin >> B >> dist;
			add_distance(A, B, dist);
		}
	}
	else if (option == "remove") {

	}
	else if (option == "edit") {

	}
}


Graph::~Graph()
{
}
