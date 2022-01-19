#include "Table.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]){
    
    // Create table with table name
    Table* newTable = new Table("airPollution");
    // Setting schema with first line of raw-data
    //
    while(1){
        string col_name;
        string col_type;
        cout << "Column name : ";
        cin >> col_name;
        cout << "Column type : ";
        cin >> col_type;
        if(col_name.compare("!stop") == 0 && col_type.compare("!stop") == 0){
            cout << "..." << endl;
            break;
        }
        else{
            newTable->set_table_schema(col_name, col_type);
        }
    }
    
    // Load data on the created table
    // Read raw data
    ifstream raw_data;
    raw_data.open(argv[1], ifstream::in);
    //raw_data.open("test_dataset.csv",ifstream::in);
    newTable->load_data(raw_data);
    newTable->scan_table();
    
    int sel_index;
    string sel_name;
    string sel_value;
    cout << "Searching column name: ";
    cin >> sel_name;
    cout << "Searching value: ";
    cin >> sel_value;
    cout << "..." << endl;
    sel_index = newTable->get_table_schema()->get_col_index(sel_name);
    newTable->select_row(sel_index, &sel_value);
    
    
    return 0;
}
