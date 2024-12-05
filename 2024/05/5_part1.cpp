#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// find which values max input, return vector of indices
vector<int> match(string value, vector<string> lookup) {
    vector<int> indices = {};
    for (int i = 0; i < lookup.size(); i++)
    {
        if (value == lookup[i]) indices.push_back(i);
    }
    return(indices);
}

int main() {
    ifstream inFile("input.txt");
    string entry;
    string text_number;
    vector<string> sort_order_1;
    vector<string> sort_order_2;
    char order_delim('|');
    char input_page_delim(',');
    vector<vector<string>> all_input_pages;
    int n_ordered_inputs = 0;
    int sum_of_middle_numbers = 0;

    while (getline(inFile, entry)) {
        string s = entry.c_str();
        stringstream entry_row(entry);

        //parse for sorting orders
        if(s.find(order_delim) < s.length())
        {
            vector<string> sorting_numbers;
            while(getline(entry_row, text_number, order_delim)){
                sorting_numbers.push_back(text_number);
            }
            sort_order_1.push_back(sorting_numbers[0]);
            sort_order_2.push_back(sorting_numbers[1]);
        }

        //parse for input pages
        if(s.find(input_page_delim) < s.length())
        {
            vector<string> input_pages;
            while(getline(entry_row, text_number, input_page_delim)){
                input_pages.push_back(text_number);
            }
            all_input_pages.push_back(input_pages);

        }
    } 

    //for all inputs containging page numbers
    for (auto input_pages:all_input_pages)
    {
        vector<int> applicable_sort_order_1;
        vector<int> applicable_sort_order_2;
        int n_pages = input_pages.size();
        bool pages_ordered = true;

        //for each pagenumber
        for (int i = 0; i < n_pages; i ++)
        {

            applicable_sort_order_1 = match(input_pages[i], sort_order_1);
            applicable_sort_order_2 = match(input_pages[i], sort_order_2);

            for  (auto rule1 : applicable_sort_order_1) // for each before-rule
            {
                for (size_t j = 0; j < i; j++) //look back
                {
                    if(input_pages[j] == sort_order_2[rule1]){
                        pages_ordered = false;
                        break;
                    }
                }                
            }

            for  (auto rule2 : applicable_sort_order_2) // for each after-rule
            {
                for (size_t j = i+1; j < n_pages; j++) //look forward
                {
                    if(input_pages[j] == sort_order_1[rule2]){
                        pages_ordered = false;
                        break;
                    }
                }                
            }
        }       

        if(pages_ordered){
            n_ordered_inputs ++;
            sum_of_middle_numbers += atoi(input_pages[n_pages/2].c_str());
        }

    }

    cout << "Total amount of ordered inputs: " << n_ordered_inputs << endl;
    cout << "The sum of middle numbers of the correct inputs is: " << sum_of_middle_numbers << endl;
    
}
