//Program for circular linked list
#include<iostream>

class Node {
	public:
	int data;
	Node *next;
}*start=NULL,*end=NULL;


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
		start = start->next;
        end->next = start;
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
        end->next = start;
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
		default:
			break;
		}
		display();	
	}	
}