#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

void add_and_mults(vector<unsigned long long> input, vector<unsigned long long>& result_vector){
  if(input.size() == 1){
    result_vector.push_back(input[0]);
    return;
  }

  vector<unsigned long long> add_path = input;
  vector<unsigned long long> mul_path = input;

  add_path[1] = add_path[0] + add_path[1];
  add_path.erase(add_path.begin());
  add_and_mults(add_path, result_vector);

  mul_path[1] = mul_path[0] * mul_path[1];
  mul_path.erase(mul_path.begin());
  add_and_mults(mul_path, result_vector);
}


bool valid_test_value(unsigned long long outcome, vector<unsigned long long> input){
  vector<unsigned long long> all_outcomes;

  add_and_mults(input, all_outcomes);

  for (auto value:all_outcomes)
  {
    if(outcome == value){ 
      return true;
    }
  }
  return false;
}

int main(){
    //parse the input
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
        
        if(valid_test_value(outcome, test_input)){
          total_calibration_result += outcome;
        }
    }

    cout << "The total calibration result is: " << total_calibration_result;
}
