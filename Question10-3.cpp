/*
Execute a programming project to illustrate the construction of an AVL search tree. Demonstrate the
construction, insertion and deletion operations.
Not done: using graphics and animation.(Not relevent in DSA practice)
*/
#include<iostream>
#include<stack>
using std::pair;
using std::cin;
using std::cout;
using std::stack;

class Node {
    public:
    int data, bf;
    Node *lchild, *rchild;
    Node(int data): data(data), bf(0) {
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
    Node *temp = root, *parent = root, *maxBfNode = NULL;
    while(temp) {
        if(temp->bf == 1 || temp->bf == -1) {
            maxBfNode = temp;
        }
        if(temp->data == data) {
            cout << "An element with same data already exists in tree!\n";
            return;
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

    Node *node = new Node(data);
    if(data > parent->data) {
        parent->rchild = node;
    }
    else {
        parent->lchild = node;
    }

    //Checking if there is any scope of tree being unbalanced.
    if(maxBfNode == NULL) {
        //no unbalanced tree. only updating bf till root node will suffice.
        temp = root;
        while(temp != node) {
            if(data > temp->data) {
                temp->bf = -1;
                temp = temp->rchild;
            }
            else {
                temp->bf = 1;
                temp = temp->lchild;
            }
        }
        return;
    }

    //Balancing of tree starts here.
    if(maxBfNode != NULL) {
        if((maxBfNode->bf == 1 && data > maxBfNode->data) || (maxBfNode->bf == -1 && data < maxBfNode->data)) {
            maxBfNode->bf = 0;
            temp = maxBfNode;
            while(temp != parent) {
                if(data > temp->data) {
                    temp->bf = -1;
                    temp = temp->rchild;
                }
                else {
                    temp->bf = 1;
                    temp = temp->lchild;
                }
            }
            return;
        }
        else {
            maxBfNode->bf = maxBfNode->bf > 0 ? 2:-2;
            //apply rotation.
            Node *parentOfUnbalancedBF = root, *unbalancedBF = root;
            while(parentOfUnbalancedBF != node) {
                if(data > parentOfUnbalancedBF->data) {
                    if(abs(parentOfUnbalancedBF->rchild->bf) == 2) {
                        unbalancedBF = parentOfUnbalancedBF->rchild;
                        break;
                    }
                    parentOfUnbalancedBF = parentOfUnbalancedBF->rchild;
                }
                else {
                    if(abs(parentOfUnbalancedBF->lchild->bf) == 2) {
                        unbalancedBF = parentOfUnbalancedBF->lchild;
                        break;
                    }
                    parentOfUnbalancedBF = parentOfUnbalancedBF->lchild;
                }
            }
            
            Node* &subroot = abs(root->bf) == 2 ? root : (parentOfUnbalancedBF->lchild == unbalancedBF ? parentOfUnbalancedBF->lchild: parentOfUnbalancedBF->rchild);
            
            if(data < unbalancedBF->data && data < unbalancedBF->lchild->data) {
                //LL rotation
                Node* newRoot = unbalancedBF->lchild;
                subroot = newRoot;
                unbalancedBF->lchild = newRoot->rchild;
                newRoot->rchild = unbalancedBF;
                
            }
            else if(data < unbalancedBF->data && data > unbalancedBF->lchild->data) {
                //LR rotation
                Node* newRoot = unbalancedBF->lchild->rchild, *childOfUnbalancedBF = unbalancedBF->lchild;
                subroot = newRoot;
                unbalancedBF->rchild = newRoot->lchild;
                newRoot->rchild = unbalancedBF;
                childOfUnbalancedBF->rchild = newRoot->lchild;
                newRoot->lchild = childOfUnbalancedBF;
            }
            else if(data > unbalancedBF->data && data > unbalancedBF->lchild->data) {
                //RR rotation
                Node* newRoot = unbalancedBF->rchild;
                subroot = newRoot;
                unbalancedBF->rchild = newRoot->lchild;
                newRoot->lchild = unbalancedBF;
            }
            else if(data > unbalancedBF->data && data < unbalancedBF->lchild->data) {
                //RL rotation
                Node* newRoot = unbalancedBF->rchild->lchild, *childOfUnbalancedBF = unbalancedBF->rchild;
                subroot = newRoot;
                unbalancedBF->lchild = newRoot->rchild;
                newRoot->lchild = unbalancedBF;
                childOfUnbalancedBF->lchild = newRoot->rchild;
                newRoot->rchild = childOfUnbalancedBF;
            }
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