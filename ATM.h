/*
Matthew Pessolano
7/16/2019
ATM.h
Purpose: Run ATM functions for customers to access
*/


#ifndef ATM_H
#define ATM_H

#include <iostream>
#include <string>
#include "Customer.h"
using namespace std;

class ATM {
public:

	/*
	Purpose: Default ATM constructor
	Parameters: None
	Output: Initialized ATM object
	*/
	ATM();
	/*
	Purpose: Performs beginning startup actions for the ATM object
	Parameters: None
	Output: Variables set to beginning default
	*/
	void activate();
	/*
	Purpose: ATM machine starts busy countdown until out of use by customer
	Parameters: custIndex is the customerList index of the customer that is using this machine
	Output: True if ATM is not already busy, false otherwise
	*/
	bool beginUse(int custIndex);
	/*
	Purpose: ATM is no longer busy and can be accessed by another customer
	Parameters: None
	Output: Index of the customer that had been using the machine is returned
	*/
	int endUse();
	/*
	Purpose: Decrement time if machine is in use
	Parameters: scale is the time multiplier for current simulation functions
	Output: Return true if machine usage time hits zero, false otherwise
	*/
	bool tickTime(int scale);
	bool timeDone() { return (processTime == 0); }
	bool isOccupied() { return occupied; }
private:
	// name of the machine, currently randomly generated
	string name;
	// true if machine is in use, false otherwise
	bool occupied;
	// true if machine can be used by customers, false otherwise
	bool on;
	// time left in current use of machine, 0 if not occupied
	int timeLeft;
	// starting time when machine is used
	int processTime;
	// index of active customer in customerList for Logic, -1 if not occupied
	int activeCustomer;
};


#endif
