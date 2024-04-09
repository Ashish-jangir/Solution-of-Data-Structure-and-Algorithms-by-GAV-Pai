/*
Execute a program to input a graph G = (V, E) as an adjacency matrix. Include functions to
(i) test if G is complete (a complete graph is a simple undirected graph in which every pair of distinct vertices is connected by a unique edge.)
(ii) obtain a path and a simple path from vertex u to vertex v.
(iii) obtain the degree of a node u, if G is undirected, and indegree and outdegree of node
u if G is directed.
*/
#include<iostream>
#include<vector>
using std::vector;
using std::cout;
using std::cin;

const int NUMOFVERTICES = 5;

bool IsComplete(int matrix[NUMOFVERTICES][NUMOFVERTICES]) {
    for(int i = 0; i < NUMOFVERTICES; i++ ) {
        for(int j = i + 1; j < NUMOFVERTICES; j++) {
            if(matrix[i][j] != 1)
                return false;
        }
    }
    return true;
}
void DegreeOfNode(int matrix[NUMOFVERTICES][NUMOFVERTICES], int node, int isDirected) {
    if(isDirected == 1) {
        int inDegree = 0, outDegree = 0;
        for(int i = 0; i< NUMOFVERTICES ; i++) {
            if(matrix[node - 1][i] == 1) outDegree++;
            if(matrix[i][node - 1] == 1) inDegree++;
        }
        cout << "Degree of node " << node << " is: " << inDegree << " in and " << outDegree << "out\n";
    } else {
        int degree = 0;
        for(int i = 0; i< NUMOFVERTICES ; i++) {
            if(matrix[node - 1][i] == 1) degree++;
        }
        cout << "Degree of node " << node << " is: " << degree << std::endl;
    }
}

bool DFS(int graph[NUMOFVERTICES][NUMOFVERTICES], int u, int v, bool (&visited)[NUMOFVERTICES], vector<int> &path) {
    visited[u] = true;
    path.push_back(u);
    if(u == v) {
        return true;
    }
    else {
        for(int i = 0; i < NUMOFVERTICES; i++) {
            if(graph[u][i] == 1 && !visited[i]) {
                if(DFS(graph, i, v, visited, path)) {
                    return true;
                }
            }
        }
    }
    path.pop_back();
    return false;
}

int main() {
    cout << "Graph of " << NUMOFVERTICES << " vertices*********************\n";
    cout << "Graph is directed\n1. Yes\n2. No\n";
    int isDirected;
    cin >> isDirected;

    int adjMatrix[NUMOFVERTICES][NUMOFVERTICES] = {{0}};

    int edges = 0;
    cout << "Please insert the number of edges: ";
    cin >> edges;
    cout << "Please insert pair of vertices which are adjecent\n";
    for (int i = 0; i < edges ; i++) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        adjMatrix[vertex1 - 1][vertex2 - 1] = 1;
        if(isDirected == 2) {
            adjMatrix[vertex2 - 1][vertex1 - 1] = 1;
        }
    }
    for(int i = 0; i < NUMOFVERTICES; i++) {
        for(int j = 0; j < NUMOFVERTICES; j++) {
            cout << adjMatrix[i][j];
        }
        cout << std::endl;
    }
    int opt;
    cout <<"1. Find if Graph is complete or not\n2. Obtain simple path\n3. Find Degree(Indegree & OutDegree if directed graph) of Node u\n";
    cin >> opt;
    vector<int> path;
    bool visited[NUMOFVERTICES] = {false};
    switch (opt)
    {
    case 1:
        cout << (IsComplete(adjMatrix) ? "Graph is complete":"Graph is not complete");
        break;
    case 2:
        cout << "Please enter the node u and v: ";
        int u, v;
        cin >>  u >> v;
        if(DFS(adjMatrix, u-1, v-1, visited, path)) {
            for (size_t i = 0; i < NUMOFVERTICES; i++)
            {
                cout << path.at(i) + 1;
            }
        }
        else {
            cout << "No path exists between these vertex";
        }
        break;
    case 3:
        int node;
        cout << "Please insert node for which degree required: ";
        cin >> node;
        DegreeOfNode(adjMatrix, node, isDirected);
        break;
    default:
        break;
    }
    return 0;
}