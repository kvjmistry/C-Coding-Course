// PHYS 30762 Programming in C++
// Assignment 6

// Krishan Mistry 13-03-17

// A matrix class - skeleton code

#include<iostream>
#include<stdlib.h> // for c style exit
#include<cmath>
#include<iomanip>
#include<string>
#include<algorithm>
using namespace std;

class matrix
{
	// Friend function to overload << operator
	friend ostream & operator<<(ostream &os, matrix &mat);

	// Friend function to overload >> operator
	friend istream & operator>>(istream &is, matrix &mat);

private:
	double *mdata;
	int rows, columns;

public:
	// Default constructor
	matrix(){ mdata = 0; rows = columns = 0;  }
	// Parameterized constructor
	matrix(int m, int n);

	// Copy constructor
	matrix(matrix&);

	// Move constructor
	matrix(matrix&&);

	// Destructor
	~matrix(){ delete mdata; }

	// Access functions
	int getrows() const { return rows; } // Return number of rows
	int getcols() const { return columns; } // Return number of columns
	int getSize() const { return rows * columns; } // Gets the size of the matrix

	// Return position in array of element (m,n)
	int index(int m, int n) const 
	{
		if (m>0 && m <= rows && n>0 && n <= columns) return (n - 1) + (m - 1)*columns;
		else { cout << "Error: out of range" << endl; exit(1); }
	}

	// Overload the () operator
	double & operator()(int m, int n) { return mdata[index(m, n)]; }
	
	// Copy  Assignment operator
	matrix& operator=(matrix&);

	// Move Assignment operator
	matrix& operator=(matrix&&);

	// Addition, subtraction and multiplication
	matrix operator+(const matrix &mat) const 
	{
		// Check if the rows and colums are the same
		int size = rows * columns;
		if (rows != mat.getrows() && columns != mat.getcols()){
			cerr << "error cannot add matrices with different dimentions" << endl;
			exit(1);
		}
		matrix temp(rows, columns);

		for (int i = 0; i < size; i++){
			temp.mdata[i] = mdata[i] + mat.mdata[i];
		}
		return temp;
	}

	matrix operator-(const matrix &mat) const
	{
		// Check if the rows and colums are the same	
		int size = rows * columns;
		if (rows != mat.getrows() && columns != mat.getcols()){
			cerr << "error cannot add matrices with different dimentions" << endl;
			exit(1);
		}
		matrix temp(rows, columns);

		for (int i = 0; i < size; i++){
			temp.mdata[i] = mdata[i] - mat.mdata[i];
		}
		return temp;
	}

	matrix operator*(const matrix &mat) const
	{
		// Check if the matrix dimentions match to multiply
		if (columns != mat.rows) {
			cerr << "error matrix dimentions do not match for multiplication!" << endl;
			exit(1);
		}

		matrix temp(rows, mat.columns);
		// Multiplying matrix loops (AB)_ij = A_ik B_kj
		for (int i = 1; i < rows+1; i++){
			for (int j = 1; j < mat.columns+1; j++){
				for (int k = 1; k < columns+1; k++)
				{
					temp.mdata[index(i,j)] += mdata[index(i,k)] * mat.mdata[index(k,j)];					
				}
			}
		}

		return temp;
	}

	// minor
	double minor(int i, int j, matrix mat);

	// determinant
	double det();

};

// Member functions defined outside class

// minor function 
double matrix::minor(int i, int j, matrix mat)  {
	matrix minor(mat.getrows() - 1, mat.getrows() - 1); // define minor to be a size less than the input matrix

	int k(0); // Counter for assinging the corresponding elements
	for (int i = 1; i < mat.getrows() + 1; i++){
		for (int p = 1; p < mat.getrows() + 1; p++){

			if (i == 1 || p == j){} // dont assign the i = 1 row or p = j col 
			else{
				minor.mdata[k] = mat.mdata[index(i, p)]; // assign the data
				k++;
			}
		}
	}
	return minor.det(); // recursive definition
}

// determinant
double matrix::det(){
	if (rows != columns){ cerr << "error, require the same number of rows and columns" << endl; exit(1); }
	int n = rows;
	double temp(0);

	if (n == 2) {
		// det of a 2x2
		temp = (mdata[0] * mdata[3]) - (mdata[1] * mdata[2]);
		return temp;
	}

	else  if (n == 1) return temp = mdata[0]; // det of a 1x1

	// Calculate the det of an nxn using minors
	for (int i = 1; i < n + 1; i++){

		temp += pow(-1.0, 1 + i) * mdata[index(1, i)] * minor(1, i, *this);
	}
	return temp;
}

// Assignment operator for deep copying
matrix & matrix::operator=(matrix &mat)
{
	cout << "copy assignment\n";
	if (&mat == this) return *this; // no self assignment

	// First delete this object's array
	delete[] mdata; mdata = 0; rows = columns = 0;
	// Now copy size and declare new array

	int size = mat.rows * mat.columns;
	
	if (size > 0)
	{
		mdata = new double[size];
		// Copy values into new array
		for (int i = 0; i < size; i++) { 
			mdata[i] = mat.mdata[i];
			rows = mat.rows;
			columns = mat.columns;

		}
	}
	return *this;// Special pointer!!!
}

// Copy constructor for deep copying
matrix::matrix(matrix &mat)
{
	// Copy size and declare new array
	//cout << "copy constructor\n";
	mdata = 0; 
	rows = mat.getrows();
	columns = mat.getcols();
	int size = rows * columns;
	if (size > 0)
	{
		mdata = new double[size];
		// Copy values into new array
		for (int i = 0; i < size; i++) {
			mdata[i] = mat.mdata[i];
			rows = mat.rows;
			columns = mat.columns;
		}
	}
}

// Move constructor
matrix::matrix(matrix &&mat)
{ // steal the data
	cout << "move constructor\n";
	rows = mat.getrows();
	columns = mat.getcols();
	mdata = mat.mdata;
	mat.rows = 0;
	mat.columns = 0;
	mat.mdata = 0;//nullptr;
}

// Move Assignment operator
matrix & matrix::operator=(matrix&& mat)
{
	cout << "move assignment\n";
	if (&mat == this) return *this; // no self assignment

	std::swap(rows, mat.rows);
	std::swap(columns, mat.columns);
	std::swap(mdata, mat.mdata);
	return *this; // Special pointer!!!
}

// Parameterized constructor implimentation
matrix::matrix(int m, int n){
	rows = m;
	columns = n;
	//cout << "Parameterised constructor called" << endl;
	if (m < 1 || n < 1 )
	{
		cout << "Error: trying to declare an unphysical square matrix" << endl;
		exit(1);
	}
	int size = m*n;
	mdata = new double[size]; // Create array of size m*n
	for (int i = 0; i<size; i++) mdata[i] = 0; // set all values to zero
}

// Overload insertion to output stream for matrices
ostream & operator<<(ostream &os, matrix &mat)
{	
	os << "\n";
	if (mat.rows == 0) { 
		 os << " no size" << endl; 
		return os << "\n--------------" << endl;
	}

		for (int i = 1; i < mat.getrows() + 1; i++){
			for (int j = 1; j < mat.getcols() + 1; j++){
				int temp = mat.index(i, j);

				if (mat.mdata[temp] < 10) { os << mat.mdata[temp] << "  "; }// Align the matrices better

				else { os << mat.mdata[temp] << " "; }

			}
			os <<  endl;
		}	
	
	os << "\n--------------" << endl;

	return os;
}

// Overload the >> operator to input stream for matrices
istream & operator>>(istream &is,  matrix &mat){
	string line;//Initialize strings for input line and matrix elements
	string element;

	getline(is, line);//Gets whole input line
	int i{ 0 };
	int numrows{ 1 };//Sets initial number of rows and columns
	int numcols{ 0 };//Set to 0 to allow checking that each row has same number of columns
	int tempcols{ 1 };

	while (line[i]){ //Loop to count number of rows and columns

		if (line[i] == ','){//Columns split by commas

			tempcols++;
		}
		else;

		if (line[i] == ' ' || i == line.length() - 1){//Rows split by spaces

			if (line[i] == ' ') numrows++;//Adds 1 to number of rows

			if (numcols == 0){//If first row

				numcols = tempcols;//Sets number of columns of matrix
				tempcols = 1;
			}

			else{

				if (numcols != tempcols){//If subsequent rows have different number of columsn gives error

					cerr << "Each row must have the same number of columns" << endl;
					exit(1);
				}
				else tempcols = 1;
			}
		}
		else;

		i++;
	}

	matrix temp(numrows, numcols);//Initializes temporary matrix with correct number of columns and rows
	mat = temp;//Sets matrix to correct size

	i = 0;
	int j{ 0 };
	int commapos{ -1 };

	while (line[i]){//Loops over whole line

		if (line[i] == ',' || line[i] == ' ' || i == line.length() - 1){//Chops line into matrix elements using comma and space positions

			element = line.substr(commapos + 1, i - commapos);
			commapos = i;
			mat.mdata[j] = stod(element);//Adds element to matrix array
			j++; i++;
		}

		else i++;
	}
	return is;

}

// Main program
int main()
{
	
	//
	// First part of assignment: constructing and deep copying matrices
	//

	// Demonstrate default constructor
	matrix a1;
	cout << "a1\n";
	cout << a1;
	

	// Parameterized constructor *** Get user to enter the details of any mxn matrix
	int m(2), n(2);
	matrix a2(m, n);
	cout << "Please enter the details of matrix a2 format must be a,b c,d: " << endl;	
	// Set values for a2 here
	cin >> a2;

	// Print matrix a2
	cout << "Example using parameterised constructor" << endl;
	cout << "a2\n";
	cout << a2;
	
	// Deep copy by assignment: define new matrix a3 then copy from a2 to a3
	matrix a3(m, n);
	cout << "a3\n";
	cout << a3;
	a3 = a2;
	cout << "Deep copy a2 to a3" << endl;
	cout << "a3\n";
	cout << a3 ;

	// Modify contents of original matrix and show assigned matrix is unchanged here
	a2(1, 2) = 5;
	cout << "Change contents of a2, a3 should stay the same" << endl;
	cout << "a2\n";
	cout << a2;
	cout << "a3\n";
	cout << a3;

	// Deep copy using copy constructor 
	matrix a4(a2);
	cout << "Example of deep copy using copy constructor: " << endl;
	cout << "a4 (should equal a2)\n";
	cout << a4;

	// Modify contents of original matrix and show copied matrix is unchanged here
	a2(2, 1) = 9;
	cout << "Example of modifying the contents of an original matrix to show copied matrix is unchanged " << endl;
	cout << "new a2 \n";
	cout << a2;
	cout << "a4 (should not equal new a2)\n";
	cout << a4;

	// Move copy construction demonstration
	matrix a5 = move(a4);
	cout << "Example using a move copy construction: " << endl;
	cout << "a5 (moved from a4)\n";
	cout << a5;
	cout << "a4 is now" << endl;
	cout << a4;

	// Move assignment demonstration
	a4 = move(a2);
	cout << "Example using a move assignment construction: " << endl;
	cout << "a4 is now the moved a2 data" << endl;
	cout << a4;
	cout << "a2 is now" << endl;
	cout << a2;
	
	//
	// Second part of assignment: matrix operations
	//

	// Addition of 2 matrices
	matrix b1(a5 + a3);
	cout << "Example of the addition of two matrices: " << endl;
	cout << "b1 (is the sum of a5 and a3)" << endl;
	cout << b1;

	// Subtraction of 2 matrices
	matrix b2(a5 - a3);
	cout << "Example of the difference between two matrices: " << endl;
	cout << "b2 (is the difference of a5 and a3)" << endl;
	cout << b2;
	// Multiplication of 2 matrices
	matrix b3(2,2);

	b3(1, 1) = 1; b3(1, 2) = 1; b3(2, 1) = 0; b3(2, 2) = 1;

	cout << "Example of the product of two matrices: " << endl;
	cout << "b3" << endl;
	cout << b3;
	cout << "product of b3 and a4" << endl;
	cout << b3 * a4;

	// Determinant
	cout << "Example of calculating the determinant of a matrix: " << endl;
	cout << "b4" << endl;
	matrix b4(4, 4);
	b4(1, 1) = 1; b4(1, 2) = 7; b4(1, 4) = 2; b4(2, 1) = 9, b4(2, 2) = 5, b4(2, 3) = 1, b4(3, 3) = 4, b4(4, 1) = 3, b4(4, 2) = 9, b4(4, 4) = 7;
	cout << b4;

	cout << "The determinant of b4" << endl;
	cout << b4.det() << endl;

	return 0;
}