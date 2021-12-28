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

vec2_t operator+(const vec2_t& a,const vec2_t& b){
    return { a.x+b.x, a.y+b.y};
}

struct diagram_t{
    std::vector<char> points;
    int width, height;

    char& get(const vec2_t& p) { return points[p.y*width+p.x]; }
    const char& get(const vec2_t& p) const{ return points[p.y*width+p.x]; }

    bool valid(const vec2_t& p) const{
        return p.x >= 0 && p.x < width && p.y >= 0 && p.y < height;
    }

    void print() const{
        std::cout << std::endl;
        for(int y=0; y<height; ++y){
            for(int x=0; x<width; ++x){
                std::cout << get({x,y});
            }
            std::cout << std::endl;
        }
    }
};

diagram_t load_input(const std::string& file){
    diagram_t ret;
    std::ifstream fs(file);
    std::string line;
    ret.width = 0;
    ret.height = 0;
    while(std::getline(fs, line)){
        ret.points.insert(ret.points.end(), line.begin(), line.end());
        ret.height++;
        ret.width = std::max(ret.width, (int)line.size());
    }    
    return ret;
}

auto process(const diagram_t& diagram)
{
    vec2_t pos = { 0,0 };

    for(int x=0; x<diagram.width; ++x){
        if(diagram.get({x,0}) == '|'){
            pos = {x,0};
            break;
        }
    }

    int d = 0;
    std::vector<vec2_t> dirs = { {0,1}, {1,0}, {0,-1}, {-1,0} };

    bool can_move = true;

    int steps = 0;
    std::string letters;
    while(can_move)
    {
        pos = pos + dirs[d];

        if(diagram.get(pos) == ' '){ // cant go any further
            break;
        }
        else if(diagram.get(pos) == '+'){
            int opp = (d+2) % 4;
            for(int i=0; i<4; ++i){
                if(i == opp){ // don't go backwards
                    continue;
                }

                auto new_pos = pos + dirs[i];
                if(!diagram.valid(new_pos)) { // don't go out of bounds
                    continue;
                }

                if(diagram.get(new_pos) != ' '){
                    d = i;
                    can_move = true;
                    break;
                }

                can_move = false;
            }
        }
        else if(isalpha(diagram.get(pos))){
            letters += diagram.get(pos);
        }

        steps++;
    }

    return std::make_pair(letters, steps+1);
}

void main()
{
    auto test_values = load_input("../src/day19/example_input.txt");
    auto actual_values = load_input("../src/day19/input.txt");

    auto [test_letters, test_steps] = process(test_values);
    auto [letters, steps] = process(actual_values);

    std::cout << "part1: " << test_letters << std::endl;
    std::cout << "part1: " << test_steps << std::endl;

    std::cout << "part2: " << letters << std::endl;
    std::cout << "part2: " << steps << std::endl;
}
