#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <map>

using namespace std;

void get_area_and_sides(int i, int j, 
                            int& area, int& sides,
                            vector<vector<char>> map,
                            vector<vector<bool>>& visited){
    if(visited[i][j]){
        return;
    }
    area++;
    visited[i][j] = true;
    char current_char = map[i][j];
    char c = current_char;
    
    int north_i = i -1;
    int south_i = i +1;

    int west_j = j -1;
    int east_j = j +1;

        if(map[north_i][j] == current_char){
            get_area_and_sides(north_i, j, area, sides, map, visited);
        }

        if (map[north_i][j] != c && map[i][east_j] != c) sides++;
        if (map[north_i][j] != c && map[i][west_j] != c) sides++;
        if (map[north_i][j] == c && map[i][east_j] == c && map[north_i][east_j] != c) sides++;
        if (map[north_i][j] == c && map[i][west_j] == c && map[north_i][west_j] != c) sides++;
        
        if(map[south_i][j] == current_char){
            get_area_and_sides(south_i, j, area, sides, map, visited);
        }

        if (map[south_i][j] != c && map[i][east_j] != c) sides++; 
        if (map[south_i][j] != c && map[i][west_j] != c) sides++;
        if (map[south_i][j] == c && map[i][east_j] == c && map[south_i][east_j] != c) sides++;
        if (map[south_i][j] == c && map[i][west_j] == c && map[south_i][west_j] != c) sides++;
        
        if(map[i][west_j] == current_char){
            get_area_and_sides(i, west_j, area, sides, map, visited);
        } 

        if(map[i][east_j] == current_char){
            get_area_and_sides(i, east_j, area, sides, map, visited);
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
        s = "." + s + ".";
        for (auto c:s)
        {
            row.push_back(c);
            visited_row.push_back(false);            
        }
        farm_plots.push_back(row);
        visited.push_back(visited_row);
    }
    vector<char> buffer_row;
    vector<bool> false_row;
    for (int i = 0; i < farm_plots[0].size(); i++)
    {
        buffer_row.push_back('.');
        false_row.push_back(false);
    }

    farm_plots.insert(farm_plots.begin(), buffer_row);
    farm_plots.insert(farm_plots.end(), buffer_row);

    visited.insert(visited.begin(), false_row);
    visited.insert(visited.end(), false_row);

    int nrow_farm = farm_plots.size();
    int ncol_farm = farm_plots[0].size();

    for(int i = 0; i < nrow_farm; i++){
        for(int j = 0; j < ncol_farm; j++){
            if(!visited[i][j] && farm_plots[i][j] != '.'){
                int area = 0;
                int sides = 0;

                get_area_and_sides(i, j, area, sides, farm_plots, visited);
                cout << i << "," << j << "  area=" << area << "  sides=" << sides << endl;
                total_cost += area*sides;

            }
        }
    }

    cout << "The total cost is: " << total_cost;

}
