#include <bits/stdc++.h>
#include "Grid.h"

int main() {
	Grid test_grid;
	test_grid.set_room_pos("12");
	test_grid.import_grid("test.txt");
	test_grid.set_door_config();
	test_grid.update_door_pos();
	for (int i = 0; i < 15; i++) {
		test_grid.print_row(i);
		std::cout << "\n";
	}
	return 0;
}