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
    add_distance("A", "B", 7);
    add_distance("A", "C", 9);
    add_distance("A", "D", 14);
    add_distance("B", "C", 10);
    add_distance("B", "E", 15);
    add_distance("C", "E", 11);
    add_distance("C", "D", 2);
    add_distance("D", "F", 9);
    add_distance("E", "F", 6);
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
        tmp.Tname1 = Tname;
        last_updts.push(tmp);
    }
    else
    {
        Tname = "Town already exist";
    }
    return  Tname;
}

void Graph::add_distance(QString tA, QString tB, long long dist)
{
    int tA_ID = towns_data[tA], tB_ID = towns_data[tB];
    adjlist[tA_ID].push_back({ tB_ID, dist });
    adjlist[tB_ID].push_back({ tA_ID, dist });
    MAX_DIST += dist ;
    UndoDetails tmp ;
    tmp.AddD = 1;
    tmp.Tname1 = tA;
    tmp.Tname2 = tB;
    last_updts.push(tmp);
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

QString Graph::get_shortestPath(QString A, QString B)
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
    }
    else {
        ans += print_path(next, towns_data[A], towns_data[B]);
        ans += "\nThis path costs = " ;
        ans += QString::number(floyd[towns_data[A]][towns_data[B]]) + "\n";
        temp.clear();
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
    UndoDetails tmp ;
    tmp.DelC = 1 ;
    for(auto it : towns_data){
        UndoDetails temp ;
        temp.Tname1 = it.first;
        for(auto it2 : adjlist[it.second]){
            QString childName = graph_data[it2.first];
            long long dist = it2.second;
            temp.childs.push_back(make_pair(childName, dist));
        }
        tmp.cityDetails.push_back(temp);
    }
    last_updts.push(tmp);
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
    tmp.Tname1 = input;
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

void Graph::edit_dist(QString a, QString b, long long new_dist){
    int a_id = towns_data[a], b_id = towns_data[b];
    UndoDetails tmp ;
    for (int i = 0; i < adjlist[a_id].size(); i++) {
        if (adjlist[a_id][i].first == b_id) {
            tmp.Tname1 = a;
            tmp.EditD = 1;
            tmp.Tname2 = b;
            tmp.dist = adjlist[a_id][i].second;
            last_updts.push(tmp);
            adjlist[a_id][i].second = new_dist;
            break;
        }
    }
    for (int i = 0; i < adjlist[b_id].size(); i++) {
        if (adjlist[b_id][i].first == a_id) {
            adjlist[b_id][i].second = new_dist;
            break;
        }
    }
}

void Graph::remove_edge(QString a, QString b){
    int a_id = towns_data[a] , b_id = towns_data[b];
    vector<pair<int, long long>> :: iterator it ;
    UndoDetails tmp ;
    for(it = adjlist[a_id].begin();it != adjlist[a_id].end();it++){
        if ((*it).first == b_id) {
            tmp.Tname1 = a;
            tmp.DelD = 1;
            tmp.Tname2 = b;
            tmp.dist = (*it).second;
            last_updts.push(tmp);
            adjlist[a_id].erase(it);
            break;
        }
    }
    for(it = adjlist[b_id].begin();it != adjlist[b_id].end();it++){
        if ((*it).first == a_id) {
            adjlist[b_id].erase(it);
            break;
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
    if(!last_updts.empty()){
        UndoDetails tmp = last_updts.top();
        last_updts.pop();
        bool temp ;
        if(tmp.AddD){
            remove_edge(tmp.Tname1, tmp.Tname2);
        }
        else if(tmp.AddT){
            del_town(tmp.Tname1);
        }
        else if(tmp.DelC){
            for(auto i : tmp.cityDetails){
                add_town(i.Tname1);
            }
            for(auto i : tmp.cityDetails){
                for(int j=0;j<i.childs.size();j++){
                    add_distance(i.Tname1, i.childs[j].first, i.childs[j].second);
                }
            }
        }
        else if(tmp.DelD){
            add_distance(tmp.Tname1, tmp.Tname2, tmp.dist);
        }
        else if(tmp.DelT){
            add_town(tmp.Tname1);
            while (!tmp.childs.empty()) {
                   add_distance(tmp.Tname1, tmp.childs.back().first, tmp.childs.back().second);
                   tmp.childs.pop_back();
            }
        }
        else if(tmp.EditD){
            edit_dist(tmp.Tname1, tmp.Tname2, tmp.dist);
        }
    }
}

void Graph::Fill(QComboBox *my_list){
    if(!isEmpty()){
        for(auto town : towns_data){
            my_list->addItem(town.first);
        }
    }
}

bool Graph::isvalid(string fn_name, QString tA, QString tB){
    if(fn_name == "Add"){
        return (!isConnected(towns_data[tA], towns_data[tB])) ;
    }
    else if(fn_name == "SP"){
        if(towns_data[tA] == 1){
            return (cost[towns_data[tB]] <= MAX_DIST) ;
        }
        else{
            return (floyd[towns_data[tA]][towns_data[tB]] <= MAX_DIST);
        }
    }
    else{
        return (isConnected(towns_data[tA], towns_data[tB]));
    }
}

Graph::~Graph()
{
    for (int i = 1; i < Towns_ID; i++) {
        delete [] floyd[i] ;
        delete [] next[i];
    }
    delete [] floyd;
    delete [] next;
}
