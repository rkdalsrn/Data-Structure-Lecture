#include "Node.h"
#include <iostream>

using namespace std;

Node::Node()
{
	row = -1;
	col = -1;
	parent_row = -1;
	parent_col = -1;
}

Node::Node(int row_, int col_, int parent_row_, int parent_col_)
{
	row = row_;
	col = col_;
	parent_row = parent_row_;
	parent_col = parent_col_;
}

Node::~Node(void)
{
}

void Node::print()
{
	cout << "(" << row << ", " << col << ")";
}
