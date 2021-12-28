#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <numeric>

using graph_t = std::map<int,std::set<int>>;

graph_t load_input(const std::string& file){
    graph_t ret;
    std::ifstream fs(file);
    std::string line;
    std::string dummy;
    int src, dst;
    std::string dst_str;
    while(std::getline(fs, line)){
        std::stringstream ss(line);
        ss >> src;

        ss >> dummy;
        while(ss >> dst_str){
            if(dst_str.back() == ','){
                dst_str.pop_back();
            }
            dst = std::stoi(dst_str);
            ret[src].insert(dst);
            ret[dst].insert(src);
        }
    } 

    return ret;
}

void dfs(int village, const graph_t& graph, std::map<int,bool>& visited){
    visited[village] = true;

    for(auto& dst : graph.at(village)){
        if(!visited[dst]){
            dfs(dst, graph, visited);
        }
    }
}

auto process(const graph_t& graph)
{
    std::map<int,bool> visited;
    for(auto& [src,_] : graph){
        visited[src] = false;
    }

    int src0_count = 0;
    int group_count = 0;

    for(auto& [src,_] : graph){
        if(!visited[src]){
            dfs(src, graph, visited);
            group_count++;
        }

        if(src == 0){
            src0_count = (int)std::count_if(visited.begin(), visited.end(), [](auto& a){
                return a.second;  
            });
        }
    }

    return std::make_pair(src0_count,group_count);
}

void main()
{
    auto test_values = load_input("../src/day12/example_input.txt");
    auto actual_values = load_input("../src/day12/input.txt");

    auto [test_src_count,test_group_count] = process(test_values);
    auto [src_count,group_count] = process(actual_values);

    std::cout << "part1: " << test_src_count << std::endl;
    std::cout << "part1: " << src_count << std::endl;

    std::cout << "part2: " << test_group_count << std::endl;
    std::cout << "part2: " << group_count << std::endl;
}