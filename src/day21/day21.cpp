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
#include <array>
#include "timer.hpp"

struct pattern_t{
    pattern_t() {}
    pattern_t(int w) : rows(w*w, ' '), width(w) {}

    char& get(int x,int y){ return rows[y*width+x]; }
    const char& get(int x,int y) const{ return rows[y*width+x]; }

    std::string rows;
    int width;
};

bool operator==(const pattern_t& a,const pattern_t& b){
    return a.rows == b.rows;
}

struct pattern_hash{
    size_t operator()(const pattern_t& pattern) const{
        return std::hash<std::string>()(pattern.rows);
    }
};

using rules_t = std::unordered_map<pattern_t,pattern_t,pattern_hash>;

pattern_t start_pattern(){
    pattern_t ret;
    ret.rows = ".#...####";
    ret.width = 3;
    return ret;
}

pattern_t rotate(const pattern_t& pattern, int n)
{
    n = n % 4;
    pattern_t new_pattern = pattern;
    for(int y=0; y<pattern.width; ++y){
        for(int x=0; x<pattern.width; ++x){
            if(n==1){
                new_pattern.get(x,y) = pattern.get(y, pattern.width-x-1);
            }else if(n==2){
                new_pattern.get(x,y) = pattern.get(pattern.width-x-1, pattern.width-y-1);
            }else if(n==3){
                new_pattern.get(x,y) = pattern.get(pattern.width-y-1, x);
            }
        }
    }
    return new_pattern;
}

pattern_t flip(const pattern_t& pattern, int n)
{
    n = n % 2;
    pattern_t new_pattern = pattern;
    for(int y=0; y<pattern.width; ++y){
        for(int x=0; x<pattern.width; ++x){
            if(n==0){
                new_pattern.get(x,y) = pattern.get(x, pattern.width-y-1);
            }else if(n==1){
                new_pattern.get(x,y) = pattern.get(pattern.width-x-1, y);
            }
        }
    }
    return new_pattern;
}

rules_t load_input(const std::string& file){
    rules_t ret;
    std::ifstream fs(file);
    std::string line;
    std::string arrow;
    while(std::getline(fs, line)){
        pattern_t pattern_in;
        pattern_t pattern_out;
        std::stringstream ss(line);
        ss >> pattern_in.rows >> arrow >> pattern_out.rows;
        pattern_in.rows.erase(std::remove(pattern_in.rows.begin(), pattern_in.rows.end(), '/'), pattern_in.rows.end());
        pattern_out.rows.erase(std::remove(pattern_out.rows.begin(), pattern_out.rows.end(), '/'), pattern_out.rows.end());
        pattern_in.width = (int)sqrt(pattern_in.rows.size());
        pattern_out.width = (int)sqrt(pattern_out.rows.size());

        // map all rotations/flips to output pattern (group p4g so 8 unique orientations, 4rots * 2flips)
        ret[pattern_in] = pattern_out;
        for(int i=1; i<4; ++i){
             ret[rotate(pattern_in, i)] = pattern_out;
        }
        pattern_t flipped = flip(pattern_in, 0);
        ret[flipped] = pattern_out;
        for(int i=5; i<8; ++i){
            ret[rotate(flipped, i)] = pattern_out;
        }
    }   

    return ret;
}


auto process(const rules_t& rules, int iters)
{
    pattern_t pattern = start_pattern();

    for(int iter=0; iter<iters; ++iter)
    {
        bool div2 = (pattern.rows.size() % 2) == 0;

        int x_grids = pattern.width / (div2 ? 2 : 3);

        int new_w = (div2 ? 3 : 4);
        pattern_t new_pattern(x_grids * new_w);

        #pragma omp parallel for
        for(int gy=0; gy<x_grids; ++gy){
            for(int gx=0; gx<x_grids; ++gx){

                pattern_t sub_pattern(div2 ? 2 : 3);

                for(int sy=0; sy<sub_pattern.width; ++sy){
                    for(int sx=0; sx<sub_pattern.width; ++sx){
                        sub_pattern.get(sx,sy) = pattern.get(gx*sub_pattern.width+sx,gy*sub_pattern.width+sy);
                    }
                }

                const pattern_t& out = rules.at(sub_pattern);

                for(int sy=0; sy<new_w; ++sy){
                    for(int sx=0; sx<new_w; ++sx){
                        new_pattern.get(gx*new_w+sx,gy*new_w+sy) = out.get(sx,sy);
                    }
                }

            }
        }

        pattern = new_pattern;
    }

    return std::count(pattern.rows.begin(), pattern.rows.end(), '#');
}

void main()
{
    auto test_values = load_input("../src/day21/example_input.txt");
    auto actual_values = load_input("../src/day21/input.txt");

    std::cout << "part1: " << process(test_values, 2) << std::endl;
    std::cout << "part1: " << process(actual_values, 5) << std::endl;

    std::cout << "part2: " << process(actual_values, 18) << std::endl;
}
