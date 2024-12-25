#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct stock_sequence{
    public:
        vector<int> prices;
        vector<int> diffs;
};

long long take_secret_step(int x){
    long long secret_x = x;
    secret_x = ((secret_x * 64) ^ x) % 16777216;
    secret_x = ((secret_x / 32) ^ secret_x) % 16777216;
    secret_x = ((secret_x*2048) ^ secret_x) % 16777216;
    return secret_x;
}

int bananas_bought(vector<int> diff_sequence, stock_sequence seq){
    for(int i = 4; i<seq.prices.size(); i++){
        if (seq.diffs[i-3] == diff_sequence[0] &&
            seq.diffs[i-2] == diff_sequence[1] &&
            seq.diffs[i-1] == diff_sequence[2] &&
            seq.diffs[i-0] == diff_sequence[3])
        {
            return seq.prices[i];
        }  
    }
    // nothing sold
    return 0;
}

int main(){
    fstream input("input.txt");
    string entry;
    int n_secrets = 2000;
    long long sum_of_secrets = 0;

    vector<stock_sequence> all_stock_seqs;
    while(getline(input, entry)){
        long long input_num = stoi(entry);
        stock_sequence seq;
        seq.prices.push_back(input_num%10);
        seq.diffs.push_back(11);
        //calculate prices
        for(int i = 0; i < n_secrets; i++) {
            input_num = take_secret_step(input_num);
            seq.prices.push_back(input_num % 10);
        }
        //calculate diffs
        for(int i = 1; i < n_secrets; i++){
            seq.diffs.push_back(seq.prices[i] - seq.prices[i-1]);
        }
        all_stock_seqs.push_back(seq);
    }

    
    int banana_counter;
    int most_bought = 0;
    vector<int> best_sequence;

    for(int i1 = -9; i1 < 10; i1++){
        for(int i2 = -9; i2 < 10; i2++){
            for(int i3 = -9; i3 < 10; i3++){
                for(int i4 = -9; i4 < 10; i4++){
                    banana_counter = 0;
                    for(auto seq:all_stock_seqs){
                        banana_counter += bananas_bought({i1, i2, i3, i4}, seq);
                    }
                    if(most_bought < banana_counter){
                        best_sequence = {i1, i2, i3, i4};
                        most_bought = banana_counter;
                    }                
                }
            }
        }
    }
    
    for(auto num:best_sequence){
        cout << num << " ";
    }
    cout << endl << "The highest amount of bananas bought is: " << most_bought << endl;
}