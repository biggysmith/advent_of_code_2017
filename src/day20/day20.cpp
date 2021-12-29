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

struct vec3_t{
    int64_t x,y,z;
};

bool operator==(const vec3_t& a,const vec3_t& b){
    return a.x==b.x && a.y==b.y && a.z==b.z;
}

vec3_t& operator+=(vec3_t& a,const vec3_t& b){
    a.x+=b.x; a.y+=b.y; a.z+=b.z;
    return a;
}

int64_t dot(const vec3_t& a,const vec3_t& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

struct particle_t{
    vec3_t pos;
    vec3_t vel;
    vec3_t acc;

    void update(){
        vel += acc;
        pos += vel;
    }
};

int64_t manhatten(const vec3_t& a){
    return std::abs(a.x) + std::abs(a.y) + std::abs(a.z);
}

std::vector<particle_t> load_input(const std::string& file){
    std::vector<particle_t> ret;
    std::ifstream fs(file);
    std::string line;
    std::string dummy;
    char comma;
    while(std::getline(fs, line)){
        particle_t particle;
        std::stringstream ss(line);

        std::string line2;
        std::getline(ss, line2, '<');
        ss >> particle.pos.x >> comma >> particle.pos.y >> comma >> particle.pos.z;

        std::getline(ss, line2, '<');
        ss >> particle.vel.x >> comma >> particle.vel.y >> comma >> particle.vel.z;

        std::getline(ss, line2, '<');
        ss >> particle.acc.x >> comma >> particle.acc.y >> comma >> particle.acc.z;

        ret.push_back(particle);
    }   

    return ret;
}

auto part1(const std::vector<particle_t>& particles)
{
    auto it = std::min_element(particles.begin(), particles.end(), [](auto& a,auto& b){
        return std::make_tuple(manhatten(a.acc),manhatten(a.vel),manhatten(a.pos)) < std::make_tuple(manhatten(b.acc),manhatten(b.vel),manhatten(b.pos));
    });
    return std::distance(particles.begin(), it);
}

auto part2(const std::vector<particle_t>& in)
{
    auto particles = in;

    bool all_moving_apart = false;

    while(!all_moving_apart)
    {
        std::set<size_t> colliders;
        for(size_t i=0; i<particles.size(); ++i){
            for(size_t j=i+1; j<particles.size(); ++j){

                if(particles[i].pos == particles[j].pos){
                    colliders.insert(i);
                    colliders.insert(j);
                }

            }
        }

        size_t v = 0;
        particles.erase(std::remove_if(particles.begin(), particles.end(), [&](auto&){
            return colliders.count(v++);
        }), particles.end());

        for(auto& particle : particles){
            particle.update();
        }

        all_moving_apart = std::all_of(particles.begin(), particles.end(), [](auto& p){
            return dot(p.vel,p.pos) > 0;
        });
    }

    return particles.size();
}

void main()
{
    auto test_values = load_input("../src/day20/example_input.txt");
    auto actual_values = load_input("../src/day20/input.txt");

    std::cout << "part1: " << part1(test_values) << std::endl;
    std::cout << "part1: " << part1(actual_values) << std::endl;

    auto test_values0 = load_input("../src/day20/example_input0.txt");

    std::cout << "part2: " << part2(test_values0) << std::endl;
    std::cout << "part2: " << part2(actual_values) << std::endl;
}
