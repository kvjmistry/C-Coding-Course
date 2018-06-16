#ifndef COMPLEX_H // Header guard
#define COMPLEX_H
#include <iostream>
#include <string>

using namespace std;

// =========================================== Complex Number Class =================================================
const double Pi(4 * atan(1)); // Define Pi

class complex
{
private:
	double Re, Im;
public:
	// Constructors & destructor
	complex(){ Re = Im = 0; }
	complex(double r, double i){ Re = r; Im = i; }
	~complex(){}

	void SetRe(double Re_); // Set Real component 
	
	void SetIm(double Im_);  // Set Imag component 

	double GetRe() const ;  // Return real component
	
	double GetIm() const;  // Return imaginary component
	
	double GetMod() const; // Return modulus
	
	double GetArg() const ; // Return the argument		
	
	complex getConj() const;// Return complex conjugate
	
	// Overload + operator for addition 	
	complex operator+(const complex &z) const;

	// Overload - operator for subtraction
	complex operator-(const complex &z) const;

	// Overload * operator for multiplication, z1*z2
	complex operator*(const complex &z) const;

	// Overload / operator for division, z1/z2
	complex operator/(const complex &z) const;

	// Make function to overload operators << and >> a friend
	friend ostream & operator<<(ostream &os, const complex &z);
	friend istream & operator>>(istream &is, complex &z);
};

// Function to overload << operator for complex numbers
ostream & operator<<(ostream &os, const complex &z);

// Function to overload >> operator for complex numbers
istream & operator>>(istream &is, complex &z);

#endif