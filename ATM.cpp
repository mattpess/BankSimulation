#include "ATM.h"

ATM::ATM()
{
	name = "ATM " + to_string(rand() % 10000);
	on = false;
	cout << "New ATM machine shipped to the bank: " << name << endl;
	activeCustomer = -1;
}

void ATM::activate()
{
	on = true;
	occupied = false;
	processTime = 200;
	timeLeft = 0;
	cout << name << " has been turned on and calibrated.\n";
}

bool ATM::beginUse(int custIndex)
{
	if (occupied)
		return false;
	else {
		cout << name << " is now in use by a customer.\n";
		timeLeft = processTime;
		occupied = true;
		activeCustomer = custIndex;
		return true;
	}
}

int ATM::endUse()
{
	if (!occupied)
		return -1;
	else {
		cout << name << " is now free to use.\n";
		occupied = false;
		int temp = activeCustomer;
		activeCustomer = -1;
		return temp;
	}
}

bool ATM::tickTime(int scale)
{
	if (!occupied)
		return false;
	else {
		timeLeft= timeLeft - (1 * scale);
		return(timeLeft <= 0);
	}
}
