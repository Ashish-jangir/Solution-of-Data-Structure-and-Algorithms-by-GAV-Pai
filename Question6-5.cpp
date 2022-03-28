// Topological sorting using multiply linked list
// multiply linked list is used to make graph
#include <iostream>
#include <vector>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::vector;

class Graph
{
    // this node represents an element of multiply linked list
public:
    class Node
    {
    public:
        int data;
        vector<Node *> links;
        Node(int data)
        {
            this->data = data;
        }
    };

    vector<Node *> vertices;

    int Order()
    {
        return vertices.size();
    }
    Node *NodeInTheList(int data)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (data == (*vertices[i]).data)
            {
                return vertices[i];
            }
        }
        return NULL;
    }
    void AddEdge(int st, int en)
    {
        Node *start = NodeInTheList(st);
        Node *end = NodeInTheList(en);
        if (start && end)
        {
            (*start).links.push_back(end);
        }
        else if (start == NULL && end)
        {
            start = new Node(st);
            (*start).links.push_back(end);
            vertices.push_back(start);
        }
        else if (start && end == NULL)
        {
            end = new Node(en);
            (*start).links.push_back(end);
            vertices.push_back(end);
        }
        else
        {
            start = new Node(st);
            end = new Node(en);
            (*start).links.push_back(end);
            vertices.push_back(start);
            vertices.push_back(end);
        }
    }

    void topologicalSortUtil(int v, vector<bool> &visited, stack<int> &Stack)
    {
        visited[v] = true;

        vector<Node *> temp = (*vertices[v]).links;
        for (int i = 0; i != temp.size(); ++i)
        {
            if (!visited[(*temp[i]).data - 1])
            {
                topologicalSortUtil((*temp[i]).data - 1, visited, Stack);
            }
        }

        Stack.push(v);
    }

    vector<int> topologicalSort()
    {
        vector<int> result;
        stack<int> Stack;

        vector<bool> visited(vertices.size(), false);

        for (int i = 0; i < vertices.size(); i++)
            if (visited[(*vertices[i]).data - 1] == false)
                topologicalSortUtil((*vertices[i]).data - 1, visited, Stack);

        while (Stack.empty() == false)
        {
            result.push_back(Stack.top() + 1);
            Stack.pop();
        }
        return result;
    }
};

int main()
{
    Graph graph;
    graph.AddEdge(1, 2);
    graph.AddEdge(2, 4);
    graph.AddEdge(2, 5);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 5);
    graph.AddEdge(4, 6);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 7);

    vector<int> result = graph.topologicalSort();
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}