#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>

struct instruction_t{
    std::string reg0;
    std::string op0;
    int value0;
    std::string reg1;
    std::string op1;
    int value1;
};

std::vector<instruction_t> load_input(const std::string& file){
    std::vector<instruction_t> ret;
    std::ifstream fs(file);
    std::string line;
    std::string dummy;
    while(std::getline(fs, line)){
        std::stringstream ss(line);
        instruction_t ins;
        ss >> ins.reg0 >> ins.op0 >> ins.value0 >> dummy >> ins.reg1 >> ins.op1 >> ins.value1;
        ret.push_back(ins);
    } 

    return ret;
}

auto process(const std::vector<instruction_t>& ins)
{
    std::map<std::string,int> regs;
    for(auto& in : ins){
        regs[in.reg0] = 0;
        regs[in.reg1] = 0;
    }

    int max_reg_ever = INT_MIN;
    for(auto& in : ins){
        bool condition = false;
        if(in.op1 == ">"){
            condition = regs[in.reg1] > in.value1;
        }else if(in.op1 == "<"){
            condition = regs[in.reg1] < in.value1;
        }else if(in.op1 == ">="){
            condition = regs[in.reg1] >= in.value1;
        }else if(in.op1 == "<="){
            condition = regs[in.reg1] <= in.value1;
        }else if(in.op1 == "=="){
            condition = regs[in.reg1] == in.value1;
        }else if(in.op1 == "!="){
            condition = regs[in.reg1] != in.value1;
        }

        if(condition){
            if(in.op0 == "inc"){
                regs[in.reg0] += in.value0;
            }else{
                regs[in.reg0] -= in.value0;
            }

            for(auto& [_,value] : regs){
                max_reg_ever = std::max(max_reg_ever, value);
            }
        }
    }

    int max_reg = INT_MIN;
    for(auto& [_,value] : regs){
        max_reg = std::max(max_reg, value);
    }

    return std::make_pair(max_reg, max_reg_ever);
}

void main()
{
    auto test_values = load_input("../src/day08/example_input.txt");
    auto actual_values = load_input("../src/day08/input.txt");

    auto test_result = process(test_values);
    auto result = process(actual_values);

    std::cout << "part1: " << test_result.first << std::endl;
    std::cout << "part1: " << result.first << std::endl;

    std::cout << "part1: " << test_result.second << std::endl;
    std::cout << "part1: " << result.second << std::endl;
}