// It's personal opinion so no need to offend but while making this program i realised that multiply linked list is worst data structure to implement.
// Multiply linked list is of no use.
// Instead of doing these problems solve leetcode dsa questions.
// Don't even waste your time to read this code just execute it to see all requrements meet and get done with it.
#include <iostream>
#include <string>
using std::string;

class Node
{
public:
    int rollNo;
    string Name;
    Node *theory1;
    Node *theory2;
    Node *lab1;
    Node *lab2;
    Node *elective;
} *os = NULL, *dsa = NULL, *la = NULL, *cn = NULL, *toc = NULL, *compiler = NULL, *agt = NULL, *fl = NULL, *osLab = NULL, *dsaLab = NULL, *cnLab = NULL, *tocLab = NULL;

Node *CreateNode(int rollNo, string name)
{
    Node *p = new Node;
    p->rollNo = rollNo;
    p->Name = name;
    p->theory1 = NULL;
    p->theory2 = NULL;
    p->lab1 = NULL;
    p->lab2 = NULL;
    p->elective = NULL;
    return p;
}

void Insert(int rollNo, string name, Node **th1, Node **th2, Node **elec, Node **lab1, Node **lab2)
{
    Node *node = CreateNode(rollNo, name);

    if (*th1 == NULL)
    {
        *th1 = node;
    }
    else
    {
        Node *temp = *th1;
        while (temp->theory1 != NULL)
        {
            temp = temp->theory1;
        }
        temp->theory1 = node;
    }

    if (*th2 == NULL)
    {
        *th2 = node;
    }
    else
    {
        Node *temp = *th2;
        while (temp->theory2 != NULL)
        {
            temp = temp->theory2;
        }
        temp->theory2 = node;
    }

    if (*elec == NULL)
    {
        *elec = node;
    }
    else
    {
        Node *temp = *elec;
        while (temp->elective != NULL)
        {
            temp = temp->elective;
        }
        temp->elective = node;
    }

    if (*lab1 == NULL)
    {
        *lab1 = node;
    }
    else
    {
        Node *temp = *lab1;
        while (temp->theory2 != NULL)
        {
            temp = temp->theory2;
        }
        temp->theory2 = node;
    }

    if (*lab2 == NULL)
    {
        *lab2 = node;
    }
    else
    {
        Node *temp = *lab2;
        while (temp->elective != NULL)
        {
            temp = temp->elective;
        }
        temp->elective = node;
    }
}

void InsertElement()
{
    int rollNo, temp;
    Node **th1, **th2, **lab1, **lab2, **elec;
    string name;
    std::cout << "Enter rollNo and name.." << std::endl;
    std::cin >> rollNo;
    std::cin.ignore();
    getline(std::cin, name);
lable:
    std::cout << "Select Theory 1 subject\n1. Operating System\n2. Data structure and algorithm\n3. Linear Algebra\n";
    std::cin >> temp;
    if (temp == 1)
    {
        th1 = &os;
    }
    else if (temp == 2)
    {
        th1 = &dsa;
    }
    else if (temp == 3)
    {
        th1 = &la;
    }
    else
    {
        std::cout << "invalid input\n";
        goto lable;
    }
lable2:
    std::cout << "Select Theory 2 subject\n1. Computer Networks\n2. Theory of Computation\n3. Compiler\n";
    std::cin >> temp;
    if (temp == 1)
    {
        th2 = &cn;
    }
    else if (temp == 2)
    {
        th2 = &toc;
    }
    else if (temp == 3)
    {
        th2 = &compiler;
    }
    else
    {
        std::cout << "invalid input\n";
        goto lable2;
    }
lable3:
    std::cout << "Select elective subject\n1. Advanced Graph Theory\n2. Fuzzy Logic\n";
    std::cin >> temp;
    if (temp == 1)
    {
        elec = &agt;
    }
    else if (temp == 2)
    {
        elec = &fl;
    }
    else
    {
        std::cout << "invalid input\n";
        goto lable3;
    }
lable4:
    std::cout << "Select Lab 1 subject\n1. Operating System Lab\n2. Data structure and algorithm Lab\n";
    std::cin >> temp;
    if (temp == 1)
    {
        lab1 = &osLab;
    }
    else if (temp == 2)
    {
        lab1 = &dsaLab;
    }
    else
    {
        std::cout << "invalid input\n";
        goto lable4;
    }
lable5:
    std::cout << "Select Lab 2 subject\n1. Computer Networks Lab\n2. Theory of Computation Lab\n ";
    std::cin >> temp;
    if (temp == 1)
    {
        lab2 = &cnLab;
    }
    else if (temp == 2)
    {
        lab2 = &tocLab;
    }
    else
    {
        std::cout << "invalid input\n";
        goto lable5;
    }
    Insert(rollNo, name, th1, th2, elec, lab1, lab2);
}

void Display(Node **ptr)
{
    int count = 0;
    if (ptr == &os || ptr == &dsa || ptr == &la)
    {
        Node *temp = *ptr;
        if (temp != NULL)
            while (1)
            {
                count++;
                std::cout << temp->rollNo << " " << temp->Name << std::endl;
                if (temp->theory1 == NULL)
                {
                    break;
                }
                temp = temp->theory1;
            }
    }
    else if (ptr == &cn || ptr == &toc || ptr == &compiler)
    {
        Node *temp = *ptr;
        if (temp != NULL)
            while (1)
            {
                count++;
                std::cout << temp->rollNo << " " << temp->Name << std::endl;
                if (temp->theory2 == NULL)
                {
                    break;
                }
                temp = temp->theory2;
            }
    }
    else if (ptr == &osLab || ptr == &dsaLab)
    {
        Node *temp = *ptr;
        if (temp != NULL)
            while (1)
            {
                count++;
                std::cout << temp->rollNo << " " << temp->Name << std::endl;
                if (temp->lab1 == NULL)
                {
                    break;
                }
                temp = temp->lab1;
            }
    }
    else if (ptr == &cnLab || ptr == &tocLab)
    {
        Node *temp = *ptr;
        if (temp != NULL)
            while (1)
            {
                count++;
                std::cout << temp->rollNo << " " << temp->Name << std::endl;
                if (temp->lab2 == NULL)
                {
                    break;
                }
                temp = temp->lab2;
            }
    }
    else if (ptr == &agt || ptr == &fl)
    {
        Node *temp = *ptr;
        if (temp != NULL)
            while (1)
            {
                count++;
                std::cout << temp->rollNo << " " << temp->Name << std::endl;
                if (temp->elective == NULL)
                {
                    break;
                }
                temp = temp->elective;
            }
    }
    if (count == 0)
    {
        std::cout << "No student enrolled in this course\n";
    }
    else
    {
        std::cout << "Total no of student enrolled in it: " << count << std::endl;
    }
}

Node **Menu()
{
    std::cout << "Enter the option:\n1. OS\n2. DSA\n3. LA\n4. CN\n5. TOC\n6. Compiler\n";
    std::cout << "7. OS LAB\n8. DSA LAB\n9. CN LAB\n10. TOC LAB\n11. AGT\n12. FL";
    int opt2;
    std::cin >> opt2;
    switch (opt2)
    {
    case 1:
        return (&os);
        break;
    case 2:
        return (&dsa);
        break;
    case 3:
        return (&la);
        break;
    case 4:
        return (&cn);
        break;
    case 5:
        return (&toc);
        break;
    case 6:
        return (&compiler);
        break;
    case 7:
        return (&osLab);
        break;
    case 8:
        return (&dsaLab);
        break;
    case 9:
        return (&cnLab);
        break;
    case 10:
        return (&tocLab);
        break;
    case 11:
        return (&agt);
        break;
    case 12:
        return (&fl);
        break;
    }
}

void Update(int rolln, Node **curr, Node **New)
{
    Node *temp = *curr;
    if (curr == &os || curr == &dsa || curr == &la)
    {
        if (temp->theory1 == NULL)
            *curr = NULL;
        else
        {
            while (1)
            {
                if (temp->theory1->rollNo == rolln)
                {
                    break;
                }
                temp = temp->theory1;
            }
            Node *old = temp->theory1;
            temp->theory1 = temp->theory1->theory1;
            temp = old;
            temp->theory1 = NULL;
        }
    }
    else if (curr == &cn || curr == &toc || curr == &compiler)
    {
        if (temp->theory1 == NULL)
            *curr = NULL;
        else
        {
            while (1)
            {
                if (temp->theory2->rollNo == rolln)
                {
                    break;
                }
                temp = temp->theory2;
            }
            Node *old = temp->theory2;
            temp->theory2 = temp->theory2->theory2;
            temp = old;
            temp->theory2 = NULL;
        }
    }
    else if (curr == &osLab || curr == &dsaLab)
    {
        if (temp->theory1 == NULL)
            *curr = NULL;
        else
        {
            while (1)
            {
                if (temp->lab1->rollNo == rolln)
                {
                    break;
                }
                temp = temp->lab1;
            }
            Node *old = temp->lab1;
            temp->lab1 = temp->lab1->lab1;
            temp = old;
            temp->lab1 = NULL;
        }
    }
    else if (curr == &cnLab || curr == &tocLab)
    {
        if (temp->theory1 == NULL)
            *curr = NULL;
        else
        {
            while (1)
            {
                if (temp->lab2->rollNo == rolln)
                {
                    break;
                }
                temp = temp->lab2;
            }
            Node *old = temp->lab2;
            temp->lab2 = temp->lab2->lab2;
            temp = old;
            temp->lab2 = NULL;
        }
    }
    else
    {
        if (temp->theory1 == NULL)
            *curr = NULL;
        else
        {
            while (1)
            {
                if (temp->elective->rollNo == rolln)
                {
                    break;
                }
                temp = temp->elective;
            }
            Node *old = temp->elective;
            temp->elective = temp->elective->elective;
            temp = old;
            temp->elective = NULL;
        }
    }

    Node *temp2 = *New;
    if (New == &os || New == &dsa || New == &la)
    {
        if (temp2 == NULL)
        {
            *New = temp;
        }
        else
        {
            while (temp2->theory1 != NULL)
            {
                temp2 = temp2->theory1;
            }
            temp2->theory1 = temp;
        }
    }
    else if (New == &cn || New == &toc || New == &compiler)
    {
        if (temp2 == NULL)
        {
            *New = temp;
        }
        else
        {
            while (temp2->theory2 != NULL)
            {
                temp2 = temp2->theory2;
            }
            temp2->theory2 = temp;
        }
        temp->theory2 = NULL;
    }
    else if (New == &osLab || New == &dsaLab)
    {
        if (temp2 == NULL)
        {
            *New = temp;
        }
        else
        {
            while (temp2->lab1 != NULL)
            {
                temp2 = temp2->lab1;
            }
            temp2->lab1 = temp;
        }
        temp->lab1 = NULL;
    }
    else if (New == &cnLab || New == &tocLab)
    {
        if (temp2 == NULL)
        {
            *New = temp;
        }
        else
        {
            while (temp2->lab2 != NULL)
            {
                temp2 = temp2->lab2;
            }
            temp2->lab2 = temp;
        }
        temp->lab2 = NULL;
    }
    else
    {
        if (temp2 == NULL)
        {
            *New = temp;
        }
        else
        {
            while (temp2->elective != NULL)
            {
                temp2 = temp2->elective;
            }
            temp2->elective = temp;
        }
        temp->elective = NULL;
    }
}

int main()
{
    int n;
    std::cout << "Enter the size: ";
    std::cin >> n;
    std::cout << "Now Enter records.." << std::endl;
    for (int i = 0; i < n; i++)
    {
        InsertElement();
    }
    while (1)
    {
        std::cout << "Choose an following option\n1. Display the list and count of perticular subject";
        std::cout << "\n2. Insert a new record\n3. Update information of an user\n";
        int opt;
        std::cin >> opt;
        switch (opt)
        {
        case 1:
            Display(Menu());
            break;
        case 2:
            InsertElement();
            break;
        case 3:
            std::cout << "Enter The roll no. and current subject and new subject\n";
            int rolln;
            std::cin >> rolln;
            Node **curr = Menu();
            Node **New = Menu();
            Update(rolln, curr, New);
            break;
        }
    }
}