#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <istream>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

vector<long> vector1;
vector<long> vector2;
int similarity_score = 0;

int main()
{
    ifstream inFile ("input.txt");
    string entry;

    regex rgx("^([0-9]+).*?([0-9]+)$");

    while (getline(inFile, entry)){
        const string s = entry.c_str();
        smatch m;

        if(regex_search(s.begin(), s.end(), m, rgx)){
            vector1.push_back(stoi(m[1].str()));
            vector2.push_back(stoi(m[2].str()));
        } else {
            cout << "regex did not match on: " << s << "\n";
            return(1);
        }
    }

    for(auto i : vector1){
        int occurance = 0;
        for(auto j : vector2){
            if(i==j){
                occurance += 1;
            }
        }
        similarity_score += i * occurance;
    }

    cout << "The similarity score is: " << similarity_score << "\n";
    
    return(0);
}