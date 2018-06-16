// Assignment 8

// Krishan Mistry 27-03-17

#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<cmath>

using namespace std;

const double Pi(3.14159);

// Abstract Base class
class Shape {
protected:
	string name;
public:
	virtual ~Shape(){};				// Virtual destructor in abstract base class 	
	virtual void print_data() = 0;	// Virtual function to print the data
	virtual string GetName() = 0;   // Virtual function for getting the name of the shape
	virtual double Area() = 0;      // Virtual function for calculating the area (needed for accessing area for prism class)
	virtual double Volume() = 0;    // Virtual function for calculating the volume (arbitary)
};

// Abstract derived class for 2D Shapes
class Shape2D : public Shape {
protected:
	double lengtha;
	double lengthb;

public:
	virtual ~Shape2D(){};			  		// Virtual destructor	
	//virtual double Area() = 0;				// Virtual function for calculating the area
	//virtual double Volume() = 0;            // Virtual function for calculating the volume (arbitary)
	//virtual string GetName() = 0;			// Virtual function for getting the name of the shape
};

// Abstract derived class for 3D Shapes
class Shape3D : public Shape {
protected:
	double lengtha;
	double lengthb;
	double lengthc;

public:
	virtual ~Shape3D(){};			// Virtual destructor	
	//virtual double Volume() = 0;	// Virtual function for calulating the volume
	//virtual double Area() = 0;      // Virtual function for calculating the area (needed for accessing area for prism class)
	//virtual string GetName() = 0;   // Virtual function for getting the name of the shape

};

class Rectangle : public Shape2D {
public:
	Rectangle(){ lengtha = 0; lengthb = 0; name = "Rectangle"; };  // Defconstructor
	Rectangle(double lengtha_, double lengthb_) { lengtha = lengtha_; lengthb = lengthb_;  name = "Rectangle"; } // Parameterised constructor
	~Rectangle(){}; // Destructor

	double Area(){ return lengtha * lengthb; } // Overriden function for calculating the area
	double Volume(){ return 0; } // Initialise the volume function

	// Print the data
	void print_data(){
		cout << name << ":" << endl << setprecision(3) << "Area = " << Area() << endl << endl;

	}

	// Get the name of the Shape through an overridden function
	string GetName(){ return name; }
	
};

class Square : public Rectangle {
public:
	Square() : Rectangle(0, 0) { name = "Square"; }							// Defconstructor
	Square(double length) : Rectangle(length, length) { name = "Square"; }  // Parameterised constructor
	~Square(){};															// Destructor
};

class Ellipse : public Shape2D {
public:
	Ellipse(){ lengtha = 0; lengthb = 0; name = "Ellipse"; };												 // Defconstructor
	Ellipse(double lengtha_, double lengthb_) { lengtha = lengtha_; lengthb = lengthb_;  name = "Ellipse"; } // Parameterised constructor
	~Ellipse(){};																							 // Destructor

	double Area(){ return Pi * lengtha * lengthb; }	 // Overriden function for calculating the area
	double Volume(){ return 0; } // Initialise the volume function
	// Print the data
	void print_data(){
		cout << name << ":" << endl << setprecision(3) << "Area = " << Area() << endl << endl;

	}

	// Get the name of the Shape through an overridden function
	string GetName(){ return name; }

};

class Circle : public Ellipse {
public:
	Circle() : Ellipse(0, 0) { name = "Circle"; }						 // Defconstructor
	Circle(double length) : Ellipse(length, length) { name = "Circle"; } // Parameterised constructor
	~Circle(){};														 // Destructor
};

class Cuboid : public Shape3D {
public:
	Cuboid(){ lengtha = 0; lengthb = 0; lengthc = 0; name = "Cuboid"; };  // Defconstructor
	Cuboid(double lengtha_, double lengthb_, double lengthc_) { lengtha = lengtha_; lengthb = lengthb_; lengthc = lengthc_; name = "Cuboid"; } // Parameterised constructor
	~Cuboid(){}; // Destructor

	double Volume(){ return lengtha * lengthb * lengthc; } // Overriden function for calculating the volume

	double Area(){ return 2 * (lengtha * lengthb + lengthb * lengthc + lengtha * lengthc); } // Area of Cuboid

	// Print the data
	void print_data(){
		cout << name << ":" << endl << setprecision(3) << "Volume = " << Volume() << endl << "SArea = " << Area() << endl << endl;

	}

	// Get the name of the Shape through an overridden function
	string GetName(){ return name; }

};

class Cube : public Cuboid {
public:
	Cube() : Cuboid(0, 0, 0) { name = "Cube"; };								// Defconstructor
	Cube(double length) : Cuboid(length, length, length) {  name = "Cube"; };	// Parameterised constructor
	~Cube(){};																	// Destructor

};

class Ellipsoid : public Shape3D {
public:
	Ellipsoid(){ lengtha = 0; lengthb = 0; lengthc = 0; name = "Ellipsoid "; };  // Defconstructor
	Ellipsoid(double lengtha_, double lengthb_, double lengthc_) { lengtha = lengtha_; lengthb = lengthb_; lengthc = lengthc_; name = "Ellipsoid "; } // Parameterised constructor
	~Ellipsoid(){}; // Destructor

	double Volume(){ return (4.0/3.0) * Pi *  lengtha * lengthb * lengthc; } // Overriden function for calculating the volume

	double Area(){ 
		double temp(0.0);
		double p(1.6075);

		// Use Knud Thomsens formula
		temp = pow(lengtha, p) * pow(lengthb, p); // First term in formula etc..
		temp += pow(lengtha, p) * pow(lengthc, p);
		temp += pow(lengthb, p) * pow(lengthc, p);
				
		return 4.0 * Pi * pow(((1.0/3.0) * temp), 1.0/p); } 

	// Print the data
	void print_data(){
		cout << name << ":" << endl << setprecision(3) << "Volume = " << Volume() << endl << "SArea = " << Area() << endl << endl;

	}

	// Get the name of the Shape through an overridden function
	string GetName(){ return name; }

};

class Sphere : public Ellipsoid  {
public:
	Sphere() : Ellipsoid(0, 0, 0) { name = "Sphere"; };								 // Defconstructor
	Sphere(double length) : Ellipsoid(length, length, length) { name = "Sphere"; };  // Parameterised constructor
	~Sphere(){};																	 // Destructor

};

class Prism : public Shape3D {
private:
	Shape *Object2D;													// Shape pointer to point the the relavent 2D class

public:
	Prism(){ lengtha = 0; lengthb = 0; lengthc = 0; name = "Prism"; };  // DefConstructor
	Prism(double height, Shape *Shape_Pointer) {						// Param Constructor
		lengthc = height;												// Height of the prism extrusion
		Object2D = Shape_Pointer;										// Area of 2D shape
		name = Shape_Pointer -> GetName() + " Prism";					// Get total name of the prism
	}
	
	~Prism(){};															// Destructor

	// Get the volume
	double Volume(){ return Object2D -> Area() * lengthc; };		    // Override the volume function

	// Print the data
	void print_data(){
		cout << name << ":" << endl << setprecision(3) << "Volume = " << Volume() << endl << endl;
	}

	double Area() { return 0; }											// Define a function for the abstract base class
	string GetName(){ return name; }									// Defone a function for thr abstract base class

};

int main(){

	// Vector of Base class pointers
	vector<Shape*> Shape_vec;
	Shape_vec.push_back(new Rectangle(5,6)); // Create a rectangle etc...
	Shape_vec.push_back(new Square(10));
	Shape_vec.push_back(new Ellipse(2,1));
	Shape_vec.push_back(new Circle(9));
	Shape_vec.push_back(new Cuboid(1,2,3));
	Shape_vec.push_back(new Cube(1));
	Shape_vec.push_back(new Ellipsoid(1,2,4));
	Shape_vec.push_back(new Sphere(2));
	Shape_vec.push_back(new Prism(2, Shape_vec[0]));

	// Print the Data
	for (auto Shape_vecit = Shape_vec.begin(); Shape_vecit < Shape_vec.end(); Shape_vecit++){
		(*Shape_vecit)->print_data(); 
	}

	// Free up memory
	for (auto Shape_vecit = Shape_vec.begin(); Shape_vecit < Shape_vec.end(); Shape_vecit++){
		delete *Shape_vecit; 
	}

	Shape_vec.clear(); // Clear the vector
	cout << "Shape vector now has size " << Shape_vec.size() << endl;

	// Finito
	return 0;
}