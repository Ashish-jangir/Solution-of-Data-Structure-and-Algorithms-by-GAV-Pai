/*
1. Write a program to input a binary tree implemented as a linked representation. Execute
Algorithms 8.1-8.3 to perform inorder, postorder and preorder traversals of the binary tree.

Algorithm 8.1:
Recursive procedure to perform Inorder traversal of a binary tree
procedure INORDER_TRAVERSAL (NODE)
    #NODE refers to the Root node of the binary tree
    #in its first call to the procedure. Root node is the
    #starting point of the traversal
    If NODE != NIL then
    { 
        call INORDER_TRAVERSAL (LCHILD(NODE));
        #Inorder traverse the left subtree (L)
        print (DATA (NODE)) ;
        #Process node (P)
        call INORDER_TRAVERSAL (RCHILD(NODE));
        #Inorder traverse the right subtree (R)
    }
end INORDER_TRAVERSAL.

Algorithm 8.2:
Recursive procedure to perform Postorder traversal of a binary tree
procedure POSTORDER_TRAVERSAL (NODE)
    #NODE refers to the Root node of the binary tree
    #in its first call to the procedure. Root node is the
    #starting point of the traversal
    If NODE != NIL then
    { 
        call POSTORDER_TRAVERSAL (LCHILD(NODE));
        #Postorder traverse the left subtree (L)
        call POSTORDER_TRAVERSAL (RCHILD(NODE));
        #Postorder traverse the right subtree (R)
        print (DATA (NODE)) ;
        #Process node (P)
    }
end POSTORDER_TRAVERSAL.

Algorithm 8.3:
Recursive procedure to perform Preorder traversal of a binary tree
procedure PREORDER_TRAVERSAL (NODE)
    #NODE refers to the Root node of the binary tree
    #in its first call to the procedure. Root node is the
    #starting point of the traversal
    If NODE != NIL then
    { 
        print (DATA (NODE)) ;
        #Process node (P)
        call PREORDER_TRAVERSAL (LCHILD(NODE));
        #Preorder traverse the left subtree (L)
        call PREORDER_TRAVERSAL (RCHILD(NODE));
        #Preorder traverse the right subtree (R)
    }
end PREORDER_TRAVERSAL.

3. Write a recursive procedure to count the number of nodes in a binary tree.

5. Write non-recursive procedures to perform the inorder, postorder and preorder traversals of
a binary tree.

6. Level order traversal: It is a kind of binary tree traversal where elements in the binary tree
are traversed by levels, top to bottom and within levels, left to right. Write a procedure to
execute the level order traversal of a binary tree.

7. Implement the ADT of a binary tree in a language of your choice. Include operations to
(i) obtain the height of a binary tree and (ii) the list of leaf nodes.
*/
#include<iostream>
#include <stack>    //we already created stack in problem 8.2 so now using readymade stack

using std::stack;

#define SIZE 50

class Node {
    public: 
    Node *lchild, *rchild;
    int data;
};

class Queue {
    public: 
    int front, rear;
    int size;
    Node **array;
};

Node* newNode(int data) {
    Node *newNode = new Node();
    newNode->lchild = newNode->rchild = NULL;
    newNode->data = data;
    return newNode;
}

Queue* createQueue(int size) {
    Queue *queue = new Queue();
    queue->front = queue->rear = -1;
    queue->size = size;
    queue->array = new Node* [size * sizeof(Node*)];

    for(int i = 0; i < size; i++ ) {
        queue->array[i] = NULL;
    }
    return queue;
}

// Standard Queue Functions 
int isEmpty(Queue* queue) 
{ 
    return queue->front == -1; 
} 
 
int isFull(Queue* queue) 
{ return queue->rear == queue->size - 1; } 
 
int hasOnlyOneItem(Queue* queue) 
{ return queue->front == queue->rear; } 

void Enqueue(Node *data, Queue *queue) {
    if(isFull(queue)) {
        std::cout << "Queue is already full\n";
    }
    else if(isEmpty(queue)) {
        queue->array[queue->rear + 1] = data;
        queue->rear++;
        queue->front++;
    }
    else {
        queue->array[queue->rear + 1] = data;
        queue->rear++;
    }
}

Node* Dequeue(Queue *queue) {
    if(isEmpty(queue)) {
        return NULL;
    }
    Node *front = queue->array[queue->front];
    if(hasOnlyOneItem(queue)) {
        queue->front = -1;
        queue->rear = -1;
    }
    else {
        queue->front++;
    }
    return front;
}

Node* getFront(Queue *queue) {
    if(isEmpty(queue)) {
        return NULL;
    }
    else {
        return queue->array[queue->front];
    }
}

bool hasBothChild(Node *node) {
    if(node->lchild != NULL && node->rchild != NULL) {
        return true;
    }
    else {
        return false;
    }
}

void insert(Node **root, int i, Queue *queue) {
    int data;
    std::cin >> data;
    Node *nodeToInsert = newNode(data);
    if(*root == NULL) {
        *root = nodeToInsert;
    } else {
        Node *front = getFront(queue);
        if(front->lchild == NULL) {
            front->lchild = nodeToInsert;
        }
        else if(front->rchild == NULL) {
            front->rchild = nodeToInsert;
        }
        if(hasBothChild(front)) {
            Dequeue(queue);
        }
    }
    Enqueue(nodeToInsert, queue);

}

void INORDER_TRAVERSAL(Node *currentNode) {
    if(currentNode != NULL) {
        INORDER_TRAVERSAL(currentNode->lchild);
        std::cout << currentNode->data << " ";
        INORDER_TRAVERSAL(currentNode->rchild);
    }
}

void INORDER_TRAVERSAL_NONRECURSIVE(Node *currentNode) {
    stack<Node*> stack;
    while(1) {
        while(currentNode) {
            stack.push(currentNode);
            currentNode = currentNode->lchild;
        }
        if(stack.empty())
            break;
        currentNode = stack.top();
        std::cout << currentNode->data << " ";
        stack.pop();
        currentNode = currentNode -> rchild;
    }
}

void POSTORDER_TRAVERSAL(Node *currentNode) {
    if(currentNode != NULL) {
        POSTORDER_TRAVERSAL(currentNode->lchild);
        POSTORDER_TRAVERSAL(currentNode->rchild);
        std::cout << currentNode->data << " ";
    }
}
void POSTORDER_TRAVERSAL_NONRECURSIVE(Node *currentNode) {
    stack<Node*> stack;
    Node *previous = NULL;
    do
    {
        while(currentNode) {
            stack.push(currentNode);
            currentNode = currentNode->lchild;
        }
        while(currentNode == NULL && !stack.empty()) {
            currentNode = stack.top();
            if(currentNode->rchild == NULL || currentNode->rchild == previous) {
                std::cout << currentNode->data << " ";
                stack.pop();
                previous = currentNode;
                currentNode = NULL;
            }
            else {
                currentNode = currentNode->rchild;
            }
        }
    } while (!stack.empty());   
}


void PREORDER_TRAVERSAL(Node *currentNode) {
    if(currentNode != NULL) {
        std::cout << currentNode->data << " ";
        PREORDER_TRAVERSAL(currentNode->lchild);
        PREORDER_TRAVERSAL(currentNode->rchild);
    }
}

void PREORDER_TRAVERSAL_NONRECURSIVE(Node *currentNode) {
    stack<Node*> stack;
    while(1) {
        while(currentNode) {
            std::cout << currentNode->data << " ";
            if(currentNode->lchild)
                stack.push(currentNode);
            currentNode = currentNode->lchild;
        }
        if(stack.empty())
            break;
        currentNode = stack.top();
        stack.pop();
        currentNode = currentNode -> rchild;
    }
}

void PreorderCounting(Node *currentNode, int *count) {
    if(currentNode != NULL) {
        *count += 1;
        PreorderCounting(currentNode->lchild, count);
        PreorderCounting(currentNode->rchild, count);

    }
}

int NumberOfNodes(Node* root) {
    int count = 0;
    PreorderCounting(root, &count);
    return count;
}

void LEVEL_ORDER_TRAVERSAL(Node *root) {
    Queue *queue = createQueue(SIZE);
    Enqueue(root, queue);
    while(!isEmpty(queue)) {
        Node *node = Dequeue(queue);
        std::cout << node->data << " ";
        if(node->lchild)
            Enqueue(node->lchild, queue);
        if(node->rchild)
            Enqueue(node->rchild, queue);
    }    
}

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

void listLeafNodes(Node *currentNode) {
    if(currentNode->lchild == NULL && currentNode->rchild == NULL) {
        std::cout << currentNode->data << " ";
    }
    else {
        if(currentNode->lchild)
            listLeafNodes(currentNode->lchild);
        if(currentNode->rchild)
            listLeafNodes(currentNode->rchild);
    }
}

int main() {
    Node *root = NULL;
    Queue *queue = createQueue(SIZE);

    int n;
    std::cout << "Please enter the number of elements to be inserted in tree: \n";
    std::cin >> n;
    for(int i = 0; i < n; i++) {
        insert(&root, i, queue);
    }
    int opt;
    bool quit = false;
    while(!quit) {
        std::cout<< "\nPlease select the operation\n";
        std::cout<< "0. To Quit\n";
        std::cout<< "1. Preorder Traversal\n";
        std::cout<< "2. Inorder Traversal\n";
        std::cout<< "3. Postorder Traversal\n";
        std::cout<< "4. Count number of nodes\n";
        std::cout<< "5. Preorder Traversal NonRecursive\n";
        std::cout<< "6. Inorder Traversal NonRecursive\n";
        std::cout<< "7. Postorder Traversal NonRecursive\n";
        std::cout<< "8. Level order traversal\n";
        std::cout<< "9. Calculate the height of tree\n";
        std::cout<< "10. The list of leaf nodes\n";
        std::cin >> opt;
        switch (opt) {
            case 0:
                quit = true;
                break;
            case 1:
                PREORDER_TRAVERSAL(root);
                break;
            case 2:
                INORDER_TRAVERSAL(root);
                break;
            case 3:
                POSTORDER_TRAVERSAL(root);
                break;
            case 4:
                std::cout << "Number of Nodes: " << NumberOfNodes(root) << std::endl;
                break;
            case 5:
                PREORDER_TRAVERSAL_NONRECURSIVE(root);
                break;
            case 6:
                INORDER_TRAVERSAL_NONRECURSIVE(root);
                break;
            case 7:
                POSTORDER_TRAVERSAL_NONRECURSIVE(root);
                break;
            case 8:
                LEVEL_ORDER_TRAVERSAL(root);
                break;
            case 9:
                std::cout << "Height of the tree: " << CALCULATE_HEIGHT(root);
                break;
            case 10:
                listLeafNodes(root);
                break;
            default:
                break;
        }
    }
    return 0;
}