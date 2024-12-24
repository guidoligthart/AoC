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

string get_dir_pad_instruction(string command){
    string instruction;
    char current_char = 'A';
    int h_dist, v_dist;
    char h_char, v_char;
    vector<int> from, to;
    for(auto character:command){
        from = dir_pad[current_char];
        to = dir_pad[character];
        current_char = character;

        h_dist = to[1] - from[1];
        v_dist = to[0] - from[0];

        if (h_dist > 0) h_char = '>';
        if (h_dist < 0) h_char = '<';
        if (v_dist > 0) v_char = 'v';
        if (v_dist < 0) v_char = '^';
    
        if(from[0] == 0 && to[1] == 0){
            for(int i = 0; i < abs(v_dist); i++){
                instruction += v_char;
            }
            for(int i = 0; i < abs(h_dist); i++){
                instruction += h_char;
            }
        } else if (to[0] == 0 && from[1] == 0){
            for(int i = 0; i < abs(h_dist); i++){
                instruction += h_char;
            }
            for(int i = 0; i < abs(v_dist); i++){
                instruction += v_char;
            }
        } else {
            if (h_dist < 0){
                for(int i = 0; i < abs(h_dist); i++) instruction += h_char;
            }
            if (v_dist < 0){
                for(int i = 0; i < abs(v_dist); i++) instruction += v_char;
            }
            if (h_dist > 0){
                for(int i = 0; i < abs(h_dist); i++) instruction += h_char;
            }
            if (v_dist > 0){
                for(int i = 0; i < abs(v_dist); i++) instruction += v_char;
            }
        }
        instruction += 'A';
    }
    return(instruction);
}

string get_num_pad_instruction(string command){
    string instruction;
    char current_char = 'A';
    int h_dist, v_dist;
    char h_char, v_char;
    vector<int> from, to;
    for(auto character:command){
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
    }
    return(instruction);
}

int main(){
    fstream input("input.txt");
    string entry;

    int n_robots = 4;
    int sum_of_complexities = 0;
    while(getline(input, entry)){
        string instruction = get_num_pad_instruction(entry);
        for (int i = 2; i < n_robots; i++){
            instruction = get_dir_pad_instruction(instruction);
        }
        entry.pop_back();
        int num_value_entry = stoi(entry);
        sum_of_complexities += (num_value_entry * instruction.size());
    }

    cout << "The sum of complexities is: " << sum_of_complexities << endl;
}