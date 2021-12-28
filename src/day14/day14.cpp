#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <set>
#include <iomanip>

std::string hex_to_bin(const std::string& hex)
{
    auto to_bin = [](char c){
        switch(c)
        {
            case '0': return "0000";
            case '1': return "0001";
            case '2': return "0010";
            case '3': return "0011";
            case '4': return "0100";
            case '5': return "0101";
            case '6': return "0110";
            case '7': return "0111";
            case '8': return "1000";
            case '9': return "1001";
            case 'a': return "1010";
            case 'b': return "1011";
            case 'c': return "1100";
            case 'd': return "1101";
            case 'e': return "1110";
            case 'f': return "1111";
            default:    throw std::exception("invalid hex character");
        };
    };

    std::string ret;
    for(auto c : hex){
        ret += to_bin(c);
    }
    
    return ret;
}

std::string knot_hash(std::string lengths, int n=256)
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
        ss << std::setfill('0') << std::setw(2) << std::hex << std::accumulate(it+1, it+16, *it, std::bit_xor<int>());
    }

    return hex_to_bin(ss.str());
}

size_t part1(const std::string& input)
{
    size_t sum = 0;
    for(int i=0; i<128; ++i){
        std::string row_str = input + "-" + std::to_string(i);
        std::string hash = knot_hash(row_str);
        sum += std::count(hash.begin(), hash.end(), '1');
    }

    return sum;
}

struct grid_t{
    grid_t() : points(128*128,0) {}
    int& get(int x,int y){ return points[y*128+x]; }

    std::vector<int> points;
};

void flood_fill(grid_t& grid, int x, int y, int region)
{
    if(x < 0 || x > 127 || y < 0 || y > 127){
        return;
    }

    if(grid.get(x,y) == 0){
        return;
    }
    
    if(grid.get(x,y) == 1){
        grid.get(x,y) = region;
        flood_fill(grid, x+1, y, region);
        flood_fill(grid, x-1, y, region);
        flood_fill(grid, x, y+1, region);
        flood_fill(grid, x, y-1, region);
    }
}

size_t part2(const std::string& input)
{
    grid_t grid;

    for(int i=0; i<128; ++i){
        std::string row_str = input + "-" + std::to_string(i);
        std::string hash = knot_hash(row_str);
        std::transform(hash.begin(), hash.end(), grid.points.begin()+i*128, [](auto& a){
            return a-'0';   
        });
    }

    int curr_region = 2;
    std::set<int> used_regions;

    for(int y=0; y<128; ++y){
        for(int x=0; x<128; ++x){

            if(grid.get(x,y) == 1){
                flood_fill(grid, x, y, curr_region);
                curr_region++;
            }

            if(grid.get(x,y) != 0){
                used_regions.insert(grid.get(x,y));
            }

        }
    }

    return used_regions.size();
}

void main()
{
    std::cout << "part1: " << part1("flqrgnkx") << std::endl;
    std::cout << "part1: " << part1("amgozmfv") << std::endl;

    std::cout << "part2: " << part2("flqrgnkx") << std::endl;
    std::cout << "part2: " << part2("amgozmfv") << std::endl;
}