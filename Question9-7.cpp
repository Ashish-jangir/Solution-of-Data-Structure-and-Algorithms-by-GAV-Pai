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
#include<map>
using std::vector;
using std::cout;
using std::cin;
using std::queue;
using std::map;
using std::pair;
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
    map<int, Node> headNodes;
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
    Graph(int size) : size(size) { }
    Graph() : size(0) {}

    void InsertVertex() {
        Node node;
        headNodes.insert(pair<int, Node>(headNodes.end()->first, node));
        size++;
    }

    void DeleteVertex(int vertexTag) {
        headNodes.erase(vertexTag - 1);
        auto it = headNodes.begin();
        while(it != headNodes.end()) {
            Node *temp = it->second.link, *previous = &it->second;
            while(temp != nullptr) {
                if(temp->vertexTag == vertexTag) {
                    previous->link = temp->link;
                    delete(temp);
                }
                previous = temp;
                temp = temp->link;
            }
            it++;
        }
    }
    
    void StoreData(int data, int vertex) {
        headNodes[vertex - 1].data = data;
    }

    int RetrieveData(int vertex) {
        return headNodes[vertex - 1].data;
    }

    void InsertEdge(int u, int v, int weight) {
        Node *nodeV = new Node(v, weight);
        if(headNodes.find(u-1) == headNodes.end()) {
            Node node;
            node.vertexTag = u;
            headNodes.insert(pair<int, Node>(u - 1, node));
        }
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
        Node *temp = &headNodes[u-1], *previous = nullptr;
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
            previous->link = temp->link;
            delete(temp);
        }
        else {
            cout << "Edge not found\n";
        }
    }

    int getSize() {
        return size;
    }
    
    bool isEmpty() {
        return (headNodes.size() == 0);
    }
    
    void displayGraph() {
        auto it = headNodes.begin();
        while (it != headNodes.end())
        {
            cout << it->first + 1 << "\t->\t";
            Node *temp = it->second.link;
            while(temp != nullptr) {
                cout << "( " <<temp->vertexTag << ", " << temp->edgeWeight << ") \t->\t";
                temp = temp->link;
            }
            cout << "NULL\n";
            it++;
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
    int numOfVertex, numOfEdges, opt, u, v, w, vertexTag, data;
    vector<int> bfsTraversal, dfsTraversal;
    cout << "Please enter the number of vertices: ";
    cin >> numOfVertex;
    Graph graph = Graph(numOfVertex);
    cout << "Please enter number of edges: ";
    cin >> numOfEdges;
    cout << "Please Enter pairs of first, last vertex and weight of edges\n";
    for (size_t i = 0; i < numOfEdges; i++)
    {
        cin >> u >> v >> w;
        graph.InsertEdge(u, v, w);
    }

    bool quit = false;
    while(!quit) {
        cout << "1. Check if graph G is empty\n";
        cout << "2. Insert an isolated vertex V into a graph G\n";
        cout << "3. Insert an edge connecting vertices U, V into a graph G.\n";
        cout << "4. Delete vertex V and all the edges incident on it from the graph G.\n";
        cout << "5. Delete an edge from the graph G connecting the vertices U, V.\n";
        cout << "6. Store ITEM into a vertex V of graph G\n";
        cout << "7. Retrieve data of a vertex V in the graph G and return it in ITEM\n";
        cout << "8. Perform Breadth first traversal of a graph G.\n";
        cout << "9. Perform Depth first traversal of a graph G.\n";
        cout << "10. Display Graph\n";
        cout << "11. End\n";
        cin >> opt;
        switch (opt)
        {
        case 1:
            cout << "Graph is " << (graph.isEmpty() ? "" : "not ") << "empty\n";
            break;
        case 2:
            graph.InsertVertex();
            break;
        case 3:
            cout << "Please insert u, v and weight: ";
            cin >> u >> v >> w;
            graph.InsertEdge(u, v, w);
            break;
        case 4:
            cout << "Please insert vertex that needs to be deleted: ";
            cin >> vertexTag;
            graph.DeleteVertex(vertexTag);
            break;
        case 5:
            cout << "Please insert u and v: ";
            cin >> u >> v;
            graph.DeleteEdge(u, v);
            break;
        case 6:
            cout << "Please insert the vertex and iteam data: ";
            cin >> vertexTag >> data;
            graph.StoreData(data, vertexTag);
            break;
        case 7:
            cout << "Please insert vertex for which data needs to be retrieved: ";
            cin >> vertexTag;
            data = graph.RetrieveData(vertexTag);
            cout << "Retrieved data: " << data << std::endl;
            break;
        case 8:
            cout << "Starting vertex for Breath First Traversal: ";
            cin >> u;
            cout << "BFS travesal:\n";
            bfsTraversal = graph.BFSTraversal(u);
            for (size_t i = 0; i < bfsTraversal.size(); i++)
            {
                cout<<bfsTraversal.at(i) << " ";
            }
            cout << std::endl;
            break;
        case 9:
            cout << "Starting vertex for Depth First Traversal: ";
            cin >> u;
            cout << "DFS travesal:\n";
            dfsTraversal = graph.DFSTraversal(u);
            for (size_t i = 0; i < bfsTraversal.size(); i++)
            {
                cout<<dfsTraversal.at(i) << " ";
            }
            cout << std::endl;
            break;
        case 10:
            cout << "Graph\n";
            graph.displayGraph();
            break;
        default:
            quit = true;
            break;
        }
    }
    
    return 0;
}
