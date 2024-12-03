#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <istream>
#include <string>
#include <algorithm>

using namespace std;

vector<long> vector1;
vector<long> vector2;
long sum = 0;

string first_num;
string second_num;

int main()
{
    ifstream inFile ("input.txt");
    string entry;

    while (getline(inFile, entry))
    {
        istringstream iss(entry);

        getline(iss, first_num, ' ');
        getline(iss, second_num, '\t');
        
        vector1.push_back(atoi(first_num.c_str()));
        vector2.push_back(atoi(second_num.c_str()));

    }

    sort(vector1.begin(), vector1.end());
    sort(vector2.begin(), vector2.end());

    int vecSize = vector1.size();

    for (int i = 0; i < vecSize; ++i)
    {
        sum += abs(vector1[i] - vector2[i]);
    }

    cout << "The sum of distances is: " << sum << "\n";
    return(0);
}