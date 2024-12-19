#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

unsigned long long concat(unsigned long long a, unsigned long long b) 
{ 
    string s = to_string(a) + to_string(b); 
    return stoull(s); 
} 

bool test_conc_add_and_mults(vector<unsigned long long> input, unsigned long long stop_at){
  if(input.size() == 1){
    return input[0] == stop_at;
  }

  vector<unsigned long long> add_path = input;
  vector<unsigned long long> mul_path = input;
  vector<unsigned long long> conc_path = input;

  
  add_path[1] = add_path[0] + add_path[1];
  add_path.erase(add_path.begin());

  if(!test_conc_add_and_mults(add_path, stop_at)){
    mul_path[1] = mul_path[0] * mul_path[1];
    mul_path.erase(mul_path.begin());
    if(!test_conc_add_and_mults(mul_path, stop_at)){
        conc_path[1] = concat(conc_path[0], conc_path[1]);
        conc_path.erase(conc_path.begin());
        return test_conc_add_and_mults(conc_path, stop_at);
    }
  }
  return true;
}

int main(){
    ifstream inFile("input.txt");
    string entry;
    regex pattern(R"([0-9]+)");
    unsigned long long total_calibration_result = 0;

    while (std::getline(inFile, entry)) {
        string s = entry.c_str();
        smatch m;
        vector<unsigned long long> input_numbers;
        while(std::regex_search(s, m, pattern)) {
            unsigned long long num = stoull(m[0]);
            s = m.suffix();
            input_numbers.push_back(num);
        }
        unsigned long long outcome = input_numbers[0];
        vector<unsigned long long> test_input(input_numbers.begin() + 1, input_numbers.end());
        
        if(test_conc_add_and_mults(test_input, outcome)){
          total_calibration_result += outcome;
        }
    }

    cout << "The total calibration result is: " << total_calibration_result;
}
