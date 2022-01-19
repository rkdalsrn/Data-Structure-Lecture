#include <iostream>
#include <list>
using namespace std;

template <typename T>
class Field{
    private :
    int col_index;
    string type_name;
    T value;
    public :
    Field(int col_index, string type_name, T value);
    T get_value();
};

template <typename T>
Field<T>::Field(int col_index, string type_name, T value){
    this->col_index = col_index;
    this->type_name = type_name;
    this->value = value;
}

template <typename T>
T Field<T>::get_value(){
    return value;
}

class Row{
    private :
    vector<void*> field_list;
    public :
    void add_field(void* field);
    vector<void*> get_field_list();
};

void Row::add_field(void* field){
    field_list.push_back(field);
}

vector<void*> Row::get_field_list(){
    return field_list;
}
