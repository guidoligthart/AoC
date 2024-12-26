#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>

using namespace std;

vector<vector<string>> find_pairs(vector<string> x, vector<string> y){
   vector<vector<string>> pairs, return_vec;
   map<vector<string>, bool> pair_cache; 
    for (int i = 0; i < x.size(); i++){
        for (int j = 0; j < x.size(); j++){
            if(x[i] == y[j]){
                pairs.push_back({x[j], x[i], y[i]});
            }
        }
    }

    for(auto pair:pairs){
        for (int i = 0; i < x.size(); i++){
            if((x[i] == pair[2] && y[i] == pair[0]) || y[i] == pair[2] && x[i] == pair[0]){
                sort(pair.begin(), pair.end());
                if (!pair_cache[pair]){
                    pair_cache[pair] = true;
                    return_vec.push_back(pair);
                }
            }
        }
    }
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

    vector<vector<string>> all_pairs = find_pairs(pair_x, pair_y);
    int pair_with_t_counter = 0;

    for(auto pair:all_pairs){
        for(auto pc:pair){
            cout << pc << " ";
            if(pc[0] == 't'){
                pair_with_t_counter++;
                //cout << " hit! ";
                goto continue2;
            }
        }
        continue2:;
         cout<< endl;
    }

    cout << pair_with_t_counter;
}