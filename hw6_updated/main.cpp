#include <iostream>
#include <time.h>
#include "Inv_index.h"

using namespace std;

int main() {
    Inv_index* ii = new Inv_index();
    
    ii->construct("./data.txt"); //Put data.txt and codes in same directory 
    int searchResult = -1;
    
    clock_t begin, end;
    
    ////////Start running time measurement
    //This test scenario will take within 1 second,
    // so I will execute more functions with bigger dataset
    // when evaluate your codes
    begin = clock();
        
    searchResult = ii->print_single("cat", 10);
    cout<<endl<<searchResult<<" document(s) found!"<<endl;
    
    searchResult = ii->print_single("happy", 10);
    cout<<endl<<searchResult<<" document(s) found!"<<endl;

    searchResult = ii->print_double("cat", "happy", 10);
    cout<<endl<<searchResult<<" document(s) found!"<<endl;
    
    searchResult = ii->print_double("dog", "happy", 10);
    cout<<endl<<searchResult<<" document(s) found!"<<endl;
    
    searchResult = ii->print_double("win", "happy", 10);
    cout<<endl<<searchResult<<" document(s) found!"<<endl;
    
    searchResult = ii->print_double("money", "happy", 10);
    cout<<endl<<searchResult<<" document(s) found!"<<endl;
    
    searchResult = ii->print_double("earn", "happy", 10);
    cout<<endl<<searchResult<<" document(s) found!"<<endl;
    
    searchResult = ii->print_double("family", "happy", 10);
    cout<<endl<<searchResult<<" document(s) found!"<<endl;
    
    end = clock();
    ////////End running time measurement
    cout<<"Running time: "<<(float(end - begin))/(CLOCKS_PER_SEC)<<" seconds"<<endl;

    delete ii;

    return 0;
}
