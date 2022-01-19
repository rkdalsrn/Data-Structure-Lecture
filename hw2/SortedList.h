#include <iostream>
#include <algorithm>

using namespace std;

class SortedList
{
public:
    SortedList(); //TODO
    ~SortedList(); //TODO
    
    void load(int* data, int size);
    int retrieve(int index); //TODO
    void find(int x); //TODO
    void insert(int x); //TODO
    void deleteElem(int index); //TODO
    void printAll(); //for debugging
    
private:
    void sort_main();
    int binarySearch(int* arr, int left, int right, int x);
    int seqSearch(int* arr, int range, int x); //TODO
    void merge();
    int* main_list;
    int* delta_list;
    bool* isDeleted; //bit vector holds deletion flags
    int mList_size; //size of main_list
    int dList_size = 100; //fixed max size
    int lastPos; //holds last position of delta_list.
    int numElements; //holds the number of undeleted elements
};

//Constructor
SortedList::SortedList()
{
    //------------TODO------------//
    //Initialize delta_list, lastPos, numElements
    delta_list = new int[dList_size];
    lastPos = -1;
    numElements = 0;
}

//Destructor
SortedList::~SortedList() /////////
{
    //------------TODO------------//
    //Free arrays
    delete[] delta_list;
    delta_list = NULL;
}

//Load data from input array
//Sort main_list after input process
void SortedList::load(int* data, int size)
{
    main_list = new int[size];
    mList_size = size;
    isDeleted = new bool[mList_size];
    for (int i = 0; i < size; i++) {
        main_list[i] = data[i];
        isDeleted[i] = false;
        numElements++;
    }
    sort_main();
}

int SortedList::retrieve(int index)
{
    //------------TODO------------//
    //Return data from certain index
    //Hint1: range check!!
    //Hint2: index is continuous at the end of main list & the begin of delta list
    if((index >= 0) && (index < mList_size)){
        if(isDeleted[index] == false){
            return main_list[index];
        }
        else{
            cout<<"error: deleted element!"<<endl;
            return -1;
        }
    }
    else if((index < mList_size + lastPos + 1) && (index >= mList_size)){
        return delta_list[index-mList_size];
    }
    else{
        cout<<"error: out of range!"<<endl;
        return -1;
    }
}

//Find first undeleted element in main_list & delta_list.
void SortedList::find(int x) ////////////////////think
{
    //------------TODO------------//
    //find x in main_list(Binary search)
    //find x in delta_list(Sequential search)
    //If found, print message:
    ////cout<<"Index of "<<x<<" is: "<<[some_index]<<endl;
    //If not found, print message:
    ////cout<<"Value "<<x<<" is not found"<<endl;
    
    //Hint1: check isDeleted array
    //Hint2: Because there are duplicated elements in main_list, so check next element if isDeleted[index] is true
    int ming = 0;
    bool ming2 = true;
    while(ming2){
        if(binarySearch(main_list, ming, mList_size-1, x) == -1){
            ming2 = false;
            break;
        }
        ming = binarySearch(main_list, ming, mList_size-1, x);
        if(isDeleted[ming] == false){
            cout<<"Index of "<< x <<" is: "<< ming <<endl;
            return;
        }
        else{
            ming++;
        }
    }
    if(seqSearch(delta_list, lastPos+1, x) != -1){
        cout<<"Index of "<<x<<" is: "<<seqSearch(delta_list, lastPos+1, x) + mList_size<<endl;
        return;
    }
    else{
        cout<<"Value "<<x<<" is not found"<<endl;
        return;
    }
}

//Insert to delta_list
//If delta_list is full, merge main_list & delta_list.
//And then insert to delta_list
void SortedList::insert(int x)
{
    //------------TODO------------//
    //Implement insert function
    //Hint: manage some member vatiables
    if(lastPos == dList_size - 1){
        merge();
    }
    delta_list[lastPos+1] = x;
    numElements++;
    lastPos++;
}

//If index is in the range of main_list, not actually deletes data.
//If index is in the range of delta_list, delete data
void SortedList::deleteElem(int index)
{
    if(index < 0){
        cout<<"error:out of range!"<<endl;
    }
    else if(index < mList_size){ //if index is in the range of main_list
        if(isDeleted[index]){
            cout<<"error: already deleted!"<<endl;
        }
        else {
            isDeleted[index] = true; //late-deletion
            numElements--;
        }
    }
    else if(index <= mList_size + lastPos){
        //------------TODO------------//
        //Implement delta_list data deletion
        //----------------------------//
        for(int i = index - mList_size; i <= lastPos; i++){
            if(index == mList_size + lastPos){
                delta_list[i] = -1;
                numElements--;
                lastPos--;
                return;
            }
            else{
                delta_list[i] = delta_list[i+1];
            }
        }
        numElements--;
        lastPos--;
    }
    else {
        cout<<"error: out of range!"<<endl;
    }
}

//print undeleted elements in whole lists
void SortedList::printAll()
{
    for(int i = 0; i < mList_size; i++){ //print elements in main_list
        if(!isDeleted[i]){
            cout<<retrieve(i)<<endl;
        }
    }
    
    for(int j = 0; j <= lastPos; j++){ //print elements in delta_list
        cout<<retrieve(j + mList_size)<<endl;
    }
}

//Sort main_list
//Only call sort_main() at load() and merge() to maintain order of isDeleted array
void SortedList::sort_main()
{
    sort(main_list, main_list + mList_size);
}

//Binary search algorithm (for sorted list)
//Return leftmost element index
//If not found, return -1
int SortedList::binarySearch(int* arr, int left, int right, int x)
{
    int mid = (left + right) / 2;
    if(arr[left] == x){
        return left;
    }
    else if(right == left + 1){
        if(arr[right] == x){
            return right;
        }
        else {
            return -1;
        }
    }
    else if(arr[mid] >= x){
        return binarySearch(arr, left, mid, x);
    }
    else {
        return binarySearch(arr, mid, right, x);
    }
}

//Sequential search algorithm (for unsorted list)
//Return leftmost element index
//If not found, return -1 (different from lecture notes)
int SortedList::seqSearch(int* arr, int range, int x)
{
    //------------TODO------------//
    //Implement sequential find algorithm
    for(int i = 0; i < range; i++){
        if(delta_list[i] == x){
            return i;
        }
    }
    return -1;
}

//Merge delta_list to main_list
//And initialize delta_list and isDeleted array
//Note that change in member variables after merge()
void SortedList::merge()
{
    cout<<"Merging lists..."<<endl;
    int* temp1 = main_list;
    bool* temp2 = isDeleted;
    int* newL = new int[numElements];
    int index = 0;
    
    for(int i = 0; i < mList_size; i++){
        if(!isDeleted[i]){
            newL[index] = main_list[i]; //merge only undeleted elements
            index++;
        }
    }
    for(int j = 0; j <= lastPos; j++){
        newL[index] = delta_list[j]; //merge delta_list
        index++;
    }
    
    delete[] temp1;
    delete[] temp2;
    
    mList_size = numElements; //Note: mList_size changed
    main_list = newL; //change main_list to new merged list
    sort_main(); //sort main_list after merge
    
    for(int k = 0; k < dList_size; k++){
        delta_list[k] = -1; //initialize delta_list
    }
    lastPos = -1; //Note: lastPos changed
    
    bool* deltemp = new bool[mList_size]; //to change the size of isDeleted array
    for(int l = 0; l < mList_size; l++){
        deltemp[l] = false; //initialize bit vector
    }
    isDeleted = deltemp;
    cout<<"Merge done!"<<endl;
}


