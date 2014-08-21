#ifndef _TABLEFLIP_H
#define _TABLEFLIP_H

#include <iostream>
#include <iomanip>
#include "Graphics.h"
#include "game.h"
#include "Framework\console.h"
#include "Framework\timer.h"
#include <stdlib.h>

using std::cout;
using std::cin;
using std::endl;

gamestate updateTableFlip(Graphics* console);
void drawTableFlip(Graphics* TableFlip);
void playTableFlip();

#endif