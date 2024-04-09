/*
Execute a program to input a graph G = (V, E) as an adjacency list. Include two functions
BFT and DFT to undertake a breadth first and depth first traversal of the graph. Making use
of the traversal procedures, test whether the graph is connected.
*/

#include<iostream>
#include<vector>
#include<queue>
using std::vector;
using std::cout;
using std::cin;
using std::queue;

class Graph {
    class Node {
    public:
        int vertexTag;
        Node* link;
        // Default constructor
        Node() : vertexTag(0), link(nullptr) {}
        
        // Parameterized constructor
        Node(int vertexTag) : vertexTag(vertexTag), link(nullptr) {}
    };
    int size;
    vector<Node*> headNodes;
    vector<int> dfsTraversal;
    vector<int> bfsTraversal; 
    void DFS(int u, vector<bool> &visited) {
        visited.at(u-1) = true;
        dfsTraversal.push_back(u);
        Node *temp = headNodes.at(u-1);
        while(temp != NULL) {
            if(!visited.at(temp->vertexTag - 1)) {
                DFS(temp->vertexTag, visited);
            }
            temp = temp->link;
        }
    }
public:
    Graph(int size) : size(size) {
        headNodes = vector<Node*>(size);
    }
    void InsertEdge(int u, int v) {
        Node *nodeV = new Node(v);
        if(headNodes.at(u-1) == nullptr) {
            headNodes.at(u-1) = nodeV;
        }
        else {
            Node *temp = headNodes.at(u-1);
            while(temp->link != NULL) temp = temp->link;
            temp->link = nodeV;
        }
        Node *nodeU = new Node(u);
        if(headNodes.at(v-1) == nullptr) {
            headNodes.at(v-1) = nodeU;
        }
        else {
            Node *temp = headNodes.at(v-1);
            while (temp->link != NULL) temp = temp->link;
            temp->link = nodeU;
        }
    }

    int getSize() {
        return size;
    }
    void displayGraph() {
        for (size_t i = 0; i < size; i++)
        {
            cout << i + 1 << "\t->\t";
            Node *temp = headNodes.at(i);
            while(temp != nullptr) {
                cout << temp->vertexTag << "\t->\t";
                temp = temp->link;
            }
            cout << "NULL\n";
        }
    }
    vector<int> DFSTraversal(int u) {
        vector<bool> visited = vector<bool>(size, false);
        dfsTraversal.clear();
        DFS(u, visited);
        return dfsTraversal;
    }
    vector<int> BFSTraversal(int u) {
        vector<bool> visited = vector<bool>(size, false);
        bfsTraversal.clear();
        queue<int> q;
        q.push(u);
        while(!q.empty()) {
            int current = q.front();
            q.pop();
            visited.at(current - 1) = true;
            bfsTraversal.push_back(current);
            Node *temp = headNodes.at(current - 1);
            while(temp != NULL) {
                if(!visited.at(temp->vertexTag - 1) && q.back() != temp->vertexTag) q.push(temp->vertexTag);
                temp = temp->link;
            }
        }
        return bfsTraversal;
    }

    bool isConnected() {
        DFSTraversal(1);
        return (headNodes.size() == dfsTraversal.size());
    }
};



int main() {
    //to check C++ version being used.
    //std::cout << __cplusplus / 100 % 100 << '\n';
    cout << "Please enter the number of vertices: ";
    int numOfVertex, numOfEdges;
    cin >> numOfVertex;
    Graph graph = Graph(numOfVertex);
    cout << "Please enter number of edges: ";
    cin >> numOfEdges;
    cout << "Please Enter pairs of first and last vertex of edges\n";
    for (size_t i = 0; i < numOfEdges; i++)
    {
        int u, v;
        cin >> u >> v;
        graph.InsertEdge(u, v);
    }
    cout << "Graph\n";
    graph.displayGraph();
    cout << "Please enter the starting node from where graph should be traversed.";
    int u;
    cin >> u;
    cout << "DFS travesal:\n";
    vector<int> dfsTraversal = graph.DFSTraversal(u);
    for (size_t i = 0; i < dfsTraversal.size(); i++)
    {
        cout<<dfsTraversal.at(i) << " ";
    }
    cout << std::endl;

    cout << "Is Graph connected: " << graph.isConnected() << std::endl;
    
    return 0;
}