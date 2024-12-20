#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

vector<unsigned long long> stones;
long multiplier = 2024;

void blink(vector<unsigned long long>& stones){
    for (int i = 0; i < stones.size(); i++)
    {
        if(i < 0){
            throw("Integer overflow");
        }
        if(stones[i] == 0){
            stones[i] = 1;
            continue;
        }

        int n_digits = log10(stones[i]) + 1;
        if((n_digits % 2) == 0){
            //split
            int k_division = round(pow(10, (n_digits/2)));
            int left_digit  = stones[i] / k_division;
            int right_digit = (stones[i] % k_division);
            stones[i] = left_digit;
            i++;
            stones.insert(stones.begin() + i, right_digit);
            continue;
        }
        stones[i] *= multiplier;
    }
    
}


int main(){
    //parse the input
    ifstream inFile(R"(input.txt)");
    string entry;
    while (getline(inFile, entry))
    {
        stringstream entryrow(entry);
        string input_stone;
        while(getline(entryrow, input_stone, ' ')){
            stones.push_back(atoi(input_stone.c_str()));
            cout << input_stone << " ";
        }
    }
   //stones = {125, 17};
   int n_blinks = 75;

   for (int i = 0; i < n_blinks; i++)
   {
        cout << i << endl;
        blink(stones);
   }
   
    cout << endl << "Amount of stones after " << n_blinks << " blink(s): " << stones.size();

}
