#include "vertex.h"
#include "graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;
Vertex vertex;
Graph graph;
const unsigned short int INFINITE = 9999;
const short int NV_VERTEX = -1;

/* Private Methods*/

void Graph::init_graph(){
    graph.resize(vertexes);/*Rows - Origin*/
    for (size_t i = 0; i < vertexes; i++) {
        vertexes_list[i].set_index(i); /*Assigning the indices of the vertices*/
        graph[i].resize(vertexes);/*Colums - End*/
        for (size_t j = 0; j < vertexes; j++) {
            graph[i][j] = 0;
        }
    }
}

void Graph::init_map_graph(){
    size_t i = 0;
    for (auto x : vertexes_list) {
        hash_graph[x.get_tag()];
        vertexes_list[i].set_index(i);
        i++;
    }
}

vector<vector<int>> Graph::init_sd_matrix(int vertex_idx){
    int org_idx = vertex_idx;//Graph's Matrix row index

    //n(vertexes) * m(info cols (2))
    vector<vector<int>> info_table;
    info_table.resize(vertexes); //Vertexes rows

    for (size_t idx = 0; idx < vertexes; idx++) {
        idx == org_idx ? info_table[idx].push_back(0) : info_table[idx].push_back(INFINITE); //Shortest distance from start
        info_table[idx].push_back(NV_VERTEX); //Previous vertex
    }

    return info_table;
}

unordered_map<string, wt_pair> Graph::init_sd_hash(string vertex_tag){
    unordered_map<string, wt_pair> returned;
    for (size_t i = 0; i < vertexes_list.size(); i++)
        vertex_tag != vertexes_list[i].get_tag() ? returned[vertexes_list[i].get_tag()] = make_pair(INFINITE, "NAN")
        : returned[vertexes_list[i].get_tag()] = make_pair(0, "NAN");
    return returned;
}

unordered_map<string, vector<vector<string>>> Graph::init_possible_paths(){
    unordered_map<string, vector<vector<string>>> tmp;
    vector<vector<string>> tmp_vect;
    for (auto x : vertexes_list) {
        tmp.insert(make_pair(x.get_tag(), tmp_vect));
    }
    return tmp;
}

/*Public Methods*/

