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

bool box_go_in_direction(int x1, int x2, int y, char direction, vector<vector<char>> &map, bool dont_move = false){
    int dest_y = y + dir[direction][0];
    int dest_x1 = x1 + dir[direction][1];
    int dest_x2 = x2 + dir[direction][1];

    bool move = false;

    char dest_char1 = map[dest_y][dest_x1];
    char dest_char2 = map[dest_y][dest_x2];

    if(direction == '>'){
        if(dest_char2 == '.'){
            move = true;
            }
        if(dest_char2 == '['){
            move = box_go_in_direction(dest_x1 + 1, dest_x2 +1, dest_y, direction, map);
        }
    }

    if(direction == '<'){
        if(dest_char1 == '.'){
            move = true;
            }
        if(dest_char1 == ']'){
            move = box_go_in_direction(dest_x1 - 1, dest_x2 - 1, dest_y, direction, map);
        }
    }

    if(direction == '^' || direction == 'v'){
        bool x1_accesible = false;
        bool x2_accesible = false;
        
        if(dest_char1 == '.') x1_accesible = true;
        if(dest_char1 == '[') x1_accesible = box_go_in_direction(dest_x1, dest_x1+1, dest_y, direction, map, true);
        if(dest_char1 == ']') x1_accesible = box_go_in_direction(dest_x1-1, dest_x1, dest_y, direction, map, true);
        
        if(dest_char2 == '.') x2_accesible = true;
        if(dest_char2 == '[') x2_accesible = box_go_in_direction(dest_x2, dest_x2+1, dest_y, direction, map, true);
        if(dest_char2 == ']') x2_accesible = x1_accesible;

        move = x1_accesible && x2_accesible; 
        if(!dont_move && move){
            if(dest_char1 == '[') x1_accesible = box_go_in_direction(dest_x1, dest_x1+1, dest_y, direction, map);
            if(dest_char1 == ']') x1_accesible = box_go_in_direction(dest_x1-1, dest_x1, dest_y, direction, map);
            if(dest_char2 == '[') x2_accesible = box_go_in_direction(dest_x2, dest_x2+1, dest_y, direction, map);
        }
    } 
    
    if(!dont_move && move && (direction == '^' || direction == 'v')){
        map[dest_y][dest_x2] = ']';
        map[dest_y][dest_x1] = '[';
        map[y][x2] = '.';
        map[y][x1] = '.';
    }

    if(!dont_move && move && direction == '<'){
        map[dest_y][dest_x2] = ']';
        map[dest_y][dest_x1] = '[';
        map[y][x2] = '.';
    }
    
    if(!dont_move && move && direction == '>'){
        map[dest_y][dest_x2] = ']';
        map[dest_y][dest_x1] = '[';
        map[y][x1] = '.';
    }

    return(move);
}

bool go_in_direction(int x, int y, char direction, vector<vector<char>> &map){
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
    if(dest_char == '['){
        if(box_go_in_direction(dest_x, dest_x+1, dest_y, direction, map)){
            map[dest_y][dest_x] = map[y][x];
            map[y][x] = '.';
            return true;
        } else {
            return false;
        }
    }
    if(dest_char == ']'){
        if(box_go_in_direction(dest_x-1, dest_x, dest_y, direction, map)){
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
                if (value == '#' || value == '.')
                {
                    map_row.push_back(value);
                    map_row.push_back(value);
                } else if(value == 'O'){
                    map_row.push_back('[');
                    map_row.push_back(']');
                } else if(value == '@'){
                    map_row.push_back('@');
                    map_row.push_back('.');
                }
                
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
        //draw_map(map);
        if(go_in_direction(robot_x, robot_y, direction, map)){
            robot_y += dir[direction][0];
            robot_x += dir[direction][1];
        }
    }
    draw_map(map);

    // calculate box GPS coords
    int coord_sum = 0;
    for(int i = 0; i < map.size(); i++){
        for (int j = 0; j < map[0].size(); j++)
        {
            if(map[i][j] == '['){
                coord_sum += i*100 + j;
            }
        }
        
    }

    cout << "The sum of all boxes' GPS coordinates is: " << coord_sum;  
}
