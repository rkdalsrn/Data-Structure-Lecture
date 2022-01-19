#include <iostream>
#include <string>
#include "ArrayList.h"
#include "Stack.h"

using namespace std;

class Graph {
    int V; // # of vertex
    ArrayList * adj; // V vertexes` adjacent array
    void fillOrder(int v, bool visited[],  Stack & s); 
    string DFSUtil(int v, bool visited[]); 
public: 
    Graph(int V); 
    ~Graph();
    void addEdge(int v, int w); 
    void printSCCs(); 
    Graph getTranspose(); 
    void change_PageRank(float damping_factor, int iteration);
    void one_array_format(int start_vertex, int end_vertex);
}; 

