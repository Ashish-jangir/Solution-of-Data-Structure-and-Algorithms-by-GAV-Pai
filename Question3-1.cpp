#include<iostream>
int main() {
	int arr1[10], arr2[10][10], arr3[10][10][10];
	for(int i = 0; i < 10; i++) {
		arr1[i] = rand();
		for(int j = 0; j < 10; j++) {
			arr2[i][j] = rand();
			for(int k = 0; k < 10; k++) {
				arr3[i][j][k] = rand();
			}
		}
	}
	std::cout << "Starting Address of Array 1:" << arr1 << std::endl;
	std::cout << "Starting Address of Array 2:" << arr2 << std::endl;
	std::cout << "Starting Address of Array 3:" << arr3 << std::endl;
	int choose;
	std::cout << "Enter value to Choose Array..." << std::endl;
	std::cin >> choose;
	std::cout << "You chosen array: " << choose << std::endl << "Now enter Index.."<< std::endl;
	int i,j,k;
	int *p;
	switch(choose){
		case 1:
			std::cin>>i;
			p = arr1;
			p = (p + i);
			std::cout << "Calculated: " << p << " " << "Real: " << &arr1[i];
			break;
		case 2:
			std::cin>>i>>j;
			p = &arr2[0][0];
			p = (p + i * 10 + j);
			std::cout << "Calculated: " << p << " " << "Real: " << &arr2[i][j];
			break;
		case 3:
			std::cin>>i>>j>>k;
			p = &arr3[0][0][0];
			p = (p + i * 10 * 10 + j * 10 + k);
			std::cout << "Calculated: " << p << " " << "Real: " << &arr3[i][j][k];
			break;
	}

}
