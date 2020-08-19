#include "map.h"

map::map() {

}

map::~map() {

}

void map::updateMap(int x, int y, char e) {
	mapArray[y][x] = e;
}

char map::getMapVar(int x, int y) {
	return mapArray[y][x];
}