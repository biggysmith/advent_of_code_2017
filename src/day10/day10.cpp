#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>

int process1(const std::vector<int>& lengths, int n)
{
    std::vector<int> list(n);
    std::iota(list.begin(), list.end(), 0);

    int pos = 0;
    int skip = 0;

    for(auto len : lengths){
        std::rotate(list.begin(), list.begin()+pos, list.end());
        std::reverse(list.begin(), list.begin()+len);
        std::rotate(list.begin(), list.begin()+(list.size()-pos), list.end());
        pos = (pos + len + skip) % list.size();
        skip++;
    }

    return list[0] * list[1];
}

std::string process2(std::string lengths, int n)
{
    std::vector<int> list(n);
    std::iota(list.begin(), list.end(), 0);

    lengths += 17;
    lengths += 31;
    lengths += 73;
    lengths += 47;
    lengths += 23;

    int pos = 0;
    int skip = 0;

    for(int r=0; r<64; ++r)
    {
        for(auto len : lengths){
            std::rotate(list.begin(), list.begin()+pos, list.end());
            std::reverse(list.begin(), list.begin()+len);
            std::rotate(list.begin(), list.begin()+(list.size()-pos), list.end());
            pos = (pos + len + skip) % list.size();
            skip++;
        }
    }

    std::stringstream ss;
    for(auto it=list.begin(); it<list.end(); it+=16){
        ss << std::hex << std::accumulate(it+1, it+16, *it, std::bit_xor<int>());
    }

    return ss.str();
}

void main()
{
    std::cout << "part1: " << process1({ 189,1,111,246,254,2,0,120,215,93,255,50,84,15,94,62 }, 256) << std::endl;
    std::cout << "part2: " << process2( "189,1,111,246,254,2,0,120,215,93,255,50,84,15,94,62" , 256) << std::endl;
}