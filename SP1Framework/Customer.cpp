#include "Customer.h"
#include "Position.h"
#include <stdlib.h>

Customer::Customer()//sets which item they want to buy and how much to do so
{
	itemToBuy = rand() % 6 + 1; // 1 = rice, 2 = toilet paper, 3 = canned food, 4 = instant noodles, 5 = vegetables, 6 = bandages
	quantity = rand() % 10 + 1;

	pos.setX(40); //change when we spawn them
	pos.setY(13); // ^
}

//Customer::Customer(Map map)
//{
//	int x, y;
//	bool spawnComplete = false;
//	while (spawnComplete == false)
//	{
//		
//	}
//}

Customer::~Customer()
{

}

void Customer::moveToShelfContainingItem(int itemToBuy)//brings them to the shelf depending on what item they are buying
{
	switch (itemToBuy)
	{
	case 1:
		pos.setX(0); //change when we spawn them
		pos.setY(0); // ^
		break;
	case 2:
		pos.setX(0); //change when we spawn them
		pos.setY(0); // ^
		break;
	case 3:
		pos.setX(0); //change when we spawn them
		pos.setY(0); // ^
		break;
	case 4:
		pos.setX(0); //change when we spawn them
		pos.setY(0); // ^
		break;
	case 5:
		pos.setX(0); //change when we spawn them
		pos.setY(0); // ^
		break;
	case 6:
		pos.setX(0); //change when we spawn them
		pos.setY(0); // ^
		break;
	default:
		pos.setX(0); //change when we spawn them
		pos.setY(0); // ^
		break;
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
