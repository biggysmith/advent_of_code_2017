#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <set>

size_t part1(size_t a,size_t b)
{
    size_t sum = 0;
    for(int i=0; i<40000000; ++i)
    {
        a = (a * 16807) % 2147483647;
        b = (b * 48271) % 2147483647;

        if((a & 0xFFFF) == (b & 0xFFFF)){
            sum++;
        }
    }

    return sum;
}

size_t part2(size_t a,size_t b)
{
    size_t sum = 0;
    for(int i=0; i<5000000; ++i)
    {
        do{
            a = (a * 16807) % 2147483647;
        }while((a & 3) != 0);

        do{
            b = (b * 48271) % 2147483647;
        }while((b & 7)!= 0);

        if((a & 0xFFFF) == (b & 0xFFFF)){
            sum++;
        }
    }

    return sum;
}

void main()
{
    std::cout << "part1: " << part1(65, 8921) << std::endl;
    std::cout << "part1: " << part1(516, 190) << std::endl;

    std::cout << "part2: " << part2(65, 8921) << std::endl;
    std::cout << "part2: " << part2(516, 190) << std::endl;
}