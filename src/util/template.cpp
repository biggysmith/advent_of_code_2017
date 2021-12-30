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

std::vector<int> load_input(const std::string& file){
    std::vector<int> ret;
    std::ifstream fs(file);
    std::string line;
    while(std::getline(fs, line)){

    }   

    return ret;
}

auto part1(const std::vector<int>& particles)
{

    return 0;
}

auto part2(const std::vector<int>& in)
{

    return 0;
}

void main()
{
    auto test_values = load_input("../src/day21/example_input.txt");
    auto actual_values = load_input("../src/day21/input.txt");

    std::cout << "part1: " << part1(test_values) << std::endl;
    std::cout << "part1: " << part1(actual_values) << std::endl;

    std::cout << "part2: " << part2(test_values) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}
