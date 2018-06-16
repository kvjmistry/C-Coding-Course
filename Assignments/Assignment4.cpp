
// PHYS 30762 Programming in C++
// Assignment 4

// Krishan Mistry 25/02/17

// Simple demonstration of a C++ class

// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

class Galaxy
{
private:
	string hubbleType;
	double redshift, totalMass, stellarMassFraction;
	vector<Galaxy*> Satellite; // Need pointer back to class

public:
	// Constructors
	Galaxy() : hubbleType(""), redshift{ 0 }, totalMass{ 0 }, stellarMassFraction{ 0 }, Satellite(0) {} // Default constructor

	Galaxy(string phubbleType, double predshift, double ptotalMass, double pstellarMassFraction) :
		hubbleType(phubbleType), redshift{ predshift }, totalMass{ ptotalMass }, stellarMassFraction{ pstellarMassFraction }
	{} // Parameterised Constructor

	// Destructor
	~Galaxy() {
		for (auto Galaxy : Satellite) { // Delete the Vector of Object 
			delete Galaxy;
		}
	}
	//~Galaxy() { cout << "Destroying" << hubbleType << endl; }
	
	// Return stellar mass (M_* = f_* x M_tot)
	double stellarMass() { 	return stellarMassFraction * totalMass; }

	// Change galaxy's Hubble type
	void changeType(string newType) { hubbleType = newType; }

	// Prototype for function to print out an object's data
	void printData();

	// Add satellite galaxy
	void addSatellite(string hubbleTypeIn, double z, double mass, double Smass);

};
// Print out an object's data
void Galaxy::printData(){
	cout.precision(2); // 2 Significant figures
	cout << hubbleType << " " << redshift << " " << totalMass << " " << stellarMassFraction << endl;

	// Print the Satellite Data
	if (Satellite.size() != 0){
		cout << "\nThe total number of Satellites associated with this galaxy is: " << Satellite.size() << endl;
		cout << "The details of each satellite galaxy are:  " << endl;
		for (auto iterator = Satellite.begin(); iterator < Satellite.end(); iterator++){
			(*iterator) -> printData(); // Dereference pointer which is a pointer
		}
	}
}

// Add a Satellite Galaxy to the existing Galaxy
void Galaxy::addSatellite(string hubbleTypeIn, double z, double mass, double Smass){
	Satellite.push_back(new Galaxy(hubbleTypeIn, z, mass, Smass));
		
}

// End of class and associated member functions

// Main program
int main()
{

	// Example using default constructor
	Galaxy g1;
	
	// Example using parameterised constructor

	// Initialize
	bool not_finished(true), IncorrectInput(true); // Allow user to enter as many galaxies as they like	
	string Finished, input, hubbleTypeIn;
	vector<Galaxy> Galaxy_data;
	double zTemp, z, massTemp, mass, SmassTemp, Smass;


	// Input Check
	vector<string> HTypeCmp;
	HTypeCmp.push_back("E0"); HTypeCmp.push_back("E1"); HTypeCmp.push_back("E2"); HTypeCmp.push_back("E3"); HTypeCmp.push_back("E4");
	HTypeCmp.push_back("E5"); HTypeCmp.push_back("E6"); HTypeCmp.push_back("E7"); HTypeCmp.push_back("S0"); HTypeCmp.push_back("Sa");
	HTypeCmp.push_back("Sb"); HTypeCmp.push_back("Sc"); HTypeCmp.push_back("SBa"); HTypeCmp.push_back("SBb"); HTypeCmp.push_back("SBc");
	HTypeCmp.push_back("Irr");


	while (not_finished) {

		// Ask user if they want to enter a galaxy or exit
		cout << "----------------------------------------------------------" << endl;
		cout << "Please enter 'Y' to enter a Galaxy or'N' to finish: " << endl;
		getline(cin, Finished); // Take input)

		if (Finished == "n" || Finished == "N") {
			if (Galaxy_data.size() == 0){
				// User didnt enter a galaxy so can't finish yet
				cout << "You must enter a Galaxy to start off with!" << endl;
				continue;
			}
			else{
				not_finished = false;
				continue; // Don't read rest of loop in and exit by changing the bool
			}
		}
		else if (Finished == "Y" || Finished == "y") {

		}
		else {
			cerr << "\nError in input \n" << endl;
			continue;
		}

				
		// Enter the Hybble type 
		while (IncorrectInput){
			cout << "----------------------------------------------------------" << endl;
			cout << "Please enter the Hubble Type from the list: \n" << "E0-7, S0, Sa,Sb, Sc, SBa, SBb, SBc and Irr " << endl;
			getline(cin, input);

			// Loop over input vector and see if the strings match 
			for (auto iterator = HTypeCmp.begin(); iterator < HTypeCmp.end(); iterator++){

				if (*iterator == input) {
					IncorrectInput = false;
					hubbleTypeIn = input;
					continue;
				} 					

			} 
			
			if (IncorrectInput == true) cerr << "\nError, you must enter a galaxy type from the list given!" << endl;  // No strings match
		} 
		
		IncorrectInput = true; // Reset bool

		// Enter redshift
		while (IncorrectInput){
			cout << "----------------------------------------------------------" << endl;
			cout << "Please enter the redshift in the range [0,10]: " << endl;
			getline(cin, input);

			if (input == "0"){
				// Entered a redshif of zero so deal with separatly
				zTemp = (double)atof(input.c_str());  // Convert the string to a double
				IncorrectInput = false;
				z = zTemp;
				continue;
			}

			// Convert to an integer
			zTemp = (double)atof(input.c_str());  // Convert the string to a double
			
			if (0.0 < zTemp && zTemp <= 10.0){ // If a string was entered the conversion returns 0 so reject
				// Entered a z in correct range 
				IncorrectInput = false;
				z = zTemp;
				continue;
			}
			if (IncorrectInput == true) cerr << "\nError in the input!" << endl;  // No strings match
			
		}		
		IncorrectInput = true;
		
		// Enter total mass
		while (IncorrectInput){
			cout << "----------------------------------------------------------" << endl;
			cout << "Please enter the Total mass in the range [10^7,10^12]: " << endl;
			getline(cin, input);

			// Convert to an integer
			massTemp = (double)atof(input.c_str());  // Convert the string to a double

			if (1.0e7 <= massTemp && massTemp <= 1.0e12){ // If a string was entered the conversion returns 0 so reject
				// Entered a z in correct range 
				IncorrectInput = false;
				mass = massTemp;
				continue;
			}
			if (IncorrectInput == true) cerr << "\nError in the input!" << endl;  // No strings match

		}
		IncorrectInput = true;

		// Enter the stellar mass fraction
		while (IncorrectInput){
			cout << "----------------------------------------------------------" << endl;
			cout << "Please enter the stellar mass fraction in the range [0,0.05]: " << endl;
			getline(cin, input);

			if (input == "0"){
				// Entered a redshif of zero so deal with separatly
				SmassTemp = (double)atof(input.c_str());  // Convert the string to a double
				IncorrectInput = false;
				Smass = SmassTemp;
				continue;
			}

			// Convert to an integer
			SmassTemp = (double)atof(input.c_str());  // Convert the string to a double

			if (0.0 < SmassTemp && SmassTemp <=0.05){ // If a string was entered the conversion returns 0 so reject
				// Entered a z in correct range 
				IncorrectInput = false;
				Smass = SmassTemp;
				continue;
			}
			if (IncorrectInput == true) cerr << "\nError in the input!" << endl;  // No strings match

		}
		IncorrectInput = true;


		// Add the entered galaxy details into the vector
		Galaxy_data.push_back(Galaxy(hubbleTypeIn, z, mass, Smass));

				
	} // end of inputs
	not_finished = true;

	// print out data
	cout << "----------------------------------------------------------" << endl;
	cout << "\n*************** Galaxy Classification ******************\n" << endl;
	for (auto iterator = Galaxy_data.begin(); iterator < Galaxy_data.end(); iterator++){
		iterator -> printData();

	}

	// Change Hubble type from Irr to S0
	string newType{ "S0" };
	string changeType;
		
	for (auto iterator = Galaxy_data.begin(); iterator < Galaxy_data.end(); iterator++){

		while (not_finished){
			// Ask user if they want to change a galaxy
			cout << "----------------------------------------------------------" << endl;
			cout << "Please enter 'Y' to change a Galaxy to 'S0', or'N' to keep it the same: " << endl;
			getline(cin, changeType); // Take input)

			if (changeType == "n" || changeType == "N") {
				not_finished = false;
				cout << "Galaxy type is left unchanged: " << endl;
				iterator -> printData();
				continue; // Don't read rest of loop in and exit by changing the bool
			}
			else if (changeType== "Y" || changeType== "y") {
				// Change te Galaxy Type
				iterator -> changeType(newType);
				cout << "Changed the galaxy's hubble type to: " << endl;
				iterator -> printData();
				not_finished = false;
				continue;
			}
			else {
				cerr << "\nError in input \n" << endl;
				continue;
			}

		}
		not_finished = true;

	}

	// Updated galaxy list
	cout << "----------------------------------------------------------" << endl;
	cout << "\n*************Galaxy Classification Updated****************\n" << endl;
	for (auto iterator = Galaxy_data.begin(); iterator < Galaxy_data.end(); iterator++){
		iterator -> printData();

	}


	// Get and print out stellar mass
	cout << "----------------------------------------------------------" << endl;
	cout << "********************* Stellar Mass ***********************\n" << endl;
	for (auto iterator = Galaxy_data.begin(); iterator < Galaxy_data.end(); iterator++){
		
		cout << "Galaxy:" << endl;
		iterator->printData();
		cout << "The stellar mass of galaxy:" << endl;
		cout <<iterator -> stellarMass() << "\n"<<  endl;

	}

	
	// Add satellite galaxies
	cout << "\n--------------------------------------" << endl;
	cout << "**Satellite**\n" << endl;
	for (auto iterator = Galaxy_data.begin(); iterator < Galaxy_data.end(); iterator++){
		
		while (not_finished) {

			// Ask user if they want to enter a galaxy or exit
			cout << "----------------------------------------------------------" << endl;
			cout << "Please enter 'Y' to enter a satellite galaxy or'N' to finish: " << endl;
			getline(cin, Finished); // Take input)

			if (Finished == "n" || Finished == "N") {
				not_finished = false;
				continue; // Don't read rest of loop in and exit by changing the bool
			
			}
			else if (Finished == "Y" || Finished == "y") {

			}
			else {
				cerr << "\nError in input \n" << endl;
				continue;
			}

			// Enter the Hybble type 
			while (IncorrectInput){
				cout << "----------------------------------------------------------" << endl;
				cout << "Please enter the Hubble Type from the list: \n" << "E0-7, S0, Sa,Sb, Sc, SBa, SBb, SBc and Irr " << endl;
				getline(cin, input);

				// Loop over input vector and see if the strings match 
				for (auto iterator = HTypeCmp.begin(); iterator < HTypeCmp.end(); iterator++){

					if (*iterator == input) {
						IncorrectInput = false;
						hubbleTypeIn = input;
						continue;
					}

				}

				if (IncorrectInput == true) cerr << "\nError, you must enter a galaxy type from the list given!" << endl;  // No strings match
			}

			IncorrectInput = true; // Reset bool

			// Enter redshift
			while (IncorrectInput){
				cout << "----------------------------------------------------------" << endl;
				cout << "Please enter the redshift in the range [0,10]: " << endl;
				getline(cin, input);

				if (input == "0"){
					// Entered a redshif of zero so deal with separatly
					zTemp = (double)atof(input.c_str());  // Convert the string to a double
					IncorrectInput = false;
					z = zTemp;
					continue;
				}

				// Convert to an integer
				zTemp = (double)atof(input.c_str());  // Convert the string to a double

				if (0.0 < zTemp && zTemp <= 10.0){ // If a string was entered the conversion returns 0 so reject
					// Entered a z in correct range 
					IncorrectInput = false;
					z = zTemp;
					continue;
				}
				if (IncorrectInput == true) cerr << "\nError in the input!" << endl;  // No strings match

			}
			IncorrectInput = true;

			// Enter total mass
			while (IncorrectInput){
				cout << "----------------------------------------------------------" << endl;
				cout << "Please enter the Total mass in the range [10^7,10^12]: " << endl;
				getline(cin, input);

				// Convert to an integer
				massTemp = (double)atof(input.c_str());  // Convert the string to a double

				if (1.0e7 <= massTemp && massTemp <= 1.0e12){ // If a string was entered the conversion returns 0 so reject
					// Entered a z in correct range 
					IncorrectInput = false;
					mass = massTemp;
					continue;
				}
				if (IncorrectInput == true) cerr << "\nError in the input!" << endl;  // No strings match

			}
			IncorrectInput = true;

			// Enter the stellar mass fraction
			while (IncorrectInput){
				cout << "----------------------------------------------------------" << endl;
				cout << "Please enter the stellar mass fraction in the range [0,0.05]: " << endl;
				getline(cin, input);

				if (input == "0"){
					// Entered a redshif of zero so deal with separatly
					SmassTemp = (double)atof(input.c_str());  // Convert the string to a double
					IncorrectInput = false;
					Smass = SmassTemp;
					continue;
				}

				// Convert to an integer
				SmassTemp = (double)atof(input.c_str());  // Convert the string to a double

				if (0.0 < SmassTemp && SmassTemp <= 0.05){ // If a string was entered the conversion returns 0 so reject
					// Entered a z in correct range 
					IncorrectInput = false;
					Smass = SmassTemp;
					continue;
				}
				if (IncorrectInput == true) cerr << "\nError in the input!" << endl;  // No strings match

			}
			IncorrectInput = true;


			// Add the entered galaxy details into the vector
			iterator -> addSatellite(hubbleTypeIn, z, mass, Smass);
			
		} // end of inputs
		not_finished = true;
		
		cout << "-------------------------------------------" << endl;
		cout << "The main galaxy is:" << endl;
		iterator->printData();

	}

	return 0;
}
