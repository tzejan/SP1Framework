#include "Box.h"
#include "Framework/console.h"
#include "game.h"

Box::Box() : itemtag{ ' ' }, amount{5}
{
}

Box::~Box()
{
}

int Box::getTag()
{
	return itemtag;
}

void Box::setTag(int itemtag)
{
	this->itemtag = itemtag;
}

int Box::getAmt()
{
	return amount;
}

void Box::renderBoxes(Console& Console) {
    Box* boxPtr[6] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
    for (int i = 0; i < 6; i++) {
        if (boxPtr[i] == nullptr) {
            boxPtr[i] = new Box;
        }

        COORD c;
        if (boxPtr[i] != nullptr) {

            switch (i) {
            case 0:
                c.X = 1;
                c.Y = 2;
                Console.writeToBuffer(c, (char)1, 0x55); //toilet paper purple
                break;
            case 1:
                c.X = 1;
                c.Y = 3;
                Console.writeToBuffer(c, (char)1, 0x111); //instant noodle dark blue
                break;
            case 2:
                c.X = 1;
                c.Y = 4;
                Console.writeToBuffer(c, (char)1, 0xBB); //canned food teal
                break;
            case 3:
                c.X = 1;
                c.Y = 5;
                Console.writeToBuffer(c, (char)1, 0xEE); //rice cream
                break;
            case 4:
                c.X = 1;
                c.Y = 6;
                Console.writeToBuffer(c, (char)1, 0xAA); //vegetable green
                break;
            case 5:
                c.X = 1;
                c.Y = 7;
                Console.writeToBuffer(c, (char)1, 0x99); //bandages blue
                break;


            }


        }
    }
}