//Let PQUE be a priority queue data structure and a1(p1), a2(p2), an(pn) be n elements with priorities pi, (0 <= pi <= m-1)
//(i) Implement PQUE using multiple circular queues one for each priority number.
//(iii) Execute insertions and deletions presented in a random sequence.
//
//I tried to use minimum of oops and stl concepts for people who are learning both dsa and oops together.

#include<iostream>

class CQueue {
	int arr[10];
	int front, rear;
	int n;
	
	public:
	CQueue() {
		front = -1;
		rear = -1;
		n = 10;
	}

	CQueue(int size) {
		front = -1;
		rear = -1;
		n = size;
	}
	bool isEmpty() {
		if(front == -1)
			return true;
		else
			return false;
	}
	bool isFull() {
		if((rear == n-1 && front == 0) || (rear == front-1))	//Important logic
			return true;
		else
			return false;
	}
	void Display() {
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

	void Insert(int item) {
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

	void Delete() {
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
};

class PQUE {
	CQueue pque[5];
	public:
	void Insert(int item, int pri) { //pri is allowed only from 0 to 4 because we are using index number as priority. Bigger the index bigger the priority.
		if(pque[pri].isFull()) {
			std::cout << "This priority section is full" << std::endl;
		}
		else {
			pque[pri].Insert(item);
		}
	}
	void Delete() {
		for(int i = 4; i >= 0; i--) {
			if(!pque[i].isEmpty()){
				std::cout << "In Queue no. " << i << " ";
				pque[i].Delete();
				break;
			}
			else if(i == 0)
				std::cout << "Priority queue is empty" << std::endl;
		}
	}

	void Display() {
		for(int i = 4; i >= 0; i--) {
			if(!pque[i].isEmpty()) {
				pque[i].Display();
			}
		}
	}
};
int main() {
	PQUE pque;
	pque.Insert(3, 0);
	pque.Insert(2, 1);
	pque.Insert(1, 3);
	pque.Delete();
	pque.Insert(5, 4);
	pque.Insert(6, 2);
	pque.Insert(4, 1);
	pque.Delete();
	pque.Insert(7, 0);
	pque.Insert(8, 3);
	pque.Insert(9, 2);
	pque.Insert(0, 1);
	pque.Display();

}


