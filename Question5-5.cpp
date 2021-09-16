// Execute general data structure which is a deque supporting and deletions at both ends but
//  depending on the choice input by the user, functions as a stack or a queue

#include<iostream>

class DQUE {
	int arr[100];
	int size;
	int left;
	int right;
	public:
	DQUE(int s) {
		size = s;
		left = -1;
		right = -1;
	}
	DQUE() {
		size = 100;
		left = -1;
		right = -1;
	}
	void Insert(int item, char choice) {
		if(left == -1 && right == -1) {
			left = 0;
			right = 0;
			arr[left] = item;
		}
		else if ( (left == 0 && right == size - 1) || right == left - 1 ) {
			std::cout << "Queue is full" << std::endl;
		}
		else if ( choice == 'L') {
			if( left == 0)
				left = size - 1;
			else
				left = left - 1;
			arr[left] = item;
		}
		else if ( choice == 'R') {
			right = (right + 1) % size;
			arr[right] = item;
		}
	}

	void Delete(char choice) {
		if (left == -1 && right == -1) {
			std::cout << "Queue is empty" << std::endl;
		}
		else if(left == right && left != -1) {
			std::cout << "Deleted item is " << arr[left] << std::endl;
			left = -1;
			right = -1;
		}
		else if(choice == 'L') {
			std::cout << "Deleted item is " << arr[left] << std::endl;
			left = (left + 1) % size;
		}
		else if(choice == 'R') {
			std::cout << "Deleted item is " << arr[right] << std ::endl;
			if(right == 0)
				right = size - 1;
			else
				right = right - 1;
		}
	}

	void Display() {
		if(left == -1 && right == -1) {
			std::cout << "Queue is empty" << std::endl;
		}
		else {
			for(int i = left; i != right; i = (i + 1) % size) {
				std::cout << arr[i] << " ";
			}
			std::cout << arr[right] << std::endl;
		}
	}
	bool isEmpty() {
		if(left == -1 && right == -1)
			return true;
		else 
			return false;
	}
	bool isFull() {
		if ( (left == 0 && right == size - 1) || right == left - 1 )
			return true;
		else
			return false;
	}
	int Get(char choice) {
		if(choice == 'R')
			return arr[right];
		else
			return arr[left];
	}
};

class Stack : public DQUE {
	public:
	void push(int item) {
		Insert(item, 'R');
	}
	void pop() {
		Delete('R');
	}
	int top() {
		return Get('R');
	}
	bool isEmpty() {
		return DQUE::isEmpty();
	}
	bool isFull() {
		return DQUE::isFull();
	}

};

class Queue : public DQUE{
	public:
	void Enqueue(int item) {
		Insert(item, 'R');
	}
	void Dequeue() {
		Delete('L');
	}
	bool isEmpty() {
		return DQUE::isEmpty();
	}
	bool isFull() {
		return DQUE::isFull();
	}
};

int main() {
	Stack s;
	std::cout << "Is stack empty?" << std::endl << s.isEmpty() << std::endl;
	s.push(1);
	s.push(99);
	s.push(55);
	s.pop();
	std::cout << "Top: " << s.top() << std::endl;
	s.pop();
}
