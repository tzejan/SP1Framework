#include "Relics.h"
#include <iostream>


Relics::Relics(int x, int y,int RelicNumber)
{
	this->SetEntityPosition(x, y);
	this->RelicNo = RelicNumber;

}
Relics::~Relics()
{

}

std::string Relics::RelicDialogue(void)
{
	int RelicNum = this->RelicNo;
	std::string TextOutput = "";
	if (RelicNum == 1)
	{
		TextOutput += "Raiden found the Golden Toilet Paper!\n";
		TextOutput += "He hears a choir singing in the background.\n";
	}

	else if (RelicNum == 2)
	{
		TextOutput += "Raiden found the Aegis Shield!\n";
		TextOutput += "Lightning Rumbles and Snake Hisses can be heard echoing...\n";
	}

	else if (RelicNum == 3)
	{
		TextOutput += "Raiden found an Unknown Spine!\n";
		TextOutput += "He hears a wispy voice shout, 'Ouch, my back!'\n";
	}

	else if (RelicNum == 4)
	{
		TextOutput += "Raiden found the Holy Grail!\n";
		TextOutput += "A Paladin Ghost shows up out of nowhere!\n";
	}

	else if (RelicNum == 5)
	{
		TextOutput += "Raiden found the Holy Spear, Longinus!\n";
		TextOutput += "Jesus offers him alcohol...\n";
	}

	else if (RelicNum == 6)
	{
		TextOutput += "Raiden found the KEY to Davyy Jone's Locker!\n";
		TextOutput += "The room begins to flood with water!\n";
	}

	else if (RelicNum == 7)
	{
		TextOutput += "Raiden found an Indiana Jones mini figurine!\n";
		TextOutput += "Someone whipped him from behind, when he turns around, there's no one there...\n";
	}
	else if (RelicNum == 8)
	{
		TextOutput += "Raiden found The Fire Dragon, Johnathan\n!";
		TextOutput += "He's just sitting there...\n";
	}
	else if (RelicNum == 9)
	{
		TextOutput += "Raiden found the Holy Sword, Excalibur!\n";
		TextOutput += "He can't pull it out of the stone, so he brings the stone with him...\n";
	}
	else if (RelicNum == 10)
	{
		TextOutput += "Raiden found a Small Monkey Statue!\n";
		TextOutput += "It turns out to be cursed!\n";
		TextOutput += "A Demon Monkey appears...\n";

	}
	return TextOutput;
}

char Relics::GetSymbol(void)
{
	return 'T';
}