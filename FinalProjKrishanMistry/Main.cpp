// Final Project Krishan Mistry
// AC Circuits 15-05-2017

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "validation.h"
#include "complex.h"
#include "Component.h"
#include "SubCircuit.h"
#include "Circuit.h"

using namespace std;

//======================================================================================================================
int main(){
	while (true){ // Loop for cycling the program

		cout << "This program will let you design an AC circuit and calculate its properties" << endl;
		cout << "To start, please build a component library" << endl << endl;

		double Freq(EnterValue("Freq")); // Call enter value function to enter frequency

		vector <shared_ptr<Component>> CompLibrary;  // Vector of Base class shared pointers for component library

		while (true){ // Loop over and add components

			string ComponentChoice(EnterComponent()); // Choose component
			if (ComponentChoice == "F" || ComponentChoice == "f") break; // Finished entering

			double Val = EnterValue(ComponentChoice); // Add the component value

			if (ComponentChoice == "R" || ComponentChoice == "r"){
				CompLibrary.push_back(shared_ptr<Component>(make_shared<Resistor>(Val))); // Create a resistor and add to library
			}

			if (ComponentChoice == "C" || ComponentChoice == "c"){
				CompLibrary.push_back(shared_ptr<Component>(make_shared<Capacitor>(Val, Freq))); // Create a capacitor and add to library
			}

			if (ComponentChoice == "I" || ComponentChoice == "i"){
				CompLibrary.push_back(shared_ptr<Component>(make_shared<Inductor>(Val, Freq))); // Create an inductor and add to library
			}
		}

		// Restart if user doesnt enter a component into library
		if (CompLibrary.size() == 0){ cerr << "ERROR: You need to enter at least one component!" << endl;  continue; }

		// Print the Component Library
		int i(1);
		cout << "--------------------------------------------" << endl;
		cout << "Component Library" << endl << endl;
		for (auto it = CompLibrary.begin(); it < CompLibrary.end(); it++){
			cout << i << ") "; // Numerate list
			(*it)->PrintData();
			i++;
		}
		cout << "--------------------------------------------" << endl;

		// Create the circuit from the library
		cout << "We will now create the circuit" << endl;
		Circuit FinalCircuit;
		int bound(CompLibrary.size());       // Num of components entered
		string Connection;					 // Connection type entered
		int Num;							 // Size of conponent library
		int count(0);						 // Counter to choose the question type

		while (true) {
			if (count == 0){ cout << "Is the first component in series (S) or Paralell (P)?" << endl; count++; }
			else{ cout << "Is the next component in series (S) or Paralell (P)? (press (F) to finish)" << endl; }

			Connection = EnterConnection(); // Enter the connection type 

			// Add component in series
			if (Connection == "S" || Connection == "s"){
				Num = EnterNumber(bound); // Select the component
				FinalCircuit.AddSubCircuit(shared_ptr<SubCircuit>(make_shared<Series>(CompLibrary[Num])));
			}

			// Add components in paralell 
			if (Connection == "P" || Connection == "p"){
				FinalCircuit.AddSubCircuit(shared_ptr<SubCircuit>(make_shared<Paralell>(CreateParalell(CompLibrary, false)))); // Adds a paralell connection to the circuit by calling the CreateParalell function
			}

			// Finished the Circuit
			if (Connection == "F" || Connection == "f"){
				if (FinalCircuit.CircuitSize() == 0){
					cerr << "ERROR:  you must add a component to the circuit first" << endl;
					continue;
				}
				cout << "Thanks for entering the circuit" << endl;
				break; // Come out of the loop 
			}
		}

		// Output the results
		cout.precision(3); // Set the precision
		complex FinalImpedence(FinalCircuit.CalcImpedence());
		cout << "\nThe circuit impedance is: " << FinalImpedence << " Ohms" << endl; // Impedence
		cout << "The circuit magnitude is: " << FinalImpedence.GetMod() << " Ohms" <<  endl; // Impedence magnitude
		cout << "The circuit phase is: " << FinalImpedence.GetArg() << " rad"<< endl; // Phase of the circuit

		CompLibrary.clear(); // Clear the library vector

		// Ask to end the program
		cout << "\nWould you like to enter another circuit (Y) or to exit (N)" << endl;
		string End(EndProgram()); // Input validation
				
		if (End == "Y" || End == "y") continue; // Go back to start of program
 
		if (End == "N" || End == "n") break; // End the program
	}

	return 0;
}