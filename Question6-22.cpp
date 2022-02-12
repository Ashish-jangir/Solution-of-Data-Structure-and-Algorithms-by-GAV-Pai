#include<iostream>
#include<math.h>

class CircularList {
    int size = 0;
    class Node {
	public:
	int data;
	Node *next;
    }*start=NULL,*end=NULL;

    public:
    void display() {
        Node *temp = start;
        while(temp != end) {
            std::cout<<temp->data << " ";
            temp = temp->next;
        }
        if(temp!=NULL)
            std::cout<< temp->data << std::endl;
    }

    Node* createNode(int data) {
        Node *p = new Node;
        p->next = p;
        p->data = data;
        return p;
    }
    void insertBeg(int data) {
        Node *node = createNode(data);
        if(start == NULL) {
            start = node;
            end = node;
        }
        else {
            end->next = node;
            node->next = start;
            start = node;
        }
        size++;
    }

    void insertEnd(int data) {
        Node *node = createNode(data);
        if (start == NULL) {
            start = node;
            end = node;
        }
        else {
            end->next = node;
            end = node;
            end->next = start;
        }
        size++;
    }

    void delBeg() {
        Node *temp = start;
        if(start == NULL) {
            std::cout << "List is empty" << std::endl;
        }
        else if (start == end) {
            start = NULL;
            end = NULL;
            delete(temp);
            size--;
        }
        else {
            start = start->next;
            end->next = start;
            delete(temp);
            size--;
        }
    }

    void delEnd() {
        Node *temp = start;
        if (start == NULL) {
            std::cout << "List is empty" << std::endl;
        }
        else if (start == end) {
            start = NULL;
            end = NULL;
            delete(temp);
            size--;
        }
        else {
            while(temp->next != end)
                temp = temp->next;
            end = temp;
            delete(temp->next);
            size--;
            end->next = start;
        }
    }
    void split(CircularList &a, CircularList &b) {
        int n;
        n = floor(size/2);
        Node *temp = start;
        for(int i = 0; i < n; i++) {
            a.insertEnd(temp->data);
            temp = temp->next;
        }
        for(int i = n; i < size; i++) {
            b.insertEnd(temp->data);
            temp = temp->next;
        }
    }
};
int main() {
    CircularList l1, l2, l3;
    l1.insertEnd(1);
    l1.insertEnd(2);
    l1.insertEnd(3);
    l1.insertEnd(4);
    l1.insertEnd(5);
    l1.insertEnd(6);
    l1.insertEnd(7);
    l1.insertEnd(8);
    l1.split(l2, l3);
    std::cout << "L2 :";
    l2.display();
    std::cout << "L3 :";
    l3.display();
}