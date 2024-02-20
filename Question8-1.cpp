/*Write a program to input a binary tree implemented as a linked representation. Execute
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

*/
#include<iostream>

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
        std::cout << currentNode->data << "\t";
        INORDER_TRAVERSAL(currentNode->rchild);
    }
}

void POSTORDER_TRAVERSAL(Node *currentNode) {
    if(currentNode != NULL) {
        POSTORDER_TRAVERSAL(currentNode->lchild);
        POSTORDER_TRAVERSAL(currentNode->rchild);
        std::cout << currentNode->data << "\t";
    }
}

void PREORDER_TRAVERSAL(Node *currentNode) {
    if(currentNode != NULL) {
        std::cout << currentNode->data << "\t";
        PREORDER_TRAVERSAL(currentNode->lchild);
        PREORDER_TRAVERSAL(currentNode->rchild);
    }
}

int main() {
    Node *root = NULL;
    Queue *queue = createQueue(SIZE);

    int n;
    std::cout << "Please enter the number of elements to be inserted in tree: ";
    std::cin >> n;
    for(int i = 0; i < n; i++) {
        insert(&root, i, queue);
    }

    PREORDER_TRAVERSAL(root);
    return 0;
}