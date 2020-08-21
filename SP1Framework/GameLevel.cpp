#include "GameLevel.h"

GameLevel::GameLevel() : filename(0)
{

}

GameLevel::GameLevel(string filepath)
{
	filename = filepath;
	
}

GameLevel::~GameLevel()
{
	filename = "";
}
