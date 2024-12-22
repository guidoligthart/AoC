#include <fstream>
#include <vector>
#include <regex>
#include <iostream>
#include <string>
#include <map>

using namespace std;

void check_if_pattern_is_possible(string asked_pattern, vector<string> &possible_patterns, long long &possible_patterns_counter,
                                  map<string, long long> &designs){
    if(asked_pattern == ""){
        possible_patterns_counter++;
        return;
    }
    for(auto pattern:possible_patterns){
        int pattern_size = pattern.size();
        bool pattern_fits = true;
        for(int i = 0; i < pattern_size; i++){
            pattern_fits = pattern_fits && pattern[i] == asked_pattern[i];
        }
        if(pattern_fits){
            string asked_pattern2(asked_pattern.begin() + pattern_size, asked_pattern.end());
            
            if(designs.count(asked_pattern2)){
                possible_patterns_counter += designs[asked_pattern2];
            } else{
                long long count_before = possible_patterns_counter;
                check_if_pattern_is_possible(asked_pattern2, possible_patterns, possible_patterns_counter, designs);
                designs[asked_pattern2] = possible_patterns_counter - count_before;
            }
        }
    }
    return;
}


int main(){
    //parse the input
    ifstream Infile("input.txt");
    string entry;

    vector<string> possible_patterns;
    vector<string> asked_patterns;

    regex pattern(R"(.*?([a-z]+))");
    while(getline(Infile, entry)){
        if(entry.find(", ") != entry.npos){
            string s = entry.c_str();
            smatch m;
            while(std::regex_search(s, m, pattern)) {
                possible_patterns.push_back(m[1]);
                s = m.suffix();
            }
        } else if(entry != ""){
            asked_patterns.push_back(entry);
        }
    }

    long long possible_pattern_counter = 0;
    map<string, long long> memory;

     for(auto pattern:asked_patterns){
        long long counter = 0;
        check_if_pattern_is_possible(pattern, possible_patterns, counter, memory);
        possible_pattern_counter += counter;
    }

    cout << "The sum of possible combinations is: " << possible_pattern_counter;
}