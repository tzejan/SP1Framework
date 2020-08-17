#include "Player.h"

int Player::strikes = 0;

int Player::savings = 0;

Player::Player() {
	holdingProduct = false;
}

Player::~Player() {

}

int Player::getStrikes() {
	return strikes;
}

int Player::getSavings() {
	return savings;
}

void Player::receiveStrike() {
	strikes++;
}

void Player::receivePay(int pay) {
	savings = savings + pay;
}

void Player::payRent() {
	savings = savings - 200;
}

void Player::payFood() {
	savings = savings - 30;
}

void Player::payMedicine() {
	savings = savings - 300;
}

void Player::holdsProduct() {
	holdingProduct = true;
}

bool Player::isHoldingProduct() {
	return holdingProduct;
}

void Player::releaseProduct() {
	holdingProduct = false;
}
