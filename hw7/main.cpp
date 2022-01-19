#include <iostream>
#include <sstream>
#include <fstream>
#include "Graph.h"

using namespace std;

int main()
{
    string fileName = "data.txt";
    ifstream openFile(fileName.data());
    int num1;
    int num2;
    float DF = 0.85;
    int iter_num = 10000;
    int vertex_num = 10000;
    Graph g(vertex_num);
    if(openFile.is_open()){
        string line;
        stringstream ss;
        while(getline(openFile, line)){
            ss.str(line);
            ss >> num1;
            ss >> num2;
            g.addEdge(num1, num2);
            ss.clear();
        }
        openFile.close();
    }
    g.printSCCs();
    g.change_PageRank(DF, iter_num);
    g.one_array_format(4, 6);
    return 0;
}
