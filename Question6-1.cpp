//Linked List Program
#include<iostream>

class Node {
	public:
	int data;
	Node *next;
}*start=NULL, *end=NULL;


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
	}
	else {
		temp = start;
		start = start->next;
		delete(temp);
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
	}
	else {
		while(temp->next != end)
			temp = temp->next;
		end = temp;
		delete(temp->next);
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
				display();
			}
            else {
                temp = temp->next;
            }
	    }
    }	
}

int main() {
	int n;
	std::cout << "Enter the size: ";
	std::cin >> n;
	std::cout<< "Now Enter numbers.." << std::endl;
	for(int i = 0; i < n; i++) {
		int temp;
		std::cin>> temp;
		insertEnd(temp);
	}

	while(1) {
		std::cout << "1. Insert at beginning" << std::endl << "2. Insert at end" << std::endl;
		std::cout << "3. Delete at beginning" << std::endl << "4. Delete at end" << std::endl;
		std::cout << "5. Insert at selected position" << std::endl << "2. Delete at selected position" << std::endl;
		int opt, temp,temp2;
		std::cin>>opt;
		switch (opt)
		{
		case 1:
			std::cin>> temp;
			insertBeg(temp);
			break;
		case 2:
			std::cin>> temp;
			insertEnd(temp);
			break;
		case 3:
			delBeg();
			break;
		case 4:
			delEnd();
			break;
		case 5:
			std::cin>> temp;
			std::cout << "Enter the position :";
			std::cin>> temp2;
			insertAt(temp,temp2);
			break;
		case 6:
			std::cout << "Enter the position :";
			std::cin>> temp;
			delAt(temp);
			break;
		default:
			break;
		}
		display();	
	}	
}