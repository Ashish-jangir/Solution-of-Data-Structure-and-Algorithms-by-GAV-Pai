/*
Design and implement an algorithm to execute depth first traversal of a graph represented
by its incidence matrix.

input:
size 5
edges 6
1 2
1 3
2 3
2 4
3 4
4 5
*/
#include<iostream>
#include<vector>
#include<stack>
using std::cout;
using std::cin;
using std::vector;
using std::stack;

class Graph {
    public:
    int size;
    vector<vector<int>> matrix;

    Graph(int size): size(size) {
        matrix = vector<vector<int>>(size);
    }

    void addEdge(int u, int v) {
        for (size_t i = 0; i < size; i++)
        {
            if(i == u-1) {
                matrix[i].push_back(1);
            }
            else if(i == v-1) {
                matrix[i].push_back(1);
            }
            else {
                matrix[i].push_back(0);
            }
        }
        
    }
    void displayGraph() {
        for (size_t i = 0; i < matrix.size(); i++)
        {
            for (size_t j = 0; j < matrix[i].size(); j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << std::endl;
        }
    }

    void DFS(int u) {
        vector<bool> visited(size, false);
        stack<int> s;
        s.push(u-1);
        visited[u-1] = true;
        while(!s.empty()) {
            int curr = s.top();
            s.pop();
            bool quit = false;
            int j = 0;
            while(!quit && j < matrix[curr].size()) {
                int edgeColumns = matrix[curr][j];
                if(edgeColumns == 1) {
                    for (size_t i = 0; i < size; i++)
                    {
                        if(i == curr) continue;

                        if(matrix[i][j] == 1) {
                            if(!visited[i]) {
                                visited[i] = true;
                                s.push(i);
                                cout << "(" << curr + 1 << " " << i + 1<< ") ";
                                quit = true;
                                break;
                            }
                        }
                    }
                }
                j++;
            }

        }
    }
};

int main() {
    cout << "Please enter the number of vertices: ";
    int numOfVertex, numOfEdges;
    cin >> numOfVertex;
    Graph graph(numOfVertex); // Create a graph with 6 vertices
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

    cout << "DFS Traversal:\n";
    graph.DFS(u);
    return 0;
}