#pragma once
class Player
{
private:
	static int strikes;
	static int savings;

	bool holdingProduct;

public:
	Player();
	~Player();

	static int getStrikes();
	static int getSavings();

	void receiveStrike(); //set strikes
	void receivePay(int pay); //set savings

	void payRent();
	void payFood();
	void payMedicine();

	void holdsProduct();
	bool isHoldingProduct(); //get holdingProduct
	void releaseProduct();

};

