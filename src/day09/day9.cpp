#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

std::string load_input(const std::string& file){
    std::string ret;
    std::ifstream fs(file);
    std::getline(fs, ret);
    return ret;
}

auto process(const std::string& line)
{
    int stack_size = 0;
    bool garbage = false;

    int group_count = 0;
    int group_score = 0;
    int garbage_count = 0;

    for (int i=0; i<line.size(); ++i) 
    {
        char c = line[i];

        if(c == '!'){
            i++;
            continue;
        }

        if (c == '<') 
        {
            if(!garbage){
                garbage = true;
            }else{
                garbage_count++;
            }
        } 
        else if (c == '>') 
        { 
            garbage = false;
        } 
        else if (c == '{') 
        {
            if(!garbage){
                stack_size++;
            }else{
                garbage_count++;
            }
        }
        else if (c == '}') 
        {
            if(!garbage){
                group_count++;
                group_score += stack_size;
                stack_size--;
            }else{
                garbage_count++;
            }
        }
        else if(garbage)
        {
            garbage_count++;
        }
    }

    return std::make_tuple(group_count, group_score, garbage_count);
}

void main()
{
    auto actual_values = load_input("../src/day09/input.txt");

    auto [count, score, non_cancelled] = process(actual_values);

    std::cout << "part1: " << score << std::endl;
    std::cout << "part2: " << non_cancelled << std::endl;
}