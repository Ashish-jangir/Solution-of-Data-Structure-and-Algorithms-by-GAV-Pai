//Open an ordered list L[d1, d2, ..... dn ] where each di is the name of a peripheral device, which is maintained in the alphabetical order.
//Write a program to
//(i) Insert a device dk onto the list L
//(ii) Delete an existing device di from L. In this case the new ordered list should be Lnew = (d1, d2,.... di-1, dj+1, .... dn] with (n - 1) elements
//(iii) Find the length of L
//(iv) Update device dj to dl and print the new list.

#include<iostream>
#include<string>
#include<algorithm>
using std::cout;
using std::cin;
using std::string;
using std::sort;

bool comp( string &a, string &b) {
	return a<b;
}
void swap( string &a, string &b) {
	string temp;
	temp = a;
	a = b;
	b = temp;
}
void display(string (&L)[50], int &n) {
	cout << "List of perpheral Devices: "<<std::endl;
	for (int i = 0; i < n; i++) {
	cout<< i + 1 << ". " << L[i] <<std::endl;
	}
}

void insert(string (&L)[50], int &n) {
	cout << "Please enter new peripheral device: ";
	cin >> L[n];
	n++;
	sort(L, L + n, comp);
	display(L,n);
}
void deleteDevice(string (&L)[50], int &n) {
	string temp;
	cout << "Please enter the device that you want to delete: ";
	cin >>temp;
	for(int i = 0; i < n; i++) {
		if(temp == L[i]) {
			swap(L[i], L[n-1]);
			n--;
			sort(L, L + n, comp);
			cout<<temp<< " is deleted from the list"<<std::endl;
		}
	}
	display(L,n);
}
void update(string (&L)[50], int &n) {
	string dj,dl;
	cout<<"Please Enter the new device and the device you want to update: ";
	cin >> dj >> dl;
	for(int i = 0; i < n; i++) {
		if(dl == L[i]) {
			L[i] = dj;
			sort(L, L + n, comp);
		}
	}
	display(L, n);
}
int main() {
	int n;
	cout<< "Enter the number of peripheral devices: ";
	cin>>n;
	cout << "Please Enter the name of peripheral devices without space:";
	string L[50];
	for(int i = 0; i < n; i++)
		cin >> L[i];
	sort(L,L + n,comp);
	insert(L,n);
	deleteDevice(L,n);
	cout << "Length of the list: " << n << std::endl;
	update(L,n);
}

