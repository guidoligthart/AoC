#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <regex>
#include <math.h>

using namespace std;

map<string, bool> wires;

struct equation{
    public:
        string LHS;
        string fun;
        string RHS;
        string output;
};

void print_wires(){
    for(auto wire:wires){
        cout << wire.first << ": " << wire.second << endl;
    }
}

void print_connections(vector<equation> x){
    for(auto eq:x){
        cout << eq.LHS << " " << eq.fun << " " << eq.RHS << " -> " << eq.output << endl;
    }
}

bool wire_known(string &wire){
    return(wires.count(wire) != 0);
}

void connect_wires(vector<equation> eqs){
    while(eqs.size() != 0){
        for(int i = 0; i < eqs.size(); i++){
                if(wire_known(eqs[i].LHS) && wire_known(eqs[i].RHS) && !wire_known(eqs[i].output)){
                if(eqs[i].fun == "AND") wires[eqs[i].output] = wires[eqs[i].LHS] && wires[eqs[i].RHS];
                if(eqs[i].fun == "OR")  wires[eqs[i].output] = wires[eqs[i].LHS] || wires[eqs[i].RHS];
                if(eqs[i].fun == "XOR") wires[eqs[i].output] = wires[eqs[i].LHS] != wires[eqs[i].RHS];
                eqs.erase(eqs.begin()+i);
                i--; // because of erasing the equation: counteract the increment
            }
        }
    }
}

unsigned long long binary_to_decimal(string n){
    unsigned long long num_dec = 0;
    for(int i = 0; i < n.size(); i++){
        if(n[i] == '1'){
            num_dec += pow(2, i);
        }
    }
    return num_dec;
}

int main(){
    fstream input("input.txt");
    string entry;

    regex start_wire_pattern(R"(^(.{3}): ([0-1])$)");
    regex wire_con_patterns(R"(^(.{3}) ([A-Z]+) (.{3}) -> (.{3}))");

    vector<equation> connections;
    while(getline(input, entry)){
        smatch m;
        if(entry.find(':') != string::npos){
            //parse starting wires
            regex_search(entry, m, start_wire_pattern);
            wires[m[1]] = stoi(m[2]);
        } else if (entry.size() != 0){
            //parse connections
            equation connection;
            regex_search(entry, m, wire_con_patterns);
            connection.LHS = m[1];
            connection.fun = m[2];
            connection.RHS = m[3];
            connection.output = m[4];
            connections.push_back(connection);
        }
    }
    
    connect_wires(connections);

    string z_wires_binary_output = "";
    for(auto wire:wires){
        if(wire.first[0] == 'z'){
            z_wires_binary_output += to_string(wire.second);
        }
    }

    cout << z_wires_binary_output << endl;
    cout << "The value of combined z-wires is: " << binary_to_decimal(z_wires_binary_output);
}