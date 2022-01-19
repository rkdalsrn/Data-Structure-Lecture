#include <iostream>
#include <fstream>
#include "Stack.h"
#include "StackSolver.h"

using namespace std;

StackSolver::StackSolver(void)
{
	size = 0;
}

StackSolver::~StackSolver(void)
{
	for (int i = 0; i < size; i++)
		free(maze[i]);
	free(maze);
}

void StackSolver::readInput(char* inputfile){
	ifstream file(inputfile);
	char ch;
	while (true){
		file.get(ch);
		size++;
		if (ch == '\n') break;
	}
	file.seekg(0, file.beg);

	maze = (int **)malloc(sizeof(int*)*size);
	for (int i = 0; i < size; i++){
		maze[i] = (int*)malloc(sizeof(int)*size);
	}

	int row = 0;
	int col = 0;
	while (!file.eof())
	{
		file.get(ch);
		if (ch == '\n'){
			row++;
			col = 0;
		}
		else if (ch == ' '){
			maze[row][col] = 0;
			col++;
		}
		else if (ch == '#')
		{
			maze[row][col] = 1;
			col++;
		}
	}
	file.close();
}


void StackSolver::solve(char* outputfile){

	Stack solver;
	int row = 1;
	int col = 1;
	Tree_node temp;

	solver.push(row, col, -1, -1);
	temp = Tree_node(row, col, -1, -1);
	stack_tree.insert_node(&temp);

	while (row != size - 3 || col != size - 3)
	{
		if (maze[row][col] == 0)
		{
			maze[row][col] = 2;
			solver.pop();
			if (maze[row][col - 1] == 0)
			{
				solver.push(row, col - 1, row, col);
			}
			if (maze[row - 1][col] == 0)
			{
				solver.push(row - 1, col, row, col);
			}
			if (maze[row][col + 1] == 0)
			{
				solver.push(row, col + 1, row, col);
			}
			if (maze[row + 1][col] == 0)
			{
				solver.push(row + 1, col, row, col);
			}
		}
		row = solver.top_node().row;
		col = solver.top_node().col;
		temp = Tree_node(solver.top_node().row, solver.top_node().col, solver.top_node().parent_row, solver.top_node().parent_col);
		stack_tree.insert_node(&temp);
	}
	maze[row][col] = 2;
	stack_tree.make_file_leaf_to_top(stack_tree.find_node(size - 3, size - 3), outputfile);

}
