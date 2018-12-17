#pragma once
#include <iostream>
#include <vector>
#include <QStringList>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <QString>
using namespace std;
class Graph
{
    vector< vector<pair<int, long long> > > adjlist;
    map<int, QString> graph_data;
    map<pair<int,int>, int> adjmatrix;
    vector <int> source;
    vector<long long> cost;
    priority_queue<pair<long long, int>> pq;
    int Towns_ID , No_Towns;
    long long **next , **floyd;
    QString temp ;
    QString print_path(long long **, int , int );
public:
    Graph();
    map<QString, int> towns_data;
    long long MAX_DIST = 0;
    void add_town(QString);
    bool isEmpty();
    void add_distance(QString, QString, long long, bool&);
    void apply_dijkstra();
    void apply_floyd();
    void initialize();
    QString get_shortestPath(QString, QString, bool&);
    QString display_graph();
    void delete_graph();
    void del_town(QString);
    void edit_dist(QString, QString, long long, bool&);
    void remove_edge(QString, QString, bool&);
    ~Graph();
};

