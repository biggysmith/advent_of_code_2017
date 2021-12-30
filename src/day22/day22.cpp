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

struct vec2_t{
    int x,y;
};

vec2_t& operator+=(vec2_t& a, const vec2_t& b){ a.x+=b.x; a.y+=b.y; return a; }

struct grid_t{
    grid_t() {}
    grid_t(int w,int h) : points(w*h,'.'), width(w), height(h) {}

    std::vector<char> points;
    int width, height;

    char& get(const vec2_t& p) { return points[p.y*width+p.x]; }
    const char& get(const vec2_t& p) const { return points[p.y*width+p.x]; }
};

grid_t load_input(const std::string& file){
    grid_t ret;
    std::ifstream fs(file);
    std::string line;
    ret.width = ret.height = 0;
    while(std::getline(fs, line)){
        ret.points.insert(ret.points.end(), line.begin(), line.end());
        ret.height++;
        ret.width = std::max(ret.width, (int)line.size());
    }   

    return ret;
}

int mod(int a,int b){
    return (b + (a%b)) % b;
}

auto process(const grid_t& grid, int bursts, bool part1)
{
    int inflate = 141; 
    grid_t big_grid(grid.width*inflate, grid.height*inflate);

    for(int y=0; y<grid.height; ++y){
        for(int x=0; x<grid.width; ++x){
            big_grid.get({ (big_grid.width-grid.width)/2+x, (big_grid.height-grid.height)/2+y }) = grid.get({x,y});
        }
    }

    size_t infections = 0;
    vec2_t pos = { big_grid.width/2, big_grid.height/2 };
    std::vector<vec2_t> dirs = { {0,-1}, {1,0}, {0,1}, {-1,0} };
    int d = 0;

    for(int b=0; b<bursts; ++b)
    {
        if(part1){
            if(big_grid.get(pos) == '.'){
                big_grid.get(pos) = '#';
                d = mod(d-1, 4);
                infections++;
            }else{
                big_grid.get(pos) = '.';
                d = mod(d+1, 4);
            }
        }
        else{
            if(big_grid.get(pos) == '.'){
                big_grid.get(pos) = 'W';
                d = mod(d-1, 4);
            }else if(big_grid.get(pos) == 'W'){
                big_grid.get(pos) = '#';
                infections++;
            }else if(big_grid.get(pos) == 'F'){
                big_grid.get(pos) = '.';
                d = mod(d+2, 4);
            }else{
                big_grid.get(pos) = 'F';
                d = mod(d+1, 4);
            }
        }

        pos += dirs[d];

    }

    return infections;
}

void main()
{
    auto test_values = load_input("../src/day22/example_input.txt");
    auto actual_values = load_input("../src/day22/input.txt");

    std::cout << "part1: " << process(test_values, 10000, true) << std::endl;
    std::cout << "part1: " << process(actual_values, 10000, true) << std::endl;

    std::cout << "part2: " << process(test_values, 10000000, false) << std::endl;
    std::cout << "part2: " << process(actual_values, 10000000, false) << std::endl;
}
