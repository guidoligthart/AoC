#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <map>

using namespace std;

vector<double> claw_game_solutions(double a_x, double a_y, double b_x, double b_y, double prize_x, double prize_y){
    double D = (a_x * b_y) - (b_x * a_y);
    double Dx = (prize_x * b_y) - (prize_y * b_x);
    double Dy = (prize_y * a_x) - (a_y * prize_x);
 
    double x = Dx / D;
    double y = Dy / D;
 
    return {x, y};
}

int main(){
    unsigned long long total_cost = 0;

    ifstream inFile("input.txt");
    string entry;

    regex input_pattern(R"(^(.*?): X[+=]([0-9]+), Y[+=]([0-9]+)$)");

    double a_x, a_y, b_x, b_y, prize_x, prize_y;

    while (getline(inFile, entry))
    {
        smatch m;
        std::regex_search(entry, m, input_pattern);
        if (m[1] == "Button A"){
            a_x = stod(m[2]);
            a_y = stod(m[3]);
        }
        if (m[1] == "Button B"){
            b_x = stod(m[2]);
            b_y = stod(m[3]);
        }
        if (m[1] == "Prize"){
            prize_x = stod(m[2]);
            prize_y = stod(m[3]);
            
            vector<double> a_b_count = claw_game_solutions(a_x, a_y, b_x, b_y, prize_x + 10000000000000, prize_y + 10000000000000);
            double a = a_b_count[0];
            double b = a_b_count[1];

            if((unsigned long long) a == a && (unsigned long long) b == b){
                total_cost += a*3 + b;
            }
        }
    }

    cout << "The least amount of tokens to win all possible prizes is: " << total_cost;

}
