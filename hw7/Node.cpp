#include "Node.h"
#include <iostream>

using namespace std;

Node::Node()
{
	value = -1;
}

Node::Node(int value_)
{
	value = value_;
}

Node::~Node(void)
{
}

void Node::print()
{
	cout << value;
}
