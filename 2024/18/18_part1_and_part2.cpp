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
};

maze_map construct_map(int rows, int cols){
    //construct a maze with padding
    maze_map m_map;
    for(int i = 0; i < (rows + 2); i++){
        vector<bool> wall_row;
        vector<bool> visited_row;
        vector<int> costs_row;
        for(int j = 0; j < (cols + 2); j++){
            wall_row.push_back(j == 0 || j == (cols+1) || i == 0 || i == (rows+1));
            visited_row.push_back(false);
            costs_row.push_back(Inf);
        }
        m_map.wall.push_back(wall_row);
        m_map.visited.push_back(visited_row);
        m_map.costs.push_back(costs_row);
    }
    return m_map;
}

void create_wall(vector<vector<int>> &wall_input, maze_map &map){
    map.wall[wall_input[0][1]][wall_input[0][0]] = true;
    wall_input.erase(wall_input.begin());
}

void draw_map(maze_map map){
    int map_x = map.wall[0].size();
    int map_y = map.wall.size();
    char to_draw;

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

void solve_maze(int x, int y, int end_x, int end_y, maze_map m_map, vector<vector<int>> wall_input, int step_counter, vector<int> &solutions){
    m_map.visited[y][x] = true;
    m_map.costs[y][x] = step_counter;
    if(step_counter > 3500){
        return;
    }
    if(x == end_x && y == end_y){
        //draw_map(m_map);
        cout << "Path found! Amount of steps taken: " << step_counter << endl << endl;
        solutions.push_back(step_counter);
        return;
    }
    step_counter++;
    //draw_map(m_map);
    vector<vector<int>> neighbours = get_neighbours(x, y, m_map);
    for(auto neighbour:neighbours){
        solve_maze(neighbour[1], neighbour[0], end_x, end_y, m_map, wall_input, step_counter, solutions);
    }
    return;
}

int main(){
    //parse the input
    ifstream inFile("input.txt");
    string entry;
    vector<vector<int>> wall_input;
    while (getline(inFile, entry))
    {
        istringstream row(entry);
        string col;
        vector<int> wall;
        while (getline(row, col, ','))
        {
            wall.push_back(stoi(col) + 1);
        }
        wall_input.push_back(wall);
        
    }
    int map_rows = 71;
    int map_cols = 71;

    maze_map m_map = construct_map(map_rows, map_cols);
    int input_size = wall_input.size();
    vector<vector<int>> wall_input_copy = wall_input;

    map<int, maze_map> all_maps;

    for (int i = 0; i < input_size; i++){
        create_wall(wall_input, m_map);
        all_maps[i] = m_map;
    }
    cout << "finished building all maps, start finding paths" <<endl; 

    //binary search for last possible solution;
    bool puzzle_solved = false;
    int left_i = 1024;
    int right_i = input_size - 2;
    int solveable1, solveable2;
    int i = (left_i + right_i)/2;
    while(!puzzle_solved){
        i = (left_i + right_i)/2;
        solveable1 = dijkstra(1, 1, 71, 71, all_maps[i]) != Inf;
        solveable2 = dijkstra(1, 1, 71, 71, all_maps[i+1]) != Inf;
        if(solveable1 & !solveable2){
            puzzle_solved = true;
        }
        if(solveable1 & solveable2){
            left_i = i;
        }
        if(!solveable1 & !solveable2){
            right_i = i;
        }
    }
    
    cout << "After 1024 bytes, the amount of steps to exit is: " << dijkstra(1, 1, 71, 71, all_maps[1023]) << endl;
    cout << "The first byte to drop that makes the maze impossible is: " <<
    wall_input_copy[i+1][0]-1 << "," << wall_input_copy[i+1][1]-1;

}
