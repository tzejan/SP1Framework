#pragma once
#include "Entity.h"
#include <string>
class Relics : public Entity
{
private:
	int RelicNo;
public:
	Relics(int, int, int);
	~Relics();
	char GetSymbol(void);
	std::string RelicDialogue(void);
};