#include "playerVL.h"

playerVL::playerVL(int r) {
	viewRange = r;
}

playerVL::~playerVL() {

}

void playerVL::updateVL(int x, int y) {
	for (int i = 0; (i < viewRange * 2 + 1); i++) {
		for (int j = 0; (j < viewRange * 2 + 1); i++) {
			updateMap((x - viewRange + i), (y - viewRange + j), '@');
		}
	}
}