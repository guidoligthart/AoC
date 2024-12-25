#include <map>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

long long take_secret_step(int x){
    long long secret_x = x;
    secret_x = ((secret_x * 64) ^ x) % 16777216;
    secret_x = ((secret_x / 32) ^ secret_x) % 16777216;
    secret_x = ((secret_x*2048) ^ secret_x) % 16777216;
    return secret_x;
}

int main(){
    fstream input("input.txt");
    string entry;
    int n_secrets = 2000;
    long long sum_of_secrets = 0;
    while(getline(input, entry)){
        long long input_num = stoi(entry);
        for(int i = 0; i < n_secrets; i++) input_num = take_secret_step(input_num);
        sum_of_secrets += input_num;
    }
    cout << "The sum of secret numbers is: " << sum_of_secrets << endl;
}