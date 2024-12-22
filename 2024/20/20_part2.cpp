#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

int Inf = 20000000;

using namespace std;
map<char, vector<int>> dir{{'^', {-1, 0}}, 
                           {'>', { 0, 1}}, 
                           {'v', { 1, 0}}, 
                           {'<', { 0,-1}}};

class maze_map{
    public:
        vector<vector<bool>> visited;
        vector<vector<bool>> wall;
        vector<vector<int>> costs;
        vector<int> start;
        vector<int> end;
};

maze_map construct_map(string input){
    maze_map m_map;
    ifstream inFile(input);
    string entry;

    vector<int> start;
    vector<int> end;
    int i = 0;
    int j = 0;
    while (getline(inFile, entry))
    {
        j = 0;
            vector<bool> wall_col;
            vector<bool> visited_col;

            vector<int> costs_col;
        for (auto character:entry){
            wall_col.push_back(character == '#');
            visited_col.push_back(false);
            costs_col.push_back(Inf);

            if(character == 'S') m_map.start = {i, j};
            if(character == 'E') m_map.end = {i, j};
            j++;
        }
        m_map.wall.push_back(wall_col);
        m_map.visited.push_back(visited_col);
        m_map.costs.push_back(costs_col);
        i++;
    }
    return m_map;
}

void draw_map(maze_map map){
    int map_x = map.wall[0].size();
    int map_y = map.wall.size();
    for (int i = 0; i < map_y; i++)
    {
        for(int j = 0; j < map_x; j++){
            if(map.wall[i][j]){
                cout << "█";
            } else cout << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> get_neighbours(int x, int y, maze_map &map, bool visited_matters = true){
    vector<vector<int>> neighbours;
    for(auto direction : dir){
        int dest_y = y + direction.second[0];
        int dest_x = x + direction.second[1];

        if(!map.wall[dest_y][dest_x] && (!visited_matters || !map.visited[dest_y][dest_x])){
            neighbours.push_back({dest_y, dest_x});
        }
    }
    return(neighbours);
}

vector<vector<int>>get_distant_neighbours(int row, int col, maze_map &map, int jump = 20){
    vector<vector<int>> neighbours;
    for(int i = -jump; i <= jump; i++){
        int steps_left = jump - abs(i);
        for(int j = -steps_left; j <= steps_left; j++){
            //if in bounds
            if((row+i) > 0 && (row+i) < map.wall.size() && (col+j) > 0 && (col+j) < map.wall[0].size()){
                //and not a wall
                if(!map.wall[row+i][col+j]){
                    neighbours.push_back({row+i, col+j});
                }
            }
        }
    }
    return(neighbours);
}

vector<int> which_minimum(maze_map &m_map){
    int min_value = Inf;
    vector<int> return_vector;
    for(int i = 0; i<m_map.wall.size(); i++){
        for(int j = 0; j<m_map.wall[0].size(); j++){
            if(!m_map.visited[i][j] && !m_map.wall[i][j]){
                if(m_map.costs[i][j] < min_value){
                    min_value = m_map.costs[i][j];
                    return_vector = {i, j};
                }
            }
        }
    }
    return return_vector;
}

int dijkstra(int x, int y, int end_x, int end_y, maze_map &m_map){

    m_map.costs[y][x] = 0;    
    vector<int> min_coord = {y, x};

    while(min_coord.size() != 0){
        y = min_coord[0];
        x = min_coord[1];
        vector<vector<int>> neighbours = get_neighbours(x, y, m_map);
        for(auto neighbour:neighbours){
            int new_cost = m_map.costs[y][x] + 1;
            int current_cost = m_map.costs[neighbour[0]][neighbour[1]];
            if(new_cost < current_cost){
                m_map.costs[neighbour[0]][neighbour[1]] = new_cost;
            }
        }
        m_map.visited[y][x] = true;
        //get new x and y
        min_coord = which_minimum(m_map);
    }

    return m_map.costs[end_y][end_x];
}

void reset_costs_and_visited(maze_map &m_map){
    for(int i = 0; i<m_map.wall.size(); i++){
        for(int j = 0; j<m_map.wall[0].size(); j++){
            m_map.visited[i][j] = false;
            m_map.costs[i][j] = Inf;
        }
    }

}

int main(){
    maze_map m_map = construct_map("input.txt");

    draw_map(m_map);
    
    // dijkstra is inefficient here, but I already wrote it for a previous puzzle and it works
    int base_time = dijkstra(m_map.start[1], m_map.start[0], m_map.end[1], m_map.end[0], m_map);
    
    //time to cheat
    int good_cheats = 0;
    vector<vector<int>> cheatable_walls;
    for(int i = 1; i < m_map.wall.size() - 1; i++){
        for(int j = 1; j < m_map.wall.size() - 1; j ++){
            //check if cheatable
            if(!m_map.wall[i][j]){
                vector<vector<int>> neighbours = get_distant_neighbours(i, j, m_map, 20);

                for(auto neighbour:neighbours){
                    int time_diff = m_map.costs[neighbour[0]][neighbour[1]] - m_map.costs[i][j]; 
                    int time_save = time_diff - (abs(i - neighbour[0]) + abs(j - neighbour[1]));
                    if(time_save >= 100){
                        good_cheats++;
                    }
                }
            }
        }
    }


    cout << "The amount of cheats saving more than 100 picoseconds is: " << good_cheats << endl;
}
