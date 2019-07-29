#include "Teller.h"

Teller::Teller()
{
	name = "Teller " + to_string(rand() % 10000);
	clocked = false;
	cout << "New teller hired named " << name << endl;
	activeCustomer = -1;
}

void Teller::clockIn()
{
	busy = false;
	clocked = true;
	processTime = 300;
	timeLeft = 0;
	cout << name << " has clocked in for today.\n";
}

bool Teller::beginWork(int custIndex)
{
	if (busy) {
		return false;
	}
	else {
		cout << name << " has accepted a new customer.\n";
		timeLeft = processTime;
		busy = true;
		activeCustomer = custIndex;
		return true;
	}
}

int Teller::endWork()
{
	if (!busy) {
		return -1;
	}
	else {
		cout << name << " is now free to accept a new customer.\n";
		busy = false;
		int temp = activeCustomer;
		activeCustomer = -1;
		return temp;
	}
}

bool Teller::tickTime(int scale)
{
	if (!busy) {
		return false;
	}
	else {
		timeLeft = timeLeft - (1 * scale);
		return (timeLeft <= 0);
	}
}
