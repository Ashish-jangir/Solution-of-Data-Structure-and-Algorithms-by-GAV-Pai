//For the matrix A given below obtain a sparse matrix representation B. Write a program to
//(i) Obtain B given matrix A as input, and
//(ii) Obtain the transpose of A using matrix B.
//0 0 0 0 0 0 0 0 0 0 0 0
//0 -1 0 0 0 2 0 0 0 0 0 0
//0 0 0 0 0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0 0 0 0 0
//4 0 0 -3 0 0 0 0 0 1 0 0
//0 0 0 0 0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0 0 0 0 0
//-1 0 0 0 5 0 0 0 0 0 0 0
//0 0 0 0 0 0 2 0 0 4 0 0
//0 0 0 0 0 0 0 1 1 0 0 0
#include<iostream>
using std::cout;
using std::cin;
int main() {
	int n1 = 0, n2 = 0;
	cout<< "Please Enter the number of Row and column of the Matrix: ";
	cin >> n1 >> n2;
	int matrix[n1][n2];
	cout<<"PLease Enter the Matrix to get a Sparx Matrix"<<std::endl;
	for(int i = 0; i < n1; i++) {
		for(int j = 0; j < n2; j++) {
			cin >> matrix[i][j];
		}
	}
	int sparse_matrix[ (n1 * n2) / 2][3] = {0};
	sparse_matrix[0][0] = n1;
	sparse_matrix[0][1] = n2;
	sparse_matrix[0][2] = 0;
	int y = 1;
	for(int i = 0; i < n1; i++) {
		for(int j = 0; j < n2; j++) {
			if(matrix[i][j]) {
				sparse_matrix[0][2]++;
				sparse_matrix[y][0] = j;
				sparse_matrix[y][1] = i;
				sparse_matrix[y++][2] = matrix[i][j];

			}
		}
	}
	y--;
	cout<<"Sparse Matrix:"<<std::endl;
	for(int i = 0; i < y; i++) {
		for(int j = 0; j < 3; j++) {
			cout << sparse_matrix[i][j] << " ";
		}
		cout<<std::endl;
	}
	int tmatrix[n2][n1] = {0};
	cout<<"Transpose of initial Matrix with help of Sparse Matrix:"<<std::endl;
	for(int i = 1; i < y; i++) {
		tmatrix[sparse_matrix[i][0]][sparse_matrix[i][1]] = sparse_matrix[i][2];
	}
	for(int i = 0; i < n2; i++) {
		for(int j = 0; j < n1; j++) {

			cout<<tmatrix[i][j] << " ";
		}
		cout<<std::endl;
	}
}
