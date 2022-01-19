#include "Stack.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Stack::Stack(void)
{
	capacity = 3;
	start = 2;
	top = 0;
	size = 0;
	Stack_array = (Node *)malloc(sizeof(Node)*capacity);
}

Stack::~Stack(void)
{
	/* TO DO*/
	//Prevents memory leak
    free(Stack_array);
}

void Stack::push(int row, int col, int parent_row, int parent_col)
{
	/* TO DO*/
	//push Node(row, col. parent_row, parent_col) to Stack
	//size check (for resize)
	//push node
	//top and size will be change
    if(size == capacity){
        resize();
    }
    Stack_array[top] = Node(row, col, parent_row, parent_col);
    size++;
    if(top == capacity-1){
        top = 0;
    }
    else top++;
    
}

Node Stack::top_node()
{
	/* TO DO*/
	//if there is Node in stack,
	//return the last inserted Node
	// else
	//return Node(-1,-1,-1,-1)
    if(size > 0){
        if(top == 0){
            return Stack_array[capacity-1];
        }
        else return Stack_array[top-1];
    }
    else{
        return Node(-1,-1,-1,-1);
    }
}

void Stack::pop()
{
	/* TO DO*/
	//if there is Node in stack,
	// change the size and top
	// you don`t need to initialize the top_node
    if(size > 0){
        if(top == 0){
            top = capacity-1;
        }
        else{
            top--;
        }
        size--;
    }
    else return;
}

void Stack::resize()
{
	/* TO DO*/
	//when push function called but there is no space in Stack
	//resize the Stack, from ( capacity ) to ( capacity * 2 )
	//Memory allocation and deallocation processes are required.
	//You must copy the nodes from the original memory allocation to the new memory allocation.
	//start, top, capacity, Queue_array will be change
    Node* temp;
    temp = (Node *)malloc(sizeof(Node) * 2 * capacity);
    for (int i = 0; i < top; i++) {
        temp[i] = Stack_array[i];
    }
    for (int j = top + capacity; j < 2 * capacity; j++) {
        temp[j] = Stack_array[j - capacity];
    }
    start = start + capacity;
    free(Stack_array);
    Stack_array = temp;
    temp = NULL;
    capacity = 2 * capacity;
}

void Stack::print() 
{
	for (int i = 0; i < size; i++)
	{
		Stack_array[i].print();
		cout << " ";
	}
	cout << '\n';
}
