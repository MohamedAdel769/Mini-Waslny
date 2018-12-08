#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <string>
using namespace std;
class Graph
{
	vector< vector<pair<int, int> > > adjlist;
	map<string, int> towns_data;
	map<int, string> graph_data;
	vector <int> source;
	vector<int> cost;
	priority_queue<pair<int, int>> pq;
	int Towns_ID, No_Towns;
	int **next, **floyd;
	void print_path(int **, int, int);
public:
	Graph();
	void add_town(string);
	void add_distance(string, string, int);
	void apply_dijkstra();
	void apply_floyd();
	void get_shortestPath(string, string);
	void display_graph();
	void delete_graph();
	void update_graph(string);
	~Graph();
};

