#include <iostream>
#include <string>
#include "complex.h"
#include "Component.h"
#include "SubCircuit.h"
#include "Validation.h"
#include "Circuit.h"

using namespace std;


// =========================================== Circuit Class ========================================================= 

void Circuit::AddSubCircuit(shared_ptr<SubCircuit> SubCircuit_){ TotalCircuit.push_back(SubCircuit_); }; // Add the sub circuit into the main circuit

int Circuit::CircuitSize(){ return TotalCircuit.size(); } // Function to get the circuit size

complex Circuit::CalcImpedence(){ // Function to calculate the final circuit impedence
	complex temp;

	for (auto it = TotalCircuit.begin(); it < TotalCircuit.end(); it++){ // Sums over all elements in vector using iterator
		temp = temp + (*it)->CalcImpedence();
	}

	return temp;
};

