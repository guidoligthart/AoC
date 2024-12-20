#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <map>

using namespace std;

void claw_game_solutions(int a_x, int a_y, int b_x, int b_y, int prize_x, int prize_y, vector<vector<int>>& a_b_count){
    int max_a_presses = min(prize_y/a_y, prize_x/a_x);
    
    for(int a_i = 0; a_i <= max_a_presses; a_i++){
        int b_i = 0;
        int claw_x = a_x*a_i;
        int claw_y = a_y*a_i;
        while (claw_x <= prize_x && claw_y <= prize_y)
        {
            // if on the prize; return the button presses
            if (claw_x == prize_x && claw_y == prize_y){
                a_b_count.push_back({a_i, b_i});
                break;
            }

            // otherwise press b again
            b_i++;
            claw_x += b_x;
            claw_y += b_y;

        }      
    }
}

int main(){
    int total_cost = 0;

    ifstream inFile("input.txt");
    string entry;

    regex input_pattern(R"(^(.*?): X[+=]([0-9]+), Y[+=]([0-9]+)$)");

    int a_x, a_y, b_x, b_y, prize_x, prize_y;

    while (getline(inFile, entry))
    {
        smatch m;
        std::regex_search(entry, m, input_pattern);
        if (m[1] == "Button A"){
            a_x = stoi(m[2]);
            a_y = stoi(m[3]);
        }
        if (m[1] == "Button B"){
            b_x = stoi(m[2]);
            b_y = stoi(m[3]);
        }
        if (m[1] == "Prize"){
            prize_x = stoi(m[2]);
            prize_y = stoi(m[3]);
            
            vector<vector<int>> a_b_count;
            claw_game_solutions(a_x, a_y, b_x, b_y, prize_x, prize_y, a_b_count);
            vector<int> solution_costs;
            for (auto solution:a_b_count)
            {
                solution_costs.push_back(solution[0]*3 + solution[1]);
            }

            if(solution_costs.size() > 0){
                total_cost += *min_element(solution_costs.begin(), solution_costs.end());
            }
        }
    }

    cout << "The least amount of tokens to win all possible prizes is: " << total_cost;

}
