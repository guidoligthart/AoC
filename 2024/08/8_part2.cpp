#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

int main(){
    //parse the map
    vector<vector<char>> antenna_map;
    vector<vector<bool>> antinode_map;
    ifstream inFile(R"(input.txt)");
    string entry;
    while (getline(inFile, entry))
    {
        vector<char> row;
        vector<bool> antinode_row;
        string s = entry.c_str();
        for (auto c:s)
        {
            row.push_back(c);
            antinode_row.push_back(false);            
        }
        antenna_map.push_back(row);
        antinode_map.push_back(antinode_row);
    }

    int map_nrows = antenna_map.size();
    int map_ncols = antenna_map[0].size();
    char current_char;
    char compare_char;
    int antinode_row_id;
    int antinode_col_id;
    for(int row_i = 0; row_i < antenna_map.size(); row_i++)
    {
        for(int col_i = 0; col_i < antenna_map[row_i].size(); col_i++)
        {
            char current_char = antenna_map[row_i][col_i];

            if(current_char != '.')
            {
                for(int row_i_compare = 0; row_i_compare < antenna_map.size(); row_i_compare++)
                {
                    for(int col_i_compare = 0; col_i_compare < antenna_map[row_i].size(); col_i_compare++)
                    {
                        compare_char = antenna_map[row_i_compare][col_i_compare];
                        if(compare_char == current_char & 
                           (col_i_compare != col_i & row_i_compare != row_i))
                        {
                            int delta_row = (row_i - row_i_compare);
                            int delta_col = (col_i - col_i_compare);

                            int anti_row_id = row_i;
                            int anti_col_id = col_i;
                            
                            while(anti_row_id >= 0 && anti_row_id < map_nrows &&
                                anti_col_id >= 0 && anti_col_id < map_ncols)
                            {
                                antinode_map[anti_row_id][anti_col_id] = true;
                                anti_row_id += delta_row;
                                anti_col_id += delta_col; 
                            }
                        }
                    }
                }
            }
        }
    }

    int antinode_count = 0;
    for (int i = 0; i < antenna_map.size(); i++)
    {
        for (int j = 0; j < antenna_map[0].size(); j++)
        {
            if(antinode_map[i][j])
            {
                cout << '#';
                antinode_count++;
            } else {
                cout << '.';
            }
        }
        cout << endl;        
    }
    
    cout << "The total amount of antinodes is: " << antinode_count;

}
