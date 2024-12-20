#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

bool check_in_bounds(int i, int j, vector<vector<char>>& map){
    return i >= 0 & i < map.size() &
           j >= 0 & j < map[i].size();
}

void get_area_and_perimiter(int i, int j, 
                            int& area, int& perimeter,
                            vector<vector<char>> map,
                            vector<vector<bool>>& visited){
    if(visited[i][j]){
        return;
    }
    area++;
    visited[i][j] = true;
    char current_char = map[i][j];
    
    int north_i = i -1;
    int south_i = i +1;

    int west_j = j -1;
    int east_j = j +1;

    if(check_in_bounds(north_i, j, map)){
        if(map[north_i][j] == current_char){
            get_area_and_perimiter(north_i, j, area, perimeter, map, visited);
        } else { 
            perimeter++;
        }
    } else {
        perimeter++;
    }



    if(check_in_bounds(south_i, j, map)){
        if(map[south_i][j] == current_char){
            get_area_and_perimiter(south_i, j, area, perimeter, map, visited);
        } else { 
            perimeter++;
        }
    } else {
        perimeter++;
    }

    if(check_in_bounds(i, west_j, map)){
        if(map[i][west_j] == current_char){
            get_area_and_perimiter(i, west_j, area, perimeter, map, visited);
        } else { 
            perimeter++;
        }
    } else {
        perimeter++;
    }

    if(check_in_bounds(i, east_j, map)){
        if(map[i][east_j] == current_char){
            get_area_and_perimiter(i, east_j, area, perimeter, map, visited);
        } else { 
            perimeter++;
        }
    } else {
        perimeter++;
    }
}


int main(){
    //parse the map
    vector<vector<char>> farm_plots;
    vector<vector<bool>> visited;
    ifstream inFile("input.txt");
    string entry;
    int total_cost = 0;
    while (getline(inFile, entry))
    {
        vector<char> row;
        vector<bool> visited_row;
        string s = entry.c_str();
        for (auto c:s)
        {
            row.push_back(c);
            visited_row.push_back(false);            
        }
        farm_plots.push_back(row);
        visited.push_back(visited_row);
    }

    int nrow_farm = farm_plots.size();
    int ncol_farm = farm_plots[0].size();

    for(int i = 0; i < nrow_farm; i++){
        for(int j = 0; j < ncol_farm; j++){
            if(!visited[i][j]){
                int area = 0;
                int perimeter = 0;

                get_area_and_perimiter(i, j, area, perimeter, farm_plots, visited);
                
                cout << i << "," << j << "  area=" << area << "  perim=" << perimeter << endl;
                total_cost += area*perimeter;

            }
        }
    }

    cout << "The total cost is: " << total_cost;

}
