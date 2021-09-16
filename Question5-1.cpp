//Waiting line simulation in a post office:
//In a post office, a lone postal worker serves a single queue of customers. Every customer
//receives a token # (serial number) as soon as he/she enters the queue. After service, the token
//is returned to the postal worker and the customer leaves the queue. At any point of time
//the worker may want to know how many customers are yet to be served.
//(i) Implement the system using an appropriate queue data structure, simulating a random
//arrival and departure of customers after service completion.
//(ii) If a customer arrives to operate his/her savings account at the post office, then he/she
//is attended to first by permitting him/her to join a special queue. In such a case the
//postal worker attends to them immediately before resuming his/her normal service.
//Modify the system to implement this addition in service.

#include<iostream>

int arr[100];
int arr2[100];

void Create(int &front, int &rear, int &f, int &r) {
	front = -1;
	rear = -1;
	f = -1;
	r = -1;
}

bool isEmpty(int front, int rear) {
	if(front == -1 && rear == -1)
		return true;
	else
		return false;
}

bool isFull(int front, int rear, int f, int r) {
	if(rear == 99 || r == 99)
		return true;
	else
		return false;
}

void Insert(int item, int &front, int &rear) {
	if(front == -1 && rear == -1) {
		front++;
		rear++;
		arr[rear] = item;
	}
	else if(rear == 99) {
		std::cout << "Array is full" << std::endl;
	}
	else {
		rear++;
		arr[rear] = item;
	}
}

int Delete(int &front, int &rear, int &f, int &r) {
	int temp;
	if(isEmpty(f, r)) {
		if(front == -1 && rear == -1) {
			std::cout << "Array is empty" << std::endl;
		}
		else if(front == rear && front != -1) {
			temp = arr[front];
			front = -1;
			rear = -1;
		}
		else {
			temp = arr[front];
			front++;
		}
	}
	else {
		if(f == r && f != -1) {
			temp = arr2[f];
			f = -1;
			r = -1;
		}
		else {
			temp = arr2[f];
			f++;
		}
	}
	return temp;
}

void Display(int front, int rear, int f, int r) {
	if(!isEmpty(front, rear)) {	
		if(!isEmpty(f, r)) {	
			for(int i = f; i <= r; i++) {
				std::cout << arr2[i] << " ";
			}
		}
		for(int i = front; i <= rear; i++) {
			std::cout << arr[i] << " ";
		}
		std::cout<< std::endl;
	}
}

// For Insertion of High Priority items
void PriInsert(int item, int &front, int &rear) {
	if(front == -1 && rear == -1) {
		front++;
		rear++;
		arr2[rear] = item;
	}
	else if(rear == 99) {
		std::cout << "Array is full" << std::endl;
	}
	else {
		rear++;
		arr2[rear] = item;
	}
}

int main() {
	int front, rear;
	int f, r;
	Create(front, rear, f, r);
	Insert(1, front, rear);
	Insert(2, front, rear);
	Insert(3, front, rear);
	PriInsert(11, f, r);
	Insert(4, front, rear);
	Insert(5, front, rear);
	PriInsert(22, f, r);
	Insert(6, front, rear);
	Insert(7, front, rear);
	PriInsert(33, f, r);
	Insert(8, front, rear);
	Insert(9, front, rear);
	std::cout << "Deleted: " << Delete(front, rear, f, r) << std::endl;
	std::cout << "Deleted: " << Delete(front, rear, f, r) << std::endl;
	std::cout << "Deleted: " << Delete(front, rear, f, r) << std::endl;
	std::cout << "Deleted: " << Delete(front, rear, f, r) << std::endl;
	std::cout << "Deleted: " << Delete(front, rear, f, r) << std::endl;
	Display(front, rear, f, r);
}
