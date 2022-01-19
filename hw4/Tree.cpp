#include "Tree.h"
#include <iostream>
#include <fstream>

using namespace std;

Tree::Tree(void)
{
	tree_start = NULL;
}

Tree::~Tree(void)
{
	/* TO DO*/
	//deallocate all Tree_node in this tree.
	//Hint : use Tree_node::delete_node_with_descendent()
    tree_start->delete_node_with_descendent();
}

void Tree::insert_node(Tree_node * node)
{
	/* TO DO*/
	//allocate memory for one new Tree_node,
	//and copy the "node" contents to the newly allocated location.
	//and add this new node to the Tree
	//you need to find parent Tree_node
	//and use Tree_node::make_child(Tree_node *) function!
	if (node->node_information.parent_row == -1 && node->node_information.parent_col == -1){
		tree_start = new Tree_node(node->node_information.row, node->node_information.col, -1, -1);
		tree_start->parent = NULL;
		return;
	}
	Tree_node* ming = new Tree_node;
	Tree_node* ming2 = find_node(node->node_information.parent_row, node->node_information.parent_col);
	ming->node_information = Node(node->node_information.row, node->node_information.col, node->node_information.parent_row, node->node_information.parent_col);
	ming->parent = ming2;
	ming2->make_child(ming);
}

Tree_node * Tree::find_node(int row, int col)
{
	/* TO DO*/
	//In tree, find the Tree_node which node_information.row = row_, node_information.col = col_
	//Hint: use Tree_node::find_descendent()
    return tree_start->find_descendent(row, col);
}
	
void Tree::make_file_leaf_to_top(Tree_node * leaf_node, char* outputfile)
{
	/* TO DO*/
	//From input leaf_node(goal) to top Tree_node (tree_start, contain start Node), write the Tree_node information to the file in accordance with the example output form
	//ex ) (end)
	//    (39, 39) <- (39, 38) <- (39, 37) <- (39, 36) <- (39, 35) <-
	//    ....
	//    ....
	//    .... <- (1, 1)
	//              (start)
	// the words "end" and "start" will not be in the output file
    ofstream myfile(outputfile);
    while(leaf_node != tree_start){
        myfile << "(" << leaf_node->node_information.row << ", " << leaf_node->node_information.col << ")";
        myfile << " <- ";
        leaf_node = leaf_node->parent;
    }
    myfile << "(" << leaf_node->node_information.row << ", " << leaf_node->node_information.col << ")";
    /*while(leaf_node != tree_start){
        cout << "(" << leaf_node->node_information.row << ", " << leaf_node->node_information.col << ")";
        cout << " <- ";
        leaf_node = leaf_node->parent;
    }
    cout << "(" << leaf_node->node_information.row << ", " << leaf_node->node_information.col << ")";*/
}
