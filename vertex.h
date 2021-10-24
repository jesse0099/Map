#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <queue>

#ifndef VERTEX_H
#define VERTEX_H
using namespace std;

typedef pair<int, int> int_pair;
typedef pair<int, string> wt_pair;

class Vertex{
public:

     Vertex();
     Vertex(string p_tag);
     vector<int> shortest_path(int end_idx);
     vector<wt_pair> hash_shortest_path(string end_vertex);
     string get_tag();
     vector<vector<int>> get_shortest_paths();
     unordered_map<string, wt_pair> get_hash_shortest_paths();
     unordered_map<string, vector<vector<wt_pair>>> get_possible_paths();
     int get_index();
     void set_index(int n_index);
     void set_tag(string n_tag);
     void set_shortest_path(vector<vector<int>> p_nd_shortest_path);
     void set_hash_shortest_path(unordered_map<string, wt_pair> p_hash_shortest_paths);
     void set_possible_paths(unordered_map<string, vector<vector<wt_pair>>> p_possible_paths);
     void add_possible_path_key(string destination);
     void add_possible_path(string key, vector<wt_pair> path);

private:
     unsigned short int index;
     vector<vector<int>> shortest_paths;
     //key = Row, pair = (Weight, Pre Vertex)
     unordered_map<string, wt_pair> hash_shortest_paths;
     unordered_map<string, vector<vector<wt_pair>>>  possible_paths;
     string tag;
};
#endif // VERTEX_H
