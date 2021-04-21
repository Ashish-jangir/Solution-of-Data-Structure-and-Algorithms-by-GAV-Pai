//Implement a stack S of n elements using arrays. Write functions to perform PUSH and POP
//operations. Implement queries using the push and pop functions to
//(i) Retrieve the mth element of the stack S from the top (m < n), leaving the stack without its top m - 1 elements
//(ii) Retain only the elements in the odd position of the stack and pop out all even positioned elements.
#include<iostream>
using std::cout;
using std::cin;

void push(int (&st)[50], int x,int &top) {
	if( top == 49) {
		cout << "Stack is full" << std::endl;
	}
	else {
		st[++top] = x;
	}
}

void pop(int &top) {
	if( top == -1) {
		cout << "Stack is already empty" << std::endl;
	}
	else{
		top--;
	}
}

int mpop(int (&st)[50],int &top, int m) {
       for (int i = 0; i < m - 1; i++)
	       pop(top);
	return st[top];
}	

void evenpop(int (&st)[50], int &top) {
	int *temp1 = st, temp2 = top;
	top = -1;
	for (int i = 0; i <= temp2; i++){
		if( temp1[i] % 2) {
			st[++top] = temp1[i];
		}
	}
}
void display(int (&st)[50], int &top) {
	for(int i = top; i >= 0; i--)
		cout<<st[i] << std::endl;
}
int main() {
	int st[50],n,top = -1;
       	cout <<"1. Push" << std::endl << "2. Pop" <<std::endl;
		cout<<"3. Retrieve mth element" << std::endl << "4. Retain only odd positions of stack" << std::endl << "5. Quit" << std::endl;

	while(1) {
		cout<<"Enter choice: ";
		cin >>n;
		switch(n) {
			case 1:
				int x;
				cout << "Enter element to push: ";
				cin >> x;
				push(st,x,top);
				display(st,top);
				break;
			case 2:
				pop(top);
				display(st, top);
				break;
			case 3:
				int m;
				cout << "Enter M to pop mth element of stack: ";
				cin >> m;
				cout << "Mth element of stack is: " << mpop(st,top,m)<< std::endl;
				display(st,top);
				break;
			case 4:
				evenpop(st,top);
				display(st,top);
				break;
			default:
				exit(0);
				break;
		}
	}
}
