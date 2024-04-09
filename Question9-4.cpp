/*
Design and implement an algorithm to obtain a spanning tree of a connected, undirected graph using breadth first or depth first traversal.

theory:
BFS (Breadth-First Search) and DFS (Depth-First Search) are both algorithms commonly used to traverse graphs. While Prim's algorithm is
specifically designed for finding minimum spanning trees in weighted graphs, BFS and DFS can indeed be used to find spanning trees in
both weighted and unweighted graphs.

For unweighted graphs, BFS and DFS will naturally result in spanning trees because they explore all reachable vertices from a starting
point without considering edge weights. However, for weighted graphs, using BFS or DFS to find a spanning tree may not produce a
minimum spanning tree (MST) like Prim's algorithm does.

When BFS or DFS are used to find a spanning tree in a weighted graph, they will still produce a spanning tree that connects all vertices
without cycles. However, it's important to note that this spanning tree may not necessarily minimize the total weight of the edges, as
Prim's algorithm does.

So, We'll assume that it is unweighted graphs that is given in question and we suppose to find just spanning tree not minimum spanning tree.

input: (Fig 9.26)
size: 10
edges: 12
1 5
1 7
1 6
6 10
7 9
7 3
5 4
5 9
4 2
9 2
3 8
10 8
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using std::cout;
using std::cin;
using std::vector;
using std::queue;
using std::stack;

class Graph {
public:
    int V; // Number of vertices
    vector<vector<int>> adjList;

    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u - 1].push_back(v);
        adjList[v - 1].push_back(u); // For undirected graph
    }

    void displayGraph() {
        for (size_t i = 0; i < V; i++)
        {
            cout << i + 1 << "\t->\t";
            for(int node: adjList[i]) {
                cout << node << "\t->\t";
            }
            cout << "NULL\n";
        }
    }

    void BFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex - 1] = true;
        q.push(startVertex - 1);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            cout << curr + 1 << " ";

            for (int neighbor : adjList[curr]) {
                if (!visited[neighbor - 1]) {
                    visited[neighbor - 1] = true;
                    q.push(neighbor - 1);
                    // Add the edge to the spanning tree
                    cout << "(" << curr + 1 << "-" << neighbor << ") "; // Printing the spanning tree edges
                }
            }
        }
    }
    void DFS(int startVertex) {
        vector<bool> visited(V, false);
        stack<int> s;
        
        visited[startVertex - 1] = true;
        s.push(startVertex - 1);
        
        while(!s.empty()) {
            int curr = s.top();
            s.pop();

            for (int neighbor : adjList[curr]) {
                if (!visited[neighbor - 1]) {
                    visited[neighbor - 1] = true;
                    s.push(neighbor - 1);
                    // Add the edge to the spanning tree
                    cout << "(" << curr + 1 << "-" << neighbor << ") "; // Printing the spanning tree edges
                    break;
                }
            }
            
        }
    }
};

int main() {
    cout << "Please enter the number of vertices: ";
    int numOfVertex, numOfEdges;
    cin >> numOfVertex;
    Graph graph(numOfVertex);
    cout << "Please enter number of edges: ";
    cin >> numOfEdges;
    cout << "Please Enter pairs of first and last vertex of edges\n";
    for (size_t i = 0; i < numOfEdges; i++)
    {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }
    cout << "Graph\n";
    graph.displayGraph();
    cout << "Please enter the starting node from where graph should be traversed: ";
    int u;
    cin >> u;

    cout << "BFS Traversal:\n";
    graph.BFS(u);
    cout << "\nDFS Traversal:\n";
    graph.DFS(u);

    return 0;
}