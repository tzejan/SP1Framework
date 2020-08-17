#include "Position.h"

//Constructor fn
Position::Position()
{

	x = 0;
	y = 0;

	// initialise position coordinates
	//setPosition(0, 0);
	return;
}

//Destructor
Position::~Position()
{
}

void Position::setXPosition(int newX) {
	*x = newX;
};

void Position::setYPosition(int newY) {
	*y = newY;
};

int Position::getXPosition() {
	return *x;
}

int Position::getYPosition() {
	return *y;
}

bool Position::isCoordinatesAlreadyUsed(std::vector<Position> currentList) {
	int entries = currentList.size();
	for (int i = 0; i < entries; i++) {
		if (this->getXPosition() == currentList[i].getXPosition()) {
			if (this->getYPosition() == currentList[i].getYPosition()) {
				return true;
			}
		}
	}
	return false;
}

void Position::generateRandomMapCoordinates() {
	/* initialize random seed: */

	int newX, newY;


	newX = rand() % 79;
	newY = rand() % 24;
	setXPosition(newX);
	setYPosition(newY);
	return;
}