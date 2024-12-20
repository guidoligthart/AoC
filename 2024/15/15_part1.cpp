#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
map<char, vector<int>> dir{{'^', {-1, 0}}, 
                           {'>', { 0, 1}}, 
                           {'v', { 1, 0}}, 
                           {'<', { 0,-1}}};

void draw_map(vector<vector<char>> map){
    int map_x = map[0].size();
    int map_y = map.size();
    char to_draw;

    for (int i = 0; i < map_y; i++)
    {
        for(int j = 0; j < map_x; j++){
            cout << map[i][j];
        }
        cout << endl;
    }
}

bool go_in_direction(int x, int y, char direction, vector<vector<char>>& map){
    int dest_y = y + dir[direction][0];
    int dest_x = x + dir[direction][1];

    char dest_char = map[dest_y][dest_x];
    if(dest_char == '.'){
        map[dest_y][dest_x] = map[y][x];
        map[y][x] = '.';
        return true;
    } 
    if(dest_char == '#'){
        return false;
    }
    if(dest_char == 'O'){
        if(go_in_direction(dest_x, dest_y, direction, map)){
            map[dest_y][dest_x] = map[y][x];
            map[y][x] = '.';
            return true;
        } else {
            return false;
        }
    }
}

int main(){
    ifstream inFile("input.txt");
    string entry;
    vector<vector<char>> map;
    string instructions = "";

    while (getline(inFile, entry))
    {
        if(entry[0] == '#'){
            vector<char> map_row;
            for(auto value:entry){
                map_row.push_back(value);
            }
            map.push_back(map_row);
        } else {
            instructions += entry;
        }
        
    }

    //find robot (@)
    int robot_x = 0;
    int robot_y = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].size(); j++){
            if(map[i][j] == '@'){
                robot_y = i;
                robot_x = j;
            }
        }
    }

    // follow instructions
    for(auto direction:instructions){
        if(go_in_direction(robot_x, robot_y, direction, map)){
            robot_y += dir[direction][0];
            robot_x += dir[direction][1];
        }
    }

    // calculate box GPS coords
    int coord_sum = 0;
    for(int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[0].size(); j++)
        {
            if(map[i][j] == 'O'){
                coord_sum += i*100 + j;
            }
        }
        
    }

    cout << "The sum of all boxes' GPS coordinates is: " << coord_sum;  
}
