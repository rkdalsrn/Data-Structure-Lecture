#pragma once
#include "Node.h"
class ArrayList
{
public:
	int capacity;
	int size;
	Node * array;
	ArrayList();
	~ArrayList();
	void push(int value_);
	Node i_th_node(int index);
	int i_th_node_value(int index);
	void resize();
	void print();
};
