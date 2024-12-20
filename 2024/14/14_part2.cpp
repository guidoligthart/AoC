#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <map>

using namespace std;

class robot {
    public:
        int x, y, vx, vy;
};

void take_n_steps(robot &r, int n){
             r.x += r.vx*n;
             r.y += r.vy*n;
}

void adjust_for_teleportation(robot &r, int map_size_x, int map_size_y){
    r.x %= map_size_x;
    r.y %= map_size_y;

    if(r.x < 0){
        r.x += map_size_x;
    }
    if(r.y < 0){
        r.y += map_size_y;
    }
}

void draw_map(vector<vector<int>> map){
    int map_x = map[0].size();
    int map_y = map.size();
    char to_draw;

    for (int i = 0; i < map_y; i++)
    {
        for(int j = 0; j < map_x; j++){
            if(map[i][j] == 0){
                to_draw = ' ';
            } else {
                to_draw = '#';
            }
            cout << to_draw;
        }
        cout << endl;
    }
}

int max_robots_in_rows(vector<vector<int>> map){
    vector<int> row_counts;
    for (vector<int> row:map)
    {
        int row_count = 0;
        for(int value:row){
            if(value > 0) row_count++;
        }
        row_counts.push_back(row_count);
    }
    return(*max_element(row_counts.begin(), row_counts.end()));  
}

vector<vector<int>> construct_map(int map_cols, int map_rows){    
    vector<vector<int>> map;
    for(int i = 0; i < map_rows; i++){
        vector<int> map_row;
        for (int j = 0; j < map_cols; j++)
        {
            map_row.push_back(0);
        }
        map.push_back(map_row);   
    }
    return(map);
}

int main(){
    ifstream inFile("input.txt");
    string entry;
    regex input_pattern(R"(^p=([0-9]+),([0-9]+) v=(-?[0-9]+),(-?[0-9]+)$)");
    vector<vector<int>> robot_positions, robot_speeds;
    vector<robot> robots;

    while (getline(inFile, entry))
    {
        smatch m;
        std::regex_search(entry, m, input_pattern);
        robot r;
        r.x = stoi(m[1]);
        r.y = stoi(m[2]);
        r.vx = stoi(m[3]);
        r.vy = stoi(m[4]);

        robots.push_back(r);
    }

    int map_cols = 101;
    int map_rows = 103;

    vector<vector<int>> map = construct_map(map_cols, map_rows);

    for(int i = 0; i <= 10000; i++)
    {
  
        map = construct_map(map_cols, map_rows);
        for (auto robot:robots)
            {
                take_n_steps(robot, i);
                adjust_for_teleportation(robot, map_cols, map_rows);
                map[robot.y][robot.x]++;   
            }
        if (max_robots_in_rows(map) > 32)
        {
            draw_map(map);
            cout << "============ i=" << i << " ======================";
        }
        
    }
}
