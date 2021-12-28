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

    void run(std::queue<int64_t>& rcv, std::queue<int64_t>& snd)
    {
        auto get = [&](const std::string& s){
            return (s[0]>='a' && s[0]<='z') ? regs[s] : std::stoll(s);
        };

        while(ipos < instructions.size())
        {
            auto& ins = instructions[ipos];

            if(ins.op == "snd"){
                snd.push(get(ins.x));
                regs["sent"]++;
            }else if(ins.op == "set"){
                regs[ins.x] = get(ins.y);
            }else if(ins.op == "add"){
                regs[ins.x] += get(ins.y);
            }else if(ins.op == "mul"){
                regs[ins.x] *= get(ins.y);
            }else if(ins.op == "mod"){
                regs[ins.x] %= get(ins.y);
            }else if(ins.op == "rcv"){
                if(!rcv.empty()){
                    regs[ins.x] = rcv.front();
                    rcv.pop();
                }else{
                    return;
                }
            }else if(ins.op == "jgz"){
                if(get(ins.x) > 0){
                    ipos += get(ins.y) - 1;
                }
            }

            ipos++;
        }
    }

    size_t messages_sent() const {
        return regs.at("sent");
    }

    const std::vector<instruction_t>& instructions;
    std::map<std::string,int64_t> regs;
    size_t ipos = 0;
};

int64_t part1(const std::vector<instruction_t>& instructions)
{
    std::queue<int64_t> rcv;
    std::queue<int64_t> snd;

    program_t prog(instructions,0);
    prog.run(rcv,snd);
    return snd.back();
}

int64_t part2(const std::vector<instruction_t>& instructions)
{
    std::queue<int64_t> rcv;
    std::queue<int64_t> snd;

    program_t prog0(instructions,0);
    program_t prog1(instructions,1);

    do{
       prog0.run(rcv, snd);
       prog1.run(snd, rcv);
    } while(!rcv.empty() || !snd.empty());

    return prog1.messages_sent();
}

void main()
{
    auto test_values = load_input("../src/day18/example_input.txt");
    auto actual_values = load_input("../src/day18/input.txt");

    std::cout << "part1: " << part1(test_values) << std::endl;
    std::cout << "part1: " << part1(actual_values) << std::endl;

    auto test_values0 = load_input("../src/day18/example_input0.txt");

    std::cout << "part2: " << part2(test_values0) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}
