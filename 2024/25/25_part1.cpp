#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

struct lock{
    public:
        vector<int> pins;
        int depth = 5;
        int height = 5;
};

struct key{
    public:
        vector<int> keyshape;
};

lock construct_lock(vector<string> lock_string){
    lock return_lock;
    for(int col = 0; col < lock_string[0].size(); col++){
        int col_n = 0;
        for(int row = 1; row < lock_string.size(); row++){
            if(lock_string[row][col] == '#') col_n++; 
        }
        return_lock.pins.push_back(col_n);
    }
    return(return_lock);
}

key construct_key(vector<string> key_string){
    key return_key;
    for(int col = 0; col < key_string[0].size(); col++){
        int col_n = 0;
        for(int row = 0; row < key_string.size() -1; row++){
            if(key_string[row][col] == '#') col_n++; 
        }
        return_key.keyshape.push_back(col_n);
    }
    return(return_key);
}

void print_key(key key){
    for(auto i:key.keyshape){
        cout << i << " ";
    }
    cout << endl;
}
void print_lock(lock lock){
    for(auto i:lock.pins){
        cout << i << " ";
    }
    cout << endl;
}

bool key_matches_lock(key key, lock lock){
    for(int i = 0; i < lock.depth; i++){
        if((key.keyshape[i] + lock.pins[i]) > lock.height) return(false);
    }
    return(true);
}

int main(){
    fstream input("input.txt");
    string entry;

    vector<string> input_item;
    bool make_key, make_lock;
    vector<key> keys;
    vector<lock> locks; 
    while(getline(input, entry)){
        if(entry.size() == 0){
            if(input_item[0][0] == '.')  keys.push_back( construct_key(input_item));
            if(input_item[0][0] == '#') locks.push_back(construct_lock(input_item));
            input_item.clear();
        } else {
            cout << entry << endl;
            input_item.push_back(entry);
        }
    }
    if(input_item[0][0] == '.')  keys.push_back( construct_key(input_item));
    if(input_item[0][0] == '#') locks.push_back(construct_lock(input_item));

    int n_combs = 0;
    for(auto x:keys){
        for(auto y:locks){
            if(key_matches_lock(x, y)) n_combs++;
        }
    }

    cout << "The total amount of unique combinations is: " << n_combs;

}