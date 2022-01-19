#pragma once
class Node
{
public:
	int row;
	int col;
	int parent_row;
	int parent_col;
	Node();
	Node(int row_, int col_, int parent_row_, int parent_col_);
	~Node(void);
	void print();
};
