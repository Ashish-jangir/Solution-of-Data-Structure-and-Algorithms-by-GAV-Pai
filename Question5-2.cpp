//Write a program to maintain a list of items as a circular queue which is implemented using
//an array. Simulate insertions and deletions to the queue and display a graphical
//representation of the queue after every operation.

#include<iostream>

int arr[100];

void Display(int front, int rear, int n) {
	if(front == -1)
		std::cout << "Queue is empty";
	else {
		for(int i = front; i != rear ; i = (i + 1) % n) {	// Important logic
			std::cout << arr[i] << " ";
		}
		std::cout << arr[rear];
	}
	std::cout<< std::endl;
}

void Insert(int item, int &front, int &rear, int n) {
	if((rear == n-1 && front == 0) || (rear == front-1)) {	//Important logic
		std::cout << "Queue is Full" << std::endl;	
	}
	else {
		if(front == -1 && rear == -1) {
			front = 0;
			rear = 0; 
			arr[rear] = item;
		}
		else {
			rear = (rear + 1) % n;
			arr[rear] = item;
		}
	}
}

void Delete(int &front, int &rear, int n) {
	if(front == -1) {
		std::cout << "Queue is Empty" << std::endl;
	}
	else {
		int temp = front;
		if(front == rear) {
			front = -1;
			rear = -1;
		}
		else {	
			front = ( front + 1 ) % n;
		}
		std::cout << "Deleted item: " << arr[temp] << std::endl;
	}
}


int main() {
	int front = -1, rear = -1;
	int n;
	std::cout << "Enter the size of Queue: ";
	std::cin >> n;
	Insert(1, front, rear, n);
	Insert(2, front, rear, n);
	Insert(3, front, rear, n);
	Insert(4, front, rear, n);
	Insert(5, front, rear, n);
	Display(front, rear, n);
	Delete(front, rear, n);
	Insert(6, front, rear, n);
	Delete(front, rear, n);
	Insert(7, front, rear, n);
	Delete(front, rear, n);
	Insert(8, front, rear, n);
	Display(front, rear, n);
}

