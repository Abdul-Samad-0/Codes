#include<iostream>
using namespace std;



void display(int Matrix[][5], int m, int n);
int sum(int Matrix[][5], int m, int n);
void transpose(int Matrix[][5], int m, int n);
void input_kernel(int Matrix[][5], int** Matrix1, int a, int b, int m, int n);
void spiral_print(int Matrix[][5], int m, int n);
void Apply_filter(int Matrix[][5], int** Matrix1, int a, int b, int m, int n);
bool upper_triangular(int Matrix[][5], int m, int n);
bool lower_triangular(int Matrix[][5], int m, int n);
bool identity_matrix(int Matrix[][5], int m, int n);
void Reverse(int Matrix[][5], int m, int n);
void Rotate_image(int Matrix[][5], int m, int n);
void product(int** Matrix, int** Matrix1, int m, int n, int m1, int n1);







int main() {

	int Matrix[5][5] = { 0 };


	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			Matrix[i][j] = 5 + j;
		}
		cout << endl;
	}

	cout << "  \t original Matrix   " << endl;
	display(Matrix, 5, 5);
	cout << " \t Sum of matrix is :" << sum(Matrix, 5, 5) << endl;



	cout << " \t transposed Matrix is " << endl;
	transpose(Matrix, 5, 5);
	display(Matrix, 5, 5);


	cout << " \t spiral  of transposed matrix " << endl;
	spiral_print(Matrix, 5, 5);

	cout << endl;


	cout   << " \t Rotated image by  90 degree clock wise" << endl;
	Rotate_image(Matrix, 5, 5);




	if (upper_triangular(Matrix, 5, 5)) {
		cout << " \t  Matrix is upper triangular " << endl;
	}
	else {
		cout << "  \t Matrix is not upper triangular" << endl;
	}
	if (lower_triangular(Matrix, 5, 5)) {
		cout << " \t  Matrix is lower triangular" << endl;
	}
	else {
		cout << " \t  Matrix is not lower triangular" << endl;
	}
	if (identity_matrix(Matrix, 5, 5)) {
		cout << "  \t Matrix is identity matrix " << endl;
	}
	else {
		cout << "  \t Matrix is not identity matrix " << endl;
	}



	cout << " \t product of two matrix " << endl;

	int rw, cl;
	cout << " \t please enter the rows and columns of Matrix 1 :";
	cin >> rw >> cl;

	int** A = new  int* [rw];

	for (int i = 0; i < rw; i++) {
		A[i] = new int[cl];
	}


	int rw1, cl1;
	cout << " \t please enter the rows and columns of Matrix 2 :";
	cin >> rw1 >> cl1;

	int** B = new  int* [rw1];

	for (int i = 0; i < rw1; i++) {
		B[i] = new int[cl1];
	}

	
	if (cl != rw1 ) {
		cout << " \t product is not possible   columns of matrix 1 is not equal to rows of matrix 2 " << endl;
		
	}
	else {
		cout << " \t please enter the values of matrix 1 " << endl;
		for (int i = 0; i < rw; i++) {
			for (int j = 0; j < cl; j++) {
				cin >> A[i][j];
			}
		}

		cout << " \t please enter the values of matrix 2 " << endl;
		for (int i = 0; i < rw1; i++) {
			for (int j = 0; j < cl1; j++) {
				cin >> B[i][j];
			}
		}

		product(A, B, rw, cl, rw1, cl1);
	}

	int m, n;
	cout << " \t please enter the rows and columns of kernel applied to image respectively :";
	cin >> n >> m;

	int** kernel = new  int* [n];

	for (int i = 0; i < n; i++) {
		kernel[i] = new int[m];
	}

	input_kernel(Matrix, kernel, 5, 5, n, m);

	system("pause");
	return 0;
}

void display(int Matrix[][5], int m, int n) {

	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << Matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int sum(int Matrix[][5], int m, int n) {
	int sum = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			sum += Matrix[i][j];
		}

	}

	return sum;
}

void transpose(int Matrix[][5], int m, int n) {


	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i > j) {
				int temp1 = Matrix[j][i];
				int temp2 = Matrix[i][j];
				swap(temp1, temp2);
				Matrix[j][i] = temp1;
				Matrix[i][j] = temp2;
			}
		}
	}

}

void spiral_print(int Matrix[][5], int m, int n) {
	int top = 0, bottom = m - 1, left = 0, right = n - 1;

	while (top <= bottom && left <= right) {

		for (int i = left; i <= right; i++) {
			cout << Matrix[top][i] << "  ";
		}
		top++;




		for (int i = top; i <= bottom; i++) {
			cout << Matrix[i][right] << "  ";
		}
		right--;


		if (top <= bottom) {
			for (int i = right; i >= left; i--) {
				cout << Matrix[bottom][i] << "  ";
			}
			bottom--;

		}


		if (left <= right) {
			for (int i = bottom; i >= top; i--) {
				cout << Matrix[i][left] << "  ";
			}
			left++;
		}
	}
}


void Apply_filter(int Matrix[][5], int** Matrix1, int row01, int col01, int row02, int col02) {

	int padding = (row02 - 1) / 2;
	int checker = (row02 - 1) % 2;


	if (checker == 0) {

		int padded_rows = row01 + 2 * padding;
		int padded_cols = col01 + 2 * padding;

		int** padded = new int* [padded_rows];
		for (int i = 0; i < padded_rows; i++) {
			padded[i] = new int[padded_cols];
		}

		for (int i = 0; i < padded_rows; i++) {
			for (int j = 0; j < padded_cols; j++) {
				padded[i][j] = 0;
			}
		}

		for (int i = 0; i < row01; i++) {
			for (int j = 0; j < col01; j++) {
				padded[i + padding][j + padding] = Matrix[i][j];
			}
		}

		cout << " \t padded Matrix is : " << endl;
		for (int i = 0; i < padded_rows; i++) {
			for (int j = 0; j < padded_cols; j++) {
				cout << padded[i][j] << " ";
			}
			cout << endl;
		}

		int row1 = row01;
		int col1 = col01;

		int** result = new int* [row1];
		for (int i = 0; i < row1; i++) {
			result[i] = new int[col1];
		}


		for (int i = 0; i < row1; i++) {
			for (int j = 0; j < col1; j++) {
				int num = 0;                          
				for (int s = 0; s < row02; s++) {
					for (int h = 0; h < col02; h++) {
						num += padded[s + i][h + j] * Matrix1[s][h];
					}
				}
				result[i][j] = num;
			}
		}

		cout << "  \t End result " << endl;
		for (int i = 0; i < row1; i++) {
			for (int j = 0; j < col1; j++) {
				cout << result[i][j] << "  ";
			}
			cout << endl;
		}


		for (int i = 0; i < padded_rows; i++) {
			delete[] padded[i];
		}
		delete[] padded;

		for (int i = 0; i < row1; i++) {
			delete[] result[i];
		}
		delete[] result;
	}
	else {
		int row1 = row01;
		int col1 = col01;

		int** result = new int* [row1];
		for (int i = 0; i < row1; i++)
			result[i] = new int[col1];


		for (int i = 0; i < row1; i++) {
			for (int j = 0; j < col1; j++) {
				int num = 0;
				for (int s = 0; s < row02; s++)
					for (int h = 0; h < col02; h++)
						num = num + Matrix[s + i][h + j] * Matrix1[s][h];
				result[i][j] = num;
				num = 0;
			}
		}

	}
}

void input_kernel(int Matrix[][5], int** Matrix1, int a, int b, int m, int n) {

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> Matrix1[i][j];
		}
	}


	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			Matrix[i][j] = 5 + j;
		}
		cout << endl;
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << Matrix1[i][j] << "  ";
		}
		cout << endl;
	}


	Apply_filter(Matrix, Matrix1, a, b, m, n);

}
bool upper_triangular(int Matrix[][5], int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i > j) {
				if (Matrix[i][j] != 0) {
					return false;
				}
			}
		}
	}


	return true;

}
bool lower_triangular(int Matrix[][5], int m, int n) {

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i < j) {
				if (Matrix[i][j] != 0) {
					return false;
				}
			}
		}
	}
	return true;
}

bool identity_matrix(int Matrix[][5], int m, int n) {

	if (lower_triangular(Matrix, m, n) == 1 && upper_triangular(Matrix, m, n) == 1) {
		for (int i = 0; i < m; i++) {
			if (Matrix[i][i] != 1) { return false; }
			if (Matrix[i][i] != 0) { return false; }
		}
		for (int i = 0; i < m; i++) {
			if (Matrix[i][i] != 1) { return false; }
		}
	}
	else{
		return false;
	}
	return true;
}


void Reverse(int Matrix[][5], int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n / 2; j++) {
			swap(Matrix[i][j], Matrix[i][n - 1 - j]);
		}
	}
}

void Rotate_image(int Matrix[][5], int m, int n) {

	transpose(Matrix, m, n);
	Reverse(Matrix, m, n);



	display(Matrix, 5, 5);
}
void product(int** Matrix,  int** Matrix1, int m, int n, int m1, int n1) {

	int** result = new int* [m];
	for (int i = 0; i < m; i++)
		result[i] = new int[n1];



	int sum = 0;
	for (int k = 0; k < m; k++) {
		for (int i = 0; i < n1; i++) {
			for (int j = 0; j < n; j++) {
				sum += Matrix[k][j] * Matrix1[j][i];
			}
			result[k][i] = sum;
			sum = 0;
		}
	}



	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n1; j++) {
			cout << result[i][j] << "  ";
		}
		cout << endl;
	}



}

