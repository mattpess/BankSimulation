/*
Matthew Pessolano
7/22/2019
Logic.h
Purpose: Handle backend logic of the bank simulation
*/

#ifndef LOG_H
#define LOG_H

#include "ATM.h"
#include "Customer.h"
#include "Office.h"
#include "Teller.h"

class Logic {

public:
	Logic(int cSize, int aSize, int tSize, int oSize);
	/*
	Purpose: Generate new customers randomly if not already in bank
	Parameters: None
	Output: None; may change status of some Customers and make them active on a 1/1000 chance
	*/
	void newCustomer();
	/*
	Purpose: Simulates one loop of bank operations (tick time, pair bank objects with customers, end pairs of customers and objects, remove finished customers)
	Parameters: None
	Output: None
	*/
	void bankLoop();
	/*
	Purpose: Returns if a given object at a given index has a customer
	Parameters: index is the object's place in its list, and object corresponds with 1 for ATM, 2 for Teller, and 3 for Office
	Output: True if object is busy, false otherwise
	*/
	bool hasCustomer(int object, int index);
	/*
	Purpose: Calculates number of customers that are idle
	Parameters: None
	Output: Integer equal to number of customers that are active but not busy
	*/
	int idleCustomers();
	/*
	Purpose: Calculates number of customers total
	Parameters: None
	Output: Integer equal to number of customers that are active
	*/
	int totalCustomers();
	int getCustServed() { return customersServed; }
	/*
	Purpose: Change time scale of simulation
	Parameters: flag is 0 for decrease and 1 for increase
	Output: None
	*/
	void changeTime(int flag);
	int getScale() { return timeScale; }
	int getSizeA() { return atmSize; }
	int getSizeO() { return officeSize; }
	int getSizeT() { return tellerSize; }
	bool powerOff() { return powerOut; }
	bool robberOut() { return robberActive; }

private:
	// amount of customers possible in bank at once
	int customerSize = 30;
	// amount of offices active
	int officeSize = 10;
	// amount of atms active
	int atmSize = 10;
	// amount of tellers active
	int tellerSize = 8;
	// list of customers possible in bank
	Customer *customerList;
	// list of all offices
	Office *officeList;
	// list of all atms
	ATM *atmList;
	// list of all tellers
	Teller *tellerList;
	// count of served customers
	int customersServed;
	// affects speed of actions, such as customers entering or objects finishing
	int timeScale;
	// power outage status
	bool powerOut;
	// time left in power outtage
	int powerTime;
	// robber status
	bool robberActive;
	//time left until robber done
	int robberTime;
};

#endif
