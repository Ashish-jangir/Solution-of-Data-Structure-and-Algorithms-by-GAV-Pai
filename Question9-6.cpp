/*
Design and implement an algorithm to obtain an Eulerian walk of an undirected graph in
the event of such a walk being available.
solution:
using FLEURY’S ALGORITHM
1. Start at any vertex if finding an Euler circuit. If finding an Euler path, start at one of the two vertices with odd degree.
2. Choose any edge leaving your current vertex, provided deleting that edge will not separate the graph into two disconnected sets of edges.
3. Add that edge to your circuit and delete it from the graph.
4. Continue until you’re done.

input:
https://youtu.be/vvP4Fg4r-Ns
size 7
edges 10
1 2
1 5
1 7
1 6
2 3
2 5
2 5
3 4
4 5
6 7

*/
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm> // for std::find() function
using std::cin;
using std::cout;
using std::queue;
using std::stack;
using std::vector;

class Graph
{
public:
    int V; // Number of vertices
    vector<vector<int>> adjList;

    Graph(int vertices) : V(vertices)
    {
        adjList.resize(V);
    }

    void addEdge(int u, int v)
    {
        adjList[u - 1].push_back(v);
        adjList[v - 1].push_back(u); // For undirected graph
    }

    void displayGraph()
    {
        for (size_t i = 0; i < V; i++)
        {
            cout << i + 1 << "\t->\t";
            for (int node : adjList[i])
            {
                cout << node << "\t->\t";
            }
            cout << "NULL\n";
        }
    }

    vector<int> BFS(int startVertex)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        vector<int> bfsTraversal;

        visited[startVertex - 1] = true;
        q.push(startVertex - 1);
        bfsTraversal.push_back(startVertex);

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            // cout << curr + 1 << " ";

            for (int neighbor : adjList[curr])
            {
                if (!visited[neighbor - 1])
                {
                    visited[neighbor - 1] = true;
                    q.push(neighbor - 1);
                    bfsTraversal.push_back(neighbor);
                    // Add the edge to the spanning tree
                    // cout << "(" << curr + 1 << "-" << neighbor << ") "; // Printing the spanning tree edges
                }
            }
        }
        return bfsTraversal;
    }

    vector<int> DFS(int startVertex)
    {
        vector<bool> visited(V, false);
        stack<int> s;
        vector<int> dfsTraversal;
        s.push(startVertex - 1); // Push the starting vertex onto the stack

        while (!s.empty())
        {
            int curr = s.top();
            s.pop();

            if (!visited[curr])
            {
                visited[curr] = true;
                dfsTraversal.push_back(curr + 1); // Add the current vertex to the traversal list

                // Visit all neighbors of the current vertex
                for (int neighbor : adjList[curr])
                {
                    if (!visited[neighbor - 1])
                    {
                        s.push(neighbor - 1); // Push unvisited neighbors onto the stack
                    }
                }
            }
        }
        return dfsTraversal;
    }

    bool isConnected()
    {
        return (V == DFS(1).size());
    }
    
    bool checkingBridge(int secondVertex, int firstVertex)
    {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[secondVertex - 1] = true;
        q.push(secondVertex - 1);

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            int count = 0;
            for (int neighbor : adjList[curr])
            {
                if(neighbor == firstVertex) {
                    count++;
                    if(count > 1) return false;
                }
                if (!visited[neighbor - 1] && !(curr == (secondVertex - 1) && neighbor == firstVertex))
                {
                    visited[neighbor - 1] = true;
                    q.push(neighbor - 1);
                    if (neighbor == firstVertex)
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void eulerianWalk()
    {
        // 0. First check if graph is connected and how much vertices are there with odd degree.
        if (!isConnected())
            return;

        // 1. Start at any vertex if finding an Euler circuit. If finding an Euler path, start at one of the two vertices with odd degree.
        int oddDegreeVertices = 0;
        int oddDegreeVertexIndex = 0;
        for (size_t i = 0; i < V; i++)
        {
            if (adjList[i].size() % 2 != 0)
            {
                oddDegreeVertices++;
                oddDegreeVertexIndex = i;
            }
        }
        int curr = oddDegreeVertexIndex;

        // 2. Choose any edge leaving your current vertex, provided deleting that edge will not separate the graph into two disconnected sets of edges.
        // 3. Add that edge to your circuit and delete it from the graph.
        // 4. Continue until you’re done.
        if (oddDegreeVertices == 0 || oddDegreeVertices == 2)
        {
            // Euler walk exists
            while (adjList[curr].size() != 0)
            {
                for (size_t i = 0; i < adjList[curr].size(); i++)
                {
                    int secondVertex = adjList[curr][i];
                    bool isBridge = checkingBridge(secondVertex, curr + 1);
                    if (adjList[curr].size() == 1 || !isBridge)
                    {
                        // delete edge without thinking because only one unvisited edge
                        cout << curr + 1<< " ";

                        adjList[curr].erase(adjList[curr].begin() + i);
                        auto it = std::find(adjList[secondVertex - 1].begin(), adjList[secondVertex - 1].end(), curr + 1);
                        adjList[secondVertex - 1].erase(it);
                        
                        curr = secondVertex - 1;
                        break;
                    }
                }
            }
            cout << std::endl;
        }
        else
        {
            // Euler walk does not exists
            cout << "Euler Walk does not exists\n";
        }
    }
};

int main()
{
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
    cout << "Eulerian Walk:\n";
    graph.eulerianWalk();

    return 0;
}