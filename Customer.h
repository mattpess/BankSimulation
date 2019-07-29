/*
Matthew Pessolano
7/16/2019
Customer.h
Purpose: Handles customer's needs and information in bank
*/


#ifndef CUS_H
#define CUS_H

#include <iostream>
#include <string>
using namespace std;

class Customer {
public:

	/*
	Purpose:
	Parameters:
	Output:
	*/
	Customer();
	/*
	Purpose:
	Parameters:
	Output:
	*/
	void initCustomer();
	/*
	Purpose:
	Parameters:
	Output:
	*/
	int getNextNeed();
	/*
	Purpose:
	Parameters: 1 for atm, 2 for teller, 3 for office
	Output:
	*/
	void removeNeed(int need);
	void setBusy(bool status) { busy = status; }
	string getName() { return name; }
	bool isBusy() { return busy; }
	bool isActive() { return active; }

private:
	string name;
	bool needsTeller;
	bool needsOffice;
	bool needsATM;
	bool busy;
	bool active;
};


#endif


