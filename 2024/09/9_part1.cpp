#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

void clean_disc(vector<string>& disc){
    while(disc.back() == "."){
        disc.pop_back();
    }
}

int main(){
    //parse the map
    ifstream inFile(R"(input.txt)");
    string entry;
    vector<int> disc_map;
    long long check_sum = 0;
    while (getline(inFile, entry))
    {
        vector<int> map_row;
        string s = entry.c_str();
        for (auto c:s)
        {
            disc_map.push_back(c - '0');    
        }
    }

    //construct disk
    vector<string> disc;
    int file_id = 0;
    string char_to_add;
    for(int i = 0; i < disc_map.size(); i++)
    {
        if((i % 2) == 0){
            char_to_add = to_string(file_id);
            file_id++;
        } else {
            char_to_add = '.';
        }

        for (int j = 0; j < disc_map[i]; j++)
        {
            disc.push_back(char_to_add);
        }
            
    }
 
    int disc_size = disc.size();
    for (int i = 0; i < disc_size; i++)
    {
        clean_disc(disc);
        if(disc[i] == "."){
            disc[i] = disc.back();
            disc.pop_back();
        }
        disc_size = disc.size();
    }

    for (int i = 0; i < disc_size; i++)

    {
        check_sum += (i * stoi(disc[i].c_str()));
    }
    
    cout << "Filesystem checksum: " << check_sum;
}
