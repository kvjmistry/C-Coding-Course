// Assignment 7
// Vectors 

// 19-03-17 Krishan Mistry

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<sstream>

using namespace std;

class Cartesian
{
protected:
	vector<double> r ; // Cartesian Vector
	int vecSize; 
public:
	// Default constructor implimentation
	Cartesian() { r; vecSize = 0; };

	// Secondary parameterized constructor implimentation
	Cartesian(int size){ 
		vecSize = size; 
		// sets size of vector in this case with zeros
		for (int i(0); i < size; i++){
			r.push_back(0);
		}
	} 

	// Parameterized constructor implimentation
	Cartesian(int size,string elements) : r(0) {
		stringstream ss(elements); // Use a stringstream to take the input
		double j;
		vecSize = size;

		while (ss >> j)
		{
			r.push_back(j); // Add elements to the vector

			if (ss.peek() == ','|| ss.peek() == ' '){ // Ignore the , or ' '
				ss.ignore();
			}	
		}

		if ( r.size() != size) { cerr << "Error input lengths do not match" << endl; exit(1); }
	}

	// Acess function for vector size
	int getSize(){ return vecSize; }

	// Copy constructor
	Cartesian(Cartesian&);

	// Move constructor
	Cartesian(Cartesian&&);

	// Copy  Assignment operator
	Cartesian& operator=(Cartesian&);

	// Move Assignment operator
	Cartesian& operator=(Cartesian&&);

	// Destructor
	~Cartesian(){}

	// Overload the [] operator
	double & operator[](int m) {	
		
		int comp(r.size()); // comparison for size of vector
		if (m > comp || m < 0) { cerr << "Error out of range" << endl; exit(1); } // Access out of bounds
		else { return r[m]; }
		 
	}

	double dot_product(Cartesian& vec){

		// Check if the vectors are the same size
		if (vecSize != vec.vecSize){
			cerr << "Error vectors are not the same size" << endl;
			exit(1);
		}
		// Calculate the dot product
		double temp(0);
		for (size_t k(0); k < r.size(); k++){
			temp += r[k] * vec.r[k];

		}
		return temp;
	}
	
	// Friend function to overload << operator
	friend ostream & operator<<(ostream &os, Cartesian &mat);
};

// Assignment operator for deep copying
Cartesian & Cartesian::operator=(Cartesian &vec)
{
	cout << "copy assignment\n";
	if (&vec == this) return *this; // no self assignment

	// First delete this object's array
	r.clear();
	vecSize = 0;

	// Copy values into new array
	for (size_t i(0); i < vec.r.size(); i++) {
		r.push_back(vec[i]);
	}
	vecSize = vec.getSize();

	return *this;// Special pointer!!!
}

// Copy constructor for deep copying
Cartesian::Cartesian(Cartesian &vec)
{
	r; 
	vecSize = 0;
	// Copy size and declare new array
	//cout << "copy constructor\n";
	for (size_t i(0); i < vec.r.size(); i++) {
		r.push_back(vec[i]);
	}	
	vecSize = vec.getSize();
}

// Move constructor
Cartesian::Cartesian(Cartesian &&vec)
{ // steal the data
	cout << "move constructor\n";
	r = vec.r;
	vecSize = vec.vecSize;
	vec.r.clear();
	vec.vecSize = 0;
}

// Move Assignment operator
Cartesian & Cartesian::operator=(Cartesian&& vec)
{
	cout << "move assignment\n";
	if (&vec == this) return *this; // no self assignment

	std::swap(r, vec.r);
	std::swap(vecSize, vec.vecSize);
	return *this; // Special pointer!!!
}

// Output stream for overloadint the << operator
ostream & operator<<(ostream &os, Cartesian &mat)
{
	os << "( ";

	for (size_t j(0); j < mat.r.size(); j++){

		if (j == mat.r.size()-1) os << mat.r[j] << " ";
		else os << mat.r[j] << ", ";

	}
	os << ")" ;

	return os;
}


class Minkowski : public Cartesian
{

public:
	// Default constructor
	Minkowski() : Cartesian(4) {};

	// Parameterised constructer 1
	Minkowski(double ct_, double x_, double y_, double z_ ) : Cartesian(4) {			
		r[0] = ct_; // Add each input into the vector
		r[1] = x_;
		r[2] = y_;
		r[3] = z_;
	};

	// Parameterised constructer 2 
	Minkowski(int size, double ct_, string elements ) :  Cartesian(size){
		 
		if (size != 3) { cerr << "Must enter a vector of size 3" << endl; exit(1); } // Check Size
		
		r[0] = ct_; // add the time term

		stringstream ss(elements); // Use a stringstream to add rest of the vector
		int j;
		vecSize = size;

		r.pop_back(); // resize the vector so the Minkowsi vector elements can be added in the right place
		r.pop_back();

		while (ss >> j)
		{
			r.push_back(j); // Add elements to the vector

			if (ss.peek() == ',' || ss.peek() == ' '){ // Ignore the , or ' '
				ss.ignore();
			}
		}
		
	};

	// Destructor
	~Minkowski(){}

	// Copy constructor
	Minkowski(Minkowski&);

	// Move constructor
	Minkowski(Minkowski&&);

	// Copy  Assignment operator
	Minkowski& operator=(Minkowski&);

	// Move Assignment operator
	Minkowski& operator=(Minkowski&&);

	// Override the dot_product function
	double dot_product(Minkowski& vec){
		// Check if the vectors are the same size
		if (r.size() != vec.r.size()){
			cerr << "Error vectors are not the same size" << endl;
			exit(1);
		}
		// Calculate the dot product
		double temp(0);
		for (size_t k(0); k < r.size(); k++){
			
			if (k == 0) temp += r[k] * vec.r[k]; // Time term
			else temp -= r[k] * vec.r[k]; // Spacial terms

		}
		return temp;
	}

	// Boost function
	Minkowski boost(Cartesian &beta){

		if (beta.getSize() != 3 || (beta[0] > 1 && beta[1] > 1 && beta[2] > 3)){ cerr << "Error the velocity needs to be a 3-vector and needs to be less than c!" << endl; exit(1); }

		double gamma = pow( 1 - beta.dot_product(beta), -0.5); // Lorentz factor gamma

		double product =r[1]*beta[0] + r[2]*beta[1] + r[3]*beta[2]; //Calculates product of r and beta 

		double factor = (((gamma - 1)*product) / (beta.dot_product(beta))) - (gamma*r[0]); //Calculates scalar factor 

		Minkowski temp; // Calculate the boost
		temp.r[0] = gamma * (r[0] - beta[0] * r[1]);
		temp.r[1] = r[1] + factor * beta[0];
		temp.r[2] = r[2] + factor  * beta[1];
		temp.r[3] = r[3] + factor * beta[2];

		return temp; // return the temp Minkowski vector
	}

	// Friend function to overload << operator
	friend ostream & operator<<(ostream &os, Minkowski &mat);

};

// Assignment operator for deep copying
Minkowski & Minkowski::operator=(Minkowski &vec)
{
	cout << "copy assignment\n";
	if (&vec == this) return *this; // no self assignment

	// First delete this object's array
	r.clear();
	vecSize = 0;

	// Copy values into new array
	for (size_t i(0); i < vec.r.size(); i++) {
		r.push_back(vec[i]);
	}
	vecSize = vec.vecSize;

	return *this;// Special pointer!!!
}

// Copy constructor for deep copying
Minkowski::Minkowski(Minkowski &vec)
{
	r;
	vecSize = 0;
	// Copy size and declare new array
	//cout << "copy constructor\n";
	for (size_t i(0); i < vec.r.size(); i++) {
		r.push_back(vec[i]);
	}
	vecSize = vec.getSize();
}

// Move constructor
Minkowski::Minkowski(Minkowski &&vec)
{ // steal the data
	cout << "move constructor\n";
	r = vec.r;
	vecSize = vec.vecSize;
	vec.r.clear();
	vec.vecSize = 0;
}

// Move Assignment operator
Minkowski & Minkowski::operator=(Minkowski&& vec)
{
	cout << "move assignment\n";
	if (&vec == this) return *this; // no self assignment

	std::swap(r, vec.r);
	std::swap(vecSize, vec.vecSize);
	return *this; // Special pointer!!!
}

// Output stream for overloadint the << operator
ostream & operator<<(ostream &os, Minkowski &mat)
{
	os << "( ";

	for (size_t j(0); j < mat.r.size(); j++){

		if (j == mat.r.size() - 1) os << mat.r[j] << " ";
		else os << mat.r[j] << ", ";

	}
	os << ")" << endl;

	return os;
}


class Particle{
private:
	Minkowski Position;
	double mass; // Mass in MeV
	Cartesian beta; // in \c^2

public:
	Particle() : Position(), beta(3), mass(0) {}

	// Param constructor Minkowski(psoition) || mass || Cartesian(beta)	
	Particle(Minkowski M_, double mass_, Cartesian C_) : Position(M_), beta(C_) ,mass(mass_){}

	~Particle(){};
	
	// Calculate the gamma factor
	double getGamma(){ return pow(1 - beta.dot_product(beta), -0.5); }

	// Calculate the energy
	double getEnergy() { return getGamma() * mass; }
	
	// Calcukate the momentum
	Cartesian getMom() {

		Cartesian temp(3); // Use temp vector to calculate momentum

		temp[0] = getGamma() * mass * beta[0]; // Calculations for each componet
		temp[1] = getGamma() * mass * beta[1];
		temp[2] = getGamma() * mass * beta[2];

		return temp;
	}

};


int main(){
	
	// Demonstrate the Cartesian Class copy construction, copy assignment, 
	cout << "\n============ Cartesian =============" << endl << endl;
	Cartesian b1; // Default constructer
	Cartesian a1(4, "1,4,7,4"); // Parameterised constructor
	cout << "Parameterised constructor implimentation" << endl;
	cout << "a1 = " << a1 << endl;

	Cartesian a2(4, "1,5,7,7");
	cout << "a2 = " << a2 << endl;

	double dp(a1.dot_product(a2)); // Dot product demonstration
	cout << "\nDot product(a2,a1) = " << dp << endl << endl;
		
	Cartesian a3(a1); // Copy constructor
	cout << "a3(a1) = " << a3 << endl << endl;
	
	a3 = a2; // Copy assignment 
	cout << "a3 = a2 = " << a3 << endl << endl;
	
	Cartesian a4 = move(a1); // Move constructor
	cout << "a4 = move(a1) = " << a4 << endl ;
	cout << "a1 = " << a1 << endl << endl;
		
	b1 = move(a2); // Move assignment
	cout << "b1 = move(a2) = " << b1 << endl;
	cout << "a2 = " << a2 << endl;

	// Minkowski Class demonstration ---------------------------------------
	cout << "\n============ Minkowski =============" << endl << endl;
	Minkowski m1;
	cout << "Default constructor" << endl << "m1 = " << m1 << endl;

	Minkowski m2(3, 2, "1,1,1"); // Parameterised constructor 1 implimentation
	cout << "Param constructor 1 " << endl <<"m2 = " << m2 << endl;

	Minkowski m3(5, 4, 2, 0); // Parameterised constructer 2 implimentation
	cout << "Param constructor 2" << endl <<"m3 = " << m3 << endl;
	
	Minkowski m5 = move(m2); // Copy constructor
	cout << "m5(m2) = " << m5 << "m2 = "<<  m2 << endl;

	m2 = m5; // Copy assignment 
	cout << "m2 = m5 = " << m2 << "m5 = "<< m5 << endl;

	double dp_m(m2.dot_product(m3)); // Dot product demonstration
	cout << "\nDot product(m2,m3) = " << dp_m << endl << endl;

	Cartesian beta(3, "0.75,0,0");

	Minkowski boost(m3.boost(beta));
	cout << "\nBoost m3 = " << boost << endl;
	
	// Particle Class demonstration ---------------------------------------
	cout << "\n============ Particle =============" << endl << endl;

	Particle electron(m5, 0.511, beta);

	cout << "The gamma factor of the electron: " << electron.getGamma() << endl << endl; // Gamma factor demonstration

	cout << "The energy of the electron: " << electron.getEnergy() << " MeV"<< endl <<endl; // Energy demonstration

	cout << "The momentum of the electron: " << electron.getMom() << " MeV/c" << endl << endl; // Momentum demonstration

	return 0;
}