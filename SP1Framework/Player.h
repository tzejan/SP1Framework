#pragma once
#include "Entity.h"

class Player :
	public Entity
{
private:
	static int strikes;
	static int savings;

	bool holdingProduct;

public:
	Player();
	~Player();

	static int getStrikes(); // return strikes
	static int getSavings(); // return savings

	void receiveStrike(); //set strikes, strikes++
	void receivePay(int pay); //set savings, increase savings

	void payRent(); // rent cost = 200 
	void payFood(); // food cost = 30
	void payMedicine(); // medicine cost = 300

	void holdsProduct(); //set holdingProduct = true
	bool isHoldingProduct(); //get holdingProduct
	void releaseProduct(); //set holdingProduct = false

};

