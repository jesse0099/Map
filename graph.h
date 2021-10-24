#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <queue>
#include "vertex.h"

#ifndef GRAPH_H
#define GRAPH_H

using namespace std;
typedef unordered_map <string, vector<wt_pair>> Hash_Graph;
typedef priority_queue <int_pair, vector<int_pair>, greater<int_pair>> min_heap_pair_queue;
typedef priority_queue <wt_pair, vector<wt_pair>, greater<wt_pair>> min_heap_wt_pair_queue;

class Graph{

  private:
    size_t vertexes;
    vector<Vertex> vertexes_list;
    Hash_Graph hash_graph;
    vector<vector<int>>  graph;
    void init_graph();
    void init_map_graph();
    vector<vector<int>> init_sd_matrix(int vertex_idx);
    unordered_map<string, wt_pair> init_sd_hash(string vertex_tag);
    unordered_map<string, vector<vector<string>>> init_possible_paths();

  public:
    void print_graph();
    void print_hash_graph();
    void foo();
    void add_edge(string vertex_a, string vertex_b, int weight, bool bidir = false);
    void add_hash_edge(string vertex_a, string vertex_b, int weight, bool bidir = false);
    void shortest_paths(string vertex, int vertex_idx = -1);
    vector<int> shortest_path(string start_vertex, string end_vertex);
    void hash_shortest_paths(string vertex, int vertex_idx = -1);
    vector<wt_pair> hash_shortest_path(string start_vertex, string end_vertex);
    void get_all_paths(string source, string destination);
    void get_all_paths_utils(string source, string destination, unordered_map<string, bool>& visited, vector<wt_pair> path, int& path_index, int source_idx, int source_w);
    void update_sd(int pre_vertex, vector<int> neighbors, vector<int> neighbors_distances, vector<vector<int>>& info_table, min_heap_pair_queue& m_q);
    void update_hash_sd(string current_vertex, vector<wt_pair>  current_neighbors, unordered_map<string, wt_pair>& info_table, min_heap_wt_pair_queue& m_q);
    int vertex_index(string tag);
    int get_uv_known_sd_vertex(vector<vector<int>> info_table, vector<int> visited);
    vector<int> get_current_uv_neighbors(int current_idx, vector<int> visited);
    vector<int> get_current_uv_neighbors_sd(int current_idx, vector<int> neighbors, vector<vector<int>> infotable);
    Graph(vector<Vertex> p_vertexes, bool init_hash_graph = false);
    Graph();
    Hash_Graph get_hash_graph();
    vector<vector<int>> get_graph();
    vector<Vertex> get_vertexes_list();
    size_t get_vertexes();
    void set_graph(vector<vector<int>> p_graph);
    void set_vertexes_list(vector<Vertex> p_vertexes_list);
    void set_vertexes(int p_vertexes);
    void set_hash_graph(Hash_Graph p_hash_graph);
};

#endif // GRAPH_H
