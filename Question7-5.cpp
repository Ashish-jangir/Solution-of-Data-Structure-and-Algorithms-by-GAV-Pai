// Develop a program to simulate a calculator which performs the addition, subtraction,
// multiplication and division of polynomials.
#include<iostream>
using std::pair;

class Node {
    public:
    float coeff;
    float exp;
    Node* link;
    Node(float coeff, float exp) {
        this->coeff = coeff;
        this->exp = exp;
    }
};

void insertNode(Node** front, Node** rear, float coeff, float exp) {
    if(*front == NULL) {
        Node* n = new Node(coeff, exp);
        *front = n;
        *rear = n;
    }
    else {
        Node* n = new Node(coeff, exp);
        (*rear)->link = n;
        *rear = n;
    }
}

void refactorPolynomial(Node **front, Node **rear) {
    Node *curr1 = *front, *curr2 = *front;
    while(curr1 != NULL) {
        curr2 = curr1->link;
        Node* previousNode = curr1;
        while(curr2 != NULL) {
            if(curr1 != curr2 && curr1->exp == curr2->exp) {
                curr1->coeff = curr1->coeff + curr2->coeff;
                previousNode->link = curr2->link;
                delete(curr2);
                curr2 = previousNode->link;
            }
            previousNode = curr2;
            curr2 = curr2->link;
        }
        *rear = curr1;
        curr1 = curr1->link;
    }
}

void DisplayPolynomial(Node* front) {
    Node* curr = front;
    while(curr != NULL) {
        std::cout << (curr->coeff > 0 ? "+":"") << curr->coeff << "x^" << curr->exp;
        curr = curr->link;
    }
    std::cout << std::endl;
}

pair<Node*,Node*> addPolynomials(Node* front1, Node* rear1, Node* front2, Node* rear2) {
    Node *curr1 = front1, *curr2 = front2, *frontOutput = NULL, *rearOutput = NULL;
    while(curr1 != NULL && curr2 != NULL) {
        if(curr1->exp == curr2->exp) {
            float coeff = curr1->coeff + curr2->coeff;
            if(coeff != 0) {
                insertNode(&frontOutput, &rearOutput, curr1->coeff - curr2-> coeff, curr1->exp);
            }
            curr1 = curr1->link;
            curr2 = curr2->link;
        }
        else if(curr1->exp > curr2->exp) {
            insertNode(&frontOutput, &rearOutput, curr1->coeff, curr1->exp);
            curr1 = curr1->link;
        }
        else {
            insertNode(&frontOutput, &rearOutput, curr2->coeff, curr2->exp);
            curr2 = curr2->link;
        }
    }
    if(curr1 != NULL) {
        while(curr1 != NULL) {
            insertNode(&frontOutput, &rearOutput, curr1->coeff, curr1->exp);
            curr1 = curr1->link;
        }
    }
    if(curr2 != NULL) {
        while(curr2 != NULL) {
            insertNode(&frontOutput, &rearOutput, curr2->coeff, curr2->exp);
            curr2 = curr2->link;
        }
    }
    return std::make_pair(frontOutput, rearOutput);
}

pair<Node*,Node*> subtractPolynomials(Node* front1, Node* rear1, Node* front2, Node* rear2) {
    Node *curr1 = front1, *curr2 = front2, *frontOutput = NULL, *rearOutput = NULL;
    while(curr1 != NULL && curr2 != NULL) {
        if(curr1->exp == curr2->exp) {
            float coeff = curr1->coeff - curr2->coeff;
            if(coeff != 0) {
                insertNode(&frontOutput, &rearOutput, curr1->coeff - curr2-> coeff, curr1->exp);
            }
            curr1 = curr1->link;
            curr2 = curr2->link;
        }
        else if(curr1->exp > curr2->exp) {
            insertNode(&frontOutput, &rearOutput, curr1->coeff, curr1->exp);
            curr1 = curr1->link;
        }
        else {
            insertNode(&frontOutput, &rearOutput, -curr2->coeff, curr2->exp);
            curr2 = curr2->link;
        }
    }
    if(curr1 != NULL) {
        while(curr1 != NULL) {
            insertNode(&frontOutput, &rearOutput, curr1->coeff, curr1->exp);
            curr1 = curr1->link;
        }
    }
    if(curr2 != NULL) {
        while(curr2 != NULL) {
            insertNode(&frontOutput, &rearOutput, -curr2->coeff, curr2->exp);
            curr2 = curr2->link;
        }
    }
    return std::make_pair(frontOutput, rearOutput);
}

pair<Node*,Node*> multiplyPolynomials(Node* front1, Node* rear1, Node* front2, Node* rear2) {
    Node *curr1 = front1, *curr2 = front2;
    Node *frontOutput = NULL, *rearOutput = NULL;
    while(curr1 != NULL) {
        while(curr2 != NULL) {
            insertNode(&frontOutput, &rearOutput, curr1->coeff * curr2->coeff, curr1->exp + curr2->exp);
            curr2 = curr2->link;
        }
        curr2 = front2;
        curr1 = curr1->link;
    }
    refactorPolynomial(&frontOutput, &rearOutput);
    return std::make_pair(frontOutput, rearOutput);
}

void dividePolynomials(Node* frontDivisor, Node* rearDivisor, Node* frontDividend, Node* rearDividend) {
    Node *frontQuotient = NULL, *rearQuotient = NULL, *frontRemainder = NULL, *rearRemainder;
    Node *currDividend = frontDividend;
    while(frontDividend->exp >= frontDivisor->exp) {
        float coeff = frontDividend->coeff / frontDivisor->coeff;
        float exp = frontDividend->exp - frontDivisor->exp;
        Node *frontTemp = NULL, *rearTemp = NULL;
        insertNode(&frontTemp, &rearTemp, coeff, exp);
        insertNode(&frontQuotient, &rearQuotient, coeff, exp);
        pair<Node*, Node*> toBeSubtracted = multiplyPolynomials(frontTemp, rearTemp, frontDivisor, rearDivisor);
        pair<Node*, Node*> newDividend = subtractPolynomials(frontDividend, rearDividend, toBeSubtracted.first, toBeSubtracted.second);
        frontDividend = newDividend.first;
        rearDividend = newDividend.second;
    }
    std::cout << "Quotient: ";
    DisplayPolynomial(frontQuotient);
    std::cout << "Remainder: ";
    DisplayPolynomial(frontDividend);
}

int main() {
    Node *front1 = NULL, *rear1 = NULL, *front2 = NULL, *rear2 = NULL;
    std::cout << "Please insert the polynomial 1" << std::endl;
    std::cout << "Please enter the number of segments of polynomial: ";
    int seg;
    std::cin >> seg;
    //std::cout << "Now Please enter the Coefficient and Exponent for " << seg << " segments of polynomial" << std::endl;
    for(int i = 0; i < seg; i++ ) {
        int coeff, exp;
        std::cin >> coeff >> exp;
        insertNode(&front1, &rear1, coeff, exp);
    }

    //std::cout << "Please insert the polynomial 2" << std::endl;
    //std::cout << "Please enter the number of segments of polynomial: ";
    
    std::cin >> seg;
    //std::cout << "Now Please enter the Coefficient and Exponent for " << seg << " segments of polynomial" << std::endl;
    for(int i = 0; i < seg; i++ ) {
        int coeff, exp;
        std::cin >> coeff >> exp;
        insertNode(&front2, &rear2, coeff, exp);
    }
    std::cout << "Polynomial1: ";
    DisplayPolynomial(front1);
    std::cout << "Polynomial2: ";
    DisplayPolynomial(front2);

    while(true) {
        std::cout << "Please select an option" << std::endl << "1. Add polynomials" << std::endl << "2. subtract polynomials" <<
        std::endl << "3. multiply polynomials" << std::endl << "4. divide polynomials" << std::endl;
        int opt;
        std::cin >> opt;
        switch (opt)
        {
        case 1:
            std::cout << "Addition: ";
            DisplayPolynomial(addPolynomials(front1, rear1, front2, rear2).first);
            break;
        case 2:
            std::cout << "Subtraction: ";
            DisplayPolynomial(subtractPolynomials(front1, rear1, front2, rear2).first);
            break;
        case 3:
            std::cout << "Multiplication: ";
            DisplayPolynomial(multiplyPolynomials(front1, rear1, front2, rear2).first);
            break;
        case 4:
            dividePolynomials(front1, rear1, front2, rear2);
            break;
        default:
            std::cout << "Please select valid operation";
            break;
        }
    }
    return 0;
}