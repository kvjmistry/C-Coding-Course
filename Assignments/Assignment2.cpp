// PHYS 30762 Programming in C++
// Assignment 2 2017

// Program to compute mean, standard deviation and standard
// error of the mean electronic charge. Data is read from file

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>

using namespace std;

// Functions to compute mean and standard deviation

// Function for calculating the mean
double mean(double x[], int N){
	// Sum over all elements in x
	double sum(0);
	for (int i(0); i < N; i++)
		sum = sum + x[i];

	double mu = (1.0/N) * sum ;
	return mu;
}

// Function for calculating the standard deviation
double sigma(double x[], double mu,  int N){
	// Calculate the standard deviation
	double sum(0);
	double temp; //temp variable to calculate elements in the sum
	for (int i = 0; i < N; i++){
		temp = (x[i] - mu)*(x[i] - mu);
		sum = sum + temp; // sum the previous plus new element
	}

	double sigma = sqrt((1.0 / (N-1.0)) * sum); // Calculate the std
	return sigma;
}


// Main function
int main() {
	// Declare variables
	string Filename; // Filename
	string line; // String for reading in the lines
	double dline; // Conversion of string to a float

	// Ask user to enter filename
	cout << "Please enter the file name you would like to read in" << endl;
	cin >> Filename;

	// Open file and check if successful
	fstream myfile1(Filename);
	// Check to see if the file opened successfully
	if (!myfile1.good()) { 
		// Print error message and exit
		cerr << "Error: file could not be opened" << endl;
		return(1);
	}
	else { // File opening was successful
	}

	// Figure out the number of lines in the file
	int N(0); //index for the total number of measurements
	int error(0); // Counter used to skip the line being read in
	while (!myfile1.eof()){
		error = 0;
		getline(myfile1, line); // Saves the line in the file in line.
		
		// Check if there are any characters in the string
		for (size_t k(0); k < line.length(); k++) {
			if (!(isalpha(line[k])) == false) { // Returns true if a character is detected
				error = 1; 
				break; // Break the loop as charater was found (data deduced already corrupt)
			}
		}
		if (error == 1) {
			continue; // Skip the while loop for this iteration
		} 

		if (line.empty()) { // Check to see if the line is empty, if it is then do nothing
		}
		else {
			N++; // Add one to the counter
		}
	}

	// Close file and open again for reading the actual data
	myfile1.close(); 

	fstream myfile2(Filename);
	if (!myfile2.good()) {
		// Print error message and exit
		cerr << "Error: file could not be opened" << endl;
		return(1);
	}
	else { // File opening was successful
		cout << "Successfully opened the file!" << endl;
	}

	// Allocate memory for data 
	double* MillikanData = new double[N];

	// Read data from file, ignoring any additional bad data
	int i(0); //index to run over file
	int j(0); //index to determine the number of valid measurements read in
	int error2(0); 
	while (!myfile2.eof()){
		error2 = 0;
		getline(myfile2, line); // Saves the line in the file in line.

		for (size_t k(0); k < line.length(); k++) { // size_t solves a signed/unsigned mismatch with the less than condition
			if (!(isalpha(line[k])) == false) {
				error2 = 1;
				break; // Break the loop as charater was found (data deduced already corrupt)
			}
		}
		if (error2 == 1) {
			i++;
			cout << "Notice: the line number, " << i << ", was ignored due to not being a right type of data " << endl;
			continue;
		}
		// Check to see if the line is empty or contains a character, if it does then do nothing
		if (line.empty()) { 
			i++;
			cout << "Notice: the line number, " << i << ", was ignored due to an empty line " << endl; 
			
		} else {

			dline = (double)atof(line.c_str());  // Convert the string to a double
			MillikanData[j] = dline; // Store the data into an array
			i++; j++; // Add one to the counters
		}
	}
	// Close file
	myfile2.close();

	// Print number of measurements read in
	cout << "The number of measurements read in is: " << j << endl;

	// Compute mean
	double mu = mean(MillikanData, N);
	cout << "The mean is: "<< mu <<"e-19 C" << endl;

	// Compute standard deviation
	double std = sigma(MillikanData, mu, N);
	cout << "The standard deviation is: " << std << "e-19 C" << endl;

	// Compute standard error of mean
	double SterrMean = std / sqrt(N);
	cout << "The standard error on the mean is: " << SterrMean << "e-19 C" << endl;

	// Free memory
	delete[] MillikanData;

	return 0;
}