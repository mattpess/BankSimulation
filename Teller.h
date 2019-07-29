/*
Matthew Pessolano
7/16/2019
Teller.h
Purpose: Run Teller functions for customers to access
*/


#ifndef TELLER_H
#define TELLER_H

#include <string>
#include <iostream>
#include "Customer.h"
using namespace std;

class Teller {
public:

	/*
	Purpose: General Teller constructor
	Parameters: None
	Output: Initialized Teller
	*/
	Teller();
	/*
	Purpose: Sets variables to default values when Teller is added to staff
	Parameters: None
	Output: Values initialized to start accepting customers
	*/
	void clockIn();
	/*
	Purpose: Customer is accepted; teller is no longer available to new clients
	Parameters: Index of customer using Teller in customerList
	Output: Return true if teller started as not busy, false otherwise; Teller set to be busy
	*/
	bool beginWork(int custIndex);
	/*
	Purpose: Customer leaves; teller is no longer busy
	Parameters: None
	Output: Return true if teller started as busy, false otherwise; teller set to not busy
	*/
	int endWork();
	/*
	Purpose: Decrement timeLeft if currently busy
	Parameters: scale is the time multiplier for current simulation functions
	Output: True if time is decremented to zero, false otherwise or if teller not busy
	*/
	bool tickTime(int scale);
	bool timeDone() { return (processTime == 0); }
	bool isBusy() { return busy; }
private:
	// name of teller object; randomly generated currently
	string name;
	// status of teller if it busy with a customer
	bool busy;
	// status of teller if able to be used
	bool clocked;
	// time left in current use of the teller; 0 if no active customer
	int timeLeft;
	// total time a use of the teller takes a customer
	int processTime;
	// index of customer using teller in customerList; -1 if no active customer
	int activeCustomer;
};


#endif

