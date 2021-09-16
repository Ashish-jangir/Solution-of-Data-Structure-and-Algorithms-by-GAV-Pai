//Let PQUE be a priority queue data structure and a1(p1), a2(p2), an(pn) be n elements with priorities pi, (0 <= pi <= m-1)
//(ii) Implement PQUE as a two dimensional array ARR_PQUE[1:m, 1:d] where m is the
//number of priority values and d is the maximum number of data items with a given priority.
//(iii) Execute insertions and deletions presented in a random sequence.

#include<iostream>

class PQUE {
	int arr[20][20];
	int front[20], rear[20];
	int m,d;
	
	public:
	PQUE() {
		std::fill_n(front, 20, -1);
		std::fill_n(rear, 20, -1);
		m = 10;
		d = 10;
	}

	PQUE(int m, int d) {	
		std::fill_n(front, 20, -1);
		std::fill_n(rear, 20, -1);
		this->m = m;
		this->d = d;
	}
	void Display() {
		int count = 0;
		for(int i = m - 1; i >= 0; i--) {
			if(front[i] == -1 && rear[i] == -1) {
				if(i == 0 && count == 0)
					std::cout << "Queue is empty" << std::endl;
			}
			else {
				count++;
				for(int j = front[i]; j != rear[i] ; j = (j + 1) % d) {	// Important logic
					std::cout << arr[i][j] << " ";
				}
				std::cout << arr[i][rear[i]] << " ";
			}
		}
		std::cout<< std::endl;
	}

	void Insert(int item, int pri) {
		if((rear[pri] == d-1 && front[pri] == 0) || (rear[pri] == front[pri]-1)) {	//Important logic
			std::cout << "Queue of this priority is Full" << std::endl;	
		}
		else {
			if(front[pri] == -1 && rear[pri] == -1) {
				front[pri] = 0;
				rear[pri] = 0; 
				arr[pri][rear[pri]] = item;
			}
			else {
				rear[pri] = (rear[pri] + 1) % d;
				arr[pri][rear[pri]] = item;
			}
		}
	}

	void Delete() {
		for(int i = m - 1; i >= 0; i--) {
			if(front[i] == -1 && rear[i] == -1) {
				if(i == 0)
					std::cout << "Queue is empty" << std::endl;
			}
			else {
				std::cout << "Deleted item is " << arr[i][front[i]] << std::endl;
				if(front[i] == rear[i]) {
					front[i] = -1;
					rear[i] = -1;
				}
				else {
					front[i]++;
				}
				break;
			}
		}
	}
};

int main() {
	PQUE pque(10,10);	//20 is maximum allowed as argument due to arrays size
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


