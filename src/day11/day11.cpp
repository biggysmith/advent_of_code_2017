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

struct vec3_t{
    int q,r,s;
};

vec3_t& operator+=(vec3_t& a,const vec3_t& b){
    a.q+=b.q; a.r+=b.r; a.s+=b.s;
    return a;
}

int magnitude(const vec3_t& a){
    return (std::abs(a.q) + std::abs(a.r) + std::abs(a.s)) / 2;
}

vec3_t dir(const std::string& dir_str){
    if(dir_str == "n"){
        return { 0,-1,1 };
    }else if(dir_str == "ne"){
        return { 1,-1,0 };
    }else if(dir_str == "se"){
        return { 1,0,-1 };
    }else if(dir_str == "s"){
        return { 0,1,-1 };
    }else if(dir_str == "sw"){
        return { -1,1,0 };
    }else if(dir_str == "nw"){
        return { -1,0,1 };
    }else{
        throw std::exception("unrecognized dir");
    }
}

std::vector<std::string> load_input(const std::string& file){
    std::vector<std::string> ret;
    std::ifstream fs(file);
    std::string line;
    std::getline(fs, line);
    std::string dir_str;
    std::stringstream ss(line);
    while(std::getline(ss, dir_str, ',')){
        ret.push_back(dir_str);
    } 

    return ret;
}

auto process(const std::vector<std::string>& steps)
{
    int max_dist = 0;
    vec3_t pos { 0,0,0 };
    for(auto& step : steps){
        pos += dir(step);
        max_dist = std::max(magnitude(pos), max_dist);
    }

    return std::make_pair(magnitude(pos), max_dist);
}

void main()
{
    auto actual_values = load_input("../src/day11/input.txt");

    auto [fewest, furthest] = process(actual_values);

    std::cout << "part1: " << fewest << std::endl;
    std::cout << "part2: " << furthest << std::endl;
}