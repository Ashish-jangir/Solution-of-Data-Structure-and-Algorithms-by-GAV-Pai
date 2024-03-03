/*
Implement a threaded binary tree. Write procedures to insert a node NEW to the left of node
NODE when
(i) the left subtree of NODE is empty, and
(ii) the left subtree of NODE is non-empty.

Solution:
(i) When the left subtree of the given node is empty:
In this case, the new node becomes the left child of the given node. If the left child pointer of the given node is not threaded (i.e., it points to its actual left child), then you can simply set the left child pointer of the given node to the new node. Otherwise, you need to update the thread of the in-order predecessor of the given node to point to the new node, and then set the left child pointer of the given node to the new node.

(ii) When the left subtree of the given node is non-empty:
In this case, the new node becomes the left child of the given node, and the existing left child becomes the left child of the new node. You need to update the thread of the in-order predecessor of the new node to point to the existing left child, and then set the left child pointer of the new node to the existing left child. Finally, set the left child pointer of the given node to the new node.
*/
#include<iostream>
using std::cout;
using std::cin;

template<typename T>
class Node {
    public:
    T data;
    Node *lchild, *rchild;
    bool isLThread, isRThread;
    Node(T data) {
        this->data = data;
        lchild = NULL;
        rchild = NULL;
        isLThread = true;
        isRThread = true;
    }
};

Node<int>* findNode(Node<int>* currentNode, int data);
void replaceReferences(Node<int>* currentNode, Node<int>* root, Node<int>* newNode);
void traverseTree(Node<int>* currentNode);

void insertNodeLeft(Node<int>** root, int data) {
    if(*root == NULL) {
        Node<int> *node = new Node<int>(data);
        *root = node;
    }
    else {
        traverseTree(*root);
        cout<<"Please select the node where you want to insert new data:";
        int nodeData;
        cin >> nodeData;
        Node<int> *nodeFound = findNode(*root, nodeData);
        if(nodeFound) {
            Node<int> *node = new Node<int>(data);
            if(!nodeFound->isLThread) {  //there is a left subtree
                cout<< "There is a left subtree already there, Inserting new node...\n";
                replaceReferences(nodeFound->lchild, nodeFound, node);
                node->isLThread = false;
                node->lchild = nodeFound->lchild;
            }
            else {
                nodeFound->isLThread = false;
            }
            nodeFound->lchild = node;
            node->rchild = nodeFound;
        }

    }
}

Node<int>* findNode(Node<int>* currentNode, int data) {
    while(1) {
        while(!currentNode->isLThread) {
            currentNode = currentNode->lchild;
        }
        while(currentNode->isRThread) {
            if(currentNode->data == data) {
                return currentNode;
            }
            currentNode = currentNode -> rchild;
            if(currentNode == NULL) {
                return NULL;
            }
        }
        if(currentNode->data == data) {
            return currentNode;
        }
        currentNode = currentNode->rchild;
        if(currentNode == NULL) {
            return NULL;
        }
    }
}

void replaceReferences(Node<int>* currentNode, Node<int>* root, Node<int>* newNode) {
    while(1) {
        while(!currentNode->isLThread) {
            currentNode = currentNode->lchild;
        }
        while(currentNode->isRThread) {
            if(currentNode->lchild == root) {
                currentNode->lchild = newNode;
            }
            if(currentNode->rchild == root) {
                currentNode->rchild = newNode;
            }
            currentNode = currentNode -> rchild;
            if(currentNode == NULL) {
                return;
            }
        }
        if(currentNode->lchild == root) {
            currentNode->lchild = newNode;
        }
        if(currentNode->rchild == root) {
            currentNode->rchild = newNode;
        }
        currentNode = currentNode->rchild;
        if(currentNode == NULL) {
            return;
        }
    }
}


void traverseTree(Node<int>* currentNode) {
    if(currentNode == NULL) {
        cout << "Tree is Empty\n";
        return;
    }
    while(1) {
        if(currentNode == NULL) {
            break;
        }
        while(!currentNode->isLThread) {
            currentNode = currentNode->lchild;
        }
        while(currentNode->isRThread) {
            cout << currentNode->data << " ";
            currentNode = currentNode -> rchild;
            if(currentNode == NULL) {
                return;
            }
        }
        cout << currentNode->data << " ";
        currentNode = currentNode->rchild;
    }
}


int main() {
    int opt;
    Node<int> *root = NULL;
    while(true) {
        cout << "Please select option\n1. Insert new node to the left\n2. Inorder Traverse the tree\n";
        cin >> opt;
        switch (opt)
        {
        case 1:
            int data;
            cout << "Please type data to insert\n";
            cin >> data;
            insertNodeLeft(&root, data);
            break;
        case 2:
            traverseTree(root);
            break;
        default:
            break;
        }
    }
    return 0;
}