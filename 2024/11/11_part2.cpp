#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <map>

using namespace std;

map<long long, long long> blink(map<long long, long long> stone_count, long long multiplier = 2024){
    
    map<long long, long long> return_stones;

    for (auto x : stone_count)
    {
        if(x.first < 0){
            throw("Integer overflow");
        }
        if(x.first == 0){
           return_stones[1] += x.second;
           continue;
        }

        int n_digits = log10(x.first) + 1;
        if((n_digits % 2) == 0){
            //split
            long long k_division = round(pow(10, (n_digits/2)));
            long long left_digit  = x.first / k_division;
            long long right_digit = (x.first % k_division);
            return_stones[left_digit] += x.second;
            return_stones[right_digit] += x.second;
            continue;
        }
        return_stones[x.first * multiplier] += x.second;
    }

    return return_stones;
    
}

int main(){
    //parse the input
    ifstream inFile("input.txt");
    string entry;
    map<long long, long long> stone_count;
    while (getline(inFile, entry))
    {
        stringstream entryrow(entry);
        string input_stone;
        while(getline(entryrow, input_stone, ' ')){
            stone_count[atoll(input_stone.c_str())] += 1;
        }
    }

    for (auto x : stone_count)
    {
        cout << x.first << " " << x.second << endl;
    }

    int n_blinks = 75;

    for (int i = 0; i < n_blinks; i++)
    {
        cout << i << endl;
        stone_count = blink(stone_count);
    }
   
    unsigned long long total_stones = 0;

    for (auto x : stone_count){
        total_stones += x.second;
    }

    cout << endl << "Amount of stones after " << n_blinks << " blink(s): " << total_stones;

}
