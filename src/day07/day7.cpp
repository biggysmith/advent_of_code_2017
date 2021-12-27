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
#include <optional>

struct data_t{
    int weight;
    std::vector<std::string> sub_programs;
};

std::map<std::string,data_t> load_input(const std::string& file){
    std::map<std::string,data_t> ret;
    std::ifstream fs(file);
    char s;
    int val;
    std::string prog_name;
    std::string name;
    std::string line;
    while(std::getline(fs, line)){
        data_t data;
        std::stringstream ss(line);
        ss >> prog_name;

        ss >> s >> val;
        data.weight = val;

        ss >> s;
        ss >> s;
        if(ss >> name){
            while(ss >> name){
                if(name.back() == ','){
                    name.pop_back();
                }
                data.sub_programs.push_back(name);
            }
        }

        ret[prog_name] = data;
    } 

    return ret;
}

struct node_t{
    std::string name;
    int weight;
    std::set<node_t*> childeren;
};

struct relationship_t{
    node_t node;
    std::string parent;
};

void build_tree(node_t& node,std::vector<relationship_t>& relationships){
    for(auto& rel : relationships){
        if(rel.parent == node.name){
            node.childeren.insert(&rel.node);
        }
    }

    if(!node.childeren.empty()){
        for(auto& child : node.childeren){
            build_tree(*child, relationships);
        }
    }
}

auto process(const std::map<std::string,data_t>& input)
{
    std::vector<relationship_t> relationships;
    for(auto& [name,data] : input){
        relationships.push_back({ {name, data.weight}, "none" });
        for(auto& sub_prog : data.sub_programs){
            auto it = std::find_if(relationships.begin(),relationships.end(),[&](auto& a){
                return a.node.name == sub_prog;
            });
            if(it == relationships.end()){
                relationships.push_back({ {sub_prog, input.at(sub_prog).weight}, name });
            }else{
                it->parent = name;
            }
        }
    }

    node_t none = {"none", 0};
    build_tree(none, relationships);

    auto find_depth = [&](auto&& self, node_t* node, int depth) -> int{
        int max_depth = 0;
        for(auto& child : node->childeren){
            max_depth = std::max(self(self, child, depth+1), max_depth);
        }
        return std::max(max_depth, depth);
    };

    int max_depth = 0;
    node_t* root_node = nullptr;
    for(auto& child : none.childeren){
        int depth = find_depth(find_depth, child, 0);
        if(depth > max_depth){
            root_node = child;
            max_depth = depth;
        }
    }

    std::optional<int> adjested_weight;

    auto calculate_weight = [&](auto&& self, node_t* node) -> int{
        int weight = node->weight;
        std::vector<int> level_weights;
        for(auto& child : node->childeren){
            int node_weight = self(self, child);
            weight += node_weight;
            level_weights.push_back(node_weight);
        }

        if(!adjested_weight){
            auto it = std::adjacent_find(level_weights.begin(), level_weights.end(), std::not_equal_to<int>());
            if(it != level_weights.end()){
                node_t* dodgy_node = *std::next(node->childeren.begin(), std::distance(level_weights.begin(),it+1));
                adjested_weight = dodgy_node->weight - (*(it+1) - (*it));
            }
        }
        
        return weight;
    };

    calculate_weight(calculate_weight, root_node);      
    return std::make_pair(root_node->name, *adjested_weight);
}

void main()
{
    auto test_values = load_input("../src/day07/example_input.txt");
    auto actual_values = load_input("../src/day07/input.txt");

    auto [test_root,test_weight] = process(test_values);
    auto [root,weight] = process(actual_values);

    std::cout << "part1: " << test_root << std::endl;
    std::cout << "part1: " << root  << std::endl;

    std::cout << "part2: " << test_weight << std::endl;
    std::cout << "part2: " << weight  << std::endl;
}