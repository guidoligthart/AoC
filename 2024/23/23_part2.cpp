#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>

using namespace std;

map<string, vector<string>> pc_pairs;

void trace_all_steps(string x, vector<string> previous_pcs, vector<string>& result){
    vector<string> further_pcs;
    vector<string> previous_pcs2 = previous_pcs;
    previous_pcs2.push_back(x);
    bool search_further;
    if ((previous_pcs.size() + further_pcs.size()) < result.size()){
        return;
    }
    for(auto y:pc_pairs[x]){
        further_pcs = pc_pairs[y];
        search_further = true;
        for(auto prev_pc:previous_pcs2){
            search_further &= find(further_pcs.begin(), further_pcs.end(), prev_pc) != further_pcs.end();
        }
        if(search_further){
            trace_all_steps(y, previous_pcs2, result);
        } 
    }
    if (previous_pcs2.size() > result.size()){
        result = previous_pcs2;
    }

}

vector<string> find_pairs(vector<string> x, vector<string> y){
   vector<string> return_vec;
    for (int i = 0; i < x.size(); i++){
        pc_pairs[x[i]].push_back(y[i]);
        pc_pairs[y[i]].push_back(x[i]);
    }

    for(auto pc_pair:pc_pairs){
        auto it = unique(pc_pair.second.begin(), pc_pair.second.end());
        pc_pair.second.resize(distance(pc_pair.second.begin(), it));
    }

    int max_result = 3;

    
    for(auto pc_pair:pc_pairs){
        vector<string> result;
        trace_all_steps(pc_pair.first, {}, result);
        if(result.size() > max_result){
            max_result = result.size();
            return_vec = result;
        }
    }

    sort(return_vec.begin(), return_vec.end());
    return(return_vec);
}


int main(){
    fstream input("input.txt");
    string entry;
    vector<string> pair_x, pair_y;
    regex pattern(R"(([a-z]+)-([a-z]+))");
    smatch m;
    while(getline(input, entry)){
        regex_search(entry, m, pattern);
        pair_x.push_back(m[1]);
        pair_y.push_back(m[2]);
    }

    vector<string> biggest_lan = find_pairs(pair_x, pair_y);

    for(auto pc:biggest_lan){
        cout << pc << ",";
    }
}