#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ifstream inFile("C:/Users/Guido/projects/C/aoc2024_03/input.txt");
    std::string entry;
    int sum_of_mul_returns = 0;
    int n_mul = 0;

    regex pattern(R"(mul\(([0-9]{1,3}),([0-9]{1,3})\))");

    while (std::getline(inFile, entry)) {
        string s = entry.c_str();
        smatch m;
        while(std::regex_search(s, m, pattern)) {
            n_mul += 1;
            sum_of_mul_returns += stoi(m[1]) * stoi(m[2]);
            s = m.suffix();
        }
    }

    cout << "Amount of 'mul'-function calls: " << n_mul <<
        endl << "Sum of the returns: " << sum_of_mul_returns;
}
