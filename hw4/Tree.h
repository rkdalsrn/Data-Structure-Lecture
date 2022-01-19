#pragma once
#include "Tree_node.h"
class Tree
{
public:
	Tree_node * tree_start;
	Tree(void);
	~Tree(void);
	void insert_node(Tree_node * node);
	Tree_node * find_node(int row, int col);
	void make_file_leaf_to_top(Tree_node * leaf_node, char* outputfile);
};
