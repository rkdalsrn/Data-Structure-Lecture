#include <iostream>
#include "SortedList.h"

using namespace std;

int main() {
    SortedList* slist = new SortedList();
    
    //test data generation - 499, 499, 498, 498, ... 0, 0
    int* data = new int[1000];
    for (int i = 0; i < 1000; i++) {
        data[i] = (999 - i) / 2;
    }
    
    //load array to Sorted List
    cout<<"load data..."<<endl;
    slist->load(data, 1000);
    cout<<"load done!"<<endl<<endl;
    
    
    //free memory
    delete[] data;
    data=NULL;
    
    //for debugging
    //slist->printAll();
    
    slist->find(0);
    slist->find(100);
    slist->find(499);
    slist->find(10000); //cannot find
    slist->find(-1); //cannot find
    cout<<slist->retrieve(-1)<<endl; //error: out of range
    
    //insert data - 0, 500, 1, 501, ... 74, 574
    //automatically merge at i = 49
    cout<<endl<<"insert data..."<<endl;
    for (int i = 0; i < 75; i++){
        slist->insert(i);
        slist->insert(500 + i);
    }
    cout<<"insert done!"<<endl<<endl;
    
    slist->find(0);
    slist->find(100);
    slist->find(520);
    slist->find(550);
    slist->find(-1); //cannot find
    
    
    cout<<"delete element at index: 0"<<endl;
    slist->deleteElem(0);
    cout<<"delete element at index: 0"<<endl;
    slist->deleteElem(0); //error: already deleted
    slist->find(0);
    cout<<slist->retrieve(0)<<endl; //error: deleted element
    cout<<"delete element at index: 1"<<endl;
    slist->deleteElem(1);
    slist->find(0);
    cout<<"delete element at index: 2"<<endl;
    slist->deleteElem(2);
    slist->find(0); //cannot find
    cout<<"delete element at index: 1100"<<endl;
    slist->deleteElem(1100); //delete list[1100] = delta_list[0] = 50
    slist->find(550); //index of 550 decreased
    cout<<"delete element at index: 1175"<<endl;
    slist->deleteElem(1175); //error: out of range
    cout<<"delete element at index: -1"<<endl;
    slist->deleteElem(-1); //error: out of range
    
    cout<<endl<<"insert data..."<<endl;
    for(int i = 0; i < 75; i++){
        slist->insert(1000-i);
    }
    cout<<"insert done!"<<endl<<endl;
    cout<<slist->retrieve(1220)<<endl; //last element: 926, because 4 elements were deleted
    cout<<slist->retrieve(1224)<<endl; //error: out of range
    
    delete slist;
    
    return 0;
}

