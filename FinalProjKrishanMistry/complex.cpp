#include <iostream>
#include <string>
#include "complex.h"


using namespace std;

void   complex::SetRe(double Re_) { Re = Re_; } // Set Real component 

void   complex::SetIm(double Im_) { Im = Im_; } // Set Imag component  

double complex::GetRe() const { return Re; }    // Return real component

double complex::GetIm() const { return Im; }    // Return imaginary component

double complex::GetMod() const { return sqrt(Re * Re + Im * Im); } // Return modulus

double complex::GetArg() const { // Return argument
		double Arg(atan(Im / Re));
		if (Arg < 0) return atan(Im / Re) + 2 * Pi;
		else  return atan(Im / Re);
	}

	// Return complex conjugate
complex complex::getConj() const {
		complex temp(Re, -Im);
		return temp;
	}

	// Overload + operator for addition 	
complex complex::operator+(const complex &z) const {
		complex temp(Re + z.GetRe(), Im + z.GetIm());
		return temp;
	}

	// Overload - operator for subtraction
complex complex::operator-(const complex &z) const {
		complex temp(Re - z.GetRe(), Im - z.GetIm());
		return temp;
	}

	// Overload * operator for multiplication, z1*z2
complex complex::operator*(const complex &z) const {
		complex temp(Re * z.GetRe() - Im * z.GetIm(), Re * z.GetIm() + Im * z.GetRe());
		return temp;
	}

	// Overload / operator for division, z1/z2
complex complex::operator/(const complex &z) const {
		complex temp((Re * z.GetRe() - z.GetIm() * Im) / (z.GetRe() * z.GetRe() + z.GetIm() * z.GetIm()),
			(Im * z.GetRe() - Re * z.GetIm()) / (z.GetRe() * z.GetRe() + z.GetIm() * z.GetIm()));
		return temp;
	}

// Function to overload << operator for complex numbers
ostream & operator<<(ostream &os, const complex &z)
{
	if (z.Im >= 0) os << z.Re << " + " << z.Im << "i"; // Positive Im number
	else os << z.Re << " - " << -1 * z.Im << "i";	   // Negatve Im number

	return os;
}

istream & operator>>(istream &is, complex &z){
	char plus, i;
	is >> z.Re >> plus >> i >> z.Im; // Input string expected	
	if (plus == '-') z.Im = -z.Im;   // Handle negative inputs

	return is;
}
