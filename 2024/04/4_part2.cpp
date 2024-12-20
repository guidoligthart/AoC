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

    vector<int> a_pos_cols;
    vector<int> a_pos_rows;
    int a_counter = 0;

    //loop over matrix to find x's
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_cols; j++)
        {
            if(xmas_matrix[i][j] == *"A"){
                a_pos_rows.push_back(i);
                a_pos_cols.push_back(j);
                a_counter++;
            }
        }
    }

    int cross_coords[4][2] = {
        { 1,  1}, 
        { 1, -1}, 
        {-1, -1}, 
        {-1,  1}  
    };

    for (int a_i = 0; a_i < a_counter; a_i++) // for each A
    {
        int letter_pos_row;
        int letter_pos_col;
        vector<char> letters;
        int a_col = a_pos_cols[a_i];
        int a_row = a_pos_rows[a_i];
        int m_counter;
        int s_counter;
        for (int direction_i = 0; direction_i < 4; direction_i++) // for each direction
        {
            letter_pos_row = a_row + (cross_coords[direction_i][1]);
            letter_pos_col = a_col + (cross_coords[direction_i][0]);
            
            if (letter_pos_col >= 0 & letter_pos_col < xmas_matrix.size() & 
                letter_pos_row >= 0 & letter_pos_row < xmas_matrix.size())// if in bounds; check the letters
                {
                    letters.push_back(xmas_matrix[letter_pos_row][letter_pos_col]);
                }
        }

        if(letters[0] != letters[2])
        {
            for(auto letter:letters){
                if (letter == 'M') m_counter++;
                if (letter == 'S') s_counter++;
            }
            if(m_counter == 2 & s_counter == 2){
                xmas_counter++;
            }
            m_counter = 0;
            s_counter = 0;
        }
        letters.clear();
    }
    cout << "Amount of A's found: " << a_counter << endl;
    cout << "Amount of X-MAS's found: " << xmas_counter << endl;
}
