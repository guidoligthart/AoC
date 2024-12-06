#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;

bool running_in_circles(char guard_char, int guard_x, int guard_y, vector<vector<char>> map){
    //define directions
    int direction[4][2] = {
        {-1, 0}, //up
        {0,  1}, //right
        {1,  0}, //down
        {0, -1}  //left
    };

    int guard_direction =
        guard_char == '^' * 1 +
        guard_char == '>' * 2 +
        guard_char == 'v' * 3 +
        guard_char == '<' * 4;

    char direction_char[4] = {'^', '>', 'v', '<'};

    //take steps
    int next_step_x;
    int next_step_y;
    int tile_counter = 0;
    int turn_counter = 0;

    while (true)
    {
        next_step_x = guard_x + direction[guard_direction][1];
        next_step_y = guard_y + direction[guard_direction][0];

        //break if out of bounds
        if(!(next_step_x >= 0 & next_step_x < map[0].size() & next_step_y >= 0 & next_step_y < map.size())) 
        return(false);
        
        if (map[next_step_y][next_step_x] == '#')
        {
            turn_counter++;
            guard_direction = (guard_direction+1) % 4;
        } else if (map[next_step_y][next_step_x] == direction_char[guard_direction])
        {
            return(true);
        } else {
            guard_x = next_step_x;
            guard_y = next_step_y;
            map[guard_y][guard_x] = direction_char[guard_direction];      
        }   
    }
}

int main(){
    auto start = chrono::system_clock::now();
    //parse the map
    vector<vector<char>> map;
    ifstream inFile("input.txt");
    string entry;
    while (getline(inFile, entry))
    {
        vector<char> row;
        string s = entry.c_str();
        for (auto c:s)
        {
            row.push_back(c);
        }
        map.push_back(row);
    }
    
    //find guard position
    int guard_x;
    int guard_y;
    char guard_char;
    for (int row_i = 0; row_i < map.size(); row_i++)
    {
        for (int col_i = 0; col_i < map[0].size(); col_i++)
        {
            if(map[row_i][col_i] != '.' && map[row_i][col_i] != '#'){
                guard_y = row_i;
                guard_x = col_i;
                guard_char = map[row_i][col_i];
            }
        }
    }

int in_circles_counter = 0;    
    for (int new_obs_row = 0; new_obs_row < map.size(); new_obs_row++)
    {
        for (int new_obs_col = 0; new_obs_col < map[0].size(); new_obs_col++)
        {
            vector<vector<char>> duplicated_map = map;
            duplicated_map[new_obs_row][new_obs_col] = '#';
            if(running_in_circles(guard_char, guard_x, guard_y, duplicated_map)){
                in_circles_counter++;    
            } 
        }
        
    }

    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << endl << "Elapsed time: " << elapsed_seconds.count() << " seconds" << endl;

    cout << "Total possible obstacle positions which will lead to loops: " << in_circles_counter;

}
