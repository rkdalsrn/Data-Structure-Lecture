#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

class Schema{
    private :
    //private member variables
    vector<string> col_name_list;
    vector<string> col_type_list;
    string table_name;
    int num_rows;
    public :
    //constructor & destructor
    Schema(string table_name);
    //public member funcitons
    void set_col_list(string col_name, string col_type);
    void count_rows_up();
    int get_num_rows();
    int get_num_cols();
    int get_col_index(string col_name);
};

Schema::Schema(string table_name){
    this->table_name = table_name;
    num_rows = 0;
}

void Schema::set_col_list(string col_name, string col_type){
    col_name_list.push_back(col_name);
    col_type_list.push_back(col_type);
}

void Schema::count_rows_up(){
    ++num_rows;
}

int Schema::get_num_rows(){
    return num_rows;
}

int Schema::get_num_cols(){
    return col_name_list.size();
}

int Schema::get_col_index(string col_name){
    // TODO
    // Using vector iterator, return column index by column name
    // An index counts from 0
    int index = 0;
    for (vector<string>::iterator it = col_name_list.begin(); it != col_name_list.end(); it++, index++)
        if ((*it) == col_name)
            return index;
    return 0;
}

