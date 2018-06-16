
// Assignment 1 
// 30/01/17 Krishan Mistry

/* Assignment details
– Ask the user to enter the atomic number, initial and final quantum numbers, and then asks the user whether to print out the energy of the transition in J or eV
– Make use of C++ specific features described in the lecture and pelecture
– The code ask whether to repeat (“y/n”), and stop if the answer is “n” .
– Check at each stage for incorrect inputs (either in format, or violating some physical conditions)
*/

// Program to calculate transition energy using simple Bohr formula

#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>

using namespace std;

// Function to return the energy. 
double  EnergyFunction(int Z, int n_i, int n_j){
	double Energy = 13.6*((double)(Z*Z))*((1 / (double)(n_j*n_j)) - (1 / (double)(n_i*n_i)));
	return Energy;
}


int main() {
	
	// Declare variables 
	double Energy; // Energy
	int  Z, n_i, n_j; // Atomic number, initial and final quantum numbers
	const double eVtoJ{ 1.602e-19 }; //conversion from eV to J	
	int i{0}; // counter to loop if n_i< n_j
	string units{'J'}; // String to check if user wants energy in eV or J
	string Repeat {'Y'}; // String to ask if user wants to repeat

	while (Repeat == "y" || Repeat == "Y") {
		i = 0; // Reset value for i if repeated
		// Ask user to enter atomic number
		cout << "Please enter the atomic number: ";
		cin >> Z;
		while (cin.fail() || Z <= 0 || cin.peek() != '\n') {
			// Input was invalid so ask to re-enter
			cout << "Sorry, input not valid, please enter a physical value for the atomic number: ";
			cin.clear(); cin.ignore(numeric_limits < streamsize>::max(), '\n');
			cin >> Z;
		}
		// Ask user to enter initial and final quantum numbers
		while (i == 0){
			cout << "Please enter the initial quantum number: ";
			cin >> n_i;

			while (cin.fail() || n_i <= 1 || cin.peek() != '\n') {
				// Input was invalidso ask to re-enter
				cout << "Sorry, input not valid, please enter a physical value for the initial quantum number: ";
				cin.clear(); cin.ignore(100, '\n');
				cin >> n_i;
			}
			cout << "Please enter the final quantum number: ";
			cin >> n_j;
			while (cin.fail() || n_j <= 0 || cin.peek() != '\n') {
				// Input was invalidso ask to re-enter
				cout << "Sorry, input not valid, please enter a physical value for the final quantum number: ";
				cin.clear(); cin.ignore(100, '\n');
				cin >> n_j;
			}
			if (n_i < n_j){
				// User has entered n_j<n_i
				cout << "You must enter an initial quantum number to be greater than the final! " << endl;
			}
			else
				// User has correctly entered the quantum numbers
				i = 1;
		}

		// Compute photon energy, Delta E = 13.6*(Z^2)*(1/n_j^2-1/n_i^2) eV
		Energy = EnergyFunction(Z, n_i, n_j);

		// Ask the user if they want the transition energies to be displayed in J or eV
		cout << "Please enter J for result in Joules or E for result in eV: ";
		cin >> units;
		while (cin.fail() || cin.peek() != '\n' || (units != "J" && units != "E")) {
			// Input was invalid so ask to re-enter
			cout << "Sorry, input not valid, please enter J for result in J or E for result in eV: ";
			cin.clear(); cin.ignore(100, '\n');
			cin >> units;
		}

		// Output answer
		if (units== "E"){
			// User chose to have output of answer in eV
			cout << "The energy in eV is: " << setprecision(3) << Energy << endl;
		}
		else if (units == "J") {
			// User chose to have output of answer in J
			cout << "The energy in J is: " << setprecision(5) << Energy*eVtoJ << endl;
		}

		// Ask the user if they want to repeat
		cout << "Do you want to repeat again Y for yes or N for no? ";
		cin >> Repeat;
		while (cin.fail() || cin.peek() != '\n' || (Repeat != "Y" && Repeat != "N" && Repeat != "y" && Repeat != "n")) {
			// Input was invalid so ask to re-enter
			cout << "Sorry, input not valid, please enter Y to repeat or N for stop: ";
			cin.clear(); cin.ignore(100, '\n');
			cin >> Repeat;			
		}
	}

	return 0;
}