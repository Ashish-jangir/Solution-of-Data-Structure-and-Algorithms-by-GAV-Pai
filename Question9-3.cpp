/*
Implement Dijkstra's algorithm to obtain the shortest paths from the source vertex 1 to every
other vertex of the graph G given below:
- Directed Graph
- size = 8
- weighted Edges:
(1 3)=20
(1 2)=70
(1 5)=5
(2 3)=15
(3 8)=25
(3 7)=10
(3 4)=15
(5 4)=20
(5 6)=20
(5 8)=?(will consider as not exist)
(4 2)=30
(6 4)=2
(6 2)=25
(6 7)=40
(7 4)=30
(7 8)=5
(8 6)=4
(8 7)=20

input:
1 3 20
1 2 70
1 5 5
2 3 15
3 8 25
3 7 10
3 4 15
5 4 20
5 6 20
4 2 30
6 4 2
6 2 25
6 7 40
7 4 30
7 8 5
8 6 4
8 7 20
*/

#include<iostream>
#include<vector>
#include<queue>
using std::vector;
using std::cout;
using std::cin;
using std::queue;
int findMinInUnvisited(vector<bool>, vector<int>);

class Graph {
    class Node {
    public:
        int vertexTag;
        int edgeWeight;
        Node* link;
        // Default constructor
        Node() : vertexTag(0), edgeWeight(0), link(nullptr) {}
        
        // Parameterized constructor
        Node(int vertexTag, int edgeWeight) : vertexTag(vertexTag), edgeWeight(edgeWeight), link(nullptr) {}
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
    void InsertEdge(int u, int v, int weight) {
        Node *nodeV = new Node(v, weight);
        if(headNodes.at(u-1) == nullptr) {
            headNodes.at(u-1) = nodeV;
        }
        else {
            Node *temp = headNodes.at(u-1);
            while(temp->link != NULL) temp = temp->link;
            temp->link = nodeV;
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
                cout << "( " <<temp->vertexTag << ", " << temp->edgeWeight << ") \t->\t";
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
    vector<int> shortestPathDijkstra(int u) {
        //1. Assign infinite to all edges and create array of visited notes.
        vector<int> weigth = vector<int>(size, INT16_MAX);
        vector<bool> visited = vector<bool>(size, false);
        weigth[u-1] = 0;
        //2. run loop equal to size of the graph
        //3. in every iteration find the lowest weighted vertex from unvisited vertices.
        //4. reevaluate weight of other unvisited vertices.
        for (size_t i = 0; i < size; i++)
        {
            int min = findMinInUnvisited(visited, weigth);
            visited[min] = true;
            Node *temp = headNodes[min];
            while(temp != nullptr) {
                if(weigth[temp->vertexTag - 1] > (temp->edgeWeight + weigth[min]))
                    weigth[temp->vertexTag - 1] = temp->edgeWeight + weigth[min];  
                temp = temp->link;
            }
        }
        return weigth;
        
    }
};

int findMinInUnvisited(vector<bool> visited, vector<int> weight) {
    int min = INT16_MAX;
    int indexMin = 0;
    for (size_t i = 0; i < visited.size(); i++)
    {
        if(!visited[i]) {
            if(weight[i] < min) {
               min = weight[i];
               indexMin = i;
            }
        }
    }
    return indexMin;    
}



int main() {
    //to check C++ version being used.
    //std::cout << __cplusplus / 100 % 100 << '\n';
    cout << "Please enter the number of vertices: ";
    int numOfVertex, numOfEdges;
    cin >> numOfVertex;
    Graph graph = Graph(numOfVertex);
    cout << "Please enter number of edges: ";
    cin >> numOfEdges;
    cout << "Please Enter pairs of first, last vertex and weight of edges\n";
    for (size_t i = 0; i < numOfEdges; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph.InsertEdge(u, v, w);
    }
    cout << "Graph\n";
    graph.displayGraph();
    vector<int> shortestPaths = graph.shortestPathDijkstra(1);

    cout << "Shortest paths: \n";
    for (size_t i = 0; i < shortestPaths.size(); i++)
    {
        cout << i + 1 << " " << shortestPaths[i] << std::endl;
    }
    
    // cout << "Please enter the starting node from where graph should be traversed.";
    // int u;
    // cin >> u;
    // cout << "BFS travesal:\n";
    // vector<int> bfsTraversal = graph.BFSTraversal(u);
    // for (size_t i = 0; i < bfsTraversal.size(); i++)
    // {
    //     cout<<bfsTraversal.at(i) << " ";
    // }
    // cout << std::endl;

    // cout << "Is Graph connected: " << graph.isConnected() << std::endl;
    
    return 0;
}