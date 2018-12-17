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
	Towns_ID = 1;
}

void Graph::add_town(string Tname)
{
	graph_data[Towns_ID] = Tname;
	towns_data[Tname] = Towns_ID++;
	adjlist.resize(Towns_ID);
	source.resize(Towns_ID);
}

void Graph::add_distance(string tA, string tB, int dist)
{
	int tA_ID = towns_data[tA], tB_ID = towns_data[tB];
	adjlist[tA_ID].push_back({ tB_ID, dist });
	adjlist[tB_ID].push_back({ tA_ID, dist });
}

void Graph::apply_dijkstra()
{
	cost.assign(Towns_ID, 1e17);
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
	floyd = new int*[Towns_ID];
	next = new int*[Towns_ID];
	for (int i = 1; i < Towns_ID; i++) {
		floyd[i] = new int[Towns_ID];
		next[i] = new int[Towns_ID];
	}
	for (int i = 1; i < Towns_ID; i++) {
		for (int j = 1; j < Towns_ID; j++)
			floyd[i][j] = i != j ? 1e9 : 0;
	}
	for (int i = 1; i < Towns_ID; i++) {
		for (int j = 0; j < adjlist[i].size(); j++) {
			floyd[i][adjlist[i][j].first] = adjlist[i][j].second;
			floyd[adjlist[i][j].first][i] = adjlist[i][j].second;
		}
	}
	for (int i = 1; i < Towns_ID; i++) {
		for (int j = 1; j < Towns_ID; j++) {
			next[i][j] = floyd[i][j] == 1e9 ? -1 : i;
		}
	}
	for (int k = 1; k < Towns_ID; k++) {
		for (int i = 1; i < Towns_ID; i++) {
			for (int j = 1; j < Towns_ID; j++) {
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
		for (int i = 1; i < Towns_ID; i++) {
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
		for (int i = 1; i < Towns_ID; i++) {
			for (int j = 0; j < adjlist[i].size(); j++) {
				cout << graph_data[i] << " " << graph_data[adjlist[i][j].first] << " " << adjlist[i][j].second << endl;
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
	Towns_ID = 1;
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
		string deleted_town;
		while (true) {
			cin >> deleted_town;
			if (deleted_town == "null")
				break;
			int del_id = towns_data[deleted_town];
			vector<pair<int, int>> ::iterator it;
			for (int i = 0; i < adjlist[del_id].size(); i++) {
				int child = adjlist[del_id][i].first;
				for (it = adjlist[child].begin(); it != adjlist[child].end(); it++) {
					if ((*it).first == del_id) {
						adjlist[child].erase(it);
						break;
					}
				}
			}
			adjlist[del_id].clear();
			towns_data.erase(deleted_town);
			graph_data.erase(del_id);
		}
	}
	else if (option == "edit") {
		string a, b;
		int new_dist;
		while (true) {
			cin >> a;
			if (a == "null")break;
			cin >> b >> new_dist;
			int a_id = towns_data[a], b_id = towns_data[b];
			for (int i = 0; i < adjlist[a_id].size(); i++) {
				if (adjlist[a_id][i].first == b_id) {
					adjlist[a_id][i].second = new_dist;
				}
			}
			for (int i = 0; i < adjlist[b_id].size(); i++) {
				if (adjlist[b_id][i].first == a_id) {
					adjlist[b_id][i].second = new_dist;
				}
			}
		}
	}
}


Graph::~Graph()
{
}
