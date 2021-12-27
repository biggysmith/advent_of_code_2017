#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stack>

std::string load_input(const std::string& file){
    std::string ret;
    std::ifstream fs(file);
    std::getline(fs, ret);
    return ret;
}

auto process(const std::string& line)
{
    std::stack<char> stack;
    std::stack<char> garbage_stack;

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
            if(garbage_stack.empty()){
                garbage_stack.push(c);
            }else{
                garbage_count++;
            }
        } 
        else if (c == '>') 
        { 
            garbage_stack.pop(); 
        } 
        else if (c == '{') 
        { 
            if(garbage_stack.empty()){
                stack.push(c);
            }else{
                garbage_count++;
            }
        }
        else if (c == '}') 
        { 
            if(garbage_stack.empty()){
                group_count++;
                group_score += (int)stack.size();
                stack.pop();
            }else{
                garbage_count++;
            }
        }
        else if(!garbage_stack.empty())
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
    std::cout << "part1: " << non_cancelled << std::endl;
}