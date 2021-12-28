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

std::vector<std::string> load_input(const std::string& file){
    std::vector<std::string> ret;
    std::ifstream fs(file);
    std::string line;
    std::getline(fs, line);
    std::string move_str;
    std::stringstream ss(line);
    while(std::getline(ss, move_str, ',')){
        ret.push_back(move_str);
    } 

    return ret;
}

void process(std::string& programs,const std::string& move)
{
    if(move[0] == 's'){
        std::rotate(programs.begin(), programs.begin()+programs.size()-std::stoi(move.substr(1)), programs.end());
    }else if(move[0] == 'x'){
        std::swap(programs[std::stoi(move.substr(1,move.find_first_of('/')))], programs[std::stoi(move.substr(move.find_first_of('/')+1))]);
    }else if(move[0] == 'p'){
        std::swap(programs[programs.find(move[1])],programs[programs.find(move[3])]);
    }
}

std::string part1(const std::vector<std::string>& moves)
{
    std::string programs = "abcdefghijklmnop";

    for(auto& move : moves){
        process(programs, move);
    }

    return programs;
}

std::string part2(const std::vector<std::string>& moves)
{
    std::string orig_programs = "abcdefghijklmnop";
    std::string programs = orig_programs;

    std::vector<std::string> new_orders;

    do 
    {
        for(auto& move : moves){
            process(programs, move);
        }
        new_orders.push_back(programs);
    }
    while(programs != orig_programs);

    return new_orders[(1000000000 % new_orders.size())-1];
}

void main()
{
    auto actual_values = load_input("../src/day16/input.txt");

    std::cout << "part1: " << part1(actual_values) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}