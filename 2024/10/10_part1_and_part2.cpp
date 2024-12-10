#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

vector<vector<int>> lava_map;
int total_hiking_score_p1 = 0;
int total_hiking_score_p2 = 0;
int total_trail_heads = 0;

bool check_in_bounds(int i, int j){
    return i >= 0 & i < lava_map.size() &
           j >= 0 & j < lava_map[i].size();
}

void check_valid_trail(int i, int j, vector<int>& nine_pos){
    int current_number = lava_map[i][j];
    if(current_number == 9){
        nine_pos.push_back(j*lava_map[i].size()+i);
        return;
    }
    
    int north_i = i -1;
    int south_i = i +1;

    int west_j = j -1;
    int east_j = j +1;

    if(check_in_bounds(north_i, j)){
        if(lava_map[north_i][j] == (current_number + 1)) check_valid_trail(north_i, j, nine_pos);
    }
    
    if(check_in_bounds(south_i, j)){
        if(lava_map[south_i][j] == (current_number + 1)) check_valid_trail(south_i, j, nine_pos);
    }

    if(check_in_bounds(west_j, j)){
        if(lava_map[i][west_j] == (current_number + 1)) check_valid_trail(i, west_j, nine_pos);
    }

    if(check_in_bounds(east_j, j)){
        if(lava_map[i][east_j] == (current_number + 1)) check_valid_trail(i, east_j, nine_pos);
    }

    return;
    
}

int main(){
    //parse the map
    ifstream inFile(R"(input.txt)");
    string entry;
    while (getline(inFile, entry))
    {
        vector<int> map_row;
        string s = entry.c_str();
        for (auto c:s)
        {
            map_row.push_back(c - '0');    
        }
        lava_map.push_back(map_row);
    }

    for(int i = 0; i < lava_map.size(); i++){
        for(int j = 0; j < lava_map[i].size(); j++){
            vector<int> nine_pos;
            if (lava_map[i][j] == 0)
            {
                total_trail_heads++;
                check_valid_trail(i, j, nine_pos);
                sort(nine_pos.begin(), nine_pos.end());
                total_hiking_score_p2 += nine_pos.size();
                total_hiking_score_p1 += unique(nine_pos.begin(), nine_pos.end()) - nine_pos.begin();
            }
        }
    }

    cout << "The total amount of trailheads is: " << total_trail_heads << endl <<
     "The total hiking score according to part 1 is: " << total_hiking_score_p1 << endl <<
     "The total hiking score according to part 2 is: " << total_hiking_score_p2; 
}
