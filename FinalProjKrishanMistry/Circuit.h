#ifndef CIRCUIT_H // Header guard
#define CIRCUIT_H
#include <iostream>
#include <memory>
#include <vector>
#include "complex.h"

// =========================================== Circuit Class ========================================================= 
class Circuit {
private:
	vector <shared_ptr<SubCircuit>> TotalCircuit;

public:
	Circuit(){};  //  Default Constructor
	~Circuit(){}; //  Destructor

	void AddSubCircuit(shared_ptr<SubCircuit> SubCircuit_); // Add the sub circuit into the main circuit

	complex CalcImpedence(); // Function to calculate the final circuit impedence

	int CircuitSize();// Function to get the circuit size
};

#endif