// xecute a program to implement a linked stack to check for the balancing of the following
// pairs of symbols in a Pascal program. The name of the source Pascal program is the sole
// input to the program.
// Symbols: begin end , ( ), [ ], { }.
//(i) Output errors encountered during mismatch of symbols.
//(ii) Modify the program to set right the errors.
#include <iostream>
#include <string>

class Node
{
public:
    char data;
    Node *link;
    Node(char data)
    {
        this->data = data;
        link = NULL;
    }
} *start = NULL, *end = NULL;

void insertNode(char data)
{
    if (start == NULL)
    {
        start = new Node(data);
        end = start;
    }
    else
    {
        end->link = new Node(data);
        end = end->link;
    }
}

void deleteTop()
{

    if (end == NULL)
    {
        throw "stack underflow";
    }
    else if (start == end && start != NULL)
    {
        start = NULL;
        end = NULL;
    }
    else
    {
        Node *temp = start;
        while (temp->link != end)
            temp = temp->link;
        end = temp;
        end->link = NULL;
    }
}

bool isEmpty()
{
    if (end == NULL)
        return true;
    else
        return false;
}

char getTop()
{
    return end->data;
}

char expactedChar(char ch)
{
    char expacted = '0';
    if (ch == '(')
        expacted = ')';
    else if (ch == '[')
        expacted = ']';
    else if (ch == '{')
        expacted = '}';
    else if (ch == '<')
        expacted = '>';
    return expacted;
}

void printStack()
{
    if (start == end && start == NULL)
    {
        std::cout << "Empty stack";
    }
    else if (start == end)
    {
        std::cout << start->data << " ";
    }
    else
    {
        Node *temp = start;
        while (true)
        {
            std::cout << temp->data << " ";
            temp = temp->link;
            if (temp == end)
                break;
        }
    }
    std::cout << std::endl;
}

int main()
{
    char ch;
    bool shouldquit = false;
    std::string sym;
    std::string input;
    std::cout << "Start typing your pascal program. When completed type quit to end the program" << std::endl;
    int line = 0;
    while (!shouldquit)
    {
        line++;
        getline(std::cin, input);

        for (int i = 0; i < input.size(); i++)
        {
            ch = input[i];
            std::string temp = sym + ch;
            if (ch == '(' || ch == '[' || ch == '{')
            {
                sym.clear();
                insertNode(ch);
            }
            else if ((temp.find("begin") != std::string::npos || temp.find("BEGIN") != std::string::npos))
            {
                sym.clear();
                insertNode('<');
            }
            else if (ch == ')' || ch == ']' || ch == '}')
            {
                sym.clear();
                char top = getTop();
                char expactedCh = expactedChar(top);
                if (ch != expactedCh)
                {
                    std::cout << std::endl
                              << "Incorrect syntax. " << expactedCh
                              << " is expacted now" << std::endl;
                }
                else
                {
                    deleteTop();
                }
            }
            else if ((temp.find("end") != std::string::npos || temp.find("END") != std::string::npos))
            {
                sym.clear();
                ch = '>';
                char top = getTop();
                char expactedCh = expactedChar(top);
                if (ch != expactedCh)
                {
                    std::cout << std::endl
                              << "Incorrect syntax. " << expactedCh
                              << " is expacted now" << std::endl;
                }
                else
                {
                    deleteTop();
                }
            }
            else if (input == "quit")
            {
                if (isEmpty())
                    std::cout << std::endl
                              << "syntax of the program is correct";
                else
                {
                    printStack();
                    std::cout << std::endl
                              << "error in the syntax";
                }
                shouldquit = true;
                break;
            }
            else
            {
                sym.push_back(ch);
            }
        }

        std::cout << std::endl
                  << "Line: " << line << " Stack: ";
        printStack();
    }
}