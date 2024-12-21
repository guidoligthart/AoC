#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

float Inf = 20000000;

using namespace std;
map<char, vector<int>> dir{{'^', {-1, 0}}, 
                           {'>', { 0, 1}}, 
                           {'v', { 1, 0}}, 
                           {'<', { 0,-1}}};

class maze_map{
    public:
        vector<vector<char>> character;
        vector<vector<bool>> visited;
        vector<vector<bool>> wall;
        vector<vector<float>> costs;
        vector<vector<char>> direction;
        
};

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

vector<vector<int>> get_neighbours(int x, int y, maze_map &map){
    vector<vector<int>> neighbours;
    for(auto direction : dir){
        int dest_y = y + direction.second[0];
        int dest_x = x + direction.second[1];

        if(!map.wall[dest_y][dest_x] && !map.visited[dest_y][dest_x]){
            neighbours.push_back({dest_y, dest_x});
        }
    }
    return(neighbours);
}

vector<int> which_minimum(maze_map &m_map){
    float min_value = Inf;
    vector<int> return_vector;
    for(int i = 0; i<m_map.character.size(); i++){
        for(int j = 0; j<m_map.character[0].size(); j++){
            if(!m_map.visited[i][j] && !m_map.wall[i][j]){
                if(m_map.costs[i][j] < min_value){
                    min_value = m_map.costs[i][j];
                    return_vector = {i, j};
                }
            }
        }
    }
    cout << min_value << endl;
    return return_vector;
}

float calculate_costs(vector<int> to, vector<int> from, char direction, char &new_direction){
    cout << "dir="<<direction << endl;
    if(to[0] == from[0] + dir[direction][0] && 
        to[1] == from[1] + dir[direction][1]){
            return 1;
        } else {
            if(from[0] > to[0]){
                new_direction = '^';
            }
            if(from[0] < to[0]){
                new_direction = 'v';
            }
            if(from[1] < to[1]){
                new_direction = '>';
            }
            if(from[1] > to[1]){
                new_direction = '<';
            }
            return 1001;
        }
}

float dijkstra(int x, int y, int end_x, int end_y, char direction, maze_map &m_map){

    m_map.costs[y][x] = 0;
    m_map.direction[y][x] = direction;

    while(!m_map.visited[end_y][end_x]){
        vector<vector<int>> neighbours = get_neighbours(x, y, m_map);
        for(auto neighbour:neighbours){
            char possible_new_direction = m_map.direction[y][x];
            cout << "dir=" << m_map.direction[y][x] << endl;
            float new_cost = m_map.costs[y][x] + calculate_costs(neighbour, {y, x}, m_map.direction[y][x], possible_new_direction);
            float current_cost = m_map.costs[neighbour[0]][neighbour[1]];
            if(new_cost < current_cost){
                m_map.costs[neighbour[0]][neighbour[1]] = new_cost;
                m_map.direction[neighbour[0]][neighbour[1]] = possible_new_direction;
            }
        }
        m_map.visited[y][x] = true;
        //get new x and y
        vector<int> min_coord = which_minimum(m_map);
        cout << min_coord[1] << " " << min_coord[0] << endl;
        y = min_coord[0];
        x = min_coord[1];
    }

    return m_map.costs[end_y][end_x];
}

int main(){
    ifstream inFile("input.txt");
    string entry;
    maze_map map;

    while (getline(inFile, entry))
    {
        vector<char> map_row;
        vector<bool> visited_row;
        vector<bool> wall_row;
        vector<float> costs_row;
        vector<char> direction_row;
        for(auto value:entry){
            map_row.push_back(value);
            visited_row.push_back(false);
            wall_row.push_back(value == '#');
            costs_row.push_back(Inf);
            direction_row.push_back('.');
        }
        map.character.push_back(map_row);
        map.visited.push_back(visited_row);     
        map.wall.push_back(wall_row);
        map.costs.push_back(costs_row);
        map.direction.push_back(direction_row);
    }

    //find start and end
    int start_x = 0;
    int start_y = 0;
    int end_x = 0;
    int end_y = 0;
    for(int i = 0; i < map.character.size(); i++){
        for(int j = 0; j < map.character[0].size(); j++){
            if(map.character[i][j] == 'S'){
                start_y = i;
                start_x = j;
            }
            if(map.character[i][j] == 'E'){
                end_y = i;
                end_x = j;
            }
        }
    }

    int a(dijkstra(start_x, start_y, end_x, end_y, '>', map));
    
    draw_map(map.direction);
    cout << "Total cost: " << a;

    

}
