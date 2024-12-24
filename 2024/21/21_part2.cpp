#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

map<char, vector<int>> num_pad = {
    {'7', {0,0}}, {'8', {0,1}}, {'9', {0,2}},
    {'4', {1,0}}, {'5', {1,1}}, {'6', {1,2}},
    {'1', {2,0}}, {'2', {2,1}}, {'3', {2,2}},
                  {'0', {3,1}}, {'A', {3,2}}
};

map<char, vector<int>> dir_pad = {
                  {'^', {0,1}}, {'A', {0,2}},
    {'<', {1,0}}, {'v', {1,1}}, {'>', {1,2}}
};

map<char, map<char, string>> cache;

map<string, unsigned long long> get_dir_pad_instruction(map<string, unsigned long long> commands){
    map<string, unsigned long long> further_commands;
    char current_char = 'A';
    int h_dist, v_dist;
    char h_char, v_char;
    vector<int> from, to;
    for(auto button_press:commands){
        for(auto character:button_press.first){
                string further_instruction;
                from = dir_pad[current_char];
                to = dir_pad[character];

                h_dist = to[1] - from[1];
                v_dist = to[0] - from[0];

                if (h_dist > 0) h_char = '>';
                if (h_dist < 0) h_char = '<';
                if (v_dist > 0) v_char = 'v';
                if (v_dist < 0) v_char = '^';

                if(from[0] == 0 && to[1] == 0){
                    for(int i = 0; i < abs(v_dist); i++){
                        further_instruction += v_char;
                    }
                    for(int i = 0; i < abs(h_dist); i++){
                        further_instruction += h_char;
                    }
                } else if (to[0] == 0 && from[1] == 0){
                    for(int i = 0; i < abs(h_dist); i++){
                        further_instruction += h_char;
                    }
                    for(int i = 0; i < abs(v_dist); i++){
                        further_instruction += v_char;
                    }
                } else {
                    if (h_dist < 0){
                        for(int i = 0; i < abs(h_dist); i++) further_instruction += h_char;
                    }
                    if (v_dist < 0){
                        for(int i = 0; i < abs(v_dist); i++) further_instruction += v_char;
                    }
                    if (h_dist > 0){
                        for(int i = 0; i < abs(h_dist); i++) further_instruction += h_char;
                    }
                    if (v_dist > 0){
                        for(int i = 0; i < abs(v_dist); i++) further_instruction += v_char;
                    }
                }
                further_instruction += 'A';
                further_commands[further_instruction] += button_press.second;
                current_char = character;  
        }
    }
    return(further_commands);
}

map<string, unsigned long long> get_num_pad_instruction(string command){
    map<string, unsigned long long> instructions_counts;
    char current_char = 'A';
    int h_dist, v_dist;
    char h_char, v_char;
    vector<int> from, to;
    for(auto character:command){
        string instruction;
        from = num_pad[current_char];
        to = num_pad[character];
        current_char = character;

        h_dist = to[1] - from[1];
        v_dist = to[0] - from[0];

        if (h_dist > 0) h_char = '>';
        if (h_dist < 0) h_char = '<';
        if (v_dist > 0) v_char = 'v';
        if (v_dist < 0) v_char = '^';
    
        if(to[0] == 3 && from[1] == 0){
            for(int i = 0; i < abs(h_dist); i++){
                instruction += h_char;
            }
            for(int i = 0; i < abs(v_dist); i++){
                instruction += v_char;
            }
        } else if (to[1] == 0 && from[0] == 3){
            for(int i = 0; i < abs(v_dist); i++){
                instruction += v_char;
            }
            for(int i = 0; i < abs(h_dist); i++){
                instruction += h_char;
            }
        } else {
            if (h_dist < 0){
                for(int i = 0; i < abs(h_dist); i++) instruction += h_char;
            }
            if (v_dist > 0){
                for(int i = 0; i < abs(v_dist); i++) instruction += v_char;
            }
            if (h_dist > 0){
                for(int i = 0; i < abs(h_dist); i++) instruction += h_char;
            }
            if (v_dist < 0){
                for(int i = 0; i < abs(v_dist); i++) instruction += v_char;
            }
        }

        instruction += 'A';
        instructions_counts[instruction]++;
    }
    return(instructions_counts);
}

int main(){
    fstream input("input.txt");
    string entry;

    int n_robots_on_dir = 25; 
    unsigned long long sum_of_complexities = 0;
    while(getline(input, entry)){
        unsigned long long complexity = 0;
        map<string, unsigned long long> instruction = get_num_pad_instruction(entry);
        for (int i = 0; i < n_robots_on_dir; i++){
            instruction = get_dir_pad_instruction(instruction);
        }
        for(auto t:instruction){
            complexity += (unsigned long long) (t.first.size()) * t.second; 
        }
        entry.pop_back();
        unsigned long long num_value_entry = stoi(entry);
        sum_of_complexities += (num_value_entry * complexity);
    }

    cout << "The sum of complexities is: " << sum_of_complexities << endl;
}