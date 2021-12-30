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

struct component_t{
    int port0, port1;
    int used_port = -1;
};

bool operator==(const component_t& a,const component_t& b){
    return a.port0 == b.port0 && a.port1 == b.port1;
}
                
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

void find_bridge(const std::vector<component_t>& components, const std::vector<component_t>& path, std::vector<std::vector<component_t>>& final_paths){

    auto& last = path.back();
    for(auto& com : components){
        if(std::find(path.begin(), path.end(), com) == path.end()){ // not present in path

            auto extend = [&](int use){
                auto new_path = path;
                new_path.push_back({ com.port0, com.port1, use });
                final_paths.push_back(new_path);
                find_bridge(components,new_path,final_paths);
            };

            if(last.used_port == 0){
                if(last.port1 == com.port0){
                    extend(0);
                }else if(last.port1 == com.port1){
                    extend(1);
                }
            }

            if(last.used_port == 1){
                if(last.port0 == com.port0){
                    extend(0);
                }else if(last.port0 == com.port1){
                    extend(1);
                }
            }

        }
    }

}

void print_path(const std::vector<component_t>& path){
    for(auto& com : path){
        std::cout << com.port0 << "/" << com.port1 << "--";
    }
    std::cout << std::endl;
}

int strength(const std::vector<component_t>& path){
    int sum = 0;
    for(auto& com : path){
        sum += com.port0 + com.port1;
    }
    return sum;
}

auto process(const std::vector<component_t>& components)
{
    std::vector<std::vector<component_t>> final_paths;

    for(auto& com : components){
        if(com.port0 == 0){
            std::vector<component_t> path { { com.port0, com.port1, 0 } };
            final_paths.push_back(path);
            find_bridge(components, path, final_paths);
        }
    }

    int max_strength = 0;
    for(auto& path : final_paths){
        max_strength = std::max(max_strength, strength(path));
    }

    std::vector<std::vector<component_t>> longest_paths;
    int max_length = 0;
    for(auto& path : final_paths){
        if(path.size() > max_length){
            max_length = (int)path.size();
            longest_paths.clear();
        }else if(path.size() == max_length){
            longest_paths.push_back(path);
        }
    }

    int max_strength2 = 0;
    for(auto& path : longest_paths){
        max_strength2 = std::max(max_strength2, strength(path));
    }

    return std::make_pair(max_strength, max_strength2);
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
