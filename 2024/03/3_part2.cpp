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

    //lookbehind not supported; sad
    //regex pattern(R"((?<!don't\(\).*?^(do\(\)))mul\(([0-9]{1,3}),([0-9]{1,3})\))");

    //instead remove everything between 'don't()' and 'do()'
    regex dont_do_pattern(R"(don't\(\).*?do\(\))");
    regex mul_pattern(R"(mul\(([0-9]{1,3}),([0-9]{1,3})\))");

    string s;

    while (std::getline(inFile, entry)) {
        s += entry.c_str();
    }

    string s_do = std::regex_replace(s, dont_do_pattern, "");
    smatch m;

    while(std::regex_search(s_do, m, mul_pattern)) {
        cout << m.str() << endl;
        n_mul += 1;
        sum_of_mul_returns += stoi(m[1]) * stoi(m[2]);
        s_do = m.suffix();
    }

    cout << "Amount of 'mul'-function calls: " << n_mul <<
        endl << "Sum of the returns: " << sum_of_mul_returns;
}
