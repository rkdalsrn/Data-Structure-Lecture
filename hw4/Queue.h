#include "Node.h"

class Queue
{
public:

	int capacity;
	int start;
	int top;
	int size;
	Node * Queue_array;

	Queue();
	~Queue();

	void push(int row, int col, int parent_row, int parent_col);
	Node head_node();
	void pop();
	void resize();
	void print();
};
