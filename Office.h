/*
Matthew Pessolano
7/16/2019
Office.h
Purpose: Run Office functions for customers to access
*/


#ifndef OF_H
#define OF_H
#include <iostream>
#include <string>
#include "Customer.h"
using namespace std;

class Office {
public:

	/*
	Purpose: Default constructor of Office
	Parameters: None
	Output: Basic variables initialized
	*/
	Office();
	/*
	Purpose: Office object opened for use by customers
	Parameters: None
	Output: Default setting to variables set, office set to active
	*/
	void openDoor();
	/*
	Purpose: Start work process with customer in bank
	Parameters: custIndex is the index of the customer using the office in customerList
	Output: True if office is not busy and open, false otherwise
	*/
	bool takeClient(int custIndex);
	/*
	Purpose: End work with customer in bank
	Parameters: None
	Output: Index of customer previously using office, -1 if no valid customer or not busy
	*/
	int removeClient();
	/*
	Purpose: Decrement timeLeft if valid
	Parameters: scale is the time multiplier for current simulation functions
	Output: True if timeLeft is reduced to zero, false otherwise
	*/
	bool tickTime(int scale);
	bool timeDone() { return (processTime == 0); }
	bool isBusy() { return busy; }
private:
	// name of office; currently randomly generated
	string name;
	// status of office if it has a customer or not
	bool busy;
	// status of office as operational and able to accept customers
	bool clocked;
	// time left with current customer; 0 if no customer currently
	int timeLeft;
	// total time takes to process a customer with an office object
	int processTime;
	// index of current customer busy with (customerList); -1 if not busy with customer
	int activeCustomer;
};


#endif

