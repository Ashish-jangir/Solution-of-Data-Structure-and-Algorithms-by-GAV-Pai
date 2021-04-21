//Write a recursive program to obtain the nth order Fibonacci sequence number. Include
//appropriate input / output statements to track the variables participating in recursion. Do
//you observe the 'invisible' stack at work? Record your observations.

#include<iostream>
using std::cout;
using std::cin;
int fibonacci(int n) {
	if(n == 1)
		return 0;
	else if(n == 2)
		return 1;
	else {
		int x = n - 1, y = n - 2, z = 0;
		cout << " Vaiables going into Stack: n = "<< n << ", x = " << x << ", y = " << y << ", z = " << z << std::endl;
		z = fibonacci(x) + fibonacci(y);
		cout << " Vaiables going out of Stack: n = "<< n << ", x = " << x << ", y = " << y << ", z = " << z << std::endl;
		return z;
	}
}
int main() {
	int n;
	cout << "Enter order of number you want the in fibonacci series: ";
	cin >> n;
	cout << n << "th order of Fibonacci Series is: " << fibonacci(n);
}
//As you observe in output value of n, x, y are exactly beahaving as stack having operations of push and pop continuously on n,x,y
