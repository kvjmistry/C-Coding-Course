#ifndef VALIDATION_H // Header guard
#define VALIDATION_H
#include <iostream>
#include <string>

using namespace std;

double EnterValue(string Input); // Enter the freq/Res/Cap/Ind VALUE input checker
int    EnterNumber(int bound);   // Enter the component input checker
string EnterComponent();		 // Enter a component input checker
string EnterConnection();        // Enter a Paralell/Series input checker
string EndProgram();             // Enter a Paralell/Series input checker

#endif