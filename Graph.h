#pragma once
#include <iostream>
#include <vector>
#include <QStringList>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <QString>
#include <QComboBox>
using namespace std;

struct UndoDetails{
    bool AddT = 0 , AddD = 0 , DelC = 0 , DelT = 0 , DelD = 0 , EditD = 0;
    QString Tname1 , Tname2;
    long long dist;
    vector<pair<QString, long long>> childs;
    vector <UndoDetails> cityDetails ;
};

class Graph
{
    vector< vector<pair<int, long long> > > adjlist;
    map<int, QString> graph_data;
    map<QString, int> towns_data;
    vector <int> source;
    vector<long long> cost;
    priority_queue<pair<long long, int>> pq;
    int Towns_ID ;
    long long **next , **floyd;
    long long MAX_DIST = 0;
    QString temp ;
    QString print_path(long long **, int , int );
    bool isConnected(int, int);
    stack<UndoDetails> last_updts;
public:
    Graph();
    QString add_town(QString);
    bool isEmpty();
    void add_distance(QString, QString, long long);
    void apply_dijkstra();
    void apply_floyd();
    void initialize();
    void Fill(QComboBox*);
    QString get_shortestPath(QString, QString);
    QString display_graph();
    void delete_graph();
    void del_town(QString);
    void edit_dist(QString, QString, long long);
    void remove_edge(QString, QString);
    void Undo();
    bool isvalid(string, QString, QString);
    ~Graph();
};

