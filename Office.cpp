#include "Office.h"

Office::Office()
{
	name = "Office " + to_string(rand() % 10000);
	clocked = false;
	cout << "New office manager hired named " << name << endl;
	activeCustomer = -1;
}

void Office::openDoor()
{
	busy = false;
	clocked = true;
	processTime = 600;
	timeLeft = 0;
	cout << name << " has clocked in for today.\n";
}

bool Office::takeClient(int custIndex)
{
	if (busy) {
		return false;
	}
	else {
		cout << name << " has a new client in the office.\n";
		timeLeft = processTime;
		busy = true;
		activeCustomer = custIndex;
		return true;
	}
}

int Office::removeClient()
{
	if (!busy) {
		return -1;
	}
	else {
		cout << name << " has ended their client meeting.\n";
		busy = false;
		int temp = activeCustomer;
		activeCustomer = -1;
		return temp;
	}
}

bool Office::tickTime(int scale)
{
	if (!busy) {
		return false;
	}
	else {
		timeLeft = timeLeft - (1 * scale);
		return (timeLeft <= 0);
	}
}
