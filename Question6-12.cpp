//List implemented using singly linked list and two sorted lists are merged.
// Oops concepts are used here. 
#include<iostream>

class List {
    int size = 0;
    class Node {
        public:
        int data;
        Node *next;
    } *start=NULL, *end=NULL;

    // List() {
    //     start = NULL;
    //     end = NULL;
    // }

    public:
    int Size() {
        return size;
    }
    int First() {
        return start->data;
    }
    void display() {
        Node *temp = start;
        while(temp != end) {
            std::cout<<temp->data << " ";
            temp = temp->next;
        }
        std::cout<< temp->data << std::endl;
    }

    Node* createNode(int data) {
        Node *p = new Node;
        p->next = NULL;
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
            temp = start;
            start = start->next;
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
        }
    }

    void insertAt(int data, int pos) {
        Node *node = createNode(data);
        Node *temp = start;
        if(pos==1) {
            node->next = start;
            start = node;
        }
        else if(temp == NULL) {	
            std::cout<<"List is Empty"<< std::endl;
        }
        else {
            for(int i = 1; i < pos; i++) {
                if( temp->next == NULL && i<pos-1) {
                    std::cout<<"List's size is only "<< i;
                    break;
                }
                else if(i == pos - 1) {
                    if(temp == end)
                        end = node;
                    node->next = temp->next;
                    temp->next = node;
                }
                else {
                    temp = temp->next;
                }
            }
        }
        size++;
    }

    void delAt(int pos) {
        Node *temp = start;
        if(pos==1) {
            start = start->next;
            delete(temp);
        }
        else if(temp == NULL) {	
            std::cout<<"List is Empty"<< std::endl;
        }
        else {
            for(int i = 1; i < pos; i++) {
                if( temp->next == NULL && i<=pos-1) {
                    std::cout<<"List's size is only "<< i;
                    break;
                }
                else if(i == pos - 1) {
                    Node *temp2 = temp->next;
                    if(temp->next == end)
                        end = temp;
                    temp->next = temp->next->next;
                    delete(temp2);
                    size--;
                    display();
                }
                else {
                    temp = temp->next;
                }
            }
        }	
    }
    friend List merge(List, List);
};

List merge(List a, List b) {
    int size1 = a.Size();
    int size2 = b.Size();
    List::Node *temp1 = a.start, *temp2 = b.start;
    List c;
    for(int i = 0; i < size1 + size2; i++) {
        if(temp1 == NULL) {
            c.insertEnd(temp2->data);
            temp2 = temp2->next;
        }
        else if(temp2 == NULL) {
            c.insertEnd(temp1->data);
            temp1 = temp1->next;
        }
        else if(temp1->data > temp2->data) {
            c.insertEnd(temp2->data);
            temp2 = temp2->next;
        }
        else {
            c.insertEnd(temp1->data);
            temp1 = temp1->next;
        }
    }
    return c;
}

int main() {
    List list,list2;
    list.insertEnd(1);
    list.insertEnd(2);
    list.insertEnd(5);
    list.insertEnd(6);
    list.insertEnd(9);
    list2.insertEnd(3);
    list2.insertEnd(4);
    list2.insertEnd(7);
    list2.insertEnd(8);
    list.display();

    list2 = merge(list, list2);
    list2.display();
    return 0;
}