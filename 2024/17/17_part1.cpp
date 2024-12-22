#include <map>
#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <regex>
#include <fstream>

using namespace std;
using pfunc = function<int(int, map<int, int>, int)>;

void adv(int x, map<int, int> &literal_op, int &pos){
    //cout << literal_op [4] << "/" << pow(2 , literal_op[x]) << " = ";
    literal_op[4] = literal_op[4]/(pow(2 , literal_op[x]));
    pos = pos+2;
    //cout << literal_op[4] << endl;
}

void bxl(int x, map<int, int> &literal_op, int &pos){
    literal_op[5] = literal_op[5] ^ literal_op[x];
    pos = pos+2;
}

void bst(int x, map<int, int> &literal_op, int &pos){
    literal_op[5] = literal_op[x] % 8;
    pos = pos+2;
}

void jnz(int x, map<int, int> &literal_op, int &pos){
    if(literal_op[4] != 0){
        pos = literal_op[x];
    } else{
        pos = pos+2;
    }
}

void bxc(int x, map<int, int> &literal_op, int &pos){
    literal_op[5] = literal_op[5] ^ literal_op[6];
    pos = pos+2;
}

void out(int x, map<int, int> &literal_op, int &pos){
    //cout << literal_op[x] << endl;
    cout << literal_op[x] % 8 << ",";
    pos = pos+2;
}

void bdv(int x, map<int, int> &literal_op, int &pos){
    literal_op[5] = literal_op[4]/(pow(2 , literal_op[x]));
    pos = pos+2;
}

void cdv(int x, map<int, int> &literal_op, int &pos){
    literal_op[6] = literal_op[4]/(pow(2 , literal_op[x]));
    pos = pos+2;
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

    map<int, int> l_op = {{0,0}, {1,1}, {2,2}, {3,3}, 
                          {4,A}, {5,B}, {6,C}, {7,7}};

    int pos = 0;
    int x;
    while(pos < commands.size()){;
        x = commands[pos+1] - '0';
        //Map of functions would be better; I don't have that figured out yet
        if(commands[pos] == '0') adv(x, l_op, pos); else
        if(commands[pos] == '1') bxl(x, l_op, pos); else
        if(commands[pos] == '2') bst(x, l_op, pos); else
        if(commands[pos] == '3') jnz(x, l_op, pos); else
        if(commands[pos] == '4') bxc(x, l_op, pos); else
        if(commands[pos] == '5') out(x, l_op, pos); else
        if(commands[pos] == '6') bdv(x, l_op, pos); else
        if(commands[pos] == '7') cdv(x, l_op, pos); 
    }
}