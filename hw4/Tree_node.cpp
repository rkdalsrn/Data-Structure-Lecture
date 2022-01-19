#include "Tree_node.h"
#include <iostream>

using namespace std;

Tree_node::Tree_node()
{
	node_information = Node(-1, -1, -1, -1);
	parent = NULL;
	child1 = NULL;
	child2 = NULL;
	child3 = NULL;
}

Tree_node::Tree_node(int row_, int col_, int parent_row_, int parent_col_)
{
	node_information = Node(row_, col_, parent_row_, parent_col_);
	parent = NULL;
	child1 = NULL;
	child2 = NULL;
	child3 = NULL;
}

Tree_node::~Tree_node(void)
{
}

void Tree_node::print()
{
	cout << "(" << node_information.row << ", " << node_information.col << ")";
}

void Tree_node::make_child(Tree_node * child)
{
	if (child1 == NULL)
	{
		child1 = child;
		child->parent = this;
		return;
	}
	if (child2 == NULL)
	{
		child2 = child;
		child->parent = this;
		return;
	}
	if (child3 == NULL)
	{
		child3 = child;
		child->parent = this;
		return;
	}
}

void Tree_node::delete_node_with_descendent()
{
	/* TO DO*/
	//Performs memery deallocation on each child and then deallocate this Tree_node
    if (this->child1 != NULL) {
        this->child1->delete_node_with_descendent();
    }
    if (this->child2 != NULL) {
        this->child2->delete_node_with_descendent();
    }
    if (this->child3 != NULL) {
        this->child3->delete_node_with_descendent();
    }
    free(this);
}

Tree_node * Tree_node::find_descendent(int row_, int col_)
{
	Tree_node * answer1 = NULL;
	Tree_node * answer2 = NULL;
	Tree_node * answer3 = NULL;
	if (node_information.row == row_ && node_information.col == col_)
		return this;
	else
	{
		if (child1 == NULL && child2 == NULL && child3 == NULL)
			return NULL;
		if (child1 != NULL)
			answer1 = child1->find_descendent(row_, col_);
		if (child2 != NULL)
			answer2 = child2->find_descendent(row_, col_);
		if (child3 != NULL)
			answer3 = child3->find_descendent(row_, col_);
		if (answer1 != NULL)
			return answer1;
		if (answer2 != NULL)
			return answer2;
		if (answer3 != NULL)
			return answer3;
		return NULL;
	}
}
