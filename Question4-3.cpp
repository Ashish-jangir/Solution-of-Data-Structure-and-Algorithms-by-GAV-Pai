//Implement a program to evaluate any given postfix expression. Test your program for the
//evaluation of the equivalent postfix form of the expression (-(A*B)/D) ^ C + E - F * H * I
//for A = 1, B = 2, D = 3, C = 14, E = 110, F = 220, H = 16.78, I = 364.621.
// Equivalent postfix for this expression is AB*D/-C^E+FH*I*-
#include<iostream>
#include<stack> //As we have made stack in 1st question already i am gonna use ready-made stack from standard template library
#include<string>
#include<cmath>
#include<map>  // i used map. if you are not familier with it then either use two arrays or one array of pairs to store
//variables from expression and their corresponding values.
using std::map;
using std::string;
using std::pair;
using std::cout;
using std::cin;
using std::stack;

int main() {
	stack<float> stck;
	string input;
	cout<<"Please enter the expression without space here: ";
	cin >> input;
	map<char, float> variables;
	cout << "Please Enter Variables value" << std::endl;
	for(int i = 0; i < input.size(); i++) {
		if(input[i] >= 65 && input[i] <=90) {
			float value;
			cout << input[i] << " = " ;
			cin >> value;
			variables.insert({input[i], value});
		}
	}

	for(int i = 0; i < input.size(); i++) {
		if(input[i] >=65 && input[i] <=90) {
			stck.push(variables[input[i]]);
		}
		else{
			float x = stck.top();
			float y;
			stck.pop();
			if(input[i] == '-') {
				if(stck.empty())
					stck.push(-x);
				else{
					y = stck.top();
					stck.pop();
					stck.push(y - x);
				}
			}
			else if (input[i] == '+') {
				y = stck.top();
				stck.pop();
				stck.push(y + x);
			}
			else if (input[i] == '*') {
				y = stck.top();
				stck.pop();
				stck.push(y * x);
			}
			else if (input[i] == '/') {
				y = stck.top();
				stck.pop();
				stck.push(y / x);
			}
			else if (input[i] == '^') {
				y = stck.top();
				stck.pop();
				stck.push(pow(y, x));
			}
		}
	}
	cout << "My solution: " << stck.top() <<std::endl; 
}
			
