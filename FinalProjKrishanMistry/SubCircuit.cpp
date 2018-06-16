#include <iostream>
#include <string>
#include "complex.h"
#include "Component.h"
#include "SubCircuit.h"
#include "Validation.h"

using namespace std;

// =========================================== Series Class =======================================================

// Function that gets the impedence of the series component
complex Series::CalcImpedence(){ return SeriesComponent->GetImpedence(); }

// =========================================== Paralell Class =======================================================

// Function that adds each circuit in the paralell branchs impedances
complex Paralell::CalcImpedence(){
	complex UpperTemp, LowerTemp, TotalImpedence;
	complex one(1, 0);

	// Sum all the series components in upper paralell branch
	for (auto it = UpperBranch.begin(); it < UpperBranch.end(); it++){
		UpperTemp = UpperTemp + (*it)->CalcImpedence();
	}

	// Sum all the series components in lower paralell branch
	for (auto it = LowerBranch.begin(); it < LowerBranch.end(); it++){
		LowerTemp = LowerTemp + (*it)->CalcImpedence();
	}

	TotalImpedence = (one / UpperTemp) + (one / LowerTemp); // Add the upper and lower branches in paralell

	return one / TotalImpedence; // Return the total impedence
}

// Function to create a paralell circuit connection
Paralell CreateParalell(vector <shared_ptr<Component>> CompLibrary, bool SubBranch){
	vector <shared_ptr<SubCircuit>> Upper, Lower;
	int bound(CompLibrary.size());     // Num of components entered
	string ConnectionType;

	// ---------------------------------------------------- Upper Branch input ------------------------------------------------------------------------------------------------------------------------

	while (true){ // Loop over until the user has finished entering components

		if (SubBranch == false) { cout << "Would you like the next component in the  upper paralell branch to go in series (S) or paralell (P)? (Press F to move to a lower paralell branch)" << endl; }
		else { cout << "Would you like the next component in the Sub branched upper paralell branch to go in series (S) or paralell (P)? (Press F to move to a lower paralell branch)" << endl; }

		ConnectionType = EnterConnection(); // Choose connection type

		// User enters a series component
		if (ConnectionType == "S" || ConnectionType == "s"){
			int Num(EnterNumber(bound)); // Choose the component from the library
			Upper.push_back(shared_ptr<SubCircuit>(make_shared<Series>(CompLibrary[Num]))); // Adds series vector to upper paralell branch
		}

		// User enters a paralell component
		if (ConnectionType == "P" || ConnectionType == "p"){
			Upper.push_back(shared_ptr<SubCircuit>(make_shared<Paralell>(CreateParalell(CompLibrary, true)))); // Creates a sub branched paralell connection (recursively)
		}

		// User has finished entering components in the upper branch
		if (ConnectionType == "F" || ConnectionType == "f"){
			if (Upper.size() == 0){ cerr << "You must add a component to the upper branch first!" << endl; continue; } // go to start of loop

			cout << "Thanks for entering the components, now moving on the the lower paralell branch" << endl << endl;
			break; // User has finished entering the components for the upper branch
		}
	}

	// ---------------------------------------------------- Lower Branch input ------------------------------------------------------------------------------------------------------------------------
	while (true){ // Loop over until the user has finished entering components

		if (SubBranch == false) { cout << "Would you like the next component in the lower paralell branch to go in series (S) or paralell (P)? (Press F to move end paralell selection)" << endl; }
		else { cout << "Would you like the next component in the Sub branched lower paralell branch to go in series (S) or paralell (P)? (Press F to move to end paralell selection" << endl; }

		ConnectionType = EnterConnection(); // Choose connection type

		// User enters a series component
		if (ConnectionType == "S" || ConnectionType == "s"){
			int Num(EnterNumber(bound)); // Enter the component from the library
			Lower.push_back(shared_ptr<SubCircuit>(make_shared<Series>(CompLibrary[Num]))); // Add the series component to the lower branch
		}

		// User enters a paralell component
		if (ConnectionType == "P" || ConnectionType == "p"){
			Lower.push_back(shared_ptr<SubCircuit>(make_shared<Paralell>(CreateParalell(CompLibrary, true)))); // Creates a sub branched paralel connection (recursively)
		}
		// User has finished entering components in the lower branch
		if (ConnectionType == "F" || ConnectionType == "f"){
			if (Lower.size() == 0){ cerr << "You must add a component to the lower branch first!" << endl; continue; } // go to start of loop

			if (SubBranch == false) { cout << "Now moving on the the component after the paralell selection" << endl; }
			else { cout << "Now moving on the the component after the sub branched paralell selection" << endl; }
			break; // User has finished entering the components for the lower branch
		}
	}

	return Paralell(Upper, Lower);
}

