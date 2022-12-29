#ifndef _GRAPH_H
#define _GRAPH_h
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <list>
using namespace std;

struct node
{
    int data=0;
    int capacity=0;
    int flow = 0;
    struct node* link=NULL;
};
struct node* NewNode(int value, int capacity)
{
    struct node* newnode = new node;
    newnode->data = value;
    newnode->capacity = capacity;
    newnode->link = NULL;

    return newnode;
}
struct vertexlist
{
    struct node* vlisthead = nullptr;
    struct node* vlisttail = nullptr;
};
class Graph
{
public:
    int v;
    struct vertexlist* vl;

    Graph(int n)
    {
        int i=0;
        this->v = n+1;
        // declare a list for n vertex.
        this->vl = new vertexlist[n + 1];
        // Assign the head to NULL.
    }
    void MakeEmptyGraph(int n);
    void AddEdge(int v1, int v2, int cap);
    vertexlist* GetAdjList(int u);
    void printGraph(int n);
    void RemoveEdge(int v1, int v2);
    int GetCapacity(int v1, int v2);
    void increaseFlow(int s, int t, vector<int>& parent, int min_value);
};
//Decleration---------------------------------------------------------------------------------
void AddEdgeToAdj(vertexlist* vl, int v1, int v2, int cap);
void ConvertToInt(string stringToConvert, int& iVer, int& jVer, int& cap,int n);
bool bfs(int** rGraph, int vNum, int s, int t, vector<int>& parent);
void fordFulkersonWithBfs(Graph* graph, int vNum, int s, int t);
void dijkstra(Graph* grpah, int** rGraph, int n, int src, int t, vector<int>& parent, vector<int>& dist);
void dfs(int** rGraph, int vNum, int s, vector<bool>& visited);
int MaxFlow(vector<int>& dist, int n, vector<bool>& sptSet);
void minCut(int** rGraph, int vNum, int s, int t);
void fordFilkersonWithDijkstra(Graph* graph, int vNum, int s, int t);
void InvalidInput();
#endif