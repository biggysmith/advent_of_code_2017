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

struct instruction_t{
    std::string op;
    std::string x;
    std::string y;
    bool is_y_reg;
};

std::vector<instruction_t> load_input(const std::string& file){
    std::vector<instruction_t> ret;
    std::ifstream fs(file);
    std::string line;
    std::string dummy;
    while(std::getline(fs, line)){
        std::stringstream ss(line);
        instruction_t ins;
        ss >> ins.op >> ins.x >> ins.y;
        ins.is_y_reg = isalpha(ins.y[0]);
        ret.push_back(ins);
    }    
    return ret;
}

struct program_t
{
    program_t(const std::vector<instruction_t>& in,int64_t id) : instructions(in) {
        regs["p"] = id;
        regs["sent"] = 0;
    }

    auto run(std::queue<int64_t>& rcv, std::queue<int64_t>& snd)
    {
        /*auto gety = [&](const instruction_t& ins){
            return ins.is_y_reg ? regs[ins.y] : std::stoll(ins.y);
        };*/

        auto get = [&](const std::string& s){
            return (s[0]>='a' && s[0]<='z') ? regs[s] : std::stoll(s);
        };

        if(i >= instructions.size()){
            return false;
        }

        auto& ins = instructions[i];

        if(ins.op == "snd"){
            snd.push(get(ins.x));
            //std::cout << ins.op << " " << ins.x << std::endl;
            regs["sent"]++;
        }else if(ins.op == "set"){
            regs[ins.x] = get(ins.y);
            //std::cout << ins.op << " " << ins.x << " " << ins.y << std::endl;
        }else if(ins.op == "add"){
            regs[ins.x] += get(ins.y);
            //std::cout << ins.op << " " << ins.x << " " << ins.y << std::endl;
        }else if(ins.op == "mul"){
            regs[ins.x] *= get(ins.y);
            //std::cout << ins.op << " " << ins.x << " " << ins.y << std::endl;
        }else if(ins.op == "mod"){
            regs[ins.x] %= get(ins.y);
            //std::cout << ins.op << " " << ins.x << " " << ins.y << std::endl;
        }else if(ins.op == "rcv"){
            //std::cout << ins.op << " " << ins.x << std::endl;
            if(!rcv.empty()){
                regs[ins.x] = rcv.front();
                rcv.pop();
            }else{
                return false;
            }
        }else if(ins.op == "jgz"){
            //std::cout << ins.op << " " << ins.x << " " << ins.y << std::endl;
            if(get(ins.x) > 0){
                i += get(ins.y) - 1;
            }
        }

        i++;
        return true;
    }

    bool waiting() const {
        return regs.at("waiting") == 1;
    }

    size_t messages_sent() const {
        return regs.at("sent");
    }

    const std::vector<instruction_t>& instructions;
    std::map<std::string,int64_t> regs;
    size_t i = 0;
};

int64_t part1(const std::vector<instruction_t>& instructions)
{
    program_t prog(instructions,0);
    //return prog.run(std::vector<int64_t>()).back();
    return 0;
}

int64_t part2(const std::vector<instruction_t>& instructions)
{
    std::queue<int64_t> rcv;
    std::queue<int64_t> snd;

    program_t prog0(instructions,0);
    program_t prog1(instructions,1);

    while(1){
        bool a = prog0.run(rcv, snd);
        bool b = prog1.run(snd, rcv);
        if(!a && !b) {
            break;
        }
    }

    return prog1.messages_sent();
}

void main()
{
    auto test_values = load_input("../src/day18/example_input.txt");
    auto actual_values = load_input("../src/day18/input.txt");

    //std::cout << "part1: " << part1(test_values) << std::endl;
    //std::cout << "part1: " << part1(actual_values) << std::endl;

    auto test_values0 = load_input("../src/day18/example_input0.txt");

    std::cout << "part2: " << part2(test_values0) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;

    /*std::cout << "part2: " << part2(test_values) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;*/
}
