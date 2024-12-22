#include <map>
#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <regex>
#include <fstream>

using namespace std;
using pfunc = function<int(int, map<int, long long>, int)>;

void adv(int x, map<int, long long> &literal_op, int &pos){
    literal_op[4] = literal_op[4]/(pow(2 , literal_op[x]));
    pos = pos+2;
}

void bxl(int x, map<int, long long> &literal_op, int &pos){
    literal_op[5] = literal_op[5] ^ literal_op[x];
    pos = pos+2;
}

void bst(int x, map<int, long long> &literal_op, int &pos){
    literal_op[5] = literal_op[x] % 8;
    pos = pos+2;
}

void jnz(int x, map<int, long long> &literal_op, int &pos){
    if(literal_op[4] != 0){
        pos = literal_op[x];
    } else{
        pos = pos+2;
    }
}

void bxc(int x, map<int, long long> &literal_op, int &pos){
    literal_op[5] = literal_op[5] ^ literal_op[6];
    pos = pos+2;
}

void out(int x, map<int, long long> &literal_op, int &pos, string &potential_input){
    potential_input += to_string(literal_op[x] % 8);
    pos = pos+2;
}

void bdv(int x, map<int, long long> &literal_op, int &pos){
    literal_op[5] = literal_op[4]/(pow(2 , literal_op[x]));
    pos = pos+2;
}

void cdv(int x, map<int, long long> &literal_op, int &pos){
    literal_op[6] = literal_op[4]/(pow(2 , literal_op[x]));
    pos = pos+2;
}

string run_commands(long long A_value, string commands, map<int, long long> literal_op){
    literal_op[4] = A_value;
    int pos = 0;
    string potential_output;
    int x;
    while(pos < commands.size()){;
            x = commands[pos+1] - '0';        
            //Map of functions would be better; I don't have that figured out yet
            if(commands[pos] == '0') adv(x, literal_op, pos); else
            if(commands[pos] == '1') bxl(x, literal_op, pos); else
            if(commands[pos] == '2') bst(x, literal_op, pos); else
            if(commands[pos] == '3') jnz(x, literal_op, pos); else
            if(commands[pos] == '4') bxc(x, literal_op, pos); else
            if(commands[pos] == '5') out(x, literal_op, pos, potential_output); else
            if(commands[pos] == '6') bdv(x, literal_op, pos); else
            if(commands[pos] == '7') cdv(x, literal_op, pos); 
    }
    return(potential_output);
}

bool find_A_value(long long A_value, string commands, map<int, long long> &literal_op){
    /* Couldn't come up with this myself;
    Only follow the A_path of which the output's last digits
    match the input last digits */
    if(run_commands(A_value, commands, literal_op) == commands){
        cout << "The A-value is: " << A_value << endl ;
        return(true);
    }
    A_value = A_value << 3;
    for (int i = 0; i < 8; i++) {
        string output = run_commands(A_value, commands, literal_op);
        //cout << "program=" << commands << "  output=" << output << endl;
        bool same = true;
        for (int i = 0; i < output.size(); i++) {
            same = same && output[i] == commands[commands.size() - output.size() + i];
        }
        if (same && find_A_value(A_value, commands, literal_op)) return true;
        A_value++;
    }
    return false;
}


int main(){
    int A = 0;
    int B = 0;
    int C = 0;

    ifstream inFile("input.txt");
    string entry;
    string commands;
    string raw_commands;

    regex input_pattern(R"(^(.*?): (.*))");

    while (getline(inFile, entry))
    {
        smatch m;
        std::regex_search(entry, m, input_pattern);
        if (m[1] == "Register A") A = stoi(m[2]);
        if (m[1] == "Register B") B = stoi(m[2]);
        if (m[1] == "Register C") C = stoi(m[2]);
        if (m[1] == "Program") raw_commands = m[2];
        for(auto character:raw_commands){
            if(character != ','){
                commands += character;
            }
        }
    }


    map<int, long long> l_op = {{0,0}, {1,1}, {2,2}, {3,3}, 
                                {4,0}, {5,B}, {6,C}, {7,7}};


    // A is corrupt
    find_A_value(0, commands, l_op);
}