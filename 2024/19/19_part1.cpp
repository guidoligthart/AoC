#include <fstream>
#include <vector>
#include <regex>
#include <iostream>
#include <string>

using namespace std;

bool check_if_pattern_is_possible(string asked_pattern, vector<string> &possible_patterns){
    if(asked_pattern == ""){
        return(true);
    }
    for(auto pattern:possible_patterns){
        int pattern_size = pattern.size();
        bool pattern_fits = true;
        for(int i = 0; i < pattern_size; i++){
            pattern_fits = pattern_fits && pattern[i] == asked_pattern[i];
        }
        if(pattern_fits){
            string asked_pattern2(asked_pattern.begin() + pattern_size, asked_pattern.end());
            if(check_if_pattern_is_possible(asked_pattern2, possible_patterns)){
                return(true);
            }
        }
    }
    return(false);
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

    int possible_pattern_counter = 0;
    for(auto pattern:asked_patterns){
        if(check_if_pattern_is_possible(pattern, possible_patterns)){
            possible_pattern_counter++;
        }
    }
    cout << "The amount of possible asked patterns is: " << possible_pattern_counter;
}