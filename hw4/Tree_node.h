#pragma once
#include "Node.h"
class Tree_node
{
public:
	Node node_information;
	Tree_node * parent;
	Tree_node * child1;
	Tree_node * child2;
	Tree_node * child3;
	Tree_node();
	Tree_node(int row_, int col_, int parent_row_, int parent_col_);
	~Tree_node(void);
	void make_child(Tree_node * child);
	void print();
	void delete_node_with_descendent();
	Tree_node * find_descendent(int row_, int col_);
};