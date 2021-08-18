#include "Position.h"

Position::Position() {
	x = 0, y = 0;
}
Position::~Position() {

}
Position::Position(int a, int b) {
	x = a, y = b;
}

int Position::get_x(void) {
	return x;
}
void Position::set_x(int a) {
	x = a;
}

int Position::get_y(void) {
	return y;
}
void Position::set_y(int a) {
	y = a;
}