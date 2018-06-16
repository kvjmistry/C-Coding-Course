// PHYS 30762 Programming in C++
// Assignment 5

// Krishan Mistry 05-03-17

// Class for complex numbers

#include<iostream>
#include<cmath>

using namespace std;

const double Pi(4 * atan(1)); // Define Pi

class complex
{
	// Make function to overload operators << and >> a friend
	friend ostream & operator<<(ostream &os, const complex &z);
	friend istream & operator>>(istream &is, complex &z);
private:
	double Re, Im;
public:
	// Constructors & destructor
	complex(){ Re = Im = 0; }
	complex(double r, double i){ Re = r; Im = i; }
	~complex(){}

	// Return real component
	double getRe() const { return Re; }
	// Return imaginary component
	double getIm() const { return Im; }
	// Return modulus
	double getMod() const { return sqrt(Re * Re + Im * Im); }
	// Return argument
	double getArg() const { 
		double Arg(atan(Im / Re));		
		if (Arg < 0) return atan(Im / Re)+ 2* Pi;
		else  return atan(Im / Re);	
	}

	// Return complex conjugate
	complex getConj() const { 
		complex temp(Re, -Im);
		return temp;
	}
	// Overload + operator for addition 	
	complex operator+(const complex &z) const
	{
		complex temp(Re + z.getRe(), Im + z.getIm() );
		return temp;
	}

	// Overload - operator for subtraction
	complex operator-(const complex &z) const
	{
		complex temp(Re - z.getRe(), Im - z.getIm());
		return temp;
	}

	// Overload * operator for multiplication, z1*z2
	complex operator*(const complex &z) const
	{
		complex temp(Re * z.getRe() - Im * z.getIm(), Re * z.getIm() + Im * z.getRe());
		return temp;
	}

	// Overload / operator for division, z1/z2
	complex operator/(const complex &z) const
	{
		complex temp((Re * z.getRe() - z.getIm() * Im) / (z.getRe() * z.getRe() + z.getIm() * z.getIm()), 
			(Im * z.getRe() - Re * z.getIm()) / (z.getRe() * z.getRe() + z.getIm() * z.getIm()));
		return temp;
	}

};

// Function to overload << operator for complex numbers
ostream & operator<<(ostream &os, const complex &z)
{
	if (z.Im > 0) os << z.Re << "+" << z.Im << "i"; // Positive Im number
	else os << z.Re << z.Im << "i"; // Negatve Im number
	
	return os;
}

istream & operator>>(istream &is, complex &z){
	char plus, i;
	is >> z.Re >> plus >> i >> z.Im; // Input string expected	
	if (plus == '-') z.Im = -z.Im; // Handle negative inputs

	return is;
}

int main()
{
	cout.precision(3);
	complex a, b;

	// Create complex number a
	cout << "-----------------------------------------------------------" << endl;
	cout << "Please enter complex number a in the format Re +/- iIm: " << endl;
	cout << "a = ";
	cin >> a;

	// Get real and imaginary components, modulus and argument of a
	cout << "Real of a: " << a.getRe() << endl;
	cout << "Imaginary of a: " << a.getIm() << endl;
	cout << "Modulus of a: " << a.getMod() << endl;
	cout << "Argument of a: " << a.getArg() << " Rad"  << endl;

	// Get conjugate of a
	cout << "The conjugate of a is: " << a.getConj() << endl;

	// Create complex number b
	cout <<"-----------------------------------------------------------" << endl;
	cout << "Please enter complex number b in the format Re +/- iIm: " << endl;
	cout << "b = ";
	cin >> b;

	// Get real and imaginary components, modulus and argument of b
	cout << "Real of b: " << b.getRe() << endl;
	cout << "Imaginary of b: " << b.getIm() << endl;
	cout << "Modulus of b: " << b.getMod()  << endl;
	cout << "Argument of b: " << b.getArg() << " Rad" << endl;

	// Get conjugate of a
	cout << "The conjugate of b is: " << b.getConj() << endl;

	// Get sum, difference, product and quotient of a and b
	complex sum(a + b);
	complex difference(a - b);
	complex product(a * b);
	complex quotient(a / b);

	// Print out results, also demonstrating use of overloaded operator<<
	cout << "-----------------------------------------------------------" << endl;
	cout << "Sum: " << sum << endl;
	cout << "Difference: " << difference << endl;
	cout << "Product: " << product << endl;
	cout << "Quotient: " << quotient << endl;

	return 0;
}
