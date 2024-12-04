#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ifstream inFile("input.txt");
    string entry;
    int xmas_counter = 0;

    vector<vector<char>> xmas_matrix;

    while (getline(inFile, entry)) {
        string s = entry.c_str();
        vector<char> col;
        for (auto character:s)
        {
            col.push_back(character);
        }
        xmas_matrix.push_back(col);
    }

    int n_rows = xmas_matrix.size();
    int n_cols = xmas_matrix[0].size();

    vector<int> x_pos_cols;
    vector<int> x_pos_rows;
    int x_counter = 0;

    //loop over matrix to find x's
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_cols; j++)
        {
            if(xmas_matrix[i][j] == *"X"){
                x_pos_rows.push_back(i);
                x_pos_cols.push_back(j);
                x_counter++;
            }
        }
    }

    cout << "Amount of X's found: " << x_counter << endl;

    int directions_matrix[4][2] = {
        { 1,  0}, //left to right
        { 1,  1}, //top_left to bottom_right
        { 0,  1}, //top to bottom
        { 1, -1}  //bottom_left to top_right
    };

    for (int x_i = 0; x_i < x_counter; x_i++) // for each x
    {
        int letter_pos_row;
        int letter_pos_col;
        vector<char> letters;
        int x_col = x_pos_cols[x_i];
        int x_row = x_pos_rows[x_i];
        vector<int> signs = {1, -1};

        for(auto sign:signs)
        {
            for (int direction_i = 0; direction_i < 4; direction_i++) // for each direction
            {   
                    for (int letter_i = 1; letter_i <= 3; letter_i++) // check each letter
                    {
                        letter_pos_row = x_row + (directions_matrix[direction_i][1] * letter_i * sign);
                        letter_pos_col = x_col + (directions_matrix[direction_i][0] * letter_i * sign);

                        if (letter_pos_col >= 0 & letter_pos_col < xmas_matrix.size() & 
                            letter_pos_row >= 0 & letter_pos_row < xmas_matrix.size())// if in bounds; check the letters
                        {
                            letters.push_back(xmas_matrix[letter_pos_row][letter_pos_col]);
                        }

                        string s(letters.begin(), letters.end());
                        if(s == "MAS")xmas_counter++;
                        
                    }
                letters.clear();
            }
        }
        
    }

    cout << "Amount of XMAS's found: " << xmas_counter << endl;
        
}