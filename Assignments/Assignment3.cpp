// PHYS 30762 Programming in C++
// Assignment 3 2017
// Simple code to store courses using vectors and strings and then prints them out using an iterator

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<algorithm>

using namespace std;

// Function for sorting the courselist by name
bool SortName(string a, string b)
{
	int j, end;
	// Find the smallest string to run over
	int end_a = a.length();
	int end_b = b.length();
	if (end_a < end_b){
		end = end_a;
	}
	else{
		end = end_b;
	}
	// Loop over comparing each individual element comparing the letters after the 10th character in the string
	for (j = 10; j < end; j++){
		
		if (a[j] < b[j]){
			return true;
		}
		// For the reverse case
		else if (a[j] > b[j]){
		return false;
		}
		else; // letters were the same
	}
	return false;
}


int main(void)
{
	const string   degreeCode("PHYS");
	string         CourseName;
	string         line;          // For line from reading in file 
	vector<string> CourseList;    // Vector for storing the inputted courses
	vector<string> CourseListCmp; // Vector for all the courselists
	bool		   not_finished(true);
	bool           CorrectInput(true);
	bool           Flag(true);

	// Read in the file to compare inputs
	// Open file and check if successful
	fstream myfile("courselist.dat");
	// Check to see if the file opened successfully
	if (!myfile.good()) {
		// Print error message and exit
		cerr << "Error: file could not be opened" << endl;
		return(1);
	}
	else { // File opening was successful
	}

	while (!myfile.eof()){

		getline(myfile, line); // Saves the line in the file in line.	
		CourseListCmp.push_back(line); // Add the line into the vector 
	}

	myfile.close(); // Close the file 

	// Display the read in file
	cout << "Sample inputs: \n" << endl;
	for (auto iterator = CourseListCmp.begin(); iterator != CourseListCmp.end(); iterator++){
		cout << *iterator << endl;
	}

	// Gather list of courses and their codes from user
	do
	{
		
		// Ask the user to imput the filename
		cout << "---------------------------------" << endl;
		cout << "Please enter a course name, preferably from the list above: \n\n";
		cout << "** The format must be starting with a 5 digit number followed by the course name";
		cout << "** OR enter x to finish." << endl;

		getline(cin, CourseName); // Take input

		if (CourseName == "x" || CourseName == "X") {
			not_finished = false;
			continue; // Don't read rest of loop in and exit by changing the bool

		}
		else if (CourseName.length() < 5){
			// User has input less than 5 characters, this is clearly wrong
			cerr << "\nError, please enter a correct course code from the list \n" << endl;
			continue;

		}
		else if (CourseName[5] != ' '){
			// User has input less than 5 characters, this is clearly wrong
			cerr << "\nError, please enter a correct course code from the list \n" << endl;
			continue;
		}

		// Check if the course code entered was valid
		string Code(CourseName);

		// Get the course code and the name from the entered string 
		Code.erase(Code.begin() + 5, Code.end());

		// Check that the code was entered correctly
		for (size_t i(0); i < Code.length(); i++){

			if (isdigit(Code[i]) == false) {
				// User has input characters in the course code, this is clearly wrong
				Flag = false;
			}
		}
		if (Flag == false) {
			cerr << "\nError, please enter a correct course code from the list \n" << endl;
			continue; // There was a character in the course code so not valid
		}

		// User has entered a code which is from year 1 to 4
		if ((Code[0] == '1' || Code[0] == '2' || Code[0] == '3' || Code[0] == '4')) {
			cout << "Correct Filename entered!" << endl;
		}
		else{
			cerr << "\nError, please enter a correct course code from the list \n" << endl;
			continue; // There was a character in the course code so not valid
		}

		// Make the full course title
		ostringstream ofss;
		ofss << degreeCode << " " << CourseName; // Put the full course name together
		string FullCourseTitle{ ofss.str() };
		ofss.str(""); //clear ofss content

		// Append the course to the final list
		CourseList.push_back(FullCourseTitle); // Add the correctly formatted course into a vector
		
		// Reset the flag for a bad input
		Flag = true;

	} while (not_finished);

	// Print out full list of courses
	cout << endl; // Add white space between entries
	cout << "------------------------------" << endl;
	cout << "List of courses:" << endl;

	for (auto iterator = CourseList.begin(); iterator != CourseList.end(); iterator++){
		cout << *iterator << endl;

	}

	// Sort the entered list based on the year entered
	int yearChoice;
	string sortOption;

	cout << "Please enter year: ";
	cin >> yearChoice;
	while (cin.fail() || cin.peek() != '\n' || (yearChoice != 1 && yearChoice != 2 && yearChoice != 3 && yearChoice != 4)) {
		// Input was invalid so ask to re-enter
		cout << "Sorry, input not valid, please enter a year from 1,2,3 or 4: ";
		cin.clear(); cin.ignore(numeric_limits <streamsize>::max(), '\n');
		cin >> yearChoice;

	}

	cout << "-----------------------------" << endl;
	cout << "\nThe courses  entered in the year " << yearChoice << " are: " << endl;
	// Readout the courselist with  the entered year
	for (auto iterator = CourseList.begin(); iterator != CourseList.end(); iterator++){
		string test(*iterator);
		string comp = to_string(yearChoice); // Convert integer to a string and compare

		if (test.substr(5, 1) == comp){ // Check fith character which is the year
			cout << *iterator << endl;
		}
	}

	// Sort the data based on the name or the course code 
	cout << "---------------------------------------------------------" << endl;
	cout << "\nPlease enter code or name to sort the list by code or name respectively: ";
	cin >> sortOption;
	while (cin.fail() || cin.peek() != '\n' || (sortOption != "code" && sortOption != "name")) {
		// Input was invalid so ask to re-enter
		cout << "Sorry, input not valid, please enter code or name: ";
		cin.clear(); cin.ignore(numeric_limits <streamsize>::max(), '\n');
		cin >> sortOption;
	}

	if (sortOption == "code"){
		// Sort the data based on the course code 
		vector <string>::iterator Begin{ CourseList.begin() }, End{ CourseList.end() };
		sort(Begin, End); // Sort data in ascending order

		cout << "\nSorted data by code:\n" << endl;

		vector <string>::iterator Sorted;
		for (Sorted = Begin; Sorted < End; ++Sorted)
			cout << *Sorted << endl;
	}
	else {
		// sort the data based on the name 
		vector <string>::iterator Begin{ CourseList.begin() }, End{ CourseList.end() };
			
		sort(CourseList.begin(), CourseList.end(), SortName); // Call function SortName to sort

		cout << "\nSorted data by name:\n" << endl;

		vector <string>::iterator Sorted;
		for (Sorted = Begin; Sorted < End; ++Sorted)
			cout << *Sorted << endl;

	}

	return 0;
}