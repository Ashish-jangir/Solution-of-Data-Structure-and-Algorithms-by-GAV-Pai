/*
Implement a menu driven program to
i) construct an m-way search tree for a specific order m;
ii) insert elements into the m-way search tree;
iii) delete elements from the m-way search tree;
*/
#include <iostream>
#include <vector>
#include <stack>

using std::cin;
using std::cout;
using std::pair;
using std::stack;
using std::vector;

template <typename T>
class mWaySearchTree
{
    class Node
    {
    public:
        vector<T> keys;
        vector<Node *> childPointers;
        Node(T data)
        {
            keys.push_back(data);
            childPointers.push_back(nullptr);
            childPointers.push_back(nullptr);
        }
    };
    int order;
    Node *root;

    pair<Node *, int> searchNode(T data)
    {
        if (root)
        {
            Node *current = root, *pre = nullptr;
            int i;
            while (current)
            {
                pre = current;
                for (i = 0; i < current->keys.size(); i++)
                {
                    if (current->keys[i] == data)
                    {
                        return {current, i};
                    }
                    else if (current->keys[i] > data)
                    {
                        current = current->childPointers[i];
                        break;
                    }
                }
                if (current && i == current->keys.size())
                {
                    current = current->childPointers.back();
                }
            }
            return {nullptr, 0};
        }
        else
        {
            return {nullptr, 0};
        }
    }

public:
    mWaySearchTree(int order) : order(order), root(nullptr) {}

    void insert(T data)
    {
        if (root)
        {
            Node *current = root, *pre = nullptr;
            int i;
            while (current)
            {
                pre = current;
                bool skip = false;
                for (i = 0; i < current->keys.size(); i++)
                {
                    if (current->keys[i] == data)
                    {
                        cout << "Key already exists in tree!\n";
                        return;
                    }
                    else if (current->keys[i] > data)
                    {
                        // check if current node is full or not
                        if (current->keys.size() < (order - 1))
                        {
                            current->keys.insert(current->keys.begin() + i, data);
                            current->childPointers.insert(current->childPointers.begin() + i + 1, nullptr);
                            return;
                        }
                        else
                        {
                            // current node is full. Go in child node
                            current = current->childPointers[i];
                            skip = true;
                            break;
                        }
                    }
                }
                if (skip)
                    continue;

                if (current && i == current->keys.size())
                {
                    if (current->keys.size() < (order - 1))
                    {
                        current->keys.push_back(data);
                        current->childPointers.push_back(nullptr);
                        return;
                    }
                    current = current->childPointers.back();
                }
            }
            Node *node = new Node(data);
            pre->childPointers[i] = node;
        }
        else
        {
            Node *node = new Node(data);
            root = node;
        }
    }

    void deleteNode(T data)
    {
        pair<Node *, int> output = searchNode(data);
        if (output.first)
        {
            // check if its children are null or not
            if (output.first->childPointers[output.second] == nullptr && output.first->childPointers[output.second + 1] == nullptr)
            {
                // both child are null
                output.first->keys.erase(output.first->keys.begin() + output.second);
                output.first->childPointers.erase(output.first->childPointers.begin() + output.second);
                output.first->childPointers.erase(output.first->childPointers.begin() + output.second + 1);
            }
            else if (output.first->childPointers[output.second] == nullptr && output.first->childPointers[output.second + 1] != nullptr)
            {
                // only left child is null
                Node *temp = output.first->childPointers[output.second + 1], *pre = nullptr;
                while (temp)
                {
                    pre = temp;
                    temp = temp->childPointers[0];
                }
                output.first->keys[output.second] = pre->keys[0];

                pre->keys.erase(pre->keys.begin());
                pre->childPointers.erase(pre->childPointers.begin());
                pre->childPointers.erase(pre->childPointers.begin());
                if (pre->keys.size() == 0)
                {
                    delete (pre);
                }
            }
            else if (output.first->childPointers[output.second] != nullptr && output.first->childPointers[output.second + 1] == nullptr)
            {
                // only right child is null
                Node *temp = output.first->childPointers[output.second], *pre = nullptr;
                while (temp)
                {
                    pre = temp;
                    temp = temp->childPointers.back();
                }
                output.first->keys[output.second] = pre->keys[0];

                pre->keys.pop_back();
                pre->childPointers.pop_back();
                pre->childPointers.pop_back();
                if (pre->keys.size() == 0)
                {
                    delete (pre);
                }
            }
            else
            {
                // both child are not null
                Node *temp = output.first->childPointers[output.second], *pre = nullptr;
                while (temp)
                {
                    pre = temp;
                    temp = temp->childPointers.back();
                }
                output.first->keys[output.second] = pre->keys[0];

                pre->keys.pop_back();
                pre->childPointers.pop_back();
                pre->childPointers.pop_back();
                if (pre->keys.size() == 0)
                {
                    delete (pre);
                }
            }
        }
        else
        {
            cout << "Element is not found in tree!\n";
        }
    }

    void search(T data)
    {
        pair<Node *, int> output = searchNode(data);
        if (output.first)
        {
            cout << "Element found in tree!\n";
        }
        else
        {
            cout << "Element is not found in tree!\n";
        }
    }
};

int main()
{
    cout << "Program to construct m-way search tree\n";
    cout << "Please insert order of the m-way search tree: ";
    int order, opt, num;
    char element;
    cin >> order;
    mWaySearchTree<char> mTree(order);
    bool quit = false;
    while (!quit)
    {
        cout << "Please select one of the below option\n";
        cout << "1. Insert new elements\n";
        cout << "2. Delete elements\n";
        cout << "3. Search element\n";
        cout << "4. Print inorder elements of tree\n";
        cin >> opt;
        switch (opt)
        {
        case 1:
            cout << "How many inserts: ";
            cin >> num;
            cout << "Please insert " << num << " elements to insert in tree\n";
            for (size_t i = 0; i < num; i++)
            {
                cin >> element;
                mTree.insert(element);
            }
            break;
        case 2:
            cout << "Please insert element of delete: ";
            cin >> element;
            mTree.deleteNode(element);
            break;
        case 3:
            cout << "Please insert element to search in tree: ";
            cin >> element;
            mTree.search(element);
            break;
        case 4:
            // mTree.print();
            break;

        default:
            quit = true;
            break;
        }
    }

    return 0;
}
