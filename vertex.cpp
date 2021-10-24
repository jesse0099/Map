#include "vertex.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;
const short int NV_VERTEX = -1;
const string NANKEY = "NAN";

Vertex vertex;

Vertex::Vertex(){}

Vertex::Vertex(string p_tag){
    this->tag = p_tag;
}

string Vertex:: get_tag(){
    return this->tag;
}

vector<int> Vertex::shortest_path(int end_idx){
    vector<int> path;
    int objective = end_idx, previous;
    previous = objective;
    while (true) {
        previous = shortest_paths[objective][1];
        if (previous == NV_VERTEX)
            break;
        path.insert(path.begin(), previous);
        objective = previous;
    }
    path.insert(path.begin(), shortest_paths[end_idx][0]);
    path.push_back(end_idx);
    return path;
}

vector<wt_pair> Vertex::hash_shortest_path(string end_vertex){
    vector<wt_pair> path;
    string objective = end_vertex, previous;
    previous = objective;
    while (true) {
        previous = hash_shortest_paths.at(objective).second;
        if (previous == NANKEY)
            break;
        path.insert(path.begin(), make_pair(hash_shortest_paths.at(previous).first, previous));
        objective = previous;
    }
    path.insert(path.begin(), make_pair(hash_shortest_paths.at(end_vertex).first, end_vertex));
    path.push_back(make_pair(hash_shortest_paths.at(end_vertex).first, end_vertex));
    return path;
}

vector<vector<int>> Vertex::get_shortest_paths(){
   return this->shortest_paths;
}

unordered_map<string, wt_pair> Vertex::get_hash_shortest_paths(){
    return this->hash_shortest_paths;
}

unordered_map<string, vector<vector<wt_pair>>> Vertex::get_possible_paths(){
    return this->possible_paths;
}

int Vertex::get_index(){
    return this->index;
}

void Vertex::set_index(int n_index){
    this->index = n_index;
}

void Vertex::set_tag(string n_tag){
    this->tag = n_tag;
}

void Vertex::set_shortest_path(vector<vector<int>> p_nd_shortest_path){
      this->shortest_paths = p_nd_shortest_path;
}

void Vertex::set_hash_shortest_path(unordered_map<string, wt_pair> p_hash_shortest_paths){
    this->hash_shortest_paths = p_hash_shortest_paths;
}

void Vertex::set_possible_paths(unordered_map<string, vector<vector<wt_pair>>> p_possible_paths){
    this->possible_paths = p_possible_paths;
}

void Vertex::add_possible_path_key(string destination){
    vector<vector<wt_pair>> tmp;
    this->possible_paths.insert(make_pair(destination, tmp));
}

void Vertex::add_possible_path(string key, vector<wt_pair> path){
    this->possible_paths.at(key).push_back(path);
}
