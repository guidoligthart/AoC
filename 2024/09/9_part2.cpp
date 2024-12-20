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

int get_size(vector<string>& disc, int i){
    int size = 0;
    string current_value = disc[i];

    while (disc[i] == current_value)
    {
        size++;
        i++;
    }
    return(size);
}

int main(){
    //parse the map
    ifstream inFile(R"(input.txt)");
    string entry;
    vector<int> disc_map;
    vector<string> file_ids;
    long long check_sum = 0;
    int file_id_counter = 0;
    while (getline(inFile, entry))
    {
        vector<int> map_row;
        string s = entry.c_str();
        for (auto c:s)
        {
            disc_map.push_back(c - '0');
            if((file_id_counter % 2) == 0){
                file_ids.push_back(to_string(file_id_counter/2));
            } else {
                file_ids.push_back(".");
            }
            file_id_counter++;
        }
    }
    //rearrange disc_map
    string char_to_add;
    for(int i = disc_map.size() - 1; i >= 0; i--)
    {
        if(file_ids[i] != "."){
            //try and fit in an empty spot
            int required_space = disc_map[i];
            for(int j = 0; j < i; j++)
            {
                if(file_ids[j] == "."){
                    //if enough space
                    if(disc_map[j] >= required_space)
                    {
                        //move around
                        int left_over_space = disc_map[j] - required_space;
                        disc_map[j] = disc_map[i];
                        file_ids[j] = file_ids[i];
                        file_ids[i] = ".";

                        disc_map.insert(disc_map.begin() + j + 1, left_over_space);
                        file_ids.insert(file_ids.begin() + j + 1, ".");
                        break;
                        //reset i
                        i = disc_map.size();
                    }
                }
            }
        }        
    }

    //construct disc
    vector<int> disc;
    for (int i = 0; i < disc_map.size(); i++)
    {
        if(file_ids[i] == "."){
                file_ids[i] = "0";
            }
        for(int j = 0; j < disc_map[i]; j++){
            disc.push_back(stoi(file_ids[i]));
        }
    }

    for (int i = 0; i < disc.size(); i++)
    {
        
        check_sum += (i * disc[i]);
    }
    
    cout << endl << "Filesystem checksum: " << check_sum;
}
