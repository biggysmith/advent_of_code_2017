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

size_t part1(int input)
{
    int steps = 2017;

    std::list<int> list;
    list.insert(list.begin(), 0);
    int pos = 0;

    for(int i=0; i<steps; ++i){
        pos = 1 + (pos + input) % (i+1);
        list.insert(std::next(list.begin(),pos), i+1);
    }

    auto it = std::find(list.begin(), list.end(), 2017);
    auto idx = std::distance(list.begin(), it);
    return *std::next(list.begin(), (idx + 1) % steps);
}


size_t part2(int input)
{
    size_t steps = 50000000;

    size_t pos = 0;
    size_t result = 0;

    for(size_t i=0; i<steps; ++i){
        pos = 1 + (pos + input) % (i+1);
        if(pos == 1){
            result = i+1;
        }
    }

    return result;
}

void main()
{
    std::cout << "part1: " << part1(3) << std::endl;
    std::cout << "part1: " << part1(354) << std::endl;
    
    std::cout << "part2: " << part2(354) << std::endl;
}