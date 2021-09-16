//A deque DQUE is to be implemented using a circular one dimensional array of size N. Execute procedures to
//(i) Insert and delete elements from DQUE at either ends
//(ii) Implement DQUE as an output restricted deque
//(iii) Implement DQUE as an input restricted deque
//(iv) For the procedures, what are the conditions used for testing DQUE_FULL and DQUE_EMPTY?

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
	
	void Insert(int item) {	//Inserts always at right for input restricted queue
		Insert(item, 'R');
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

	void Delete() {	//Deletes always at right for output restricted queue
		Delete('R');
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
};

int main() {
	DQUE dq(10);
	dq.Insert(34, 'L');
	dq.Insert(69, 'R');
	dq.Insert(2, 'L');
	dq.Insert(49, 'R');
	dq.Insert(28, 'L');
	dq.Insert(64, 'L');
	dq.Insert(0, 'R');
	dq.Insert(9, 'L');
	dq.Delete('L');
	dq.Delete('R');
	dq.Delete('L');
	dq.Delete('L');
	dq.Display();
	dq.Delete();
	dq.Insert(39);
	dq.Insert(84);
	dq.Display();

}

