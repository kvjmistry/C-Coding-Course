#include <iostream>
#include <string>
#include "validation.h"

using namespace std;

// ========================================= Functions for user input =================================================

// Enter the freq/Res/Cap/Ind VALUE input checker
double EnterValue(string Input){
	double Value;

	while (true){ // Loop until correct value entered

		// Try block to enter the specified value
		try{
			if (Input == "Freq"){			   // User will enter a frequency
				cout << "Please enter the driving frequency of the circuit (Hz): " << endl;
			}
			if (Input == "R" || Input == "r"){ // User will enter a resistance
				cout << "Please enter the resistance in Ohms: " << endl;
			}
			if (Input == "C" || Input == "c"){ // User will enter a capacitance
				cout << "Please enter the Capacitance in pF: " << endl;
			}
			if (Input == "I" || Input == "i"){ // User will enter a Inductance
				cout << "Please enter the Inductance in H: " << endl;
			}

			cin >> Value; // Take input

			if (cin.fail() || cin.peek() != '\n'){ // Catch a bad usr input and throw the error
				cin.clear(); cin.ignore(numeric_limits <streamsize>::max(), '\n'); // Clear the stream and ingnore the rest of the line
				throw 1;
			}
			if (Value <= 0){ // Value was negative
				cin.clear(); cin.ignore(numeric_limits <streamsize>::max(), '\n'); // Clear the stream and ingnore the rest of the line
				throw 2;
			}

			break; // Usr input successful

		}
		catch (int x){ // Output the error type
			if (x == 1) cerr << "ERROR: the value entered was not suitable. " << endl;
			if (x == 2) cerr << "ERROR: the value needs to be positive" << endl;
		}
	}

	return Value;
};

// Enter the component input checker
int EnterNumber(int bound){
	int Num;

	while (true){ // Loop until correct value entered

		// Try block to enter component vector
		try{
			cout << "Please enter the  component number you would like to add: " << endl;

			cin >> Num; // Take input

			if (cin.fail() || cin.peek() != '\n'){ // Catch a bad usr input and throw the error
				cin.clear(); cin.ignore(numeric_limits <streamsize>::max(), '\n'); // Clear the stream and ingnore the rest of the line
				throw 1;
			}
			if (Num < 1){ // Value was less than 1
				cin.clear(); cin.ignore(numeric_limits <streamsize>::max(), '\n'); // Clear the stream and ingnore the rest of the line
				throw 2;
			}
			if (Num > bound){
				cin.clear(); cin.ignore(numeric_limits <streamsize>::max(), '\n'); // Clear the stream and ingnore the rest of the line
				throw 3;
			}

			break; // Usr input successful

		}
		catch (int x){ // Output the error type
			if (x == 1) cerr << "ERROR: the value entered was not suitable. " << endl;
			if (x == 2) cerr << "ERROR: the value needs to be a positive int" << endl;
			if (x == 3) cerr << "ERROR: the value needs to be from the list" << endl;
		}
	}

	return Num - 1; // C++ counts from 0!
};

// Enter a component input checker
string EnterComponent(){
	string Component;

	while (true){ // Loop over until the user enters a correct value

		// Try block to enter Resistor/Capacitor/Inductor/Finish
		try{
			cout << "What component would you like to enter, a Resistor(R), Inductor(I) or Capacitor (C) or to Finish(F))? " << endl;

			cin >> Component; // Take input

			if (cin.fail() || cin.peek() != '\n'){ // Catch a bad usr input and throw the error
				cin.clear(); cin.ignore(numeric_limits < streamsize>::max(), '\n'); // Clear the stream and ingnore the rest of the line
				throw 1;
			}
			if ((Component != "R" && Component != "r"
				&& Component != "C" && Component != "c"
				&& Component != "I" && Component != "i"
				&& Component != "F" && Component != "f")){ // Value was not right character
				cin.clear(); cin.ignore(numeric_limits < streamsize>::max(), '\n'); // Clear the stream and ingnore the rest of the line
				throw 2;
			}

			break; // Usr input successful

		}
		catch (int x){ // Output the error type
			if (x == 1) cerr << "ERROR: the compoenent entered was not suitable. " << endl;
			if (x == 2) cerr << "ERROR: the component needs to be one of R/C/I/F " << endl;
		}
	}

	return Component;
}

// Enter a Paralell/Series input checker
string EnterConnection(){
	string ConnectionType;

	while (true){ // Loop over until the user enters a correct value

		// Try block to enter the connection type
		try{

			cin >> ConnectionType; // Take input

			if (cin.fail() || cin.peek() != '\n'){ // Catch a bad usr input and throw the error
				cin.clear(); cin.ignore(numeric_limits < streamsize>::max(), '\n'); // Clear the stream and ingnore the rest of the line
				throw 1;
			}

			if ((ConnectionType != "P" && ConnectionType != "p"
				&& ConnectionType != "S" && ConnectionType != "s"
				&& ConnectionType != "F" && ConnectionType != "f")){ // Value was not right character
				cin.clear(); cin.ignore(numeric_limits < streamsize>::max(), '\n'); // Clear the stream and ingnore the rest of the line
				throw 2;
			}

			break; // Usr input successful

		}
		catch (int x){ // Output the error type
			if (x == 1) cerr << "ERROR: the connection entered was not suitable. " << endl;
			if (x == 2) cerr << "ERROR: the connection needs to be one of P/S" << endl;

		}
	}

	return ConnectionType;
}

// Enter a Paralell/Series input checker
string EndProgram(){
	string EndProgram;

	while (true){ // Loop over until the user enters a correct value

		// Try block to enter the end choice
		try{

			cin >> EndProgram; // Take input

			if (cin.fail() || cin.peek() != '\n'){ // Catch a bad usr input and throw the error
				cin.clear(); cin.ignore(numeric_limits < streamsize>::max(), '\n'); // Clear the stream and ingnore the rest of the line
				throw 1;
			}

			if ((EndProgram != "Y" && EndProgram != "y"
				&& EndProgram != "N" && EndProgram != "n")){ // Value was not right character
				cin.clear(); cin.ignore(numeric_limits < streamsize>::max(), '\n'); // Clear the stream and ingnore the rest of the line
				throw 2;
			}

			break; // Usr input successful

		}
		catch (int x){ // Output the error type
			if (x == 1) cerr << "ERROR: the connection entered was not suitable. " << endl;
			if (x == 2) cerr << "ERROR: the connection needs to be one of P/S" << endl;

		}
	}

	return EndProgram;
}