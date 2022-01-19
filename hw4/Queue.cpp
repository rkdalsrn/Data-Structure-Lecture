#include "Queue.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Queue::Queue(void)
{
	capacity = 3;
	start = 2;
	top = 0;
	size = 0;
	Queue_array = (Node *)malloc(sizeof(Node)*capacity);
}


Queue::~Queue(void)
{
	/* TO DO*/
	//Prevents memory leak
    free(Queue_array);
}



void Queue::push(int row, int col, int parent_row, int parent_col)
{
	/* TO DO*/
	//push Node(row, col. parent_row, parent_col) to Queue.
	//size check (for resize)
	//push node
	//top and size will be change
    if(size == capacity){
        resize();
    }
    Queue_array[top] = Node(row, col, parent_row, parent_col);
    size++;
    if(top == capacity-1){
        top = 0;
    }
    else top++;
}

Node Queue::head_node()
{
	/* TO DO*/
	//if there is Node in queue,
	//return the first inserted Node
	// else
	//return Node(-1,-1,-1,-1)
    if(size > 0){
        if(start+1 == capacity) return Queue_array[0];
        else return Queue_array[start+1];
    }
    else{
        return Node(-1,-1,-1,-1);
    }
}

void Queue::pop()
{
	/* TO DO*/
	//if there is Node in queue,
	// change the size and start
	// you don`t need to initialize the head_node
    if(size > 0){
        if(start+1 == capacity){
            start = 0;
        }
        else{
            start++;
        }
        size--;
    }
    else{
    }
}

void Queue::resize()
{
	/* TO DO*/
	//when push function called but there is no space in Queue
	//resize the Queue, from ( capacity ) to ( capacity * 2 )
	//Memory allocation and deallocation processes are required.
	//You must copy the nodes from the original memory allocation to the new memory allocation.
	//start, top, capacity, Queue_array will be change
    Node* temp;
    temp = (Node *)malloc(sizeof(Node) * 2 * capacity);
    for (int i = 0; i < top; i++) {
        temp[i] = Queue_array[i];
    }
    for (int i = top + capacity; i < 2 * capacity; i++) {
        temp[i] = Queue_array[i - capacity];
    }
    start = start + capacity;
    free(Queue_array);
    Queue_array = temp;
    temp = NULL;
    capacity = 2 * capacity;
}

void Queue::print()
{
	for (int i = 0; i < size; i++)
	{
		Queue_array[(start+1+i)%capacity].print();
		cout << " ";
	}
	cout << '\n';
}
