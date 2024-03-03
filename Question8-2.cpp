/*
Implement Algorithm 8.4 to convert an infix expression into its postfix form.

Algorithm 8.4:
Procedure to convert infix expression to postfix expression
procedure INFIX_POSTFIX_CONV(E)
    #to convert an infix expression E padded with a "$ "
    #as its end-of-input symbol into its equivalent
    #postfix expression
    x : = getnextchar (E);
    #obtain the next character from E
    while x != "$ " do
        case x of
            : x is an operand: print x;
            : x = ' )': while (top element of stack !='(') do
                print top element of stack and pop stack;
                end while;
                Pop '( ' from stack;
            : else : while ICP (x) £ ISP(top element of stack) do
                print top element of stack and pop stack;
                end while
                push x into stack;
        end case
        x: = getnextchar(E);
    end while
    while stack is non empty do
        print top element of stack and pop stack;
    end while
end INFIX_POSTFIX_CONV.

https://www.geeksforgeeks.org/program-to-convert-infix-notation-to-expression-tree/

*/

#include<iostream>

using std::string;
using std::cin;
using std::cout;

template<typename T>
class Node {
    public:
    Node *link;
    T data;
    Node(T data) {
        link = NULL;
        this->data = data;
    }
};

template<typename U>
class Stack {
    Node<U> *start = NULL, *end = NULL;
    public:
    U getTop() {
        if(end == NULL) {
            return NULL;
        }
        else {
            return end->data;
        }
    }
    void push(U data) {
        Node<U> *node = new Node<U>(data);
        if(start == NULL && end == NULL) {
            start = end = node;
        }
        else {
            end->link = node;
            end = node;
        }
    }
    U pop() {
        if(start == NULL && end == NULL) {
            return NULL;
        }
        else if(start == end) {
            U temp = end->data;
            delete(start);
            start = end = NULL;
            return temp;
        }
        else {
            Node<U> *cursor = start;
            while(cursor->link != end) {
                cursor = cursor->link;
            }
            U temp = end->data;
            delete(end);
            end = cursor;
            return temp;
        }
    }

    bool isEmpty() {
        return (start == NULL && end == NULL);
    }
};

int ICP(char inp) {
    switch (inp)
    {
    case '^':
        return 4;
        break;
    case '*':
        return 2;
        break;
    case '/':
        return 2;
        break;
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    case '(':
        return 4;
        break;
    default:
        return -1;
        break;
    }
}

int ISP(char inp) {
    switch (inp)
    {
    case '^':
        return 3;
        break;
    case '*':
        return 2;
        break;
    case '/':
        return 2;
        break;
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    case '(':
        return 0;
        break;
    default:
        return -1;
        break;
    }
}


string INFIX_POSTFIX_CONV(string E) {
    string output;
    Stack<char> stack = Stack<char>();
    for(int i=0; i < E.size(); i++) {
        if ((E[i] >= 65 && E[i] <= 90) || (E[i] >= 97 && E[i] <= 122))
        {
            output.push_back(E[i]);
        }
        else if(E[i] == ')') {
            while(stack.getTop() != '(') {
                output.push_back(stack.pop());
            }
            stack.pop();
        }
        else {
            while(ICP(E[i]) <= ISP(stack.getTop())) {
                output.push_back(stack.pop());
            }
            stack.push(E[i]);
        }
    }
    while(!stack.isEmpty()) {
        output.push_back(stack.pop());
    }
    return output;
}

int main() {
    cout << "Program for converting infix expression to postfix expression\n";
    cout << "Please insert the infix expression without any space\n";
    string E;
    cin >> E;
    cout << "Postfix expression= " << INFIX_POSTFIX_CONV(E);
    return 0;
}