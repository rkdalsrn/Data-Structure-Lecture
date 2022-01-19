#include "Node.h"
class Stack
{
public:
	
	int capacity;
	int start;
	int top;
	int size;
	Node * Stack_array;

	Stack();
	~Stack();

	void push(int row, int col, int parent_row, int parent_col);
	Node top_node();
	void pop();
	void resize();
	void print();
};

