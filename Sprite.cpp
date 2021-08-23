#include "Sprite.h"

std::string PlayerSprite(int Line)
{
	std::string text;
	if (Line==1)
	{
		text = "32,40,111,45,111,41,32";
	}
	else if (Line == 2)
	{
		text = "60,32,91,58,93,32,47";
	}
	else if(Line == 3)
	{
		text = "32,95,47,34,92,95,32";
	}
	return text;
}
std::string LockSprite(int Line)
{
	std::string text;
	if (Line == 1)
	{
		text = "32,32,32,95,32,32,32";
	}
	else if (Line == 2)
	{
		text = "32,32,47,32,92,32,32";
	}
	else if (Line == 3)
	{
		text = "32,40,123,59,93,41,30";
	}
	return text;
}
std::string KeySprite(int Line)
{
	std::string text;
	if (Line == 1)
	{
		text = "32,32,32,32,32,32,32";
	}
	else if (Line == 2)
	{
		text = "32,44,45,44,45,79,32";
	}
	else if (Line == 3)
	{
		text = "32,32,32,32,32,32,32";
	}
	return text;
}
std::string PitfallSprite(int Line)
{
	std::string text;
	if (Line == 1)
	{
		text = "32,32,95,95,95,32,32";
	}
	else if (Line == 2)
	{
		text = "32,124,32,32,32,124,32";
	}
	else if (Line == 3)
	{
		text = "32,124,95,95,95,124,32";
	}
	return text;
}
std::string RelicsSprite(int Line)
{
	std::string text;
	if (Line == 1)
	{
		text = "63,63,63,63,63,63,63";
	}
	else if (Line == 2)
	{
		text = "63,63,63,63,63,63,63";
	}
	else if (Line == 3)
	{
		text = "63,63,63,63,63,63,63";
	}
	return text;
}
std::string RockSprite(int Line)
{
	std::string text;
	if (Line == 1)
	{
		text = "32,32,32,32,32,32,32";
	}
	else if (Line == 2)
	{
		text = "32,32,95,168,126,44,32";
	}
	else if (Line == 3)
	{
		text = "32,47,95,95,95,124,32";
	}
	return text;
}
std::string SkeletonSprite(int Line)
{
	std::string text;
	if (Line == 1)
	{
		text = "212,40,96,94,96,41,190";
	}
	else if (Line == 2)
	{
		text = "32,92,61,124,61,79,32";
	}
	else if (Line == 3)
	{
		text = "32,95,45,34,45,95,32";
	}
	return text;
}
std::string ActiveSpikesSprite(int Line)
{
	std::string text = "";
	if (Line == 1)
	{
		text = "32,32,32,32,32,32,32";
	}
	else if (Line == 2)
	{
		text = "32,32,32,32,32,32,32";
	}
	else if (Line == 3)
	{
		text = "32,47,92,47,92,47,92";
	}
	return text;
}
std::string UnactiveSpikesSprite(int Line)
{
	std::string text = "";
	if (Line == 1)
	{
		text = "32,32,32,32,32,32,32";
	}
	else if (Line == 2)
	{
		text = "32,32,32,32,32,32,32";
	}
	else if (Line == 3)
	{
		text = "32,95,95,95,95,95,95";
	}
	return text;
}
std::string WallSprite(int Line)
{
	std::string text;
	if (Line == 1)
	{
		text = "32,124,35,35,35,124,32";
	}
	else if (Line == 2)
	{
		text = "32,124,35,35,35,124,32";
	}
	else if (Line == 3)
	{
		text = "32,124,35,35,35,124,32";
	}
	return text;
}


std::string DetectSprite(char ch,int Line)
{
	if (ch == 'P')
	{
		return PlayerSprite(Line);
	}
	else if (ch == 'R')
	{
		return RockSprite(Line);
	}
	else if (ch == 'T')
	{
		return RelicsSprite(Line);
	}
	else if (ch == 'i')
	{
		return UnactiveSpikesSprite(Line);
	}
	else if (ch == 'I')
	{
		return ActiveSpikesSprite(Line);
	}
	else if (ch == 'W')
	{
		return WallSprite(Line);
	}
	else if (ch == 'K')
	{
		return KeySprite(Line);
	}
	else if (ch == 'L')
	{
		return LockSprite(Line);
	}
	else if (ch == '0')
	{
		return PitfallSprite(Line);
	}
	else if (ch == 'S')
	{
		return SkeletonSprite(Line);
	}
}
