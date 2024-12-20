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

    for (int i = 0; i < map_y; i++)
    {
        for(int j = 0; j < map_x; j++){
            cout << map[i][j];
        }
        cout << endl;
    }
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

    for (auto robot:robots)
    {
        take_n_steps(robot, 100);
        adjust_for_teleportation(robot, map_cols, map_rows);
        map[robot.y][robot.x]++;
    }
    
    draw_map(map);

    int map_center_cols = (map_cols/2); 
    int map_center_rows = (map_rows/2);

    int q1 = 0;
    int q2 = 0;
    int q3 = 0;
    int q4 = 0;

    for(int i = 0; i < map_rows; i++){
        vector<int> map_row;
        for (int j = 0; j < map_cols; j++)
        {
          if (j < map_center_cols & i < map_center_rows) q1 += map[i][j];
          if (j > map_center_cols & i < map_center_rows) q2 += map[i][j];
          if (j < map_center_cols & i > map_center_rows) q3 += map[i][j];
          if (j > map_center_cols & i > map_center_rows) q4 += map[i][j];
        }   
    }
    cout << q1 << "*" << q2 << "*" << q3 << "*" << q4 << endl;
    cout << "The product of all quadrant robot count is: " << q1*q2*q3*q4;
}
