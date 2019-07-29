#include "Logic.h"

Logic::Logic(int cSize, int aSize, int tSize, int oSize)
{
	// Each list of bank objects is activated
	// These methods make these objects ready to be accessed by customers
	customerSize = cSize;
	customerList = new Customer[customerSize];
	atmSize = aSize; // max of 10
	if (atmSize > 10) {
		atmSize = 10;
	}
	atmList = new ATM[atmSize];
	tellerSize = tSize; // max of 8
	if (tellerSize > 8) {
		tellerSize = 8;
	}
	tellerList = new Teller[tellerSize];
	officeSize = oSize; // max of 10
	if (officeSize > 10) {
		officeSize = 10;
	}
	officeList = new Office[officeSize];

	for (int i = 0; i < atmSize; i++) {
		atmList[i].activate();
	}
	for (int i = 0; i < tellerSize; i++) {
		tellerList[i].clockIn();
	}
	for (int i = 0; i < officeSize; i++) {
		officeList[i].openDoor();
	}
	customersServed = 0;
	timeScale = 1;
	powerOut = false;
	powerTime = 0;
	robberActive = false;
	robberTime = 0;
}

void Logic::newCustomer()
{
	// each customer is called iteratively, even those actively in the bank
	for (int i = 0; i < customerSize; i++) {
		// check that customer is not already in bank
		if (customerList[i].isActive() == false) {
			// 1 in a 1000 chance of a new customer arriving every tick (for each customer not already in bank, so odds much higher than 1/1000)
			if (rand() % (1000/timeScale) == 0) {
				customerList[i].initCustomer();
			}
		}
	}
}

void Logic::bankLoop()
{
	if (!robberActive) {
		// first, we roll a chance of a power outage if not already active
		if (!powerOut) {
			if (rand() % (40000 / timeScale) == 0) {
				powerOut = true;
				powerTime = 900;
			}
			if (rand() % (60000 / timeScale) == 0) {
				robberActive = true;
				robberTime = 900;
			}
		}

		// next, we tick time and check for completed tasks
		if (!powerOut) {
			for (int i = 0; i < atmSize; i++) {
				// if the timer hits zero, it will return true
				if (atmList[i].tickTime(timeScale)) {
					// when the timer has finished, we inform the user and begin ending procedure
					cout << "ATM is now done." << endl;
					// atm is no longer busy
					int customerID = atmList[i].endUse();
					// customer no longer busy and does not need a atm
					customerList[customerID].removeNeed(1);
					customerList[customerID].setBusy(false);
				}
			}
		}

		for (int i = 0; i < tellerSize; i++) {
			// if the timer hits zero, it will return true
			if (tellerList[i].tickTime(timeScale)) {
				// when the timer has finished, we inform the user and begin ending procedure
				cout << "Teller is now done." << endl;
				// teller no longer busy
				int customerID = tellerList[i].endWork();
				// customer no longer busy and does not need a teller
				customerList[customerID].removeNeed(2);
				customerList[customerID].setBusy(false);
			}
		}

		for (int i = 0; i < officeSize; i++) {
			// if the timer hits zero, it will return true
			if (officeList[i].tickTime(timeScale)) {
				// when the timer has finished, we inform the user and begin ending procedure
				cout << "Office is now done." << endl;
				// office is no longer busy
				int customerID = officeList[i].removeClient();
				// customer is no longer busy and does not need an office
				customerList[customerID].removeNeed(3);
				customerList[customerID].setBusy(false);
			}
		}

		// next we check for customers needing new tasks on non-busy bank objects

		// looping through all customers for each ATM looking for a match of an unoccupied ATM and an unbusy customer that needs an ATM next
		if (!powerOut) {
			for (int i = 0; i < atmSize; i++) {
				for (int j = 0; j < customerSize * 2; j++) {
					int rI = rand() % customerSize;
					if (!(atmList[i].isOccupied()) && customerList[rI].isActive() && !(customerList[rI].isBusy())) {
						int temp = customerList[rI].getNextNeed();
						if (temp == 1 || temp > 4) {
							// use of ATM and setting both it and the customer to busy begins
							cout << "ATM is now in use." << endl;
							atmList[i].beginUse(rI);
							customerList[rI].setBusy(true);
						}
						else if (temp == -1) {
							customersServed++;
						}
					}
				}
			}
		}

		// looping through all customers for each teller looking for a match of an unoccupied teller and an unbusy customer that needs an teller next
		for (int i = 0; i < tellerSize; i++) {
			for (int j = 0; j < customerSize * 2; j++) {
				int rI = rand() % customerSize;
				if (!(tellerList[i].isBusy()) && customerList[rI].isActive() && !(customerList[rI].isBusy())) {
					int temp = customerList[rI].getNextNeed();
					if (temp == 2 || temp == 4 || temp > 5) {
						// use of teller and setting both it and the customer to busy begins
						cout << "Teller is now in use." << endl;
						tellerList[i].beginWork(rI);
						customerList[rI].setBusy(true);
					}
					else if (temp == -1) {
						customersServed++;
					}
				}
			}
		}

		// looping through all customers for each office looking for a match of an unoccupied office and an unbusy customer that needs an office next
		for (int i = 0; i < officeSize; i++) {
			for (int j = 0; j < customerSize * 2; j++) {
				int rI = rand() % customerSize;
				if (!(officeList[i].isBusy()) && customerList[rI].isActive() && !(customerList[rI].isBusy())) {
					int temp = customerList[rI].getNextNeed();
					if (temp == 3 || temp == 4 || temp == 5 || temp == 7) {
						// use of office and setting both it and the customer to busy begins
						cout << "Office is now in use." << endl;
						officeList[i].takeClient(rI);
						customerList[rI].setBusy(true);
					}
					else if (temp == -1) {
						customersServed++;
					}
				}
			}
		}
	}
	if (powerOut) {
		powerTime -= timeScale;
		if (powerTime <= 0) {
			powerOut = false;
		}
	}
	if (robberActive){
		robberTime -= timeScale;
		if (robberTime <= 0) {
			robberActive = false;
		}
	}

}

bool Logic::hasCustomer(int object, int index)
{
	// Object is an ATM
	if (object == 1) {
		if (index >= atmSize || index < 0) {
			return false;
		}
		else {
			return atmList[index].isOccupied();
		}
	}
	// Object is a Teller
	else if (object == 2) {
		if (index >= tellerSize || index < 0) {
			return false;
		}
		else {
			return tellerList[index].isBusy();
		}
	}
	// Object is a Teller
	else if (object == 3) {
		if (index >= officeSize || index < 0) {
			return false;
		}
		else {
			return officeList[index].isBusy();
		}
	}
	return false;
}

int Logic::idleCustomers()
{
	int count = 0;

	for (int i = 0; i < customerSize; i++) {
		if (customerList[i].isActive() && !(customerList[i].isBusy())) {
			int temp = (customerList[i].getNextNeed());
			if (temp > 0) {
				count++;
			}
			else if (temp == -1) {
				customersServed++;
			}
		}
	}

	return count;
}

int Logic::totalCustomers()
{
	int count = 0;

	for (int i = 0; i < customerSize; i++) {
		if (customerList[i].isActive()) {
			
				count++;
		
		}
	}
	return count;
}

void Logic::changeTime(int flag)
{
	if (flag == 0) {
		if (timeScale != 1) {
			timeScale--;
		}
	}
	else if (flag == 1) {
		if (timeScale != 10) {
			timeScale++;
		}
	}
}
