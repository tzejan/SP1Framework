#include "MainMenu.h"
std::string Title;
std::string Main;
int choice = 0;
int check = 0;

void ini()
{
	std::ifstream readTitle;
	readTitle.open ("ButtonMashMaster.txt"); // associate & open files
	while (!readTitle.eof()) 
	{
		Title += readTitle.get();
	}
	readTitle.close ();

	std::ifstream readMain;
	readMain.open ("MainMenu.txt"); // associate & open files
	while (!readMain.eof()) 
	{
		Main += readMain.get();
	}
	readMain.close();
}

gamestate Intro(Graphics& console)
{
		console.draw(16,3,Title.c_str(),0x3E);
		console.draw(28,20,"Press Enter to Begin!" ,0x3E);
		if(isKeyPressed(VK_RETURN))
		{
			return MAIN_MENU;
		}
}
 
gamestate MainMenu(Graphics& console)
{
		console.draw(15,3,Main.c_str(),0x19);
		console.draw(30,12,"Start game",0x19);
		console.draw(30,13,"Options",0x19);
		console.draw(30,14,"Exit game",0x19);
		if(choice == 0 && isKeyPressed(VK_DOWN))
		{
			check += 1;
			choice = check;
		}
		if(choice == 1 && isKeyPressed(VK_DOWN))
		{
			check += 1;
			choice = check;
		}
		if( choice == 1 && isKeyPressed(VK_UP))
		{
			check -= 1;
			choice = check;
		}
		if( choice == 2 && isKeyPressed(VK_UP))
		{
			check -= 1;
			choice = check;
		}
		if(choice == 0)
		{
			console.draw(27,12,"-->",0x19);
		}
		if(choice == 1)
		{
			console.draw(27,13,"-->",0x19);
		}
		if(choice == 2)
		{
			console.draw(27,14,"-->",0x19);
		}
		if(isKeyPressed(VK_RETURN))
		{
			if (choice == 0)
			{
				return GAME_SELECT;
			}
			if (choice == 1)
			{
				return OPTIONS;
			}
			if (choice == 2)
			{
				return QUIT_GAME;
			}
		}
		return MAIN_MENU;
}