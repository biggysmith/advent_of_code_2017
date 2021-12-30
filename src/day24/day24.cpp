#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <set>
#include <map>
#include <queue>
#include "timer.hpp"

struct component_t{
    int port0, port1;
    int used_port = -1;
};
            
std::vector<component_t> load_input(const std::string& file){
    std::vector<component_t> ret;
    std::ifstream fs(file);
    std::string line;
    char c;
    while(std::getline(fs, line)){
        component_t com;
        std::stringstream ss(line);
        ss >> com.port0 >> c >> com.port1;
        ret.push_back(com);
    }   
    return ret;
}

int com_strength(const component_t& com){
    return com.port0 + com.port1;
}

void find_bridge(
    const std::vector<component_t>& components, 
    const component_t& last,
    int current_strength,
    int& max_strength,
    int current_depth,
    int& max_depth,
    int& longest_max_strength
){
    for(int c=0; c<components.size(); ++c)
    {
        auto& com = components[c];

        auto extend = [&](int use){
            auto new_coms = components;
            new_coms.erase(new_coms.begin()+c);

            int new_strength = current_strength + com_strength(com);
            max_strength = std::max(max_strength, new_strength);

            find_bridge(new_coms, { com.port0, com.port1, use }, new_strength, max_strength, current_depth + 1, max_depth, longest_max_strength);
        };

        if((last.used_port == 0 && last.port1 == com.port0) || (last.used_port == 1 && last.port0 == com.port0)){
            extend(0);
        }else if((last.used_port == 0 && last.port1 == com.port1) || (last.used_port == 1 && last.port0 == com.port1)){
            extend(1);
        }
    }

    if(current_depth > max_depth){
        max_depth = current_depth;
        longest_max_strength = current_strength;
    }
    else if(current_depth == max_depth){
        longest_max_strength = std::max(longest_max_strength, current_strength);
    }
}

auto process(const std::vector<component_t>& components)
{
    int max_depth = 0;
    int max_strength = 0;
    int longest_max_strength = 0;
    for(int c=0; c<components.size(); ++c){
        auto& com = components[c];
        if(com.port0 == 0){
            auto new_coms = components;
            new_coms.erase(new_coms.begin()+c);
            find_bridge(new_coms, { com.port0, com.port1, 0 }, com_strength(com), max_strength, 0, max_depth, longest_max_strength);
        }
    }

    return std::make_pair(max_strength, longest_max_strength);
}

void main()
{
    auto test_values = load_input("../src/day24/example_input.txt");
    auto actual_values = load_input("../src/day24/input.txt");

    auto test = process(test_values);
    auto actual = process(actual_values);

    std::cout << "part1: " << test.first << std::endl;
    std::cout << "part1: " << actual.first << std::endl;

    std::cout << "part2: " << test.second << std::endl;
    std::cout << "part2: " << actual.second << std::endl;
}
