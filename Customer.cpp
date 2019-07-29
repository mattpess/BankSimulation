#include "Customer.h"

Customer::Customer()
{
	name = "Customer " + to_string(rand() % 10000);
	active = false;

}

void Customer::initCustomer()
{
	cout << name << " is active!" << endl;
	active = true;
	// randomly generate customer needs
	int randNeeds = rand() % 7;
	if (randNeeds == 0) {
		needsATM = false;
		needsTeller = true;
		needsOffice = false;
	}
	else if (randNeeds == 1) {
		needsATM = false;
		needsTeller = false;
		needsOffice = true;
	}
	else if (randNeeds == 2) {
		needsATM = true;
		needsTeller = false;
		needsOffice = false;
	}
	else if (randNeeds == 3) {
		needsTeller = true;
		needsOffice = true;
		needsATM = false;
	}
	else if (randNeeds == 4) {
		needsTeller = true;
		needsATM = true;
		needsOffice = false;
	}
	else if (randNeeds == 5) {
		needsOffice = true;
		needsATM = true;
		needsTeller = false;
	}
	else if (randNeeds == 6) {
		needsTeller = true;
		needsOffice = true;
		needsATM = true;

	}
	busy = false;
}

int Customer::getNextNeed()
{
	// order of needs: office, teller, atm.
	// must be handled in this order
	if (!active) {
		return 0;
	}
	if (needsATM && needsTeller && needsOffice) {
		return 7;
	}
	else if (needsATM && needsTeller) {
		return 6;
	}
	else if (needsATM && needsOffice) {
		return 5;
	}
	else if (needsTeller && needsOffice) {
		return 4;
	}
	else if (needsATM) {
		return 1;
	}
	else if (needsTeller) {
		return 2;
	}
	else if (needsOffice) {
		return 3;
	}
	else 
	{
		cout << name << " has left." << endl;
		active = false;
		return -1;
	}
	return 0;
}

void Customer::removeNeed(int need)
{
	if (need == 1) {
		needsATM = false;
	}
	else if (need == 2) {
		needsTeller = false;
	}
	else if (need == 3) {
		needsOffice = false;
	}
}
