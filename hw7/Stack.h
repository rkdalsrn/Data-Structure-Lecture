#pragma once
#include "Node.h"
class Stack
{
public:
	
	int capacity;
	int top;
	Node * Stack_array;

	Stack();
	~Stack();

	void push(int value_);
	Node top_node();
	int top_value();
	void pop();
	void resize();
	void print();
	bool empty();
};

