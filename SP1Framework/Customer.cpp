#include "Customer.h"
#include <stdlib.h>

Customer::Customer()
{
	itemToBuy = rand() % 6 + 1; // 1 = rice, 2 = toilet paper, 3 = canned food, 4 = instant noodles, 5 = vegetables, 6 = bandages
	quantity = rand() % 10 + 1;
	pos.setXPosition(0); //change when we spawn them
	pos.setYPosition(0); // ^
}

Customer::~Customer()
{
}

void Customer::moveToShelfContainingItem(int itemToBuy)
{
	switch (itemToBuy)
	{
	case 1:
		pos.setXPosition(0); //change when we spawn them
		pos.setYPosition(0); // ^
	case 2:
		pos.setXPosition(0); //change when we spawn them
		pos.setYPosition(0); // ^
	case 3:
		pos.setXPosition(0); //change when we spawn them
		pos.setYPosition(0); // ^
	case 4:
		pos.setXPosition(0); //change when we spawn them
		pos.setYPosition(0); // ^
	case 5:
		pos.setXPosition(0); //change when we spawn them
		pos.setYPosition(0); // ^
	case 6:
		pos.setXPosition(0); //change when we spawn them
		pos.setYPosition(0); // ^
	default:
		pos.setXPosition(0); //change when we spawn them
		pos.setYPosition(0); // ^
	}
}

bool Customer::entranceWaiting(void)
{
	//after 10 seconds trigger this function to set it to true
	return true;
}

bool Customer::shelfWaiting(void)
{
	//after 20 seconds trigger this function to set it to true
	return true;
}
