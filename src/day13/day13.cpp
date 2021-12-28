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

struct scanner_t{
    int pos;
    int range;
};

std::map<int,scanner_t> load_input(const std::string& file){
    std::map<int,scanner_t> ret;
    std::ifstream fs(file);
    std::string line;
    std::string dummy;
    while(std::getline(fs, line)){
        std::stringstream ss(line);
        int depth, range;
        ss >> depth >> dummy >> range;
        ret[depth] = { 0, range };
    }
       
    return ret;
}

int part1(const std::map<int,scanner_t>& in)
{
    auto firewall = in;

    int max_depth = 0;
    for(auto& [depth,scanner] : firewall){
        max_depth = std::max(depth, max_depth);
    }

    int severity = 0;

    for(int p=0; p<=max_depth; ++p){
        if((firewall.find(p) != firewall.end()) && (firewall[p].pos % ((firewall[p].range*2)-2)) == 0){
            severity += p * firewall[p].range;
        }

        for(auto& [depth,scanner] : firewall){
            scanner.pos++;
        }
    }

    return severity;
}

int part2(const std::map<int,scanner_t>& firewall){
    int delay = 0;
    bool caught = true;
    while (caught){
        caught = std::any_of(firewall.begin(), firewall.end(), [=](auto& layer){ 
            auto& [depth,scanner] = layer;
            return (depth + delay) % ((scanner.range*2)-2) == 0; 
        });
        delay++;
    }

    return delay-1;
}

void main()
{
    auto test_values = load_input("../src/day13/example_input.txt");
    auto actual_values = load_input("../src/day13/input.txt");

    std::cout << "part1: " << part1(test_values) << std::endl;
    std::cout << "part1: " << part1(actual_values) << std::endl;

    std::cout << "part2: " << part2(test_values) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}