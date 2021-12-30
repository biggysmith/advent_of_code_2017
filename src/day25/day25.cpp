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
#include "timer.hpp"

struct settings_t{
    int write;
    int move;
    int cont;
};

struct state_t{
    int state;
    settings_t settings[2];
};

struct blueprint_t{
    char start_state;
    int steps;
    std::vector<state_t> states;
};

blueprint_t load_input(const std::string& file){
    blueprint_t ret;
    std::ifstream fs(file);
    std::string line;

    std::getline(fs, line);
    ret.start_state = line[line.size()-2]-'A';

    std::getline(fs, line);
    std::stringstream ss(line.substr(line.find("after")+6));
    ss >> ret.steps;

    while(std::getline(fs, line)){
        if(line.empty()){
            ret.states.push_back(state_t());
            continue;
        }

        auto& state = ret.states.back();
        state.state = line[line.size()-2]-'A';

        std::getline(fs, line);
        std::getline(fs, line);
        state.settings[0].write = line[line.size()-2]-'0';

        std::getline(fs, line);
        state.settings[0].move = line[27] == 'l' ? -1 : 1;

        std::getline(fs, line);
        state.settings[0].cont = line[26]-'A';

        std::getline(fs, line);
        std::getline(fs, line);
        state.settings[1].write = line[line.size()-2]-'0';

        std::getline(fs, line);
        state.settings[1].move = line[27] == 'l' ? -1 : 1;

        std::getline(fs, line);
        state.settings[1].cont = line[26]-'A';
    }

    return ret;
}

auto part1(const blueprint_t& blueprint)
{
    std::vector<int> tape(blueprint.steps, 0);
    int pos = (int)tape.size()/2;
    int curr_state = blueprint.start_state;

    for(int i=0; i<blueprint.steps; ++i){
        auto& state = blueprint.states[curr_state];
        int one = tape[pos] != 0;
        tape[pos] = state.settings[one].write;
        pos += state.settings[one].move;
        curr_state = state.settings[one].cont;
    }

    return std::count(tape.begin(), tape.end(), 1);
}

void main()
{
    auto test_values = load_input("../src/day25/example_input.txt");
    auto actual_values = load_input("../src/day25/input.txt");

    std::cout << "part1: " << part1(test_values) << std::endl;
    std::cout << "part1: " << part1(actual_values) << std::endl;
}
