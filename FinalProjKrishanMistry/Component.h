#ifndef COMPONENT_H // Header guard
#define COMPONENT_H
#include <iostream>
#include <string>
#include "complex.h"

using namespace std;

// ========================================== Components class (Abstract Base) =======================================
class Component
{
protected:
	double freq;							 // frequency of circuit

public:
	Component(){};							 // Default constructor
	virtual ~Component(){};					 // Virtual Destructor
	virtual void SetFreq(double freq_) = 0;	 // Virtual Functions for setting/getting various quantities
	virtual double GetFreq() = 0;			 
	virtual complex GetImpedence() = 0;		 
	virtual double GetMag() = 0;			 
	virtual double GetPhase() = 0;			 
	virtual void PrintData() = 0;			 
};

	// ------------------------------------------- Resistor class --------------------------------------------------------
class Resistor : public Component{
private:
	double R; // Resistance 

public:
	Resistor()  { freq = 0; R = 0; } // Default Constructor
	~Resistor(){};					 // Destructor

	Resistor(double Res) {			 // Parameterized Constructor
		R = Res;
		freq = 0;					 // No freqency for a resistor
	}

	void    SetFreq(double freq_);	// Set and get various quantities
	double  GetFreq();
	complex GetImpedence();
	double  GetPhase();
	double  GetMag();
	void    PrintData();			// Function to print the component in the library

};

// ------------------------------------------- Capacitor class -------------------------------------------------------
class Capacitor : public Component{
private:
	double C; // Capacitance

public:
	Capacitor(){ freq = 0; C = 0; }	     // Default Constructor
	~Capacitor(){};					     // Destructor

	Capacitor(double Cap, double freq_){ // Param Constructor
		freq = freq_;
		C = Cap;
	}

	void SetFreq(double freq_);          // Set and get various quantities
	double GetFreq();
	complex GetImpedence();
	double GetPhase();
	double GetMag();
	void PrintData();					 // Function to print the component in the library

};

// ------------------------------------------- Inductor Class --------------------------------------------------------
class Inductor : public Component{
private:
	double L; // Inductance  

public:
	Inductor(){ freq = 0;  L = 0; }			 // Default Constructor
	~Inductor(){};							 // Destructor

	Inductor(double Ind, double freq_){		 // Param Constructor
		freq = freq_;
		L = Ind;
	}

	void SetFreq(double freq_);				 // Set and get various quantities
	double GetFreq();
	complex GetImpedence();
	double GetPhase();
	double GetMag();
	void PrintData();						 // Function to print the component in the library

};

#endif