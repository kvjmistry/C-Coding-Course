#ifndef SUBCIRCUIT_H // Header guard
#define SUBCIRCUIT_H
#include <iostream>
#include <memory>
#include <vector>
#include "complex.h"

using namespace std;

// =========================================== SubCircuit Class ========================================================= 
class SubCircuit
{
public:
	SubCircuit(){};						 // Default constructor
	virtual ~SubCircuit(){};			 // Virtual Destructor
	virtual complex CalcImpedence() = 0; // Virtual fuction to calculate the impedence
};

// =========================================== Series Class ========================================================= 

class Series : public SubCircuit {
private:
	shared_ptr<Component> SeriesComponent; // Pointer to series component
public:
	Series(){}  // Default constructor
	~Series(){} // Destructor
	Series(shared_ptr<Component> Component_){ SeriesComponent = Component_; } // Parameterized Constructor

	// Function that gets the impedence of the series component
	complex CalcImpedence();
};

// =========================================== Paralell Class ========================================================= 
class Paralell : public SubCircuit {
private:
	vector <shared_ptr<SubCircuit>> UpperBranch, LowerBranch; // Vector of base class pointers to the SubCircuit class

public:
	Paralell(){}    // Default constructor
	~Paralell(){ }; // Destructor
	Paralell(vector <shared_ptr<SubCircuit>> UpperBranch_, vector <shared_ptr<SubCircuit>> LowerBranch_){ UpperBranch = UpperBranch_;	LowerBranch = LowerBranch_; }

	// Function that adds each circuit in the paralell branchs impedances
	complex CalcImpedence();

	
};

// Function to create a paralell circuit connection
Paralell CreateParalell(vector <shared_ptr<Component>> CompLibrary, bool SubBranch);


#endif