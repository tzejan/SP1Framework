#include "maze_05.h"

maze_05::maze_05() {
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 50; j++) {
			updateMap(j, i, mazeArray[i][j]);
		}
	}
}

maze_05::~maze_05() {

}
