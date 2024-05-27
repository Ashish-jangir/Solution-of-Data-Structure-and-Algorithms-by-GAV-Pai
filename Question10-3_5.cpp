/*
Question: 3
Execute a programming project to illustrate the construction of an AVL search tree. Demonstrate the
construction, insertion and deletion operations.
Not done: using graphics and animation.(Not relevent in DSA practice)

Question: 5
Implement an algorithm which given an AVL search tree T and a data item X
splits the AVL search tree into two AVL search trees T_1, T_2 such that all the keys in
tree T_1 are less than or equal to X and all the keys in tree T_2 are greater than X,
respectively.
*/
#include <iostream>
#include <stack>
#include <queue>
using std::cin;
using std::cout;
using std::pair;
using std::stack;
using std::queue;

class Node
{
public:
    int data, bf;
    Node *lchild, *rchild;
    Node(int data) : data(data), bf(0)
    {
        lchild = NULL;
        rchild = NULL;
    }
};

pair<bool, Node *> searchNode(Node *, int);
Node *rotateRight(Node *);
Node *rotateLeftRight(Node *);
Node *rotateLeft(Node *);
Node *rotateRightLeft(Node *);

int CALCULATE_HEIGHT(Node* currentNode) {
    int leftHeight, rightHeight;
    if(currentNode == NULL) {
        return 0;
    }
    else {
        leftHeight = CALCULATE_HEIGHT(currentNode->lchild);
        rightHeight = CALCULATE_HEIGHT(currentNode->rchild);
        if(leftHeight > rightHeight) {
            return(leftHeight + 1);
        }
        else {
            return(rightHeight + 1);
        }
    }
}

void insertNode(Node *&root, int data)
{

    if (root == nullptr)
    {
        root = new Node(data);
        return;
    }

    // Perform BST insertion
    Node *current = root;
    Node *parent = nullptr;
    stack<Node *> ancestors;

    while (current)
    {
        if (current->data == data)
        {
            cout << "An element with the same data already exists in the tree!\n";
            return;
        }
        parent = current;
        ancestors.push(parent);
        if (data < current->data)
            current = current->lchild;
        else
            current = current->rchild;
    }
    // Insert the new node
    Node *newNode = new Node(data);
    if (data < parent->data)
        parent->lchild = newNode;
    else
        parent->rchild = newNode;

    // Update balance factors and perform rotations if necessary
    while (!ancestors.empty())
    {
        parent = ancestors.top();
        int parentData = parent->data;
        ancestors.pop();
        if (newNode == parent->lchild)
            parent->bf++;
        else
            parent->bf--;
        if (parent->bf == 0) // If balance factor becomes 0, no rotations needed
            break;
        if (parent->bf == -2 || parent->bf == 2)
        {
            // Perform rotations
            if (parent->bf == 2)
            {
                if (newNode->bf > 0)
                {
                    // Left-Left case
                    parent = rotateRight(parent);
                }
                else
                {
                    // Left-Right case
                    parent = rotateLeftRight(parent);
                }
            }
            else
            {
                if (newNode->bf < 0)
                {
                    // Right-Right case
                    parent = rotateLeft(parent);
                }
                else
                {
                    // Right-Left case
                    parent = rotateRightLeft(parent);
                }
            }
            if (!ancestors.empty())
            {
                if (parentData == ancestors.top()->lchild->data)
                    ancestors.top()->lchild = parent;
                else
                    ancestors.top()->rchild = parent;
            }
            else
            {
                root = parent;
            }
            break; // Tree balanced after rotations
        }
        newNode = parent;
    }
}

Node *rotateRight(Node *parent)
{
    Node *newRoot = parent->lchild;
    newRoot->bf = 0;
    parent->bf = 0;
    parent->lchild = newRoot->rchild;
    newRoot->rchild = parent;
    return newRoot;
}

Node *rotateLeftRight(Node *parent)
{
    Node *newRoot = parent->lchild->rchild, *childOfUnbalancedBF = parent->lchild;
    childOfUnbalancedBF->bf = 0;
    parent->lchild = newRoot->rchild;
    newRoot->rchild = parent;
    childOfUnbalancedBF->rchild = newRoot->lchild;
    newRoot->lchild = childOfUnbalancedBF;
    newRoot->bf = 0;
    parent->bf = CALCULATE_HEIGHT(parent->lchild) - CALCULATE_HEIGHT(parent->rchild);
    childOfUnbalancedBF->bf = CALCULATE_HEIGHT(childOfUnbalancedBF->lchild) - CALCULATE_HEIGHT(childOfUnbalancedBF->rchild);
    return newRoot;
}

Node *rotateLeft(Node *parent)
{
    Node *newRoot = parent->rchild;
    newRoot->bf = 0;
    parent->bf = 0;
    parent->rchild = newRoot->lchild;
    newRoot->lchild = parent;
    return newRoot;
}

Node *rotateRightLeft(Node *parent)
{
    Node *newRoot = parent->rchild->lchild, *childOfUnbalancedBF = parent->rchild;
    childOfUnbalancedBF->bf = 0;
    parent->rchild = newRoot->lchild;
    newRoot->lchild = parent;
    childOfUnbalancedBF->lchild = newRoot->rchild;
    newRoot->rchild = childOfUnbalancedBF;
    newRoot->bf = 0;
    parent->bf = CALCULATE_HEIGHT(parent->lchild) - CALCULATE_HEIGHT(parent->rchild);
    childOfUnbalancedBF->bf = CALCULATE_HEIGHT(childOfUnbalancedBF->lchild) - CALCULATE_HEIGHT(childOfUnbalancedBF->rchild);
    return newRoot;
}

void deleteNode(Node *&root, int data)
{
    Node *temp = root, *parent = root, *current = root;
    // tracking the node to be deleted
    stack<Node *> ancestors;

    while (temp)
    {
        if (temp->data == data)
        {
            break;
        }
        else if (data > temp->data)
        {
            parent = temp;
            ancestors.push(parent);
            temp = temp->rchild;
        }
        else
        {
            parent = temp;
            ancestors.push(parent);
            temp = temp->lchild;
        }
    }
    // deleting the node
    if (temp)
    {
        if (temp->rchild != NULL && temp->lchild != NULL)
        {
            Node *temp2 = temp->rchild, *parent2 = temp->rchild;
            while (temp2->lchild)
            {
                parent2 = temp2;
                ancestors.push(parent2);
                temp2 = temp2->lchild;
            }
            temp->data = temp2->data;
            if(parent2 == temp2) {
                delete (temp2);
                temp->rchild = NULL;
            }
            else {
                delete(temp2);
                parent2->lchild = NULL;
            }
        }
        else if (temp->rchild != NULL)
        {
            if (parent == temp)
            {
                root = temp->rchild;
            }
            else if (parent->lchild == temp)
                parent->lchild = temp->rchild;
            else
                parent->rchild = temp->rchild;
            delete (temp);
        }
        else if (temp->lchild != NULL)
        {
            if (parent == temp)
            {
                root = temp->lchild;
            }
            else if (parent->lchild == temp)
                parent->lchild = temp->lchild;
            else
                parent->rchild = temp->lchild;
            delete (temp);
        }
        else
        {
            if (parent->lchild == temp)
                parent->lchild = NULL;
            else
                parent->rchild = NULL;

            delete (temp);
        }
    }
    else {
        return;
    }
    // updating the bfs and check for imbalance
    while (!ancestors.empty())
    {
        parent = ancestors.top();
        ancestors.pop();

        if (data < parent->data)
        {
            parent->bf--;
        }
        else
        {
            parent->bf++;
        }

        // if(parent->bf == 0)
        //     break;

        // R0 and R1 rotation is same just updation of bf differs while L0 and L-1 is same just updation of bf differs
        if (parent->bf == -2 || parent->bf == 2)
        {
            Node *parentCopy = parent;
            if (parent->bf == 2)
            {
                if (parent->lchild->bf == 0)
                {
                    // its R0 rotation
                    Node *newroot = parent->lchild;
                    parent->lchild = newroot->rchild;
                    newroot->rchild = parent;
                    parent = newroot;
                    parent->bf = -1;
                    parent->rchild->bf = 1;
                }
                else if (parent->lchild->bf == 1)
                {
                    // its R1 rotation
                    Node *newroot = parent->lchild;
                    parent->lchild = newroot->rchild;
                    newroot->rchild = parent;
                    parent = newroot;
                    parent->bf = 0;
                    parent->rchild->bf = 0;
                }
                else
                {
                    // its R-1 rotation
                    Node *newRoot = parent->lchild->rchild, *childOfUnbalancedBF = parent->lchild;
                    parent->lchild = newRoot->rchild;
                    newRoot->rchild = parent;
                    childOfUnbalancedBF->rchild = newRoot->lchild;
                    newRoot->lchild = childOfUnbalancedBF;
                    childOfUnbalancedBF->bf = 0;
                    newRoot->bf = 0;
                    parent->bf = 0;
                    parent = newRoot;
                }
            }
            else
            {
                if (parent->rchild->bf == 0)
                {
                    // its L0 rotation
                    Node *newroot = parent->rchild;
                    parent->rchild = newroot->lchild;
                    newroot->lchild = parent;
                    parent = newroot;
                    parent->bf = 1;
                    parent->lchild->bf = -1;
                }
                else if (parent->rchild->bf == -1)
                {
                    // its L-1 rotation
                    Node *newroot = parent->rchild;
                    parent->rchild = newroot->lchild;
                    newroot->lchild = parent;
                    parent = newroot;
                    parent->bf = 0;
                    parent->lchild->bf = 0;
                }
                else
                {
                    // its L1 rotation
                    Node *newRoot = parent->rchild->lchild, *childOfUnbalancedBF = parent->rchild;
                    parent->rchild = newRoot->lchild;
                    newRoot->lchild = parent;
                    childOfUnbalancedBF->lchild = newRoot->rchild;
                    newRoot->rchild = childOfUnbalancedBF;
                    childOfUnbalancedBF->bf = 0;
                    newRoot->bf = 0;
                    parent->bf = 0;
                    parent = newRoot;
                }
            }

            if (root == parentCopy)
            {
                root = parent;
            }
        }
    }
}

pair<bool, Node *> searchNode(Node *root, int data)
{
    Node *temp = root, *parent = root;
    while (temp)
    {
        if (temp->data == data)
        {
            return {true, temp};
        }
        else if (temp->data < data)
        {
            parent = temp;
            temp = temp->rchild;
        }
        else
        {
            parent = temp;
            temp = temp->lchild;
        }
    }
    return {false, parent};
}

void displayInorderTraversal(Node *root)
{
    if (root == NULL)
    {
        cout << "Tree is empty\n";
        return;
    }

    stack<Node *> s;
    Node *currentNode = root;
    while (1)
    {
        while (currentNode)
        {
            s.push(currentNode);
            currentNode = currentNode->lchild;
        }
        if (s.empty())
            break;
        currentNode = s.top();
        std::cout << currentNode->data << " ";
        s.pop();
        currentNode = currentNode->rchild;
    }
    cout << std::endl;
}

pair<Node*, Node*> splitAVL(Node*root, queue<Node*> q) {
    Node* root1 = root;
    Node* root2 = nullptr;
    while(!q.empty()) {
        Node* front = q.front();
        insertNode(root2, front->data);
        deleteNode(root1, front->data);
        q.pop();
    }
    return {root1, root2};
}

queue<Node *> POSTORDER_TRAVERSAL_NONRECURSIVE(Node *root, int x)
{
    stack<Node*> stack;
    queue<Node*> q;
    Node *previous = NULL;
    Node *currentNode = root;
    do
    {
        while(currentNode) {
            stack.push(currentNode);
            currentNode = currentNode->lchild;
        }
        while(currentNode == NULL && !stack.empty()) {
            currentNode = stack.top();
            if(currentNode->rchild == NULL || currentNode->rchild == previous) {
                if(currentNode->data <= x) {
                    q.push(currentNode);
                }
                stack.pop();
                previous = currentNode;
                currentNode = NULL;
            }
            else {
                currentNode = currentNode->rchild;
            }
        }
    } while (!stack.empty());
    return q;
}

int main()
{
    Node *root = NULL;
    pair<bool, Node *> temp;
    int opt, data;
    bool quit = false;
    pair<Node *, Node *> splitTrees;
    queue<Node*> q;
    while (!quit)
    {
        cout << "Please select one option from below\n";
        cout << "1. Insert element\n";
        cout << "2. Delete element\n";
        cout << "3. Search for an element\n";
        cout << "4. Retrieve the elements of a binary search tree in the sorted order\n";
        cout << "5. Split AVL tree\n";
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
            if (temp.first)
            {
                cout << "Node Found!\n";
            }
            else
            {
                cout << "Node not found!\n";
            }
            break;
        case 4:
            displayInorderTraversal(root);
            break;
        case 5:
            cout << "Please insert the split value: ";
            cin >> data;
            q = POSTORDER_TRAVERSAL_NONRECURSIVE(root, data);
            splitTrees = splitAVL(root, q);
            cout << "Tree 1: ";
            displayInorderTraversal(splitTrees.first);
            cout << "Tree 2: ";
            displayInorderTraversal(splitTrees.second);
            break;
        default:
            quit = true;
            break;
        }
    }
    return 0;
}