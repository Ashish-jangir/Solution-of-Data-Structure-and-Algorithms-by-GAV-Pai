/*
Implement the ADT for graphs in a programming language of your choice choosing a linked representation for the graphs.
ADT operations:
- Check if graph G is empty
    CHECK_GRAPH_EMPTY (G) (Boolean function)
- Insert an isolated vertex V into a graph G. Ensure that V does not exist in G before insertion.
    INSERT_VERTEX (G, V)
- Insert an edge connecting vertices U, V into a graph G. Ensure that such an edge does not exist in G before insertion.
    INSERT_EDGE(G, U, V)
- Delete vertex V and all the edges incident on it from the graph G. Ensure that such a vertex exists in the graph before deletion.
    DELETE_VERTEX (G, V)
- Delete an edge from the graph G connecting the vertices U, V. Ensure that such an edge exists before deletion.
    DELETE_EDGE (G, U, V)
- Store ITEM into a vertex V of graph G
    STORE_DATA(G, V, ITEM)
- Retrieve data of a vertex V in the graph G and return it in ITEM
    RETRIEVE_DATA (G, V, ITEM)
- Perform Breadth first traversal of a graph G.
    BFT (G)
- Perform Depth first traversal of a graph G.
    DFT (G)
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
        int data;
        Node* link;
        // Default constructor
        Node() : vertexTag(0), edgeWeight(0), data(0), link(nullptr) {}
        
        // Parameterized constructor
        Node(int vertexTag, int edgeWeight) : vertexTag(vertexTag), edgeWeight(edgeWeight), data(0), link(nullptr) {}
    };
    int size;
    vector<Node> headNodes;
    vector<int> dfsTraversal;
    vector<int> bfsTraversal; 
    void DFS(int u, vector<bool> &visited) {
        visited.at(u-1) = true;
        dfsTraversal.push_back(u);
        Node *temp = headNodes.at(u-1).link;
        while(temp != NULL) {
            if(!visited.at(temp->vertexTag - 1)) {
                DFS(temp->vertexTag, visited);
            }
            temp = temp->link;
        }
    }
public:
    Graph(int size) : size(size) {
        headNodes = vector<Node>(size);
    }
    Graph() : size(0) {}

    void InsertVertex() {
        Node node;
        headNodes.push_back(node);
        size++;
    }
    
    void StoreData(int data, int vertex) {
        headNodes[vertex - 1].data = data;
    }

    int RetrieveData(int vertex) {
        return headNodes[vertex - 1].data;
    }

    void InsertEdge(int u, int v, int weight) {
        Node *nodeV = new Node(v, weight);
        if(headNodes.at(u-1).link == nullptr) {
            headNodes.at(u-1).link = nodeV;
        }
        else {
            Node *temp = headNodes.at(u-1).link;
            while(temp->link != NULL) temp = temp->link;
            temp->link = nodeV;
        }
    }

    void DeleteEdge(int u, int v) {
        Node *temp = headNodes[u-1].link, *previous = nullptr;
        bool found = false;
        while(temp != nullptr) {
            if(temp->vertexTag == v) {
                found = true;
                break;
            }
            previous = temp;
            temp = temp->link;
        }
        if(found) {
            previous = temp->link;
            delete(temp);
        }
        else {
            cout << "Edge not found\n";
        }
    }

    int getSize() {
        return size;
    }
    void displayGraph() {
        for (size_t i = 0; i < size; i++)
        {
            cout << i + 1 << "\t->\t";
            Node *temp = headNodes.at(i).link;
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
            Node *temp = headNodes.at(current - 1).link;
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
            Node *temp = headNodes[min].link;
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