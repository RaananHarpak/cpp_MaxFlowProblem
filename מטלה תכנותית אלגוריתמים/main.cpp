#include "Graph.h"


//Grpah class imp:
void Graph::MakeEmptyGraph(int n)
{
    //Graph(n);
}
void Graph::AddEdge(int v1, int v2, int cap)
{
    node* newnode2 = NewNode(v2, cap);
    if (this->vl[v1].vlisthead == nullptr)
    {
        // If the head is null insert the node to the head.
        this->vl[v1].vlisthead = newnode2;
        this->vl[v1].vlisttail = newnode2;
    }
    else
    {
        // Otherwise, add the node at the End.
        this->vl[v1].vlisttail->link = newnode2;
        this->vl[v1].vlisttail = newnode2;
    }
}
vertexlist* Graph::GetAdjList(int u)
{
    vertexlist* res;
    res = (vertexlist*)malloc(sizeof(vertexlist));
    if (res == nullptr)
        return nullptr;
    res->vlisthead = nullptr;
    res->vlisttail = nullptr;
    node* temp = this->vl[u].vlisthead;

    while (temp != nullptr)
    {
        AddEdgeToAdj(res, u, temp->data, temp->capacity);
        temp = temp->link;
    }
    //Print adj List for check
    node* tmp = res->vlisthead;
    cout << "The adj list of vertex number " << u << ":\n";
    while (tmp != nullptr)
    {
        cout << tmp->data << " with capacity: " << tmp->capacity << "\n";
        tmp = tmp->link;
    }



    return res;
}
void Graph::printGraph(int n) {
    int i;
    cout << "\n\nThe incidence list representation for the given graph: ";
    for (i = 0; i < n; i++)
    {
        cout << "\n\tV(" << i + 1 << ") -> {";
        while (this->vl[i + 1].vlisthead != NULL)
        {
            cout << this->vl[i + 1].vlisthead->data << ",";
            this->vl[i + 1].vlisthead = this->vl[i + 1].vlisthead->link;//Delete my head list
        }
        cout << "}";
    }

}
void Graph::RemoveEdge(int v1, int v2)
{
    node* temp = this->vl[v1].vlisthead;
    node* tempback = this->vl[v1].vlisthead;

    if (temp != nullptr && temp->data == v2)//delete head and there is more vertex at list
    {
        if (temp->link != nullptr)
        {
            this->vl[v1].vlisthead = this->vl[v1].vlisthead->link;
        }
        else//if delete head
        {
            this->vl[v1].vlisthead = nullptr;
            this->vl[v1].vlisttail = nullptr;
        }

    }//Delete from head
    tempback = temp;
    if(temp!=NULL)
    temp = temp->link;

    while (temp != nullptr)
    {
        if (temp->data == v2)//if there is more vertex at list
        {
            tempback->link = temp->link;
        }
        tempback = temp;
        temp = temp->link;
        //CHECK FOR DELETE FROM TAIL
    }
}
int Graph::GetCapacity(int v1, int v2)
{
    if (this->vl[v1].vlisthead == NULL)
        return 0;
    node* temp = this->vl[v1].vlisthead;
    while (temp != nullptr)
    {
        if (temp->data == v2)
            return temp->capacity;

        temp = temp->link;
    }
    return 0;

    //if there is no edge like that return ERROR
}
void Graph::increaseFlow(int s, int t, vector<int>& parent, int min_value) {
    int u;
    for (int v = t; v != s; v = parent[v]) {
        u = parent.at(v);
        node* temp = this->vl[u].vlisthead;
        while (temp != NULL)
        {
            if (temp->data == v)
            {
                temp->flow += min_value;
                break;
            }
            if (temp->link == NULL)
                temp = NULL;
            else
            temp = temp->link;
        }
    }
}

//Definition:-----------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
      #pragma region Initilization
    int n = 0;//verticesNunmber
    int m = 0;//edgesNumber
    int s, t, i, j = 0;//sVertic
    string trioInput;
    int vEdge1, vEdge2, capacityEdge;
    bool isFirstIter = true;
   

#pragma endregion

      #pragma region Get_Input_From_User
    //cout << "Please enter the number of vertices:\n";
    cin >> n;
    if (n <= 0)
        InvalidInput();

    Graph G(n);
    //cout << "Please enter the number of edges:(positive only)\n";
    cin >> m;
    if (m<0 || m>(n*n))
        InvalidInput();
    
    //cout << "Please enter the s vertic and the t vertic:\n";
    cin >> s;
    cin >> t;
    if (s<0 || s>n || t<0 || t>n)
        InvalidInput();
    
    for (i = 0; i < m; i++)//set all the edges
    {
        //cout << "Please enter the " << i + 1 << "st trio:(i j capacity)\n";
        if (isFirstIter == true)
        {
            cin.ignore();
            isFirstIter = false;
        }
        getline(cin, trioInput);
        ConvertToInt(trioInput, vEdge1, vEdge2, capacityEdge,n);
        G.AddEdge(vEdge1, vEdge2, capacityEdge);
    }

#pragma endregion

    fordFulkersonWithBfs(&G, n + 1, s, t);
    fordFilkersonWithDijkstra(&G, n + 1, s, t);
}
void ConvertToInt(string stringToConvert, int& iVer, int& jVer, int& cap,int n)
{
    int number = 0;
    int index = 0;
    while (isdigit(stringToConvert[index]))
    {
        number = number * 10 + (stringToConvert[index++] - '0');
    }
    iVer = number;
    if (isdigit(stringToConvert[index]) == false && stringToConvert[index] != ' ')
        InvalidInput();
    if (iVer<0 || iVer>n)
        InvalidInput();
    index++;
    number = 0;
    while (isdigit(stringToConvert[index]))
    {
        number = number * 10 + (stringToConvert[index++] - '0');
    }
    jVer = number;
    if (isdigit(stringToConvert[index]) == false && stringToConvert[index] != ' ')
        InvalidInput();
    if (jVer<0 || jVer>n)
        InvalidInput();
    index++;
    if (isdigit(stringToConvert[index]) == false )
        InvalidInput();
    number = 0;
    while (isdigit(stringToConvert[index]))
    {
        number = number * 10 + (stringToConvert[index++] - '0');
    }
    cap = number;
    if (cap<0)
        InvalidInput();

}
void fordFulkersonWithBfs(Graph* graph, int vNum, int s, int t)
{
    int u, v;
    int path_flow;
    int max_flow;
    // Create a residual graph and fill the residual graph with given capacities in the original graph as residual capacities in residual graph
    int** rGraph = (int**)malloc(sizeof(int*) * vNum);
    for (int i = 0; i < vNum; i++)
    {
        rGraph[i] = (int*)malloc(sizeof(int)*vNum);
        if (rGraph[i] == NULL)
            return;
    }

    // Residual graph where rGraph[i][j] indicates residual capacity of edge from i to j (if there is an edge. If rGraph[i][j] is 0, then there is not)
    for (u = 0; u < vNum; u++)
        for (v = 0; v < vNum; v++)
        {
            rGraph[u][v] = graph->GetCapacity(u, v);
        }

    // This array is filled by BFS and to store path
    vector<int> parent(vNum, 0);
    parent.at(s) = -1;
    max_flow = 0; // There is no flow initially

    // Augment the flow while there is path from source to sink
    while (bfs(rGraph, vNum , s, t, parent) == true) {
        // Find minimum residual capacity of the edges along the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
         path_flow = INT8_MAX;
        for (int v = t; v != s && v!=0; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        // update residual capacities of the edges and reverse edges along the path
        for (v = t; v != s && v != 0; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        // Add path flow to overall flow
        max_flow += path_flow;
    }
    //bfs method:
    cout << "BFS Method:\nMax flow = " << max_flow << "\n";
    minCut(rGraph, vNum, s, t);

    for (int i = 0; i < vNum; i++)
        delete[] rGraph[i];
          
    delete[] rGraph;
    parent.clear();
}
void fordFilkersonWithDijkstra(Graph* graph, int vNum, int s, int t)
{
    int u, v;
    int** rGraph = (int**)malloc(sizeof(int*) * vNum);
    for (int i = 0; i < vNum; i++)
        rGraph[i] = (int*)malloc(sizeof(int) * vNum);

    for (u = 0; u < vNum; u++)
        for (v = 0; v < vNum; v++)
            rGraph[u][v] = graph->GetCapacity(u, v);

    vector<int> parent(vNum, 0);
    parent[s] = -1;
    int max_flow = 0; 
    vector<int>dist(vNum, INT8_MIN);
    dist[s] = 0;
    dijkstra(graph,rGraph, vNum, s, t, parent, dist);

    while (dist[t] != INT8_MIN) {
        int path_flow = INT8_MAX;
        for (int v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        int min_value = INT8_MAX;
        for (int v = t; v != s; v = parent[v]) {
            u = parent[v];
            min_value = min(min_value, rGraph[u][v]);
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
        graph->increaseFlow(s, t, parent, min_value);
        dijkstra(graph, rGraph, vNum, s, t,parent,dist);
    }
    
    cout << "Greedy Method:\nMax flow = " << max_flow << "\n";
    minCut(rGraph, vNum, s, t);


    for (int i = 0; i < vNum; i++)
        free(rGraph[i]);

    free(rGraph);
    parent.clear();
    dist.clear();

}
bool bfs(int** rGraph, int vNum, int s, int t, vector<int>& parent)
{

    bool* visited = (bool*)malloc(sizeof(bool) * vNum);
    if (visited == NULL)
        return visited;
    for (int i = 0; i < vNum; i++)
        visited[i] = false;

    // Create a queue, enqueue source vertex and mark source vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < vNum; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    if (visited[t] == true)
    {
        //free(visited);
        delete[] visited;
        return true;
    }
    else
    {
        //free(visited);
        delete[] visited;
        return false;
    }
    
    
}
void AddEdgeToAdj(vertexlist* vl, int v1, int v2, int cap)
{
    node* newnode2 = NewNode(v2, cap);
    // Connection 2, v1 to v2.
    if (vl->vlisthead == nullptr)
    {
        // If the head is null insert the node to the head.
        vl->vlisthead = newnode2;
        vl->vlisttail = newnode2;
    }
    else
    {
        // Otherwise, add the node at the End.
        vl->vlisttail->link = newnode2;
        vl->vlisttail = newnode2;
    }
}
void minCut(int** rGraph, int vNum, int s, int t)
{
    vector<bool> visited(vNum, false);
    cout << "Min cut: S = ";
    dfs(rGraph, vNum, s, visited);
    bool flag = true;
    bool flag2 = true;
    for (int i = 0; i < vNum; i++)
        if (visited[i] == true && i != 0)
        {
            if (flag2 != true)
                cout << " , ";
            cout << i;
            flag2 = false;
        }
    cout << ". T = ";
    for (int i = 0; i < vNum; i++)
        if (visited[i] == false && i != 0)
        {
            if (flag != true)
                cout << " , ";
            cout << i ;
            flag = false;
        }

    visited.clear();
    cout << "\n";
}
int MaxFlow(vector<int>& dist, int n, vector<bool>& sptSet)
{
    int max = INT8_MIN;
    int max_index = 0;
    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] >= max)
            max = dist[v], max_index = v;
    return max_index;
}
void dijkstra(Graph* graph,int** rGraph, int n, int src, int t, vector<int>& parent, vector<int>& dist)
{
    vector<bool> sptSet(n, false);
    bool ifTrue = false;
    for (int i = 0; i < n; i++)
    {
        dist[i] = INT8_MIN;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < n; count++) {
        int u = MaxFlow(dist, n, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < n ; v++)
        {
            int currcapacity = rGraph[u][v];
            if (!sptSet[v] && currcapacity > 0 && dist[u] != INT8_MIN && dist[u] + currcapacity > dist[v])
            {
                dist[v] = dist[u] + currcapacity;
                parent[v] = u;
            }
        }
    }
    sptSet.clear();
}
void dfs(int** rGraph, int vNum, int s, vector<bool>& visited)
{
    visited[s] = true;
    for (int i = 0; i < vNum; i++)
        if (rGraph[s][i] > 0 && !visited[i])
        {
            dfs(rGraph, vNum, i, visited);
        }
}
void InvalidInput()
{
    cout << "invalid input";
    exit(0);
}









