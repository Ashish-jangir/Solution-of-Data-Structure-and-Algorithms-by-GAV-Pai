/*
4. Execute a program to demostrate the splaying of a tree given a specific node u in the tree.

5. In the menu driven program implemented in programming assignment 1 of Chapter 10 to perform the search, insert and delete operations on a binary search tree, introduce functions to splay the tree soon after every insert and search operations is executed.

*/
#include<iostream>
#include<stack>
using std::pair;
using std::cin;
using std::cout;
using std::stack;

class Node {
    public:
    int data;
    Node *lchild, *rchild;
    Node(int data): data(data) {
        lchild = NULL;
        rchild = NULL;
    }
};

pair<bool, Node*> searchNode(Node*, int);

void insertNode(Node* &root, int data) {
    if(root == NULL) {
        root = new Node(data);
        return;
    }
    pair<bool, Node*> temp = searchNode(root, data);
    if(temp.first) {
        cout << "An element with same data already exists in tree!\n";
    }
    else {
        Node *parent = temp.second;
        Node *node = new Node(data);
        if(data > parent->data) {
            parent->rchild = node;
        }
        else {
            parent->lchild = node;
        }
    }
}

void deleteNode(Node* &root, int data) {
    Node *temp = root, *parent = root;
    while(temp) {
        if(temp->data == data) {
            break;
        }
        else if(temp->data > data) {
            parent = temp;
            temp = temp->rchild;
        }
        else {
            parent = temp;
            temp = temp->lchild;
        }
    }
    if(temp) {
        if(temp->rchild != NULL && temp->lchild != NULL) {
            Node* temp2 = temp->rchild, *parent2 = temp->rchild;
            while(temp2->lchild) {
                parent2 = temp2;
                temp2 = temp2->lchild;
            }
            temp->data = temp2->data;
            parent2->lchild = NULL;
            delete(temp2);
        }
        else if(temp->rchild != NULL) {
            if(parent == temp) {
                root = temp->rchild;
            }
            else if(parent->lchild == temp)
                parent->lchild = temp->rchild;
            else
                parent->rchild = temp->rchild;
            delete(temp);
        }
        else if(temp->lchild != NULL) {
            if(parent == temp) {
                root = temp->lchild;
            }
            else if(parent->lchild == temp)
                parent->lchild = temp->lchild;
            else
                parent->rchild = temp->lchild;
            delete(temp);
        }
        else {
            if(parent->lchild == temp)
                parent->lchild = NULL;
            else
                parent->rchild = NULL;

            delete(temp);
        }
    }
}

pair<bool, Node*> searchNode(Node* root, int data) {
    Node *temp = root, *parent = root;
    while(temp) {
        if(temp->data == data) {
            return {true, temp};
        }
        else if(temp->data < data) {
            parent = temp;
            temp = temp->rchild;
        }
        else {
            parent = temp;
            temp = temp->lchild;
        }
    }
    return {false, parent};
}

void displayInorderTraversal(Node* root) {
    if(root == NULL) {
        cout << "Tree is empty\n";
        return;
    }

    stack<Node*> s;
    Node *currentNode = root;
    while(1) {
        while(currentNode) {
            s.push(currentNode);
            currentNode = currentNode->lchild;
        }
        if(s.empty())
            break;
        currentNode = s.top();
        std::cout << currentNode->data << " ";
        s.pop();
        currentNode = currentNode -> rchild;
    }
    cout << std::endl;
}

int main() {
    Node *root = NULL;
    pair<bool, Node*> temp;
    int opt, data;
    bool quit = false;
    while(!quit) {
        cout << "Please select one option from below\n";
        cout << "1. Insert element\n";
        cout << "2. Delete element\n";
        cout << "3. Search for an element\n";
        cout << "4. Retrieve the elements of a binary search tree in the sorted order\n";
        cin >> opt;
        switch (opt)
        {
        case 1:
            cout << "How many inserts?\n";
            int n;
            cin >> n;
            cout << "Please insert Integer data to add in element: ";
            for (size_t i = 0; i < n; i++)
            {
                cin >> data;
                insertNode(root, data);
            }
            break;
        case 2:
            cout << "Please insert Integer data to delete: ";
            cin >> data;
            deleteNode(root, data);
            break;
        case 3:
            cout << "Please insert Integer data to search: ";
            cin >> data;
            temp = searchNode(root, data);
            if(temp.first) {
                cout << "Node Found!\n";
            }
            else {
                cout << "Node not found!\n";
            }
            break;
        case 4:
            displayInorderTraversal(root);
            break;
        
        default:
            quit = true;
            break;
        }
    }
    return 0;
}
