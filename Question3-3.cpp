//Open an ordered list L[d1, d2, ..... dn ] where each di is the name of a peripheral device, which is maintained in the alphabetical order.
//Write a program to
//(i) Insert a device dk onto the list L
//(ii) Delete an existing device di from L. In this case the new ordered list should be Lnew = (d1, d2,.... di-1, dj+1, .... dn] with (n - 1) elements
//(iii) Find the length of L
//(iv) Update device dj to dl and print the new list.

//Using map class is easier but i am gonna use vector.
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using std::vector;
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
void display(vector<string> &L) {
	cout << "List of perpheral Devices: "<<std::endl;
	for (int i = 0; i < L.size(); i++) {
	cout<< i + 1 << ". " << L[i] <<std::endl;
	}
}

void insert(vector<string> &L) {
	L.push_back("0");
	cout << "Please enter new peripheral device: ";
	cin >> L.back();
	sort(L.begin(), L.end(), comp);
	display(L);
}
void deleteDevice(vector<string> &L) {
	string temp;
	cout << "Please enter the device that you want to delete: ";
	cin >>temp;
	for(int i = 0; i < L.size(); i++) {
		if(temp == L[i]) {
			swap(L[i], L.back());
			L.pop_back();
			sort(L.begin(), L.end(), comp);
			cout<<temp<< " is deleted from the list"<<std::endl;
		}
	}
	display(L);
}
void update(vector<string> &L) {
	string dj,dl;
	cout<<"Please Enter the new device and the device you want to update: ";
	cin >> dj >> dl;
	for(int i = 0; i < L.size(); i++) {
		if(dl == L[i]) {
			L[i] = dj;
			sort(L.begin(), L.end(), comp);
		}
	}
	display(L);
}
int main() {
	int n;
	cout<< "Enter the number of peripheral devices: ";
	cin>>n;
	cout << "Please Enter the name of peripheral devices without space:";
	vector<string> L(n);
	for(int i = 0; i < n; i++)
		cin >> L[i];
	sort(L.begin(),L.end(),comp);
	insert(L);
	deleteDevice(L);
	cout << "Length of the list: " << L.size() << std::endl;
	update(L);
}
