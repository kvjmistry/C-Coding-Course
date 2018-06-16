#include <iostream>
#include <string>
#include "Complex.h"
#include "Component.h"

using namespace std;


// ------------------------------------------- Resistor class -------------------------------------------------------
void    Resistor::SetFreq(double freq_){ freq = freq_; };		// Set and get various quantities
double  Resistor::GetFreq() { return 0; };
complex Resistor::GetImpedence()  { return complex(R, 0); };
double  Resistor::GetPhase()  { return GetImpedence().GetArg(); }
double  Resistor::GetMag()  { return GetImpedence().GetMod(); }
void    Resistor::PrintData(){ cout << R << " Ohm Resistor" << endl; }; // Function to print the component in the library

// ------------------------------------------- Capacitor class -------------------------------------------------------

void    Capacitor::SetFreq(double freq_){ freq = freq_; };      // Set and get various quantities
double  Capacitor::GetFreq()  { return freq; };
complex Capacitor::GetImpedence()  { return complex(0, -1.0 / (2 * Pi * C *freq*(1.0e-12))); }; // Factor of 10^-12 to convert from pF to F
double  Capacitor::GetPhase()  { return GetImpedence().GetArg(); }
double  Capacitor::GetMag()  { return GetImpedence().GetMod(); }
void    Capacitor::PrintData(){ cout << C << " pF Capacitor" << endl; }; // Function to print the component in the library

// ------------------------------------------- Inductor Class --------------------------------------------------------

void    Inductor::SetFreq(double freq_){ freq = freq_; }; // Set and get various quantities
double  Inductor::GetFreq() { return freq; };
complex Inductor::GetImpedence()  { return complex(0, 2 * Pi* L * freq); };
double  Inductor::GetPhase()  { return GetImpedence().GetArg(); }
double  Inductor::GetMag()  { return GetImpedence().GetMod(); }
void    Inductor::PrintData(){ cout << L << " H Inductor" << endl; }; // Function to print the component in the library

