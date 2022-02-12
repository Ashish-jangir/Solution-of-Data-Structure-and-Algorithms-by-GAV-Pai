#include <iostream>
#include <ostream>
#include <istream>
#include <string>
using std::istream;
using std::ostream;
using std::string;
class Car;

template <class T>
class DoublyList
{
    int size = 0;
    class Node
    {
    public:
        T data;
        Node *pre, *next;
    } *start = NULL, *end = NULL;

public:
    void display()
    {
        int count = 1;
        if (start == NULL)
        {
            std::cout << "List is empty" << std::endl;
        }
        else
        {
            Node *temp = start;
            while (1)
            {
                std::cout << count++ << "   " << temp->data;
                if (temp == end)
                {
                    break;
                }
                temp = temp->next;
            }
            std::cout << std::endl;
        }
    }
    void query(int a, int b)
    {
        int count = 1;
        if (start == NULL)
        {
            std::cout << "List is empty" << std::endl;
        }
        else
        {
            Node *temp = start;
            while (1)
            {
                if (temp->data.Price() <= b && temp->data.Price() >= a)
                    std::cout << count++ << "   " << temp->data;
                if (temp == end)
                {
                    break;
                }
                temp = temp->next;
            }
            std::cout << std::endl;
        }
    }

    Node *createNode(T data)
    {
        Node *node = new Node;
        node->data = data;
        node->pre = NULL;
        node->next = NULL;
        return node;
    }
    void insertBeg(T data)
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
        size++;
    }

    void insertEnd(T data)
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
        size++;
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
            size--;
            end = NULL;
            start = NULL;
        }
        else
        {
            Node *temp = start;
            start = start->next;
            start->pre = NULL;
            delete (temp);
            size--;
        }
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
            size--;
            end = NULL;
            start = NULL;
        }
        else
        {
            Node *temp = end;
            end = end->pre;
            end->next = NULL;
            delete (temp);
            size--;
        }
    }

    void delAt(int pos)
    {
        Node *temp = start;
        if (pos == 1)
        {
            delBeg();
        }
        else if (temp == NULL)
        {
            std::cout << "List is Empty" << std::endl;
        }
        else
        {
            for (int i = 1; i < pos; i++)
            {
                if (temp->next == NULL && i <= pos - 1)
                {
                    std::cout << "List's size is only " << i;
                    break;
                }
                else if (i == pos - 1)
                {
                    Node *temp2 = temp->next;
                    if (temp->next == end)
                    {
                        end = temp;
                        temp->next = temp->next->next;
                    }
                    else
                    {
                        temp->next = temp->next->next;
                        temp->next->pre = temp;
                    }
                    delete (temp2);
                    size--;
                }
                else
                {
                    temp = temp->next;
                }
            }
        }
    }
    void replaceAt(T data, int pos)
    {
        if (pos > size)
        {
            std::cout << "Please enter the valid index" << std::endl;
        }
        else
        {
            Node *temp = start;
            for (int i = 1; i < pos; i++)
            {
                temp = temp->next;
            }
            temp->data = data;
        }
    }
};

class Car
{
    string model;
    int price;
    string manufacturer;
    int engineCapacity;

public:
    int Price()
    {
        return price;
    }
    Car(string m, int p, string mf, int ec)
    {
        model = m;
        price = p;
        manufacturer = mf;
        engineCapacity = ec;
    }
    Car() {}

    friend ostream &operator<<(ostream &, Car);
    friend istream &operator>>(istream &, Car &);
};

ostream &operator<<(ostream &dout, Car c)
{
    std::cout << c.model << "   " << c.price << "   " << c.manufacturer << "   "
              << c.engineCapacity << "cc" << std::endl;
    return dout;
}

istream &operator>>(istream &din, Car &c)
{
    std::cin >> c.model >> c.price >> c.manufacturer >> c.engineCapacity;
    return din;
}
int main()
{
    std::cout << "The List of Car models with price, manufacturer and engine capacity" << std::endl;
    std::cout << "1. Display the list Of Models" << std::endl;
    std::cout << "2. Insert a new Model" << std::endl;
    std::cout << "3. Delete an Obsolete Model" << std::endl;
    std::cout << "4. Update any Model" << std::endl;
    std::cout << "5. For Quering some specific records" << std::endl;
    DoublyList<Car> l2;
    Car car("Tata Punch", 548000, "TATA", 1199);
    Car car2("Tata Nexon", 729000, "TATA", 1499);
    Car car3("Tata Harrier", 1439000, "TATA", 1956);
    l2.insertEnd(car);
    l2.insertEnd(car2);
    l2.insertEnd(car3);
    while (1)
    {
        std::cout << "Enter the option: ";
        int opt;
        std::cin >> opt;
        Car temp;
        int temp1, temp2;
        switch (opt)
        {
        case 1:
            l2.display();
            break;
        case 2:
            std::cin >> temp;
            l2.insertEnd(temp);
            break;
        case 3:
            std::cout << "Enter the index number of model: ";
            std::cin >> temp1;
            l2.delAt(temp1);
            break;
        case 4:
            std::cout << "Enter the index number of model: ";
            std::cin >> temp1;
            std::cout << "Enter the new details of model..." << std::endl;
            std::cin >> temp;
            l2.replaceAt(temp, temp1);
            break;
        case 5:
            std::cout << "Enter the Range from: ";
            std::cin >> temp1;
            std::cout << "to: ";
            std::cin >> temp2;
            l2.query(temp1, temp2);
            break;
        default:
            break;
        }
    }
    return 0;
}