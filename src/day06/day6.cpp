#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

std::vector<char> load_input(const std::string& file){
    std::vector<char> ret;
    std::ifstream fs(file);
    std::string line;
    std::getline(fs, line); 
    int val;
    std::stringstream ss(line);
    while(ss >> val){
        ret.push_back(val);
    }
  
    return ret;
}

struct bank_hash_t{
    size_t operator()(const std::vector<char>& b) const{
        return std::hash<std::string_view>()(std::string_view(b.data(), b.size()));
    }
};

auto process(const std::vector<char>& banks){
    
    std::unordered_map<std::vector<char>,int,bank_hash_t> seen;
    std::vector<char> new_banks = banks;

    bool seen_once = false;
    bool seen_twice = false;
    int cycles = 0;

    while(!seen_twice)
    {
        auto mx = std::max_element(new_banks.begin(), new_banks.end());
        int steps = *mx;
        *mx = 0; 
        int start = (int)std::distance(new_banks.begin(), mx)+1;
        for(int i=0; i<steps; ++i){
            new_banks[(start+i) % new_banks.size()]++; 
        }

        seen_once |= seen[new_banks] > 0;
        seen_twice = seen[new_banks] > 1;

        seen[new_banks]++;
        cycles++;
    };

    return std::make_pair(seen.size()+1, cycles-seen.size()-1);
}

void main()
{
    auto test_values = load_input("../src/day06/example_input.txt");
    auto actual_values = load_input("../src/day06/input.txt");

    auto test = process(test_values);
    auto actual = process(actual_values);

    std::cout << "part1: " << test.first << std::endl;
    std::cout << "part1: " << actual.first  << std::endl;

    std::cout << "part2: " << test.second << std::endl;
    std::cout << "part2: " << actual.second << std::endl;

}