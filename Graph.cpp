#include "Graph.h"


QString Graph::print_path(long long **next, int i, int j)
{
    if (i == j)
        temp += graph_data[i] + " ";
    else if (next[i][j] == -1)
        temp = "no path found\n" ;
    else {
        print_path(next, i, next[i][j]);
        temp += graph_data[j] + " ";
    }
    return temp;
}

Graph::Graph()
{
    Towns_ID = 1;
}

void Graph::initialize(){
    add_town("A");
    add_town("B");
    add_town("C");
    add_town("D");
    add_town("E");
    add_town("F");
    bool tmp ;
    add_distance("A", "B", 7, tmp);
    add_distance("A", "C", 9, tmp);
    add_distance("A", "D", 14, tmp);
    add_distance("B", "C", 10, tmp);
    add_distance("B", "E", 15, tmp);
    add_distance("C", "E", 11, tmp);
    add_distance("C", "D", 2, tmp);
    add_distance("D", "F", 9, tmp);
    add_distance("E", "F", 6, tmp);
}

QString Graph::add_town(QString Tname)
{
    if(towns_data.find(Tname)==towns_data.end())
    {
        graph_data[Towns_ID] = Tname;
        towns_data[Tname] = Towns_ID++;
        adjlist.resize(Towns_ID);
        source.resize(Towns_ID);
        UndoDetails tmp ;
        tmp.AddT = 1;
        tmp.Tname = Tname;
        last_updts.push(tmp);
    }
    else
    {
        Tname = "Town already exist";
    }
    return  Tname;
}

void Graph::add_distance(QString tA, QString tB, long long dist, bool& isValid)
{
    int tA_ID = towns_data[tA], tB_ID = towns_data[tB];
    if(!isConnected(tA_ID, tB_ID)){
        adjlist[tA_ID].push_back({ tB_ID, dist });
        adjlist[tB_ID].push_back({ tA_ID, dist });
        MAX_DIST += dist ;
    }
    else{
        isValid = false ;
    }
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
            long long childW = adjlist[town][i].second;
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
    floyd = new long long*[Towns_ID];
    next = new long long*[Towns_ID];
    for (int i = 1; i < Towns_ID; i++) {
        floyd[i] = new long long[Towns_ID];
        next[i] = new long long[Towns_ID];
    }
    for (int i = 1; i < Towns_ID; i++) {
        for (int j = 1; j < Towns_ID; j++)
            floyd[i][j] = i != j ? 1e17 : 0;
    }
    for (int i = 1; i < Towns_ID; i++) {
        for (int j = 0; j < adjlist[i].size(); j++) {
            floyd[i][adjlist[i][j].first] = adjlist[i][j].second;
            floyd[adjlist[i][j].first][i] = adjlist[i][j].second;
        }
    }
    for (int i = 1; i < Towns_ID; i++) {
        for (int j = 1; j < Towns_ID; j++) {
            next[i][j] = floyd[i][j] == 1e17 ? -1 : i;
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

QString Graph::get_shortestPath(QString A, QString B, bool &isValid)
{
    QString ans = "Route: " ;
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
            ans += graph_data[T_ID];
            ans += " ";
            path.pop();
        }
        ans += "\n";
        ans += "This path costs = ";
        ans += QString::number(cost[towns_data[B]]);
        if(cost[towns_data[B]] > MAX_DIST)
            isValid = false ;
    }
    else {
        ans += print_path(next, towns_data[A], towns_data[B]);
        ans += "\nThis path costs = " ;
        ans += QString::number(floyd[towns_data[A]][towns_data[B]]) + "\n";
        temp.clear();
        if(floyd[towns_data[A]][towns_data[B]] > MAX_DIST)
            isValid = false ;
    }
    return ans ;
}

bool Graph::isEmpty(){
    return towns_data.empty() ;
}

QString Graph::display_graph()
{
    QString output = "City is Empty !";
    if (!isEmpty()) {
        output.clear();
        output += "Towns: ";
        for (auto it : towns_data) {
            output += (it.first) ;
            output += " ";
        }
        output += "\n";
        output += "Distances:\n" ;
        for (int i = 1; i < Towns_ID; i++) {
                for (int j = 0; j < adjlist[i].size(); j++) {
                    output += graph_data[i];
                    output += " ";
                    output += graph_data[adjlist[i][j].first];
                    output += " ";
                    output += QString::number(adjlist[i][j].second) ;
                    output += "\n";
                }
        }
    }
    return output;
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

void Graph::del_town(QString input){
    int del_id = towns_data[input];
    UndoDetails tmp ;
    tmp.DelT = 1 ;
    tmp.Tname = input;
    vector<pair<int, long long>> ::iterator it;
    for (int i = 0; i < adjlist[del_id].size(); i++) {
        int child = adjlist[del_id][i].first;
        tmp.childs.push_back(make_pair(graph_data[child], adjlist[del_id][i].second));
        for (it = adjlist[child].begin();it!= adjlist[child].end();it++) {
            if ((*it).first == del_id) {
                adjlist[child].erase(it);
                break;
            }
        }
    }
    last_updts.push(tmp);
    adjlist[del_id].clear();
    towns_data.erase(input);
    graph_data.erase(del_id);
}

void Graph::edit_dist(QString a, QString b, long long new_dist, bool &isValid){
    int a_id = towns_data[a], b_id = towns_data[b];
    for (int i = 0; i < adjlist[a_id].size(); i++) {
        if (adjlist[a_id][i].first == b_id) {
            adjlist[a_id][i].second = new_dist;
            isValid = true ;
        }
    }
    for (int i = 0; i < adjlist[b_id].size(); i++) {
        if (adjlist[b_id][i].first == a_id) {
            adjlist[b_id][i].second = new_dist;
        }
    }
}

void Graph::remove_edge(QString a, QString b, bool &isValid){
    int a_id = towns_data[a] , b_id = towns_data[b];
    vector<pair<int, long long>> ::iterator it ;
    for(it = adjlist[a_id].begin();it != adjlist[a_id].end();it++){
        if ((*it).first == b_id) {
            isValid = true ;
            adjlist[a_id].erase(it);
        }
    }
    for(it = adjlist[b_id].begin();it != adjlist[b_id].end();it++){
        if ((*it).first == a_id) {
            adjlist[b_id].erase(it);
        }
    }
}

bool Graph::isConnected(int A,int B){
    for(int i=0;i<adjlist[A].size();i++){
        if(adjlist[A][i].first == B)
            return true ;
    }
    return false;
}

void Graph::Undo(){
    UndoDetails tmp = last_updts.top();
    last_updts.pop();
    if(tmp.AddD){

    }
    else if(tmp.AddT){
        del_town(tmp.Tname);
    }
    else if(tmp.DelC){

    }
    else if(tmp.DelD){

    }
    else if(tmp.DelT){
        add_town(tmp.Tname);
        bool temp ;
        while (!tmp.childs.empty()) {
               add_distance(tmp.Tname, tmp.childs.back().first, tmp.childs.back().second, temp);
               tmp.childs.pop_back();
        }
    }
    else if(tmp.EditD){

    }
}


Graph::~Graph()
{
}
