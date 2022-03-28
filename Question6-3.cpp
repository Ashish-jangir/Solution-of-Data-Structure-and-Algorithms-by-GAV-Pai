// Program for doubly linked list
#include <iostream>

class Node
{
public:
    int data;
    Node *pre, *next;
} *start = NULL, *end = NULL;

void display()
{
    if (start == NULL)
    {
        std::cout << "List is empty" << std::endl;
    }
    else
    {
        Node *temp = start;
        while (1)
        {
            if (temp == end)
            {
                std::cout << temp->data << " ";
                break;
            }
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
}

Node *createNode(int data)
{
    Node *node = new Node;
    node->data = data;
    node->pre = NULL;
    node->next = NULL;
    return node;
}
void insertBeg(int data)
{
    Node *node = createNode(data);
    if (start == NULL)
    {
        start = node;
        end = node;
    }
    else
    {
        node->next = start;
        start->pre = node;
        start = node;
    }
}

void insertEnd(int data)
{
    Node *node = createNode(data);
    if (start == NULL)
    {
        start = node;
        end = node;
    }
    else
    {
        end->next = node;
        node->pre = end;
        end = node;
    }
}

void delBeg()
{
    if (start == NULL)
    {
        std::cout << "List is empty" << std::endl;
    }
    else if (start == end)
    {
        delete (start);
        end = NULL;
        start = NULL;
    }
    else
    {
        Node *temp = start;
        start = start->next;
        start->pre = NULL;
        delete (temp);
    }
    display();
}

void delEnd()
{
    if (start == NULL)
    {
        std::cout << "List is empty" << std::endl;
    }
    else if (start == end)
    {
        delete (start);
        end = NULL;
        start = NULL;
    }
    else
    {
        Node *temp = end;
        end = end->pre;
        end->next = NULL;
        delete (temp);
    }
    display();
}

int main()
{
    int n;
    std::cout << "Enter the size: ";
    std::cin >> n;
    std::cout << "Now Enter numbers.." << std::endl;
    for (int i = 0; i < n; i++)
    {
        int temp;
        std::cin >> temp;
        insertEnd(temp);
    }

    while (1)
    {
        std::cout << "1. Insert at beginning" << std::endl
                  << "2. Insert at end" << std::endl;
        std::cout << "3. Delete at beginning" << std::endl
                  << "4. Delete at end" << std::endl;
        int opt, temp, temp2;
        std::cin >> opt;
        switch (opt)
        {
        case 1:
            std::cin >> temp;
            insertBeg(temp);
            break;
        case 2:
            std::cin >> temp;
            insertEnd(temp);
            break;
        case 3:
            delBeg();
            break;
        case 4:
            delEnd();
            break;
        default:
            break;
        }
        display();
    }
}