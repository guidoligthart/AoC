#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
string number;

bool same_sign(vector<int> x){
    int sign = (x[1] > 0) - (x[1] < 0);
    for(auto i : x){
        if(sign == -1 & i > 0){
            return false;
        } else if(sign == 1 & i < 0){
            return false;
        }
    }
    return true;
}

bool safe_report(vector<int> levels){
    int vectorSize = levels.size();
    vector<int> dif_vector;
    for (int i = 1; i < vectorSize; i++)
    {
        int dif = levels[i-1] - levels[i];
        if(abs(dif) > 3 || dif == 0){
            return false;
        }
        dif_vector.push_back(dif);
    }
    return same_sign(dif_vector); 
}

int main() {
    ifstream inFile("input.txt");
    std::string entry;
    int safe_counter = 0;

    while (std::getline(inFile, entry)) {
        std::istringstream iss(entry);
        vector<int> numbers;

        while(std::getline(iss, number, ' ')){
            numbers.push_back(stoi(number));
        }
        safe_counter += safe_report(numbers);
    }

    cout << "Amount of safe reports: " << safe_counter << "\n";
    
    return 0;
}