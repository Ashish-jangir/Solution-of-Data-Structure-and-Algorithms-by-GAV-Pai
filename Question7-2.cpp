// Evaluate a postfix expression using a linked stack implementation.
// input=A*B-(C+D)+E
// so space in input, no operator else than (), ^, /,*,+,-
#include <iostream>
#include <map>

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

void print_map(std::string_view comment, const std::map<char, int> &m)
{
    std::cout << comment;
    // iterate using C++17 facilities
    for (const auto &[key, value] : m)
    {
        std::cout << '[' << key << "] = " << value << "; ";
    }
    std::cout << '\n';
}

int main()
{
    // std::cout << (int)'a' << (int)'A' << (int)'z' << (int)'Z'; 97 65 122 90
    std::string input;
    std::string output;
    std::map<char, int> prcedence;
    prcedence['('] = 1;
    prcedence[')'] = 1;
    prcedence['^'] = 2;
    prcedence['/'] = 3;
    prcedence['*'] = 3;
    prcedence['+'] = 4;
    prcedence['-'] = 4;
    // print_map("Map: ", prcedence);
    // std::cout << __cplusplus;
    std::cin >> input;
    for (int i = 0; i < input.size(); i++)
    {
        if ((input[i] >= 65 && input[i] <= 90) || (input[i] >= 97 && input[i] <= 122))
        {
            output.push_back(input[i]);
        }
        else if (input[i] == ')')
        {
            if (!isEmpty())
            {
                while (getTop() != '(')
                {
                    output.push_back(getTop());
                    deleteTop();
                }
                deleteTop();
            }
        }
        else
        {
            while (!isEmpty() && prcedence[getTop()] <= prcedence[input[i]])
            {
                if (getTop() == '(')
                {
                    // deleteTop();
                    break;
                }

                output.push_back(getTop());
                deleteTop();
            }
            insertNode(input[i]);
        }
    }
    while (!isEmpty())
    {
        output.push_back(getTop());
        deleteTop();
    }
    for (int i = 0; i < output.size(); i++)
    {
        std::cout << output[i];
    }
    std::cout << std::endl;
}