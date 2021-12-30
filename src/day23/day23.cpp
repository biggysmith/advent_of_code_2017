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
    program_t(const std::vector<instruction_t>& in, bool debug) : instructions(in) {
        for(char c='a'; c<='h'; ++c){
            regs[std::string(1,c)] = 0;
        }
        regs["a"] = debug ? 0 : 1;
        regs["mul"] = 0;
    }

    void run()
    {
        if(regs["a"] == 0)
        {
            auto get = [&](const std::string& s){
                return (s[0]>='a' && s[0]<='z') ? regs[s] : std::stoll(s);
            };

            while(ipos < instructions.size())
            {
                auto& ins = instructions[ipos];

                if(ins.op == "set"){
                    regs[ins.x] = get(ins.y);
                }else if(ins.op == "sub"){
                    regs[ins.x] -= get(ins.y);
                }else if(ins.op == "mul"){
                    regs[ins.x] *= get(ins.y);
                    regs["mul"]++;
                }else if(ins.op == "jnz"){
                    if(get(ins.x) != 0){
                        ipos += get(ins.y) - 1;
                    }
                }

                ipos++;
            }
        }
        else
        {

        #if 0
            // straight convert to C code
            int a = (int)regs["a"];
            int b = 0;
            int c = 0;
            int d = 0;
            int e = 0;
            int f = 0;
            int g = 0;
            int h = 0;

            b = 99; // aa
            c = b;  // bb
            if(a) { goto next1; } // cc
            if(1) { goto next2; } 
    next1:  b *= 100; // dd                                         
            regs["mul"]++;   
            b -= -100000;   //ee 
            c = b;          //ff
            c -= -17000;    // hh
    next2:  f = 1;  // jj
    next7:  d = 2;  // kk
    next4:  e = 2;  //mm
    next3:  g = d;
            g *= e;                                             
            regs["mul"]++;         
            g -= b;                
            if(g) { goto next0; }  
            f = 0;                  // oo
    next0:  e -= -1; // nn
            g = e;                  // mm
            g -= b; // hh           // mm
            if(g) { goto next3; }   // mm
            d -= -1; 
            g = d;                  // ll
            g -= b;                 // ll
            if(g) { goto next4; }   // ll
            if(f) { goto next5; }   // pp
            h -= -1;                // pp
    next5:  g = b;                  // ii
            g -= c;                 // ii
            if(g) { goto next6; }   // ii
            if(1) { goto next8; }
    next6:  b -= -17;               // qq
            if(1) { goto next7; }
    next8:  ;
        #endif

            // better C code
            int a = (int)regs["a"];
            int b = 0;
            int c = 0;
            int d = 0;
            int e = 0;
            int f = 0;
            int g = 0;
            int h = 0;

            b = 99; // aa
            c = b;  // bb

            if(a){ // cc
                b *= 100;       // dd
                b -= -100000;   // ee
                c = b;          // ff
                c -= -17000;    // hh
            }

            while(b <= c){ // ii
                f = 1; // jj
                d = 2; // kk
                while(d < b){ // ll
                    // slow bit that emulates missing % instruction
                    /*e = 2; // mm
                    while(e < b){ // nn
                        
                        if(d*e == b){ // mm
                            f = 0; // oo
                        }
                        e++; // nn
                    }*/

                    // replace with % saves the day
                    if(b % d == 0){
                        f = 0;
                    }
                    d++; // ii
                }
                        
                if(f == 0){ // pp
                    h++; // pp
                }

                b += 17; // qq
            }

            regs["h"] = h;
        }


    }

    int64_t muls_executed() const{
        return regs.at("mul");
    }

    int64_t h_value() const{
        return regs.at("h");
    }

    const std::vector<instruction_t>& instructions;
    std::map<std::string,int64_t> regs;
    size_t ipos = 0;
};

void transpile(const std::vector<instruction_t>& instructions){
    auto get = [&](const std::string& s){
        return (s[0]>='a' && s[0]<='z') ? ("regs[\"" + s + "\"]") : s;
    };

    for(auto& ins : instructions){
        if(ins.op == "set"){
            std::cout << "regs[\"" << ins.x << "\"] = " << get(ins.y) << ";" << std::endl;
        }else if(ins.op == "sub"){
            std::cout << "regs[\"" << ins.x << "\"] -= " << get(ins.y) << ";" << std::endl;
        }else if(ins.op == "mul"){
            std::cout << "regs[\"" << ins.x << "\"] *= " << get(ins.y) << ";" << std::endl;
        }else if(ins.op == "jnz"){
            std::cout << "if(" << get(ins.x) << " != 0) { ipos += " << get(ins.y) << "; }" << std::endl;
        }
    }
}

auto part1(const std::vector<instruction_t>& instructions)
{
    program_t prog(instructions, true);
    prog.run();

    return prog.muls_executed();
}

auto part2(const std::vector<instruction_t>& instructions)
{
    program_t prog(instructions, false);
    prog.run();

    return prog.h_value();
}

void main()
{
    auto actual_values = load_input("../src/day23/input.txt");

    std::cout << "part1: " << part1(actual_values) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}
