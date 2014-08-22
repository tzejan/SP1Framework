//testtest
#include "subgame.h"
using std::ifstream;
using std::ofstream;
std::string subdrawarray[30];
Directory Subfold(L"Submarine\\",L"*.txt");//Class
//Objective of this game is to shoot the monsters as much as you can as it appears
int framecounter = 0;

int higherscore = 0;

int enemiesapp[15]={};//dictates when the enemy with appear.


 void initialisesubdrawings()//the fstream thingys
 {
	 ifstream drawdata;//get input/stuff from file
	 for(int i = 0; i < Subfold.size();++i )
	 {
		 drawdata.open(Subfold[i]);
		 while(!drawdata.eof())
		 {
			 subdrawarray[i].push_back(drawdata.get());
		 }
		 drawdata.close();
		 subdrawarray[i].pop_back();
	 }
 }

 void playsubcontrolsmechanics(Graphics* console)//only starts after 3 sec
{
		framecounter++;
	if(framecounter == 1)
	 {
		 console->draw(42,10,subdrawarray[4].c_str(),0x1A);
	 }
	 if(framecounter == 30)
	 {
		 console->draw(42,10,subdrawarray[3].c_str(),0x1A);
	 }
	 if(framecounter == 60)
	 {
		 console->draw(42,10,subdrawarray[2].c_str(),0x1A);
	 }
	 if(framecounter == 90)
	 {
		 console->draw(42,10,subdrawarray[5].c_str(),0x1A);
	 }
	if(framecounter > 90)
	{
		if(isKeyPressed(VK_LEFT))
		{
		console->draw(4,24,subdrawarray[0].c_str(),0x1A);
		}
		if(isKeyPressed(VK_UP))
		{
		console->draw(42,24,subdrawarray[0].c_str(),0x1A);
		}
	
		if(isKeyPressed(VK_RIGHT))
		{
		console->draw(79,24,subdrawarray[0].c_str(),0x1A);
		}
	}
}

 void playgamestate(Graphics* console)
 {
	  if(framecounter >= 150 && framecounter <= 230)
	  {
		  console->draw(5,4,subdrawarray[7].c_str(),0x1A);
		  if(isKeyPressed(VK_LEFT) &&(framecounter >= 150 && framecounter <= 230))
		  {
			  console->draw(5,4,subdrawarray[6].c_str(),0xB2);
			  higherscore++;
		  }
	  }
	  if(framecounter >= 300 && framecounter <=360)
	  {
		  console->draw(80,4,subdrawarray[7].c_str(),0x1A);
		  if(isKeyPressed(VK_RIGHT) && (framecounter >= 300 && framecounter <=360))
		  {
			  console->draw(80,4,subdrawarray[6].c_str(),0xB2);
			  higherscore++;
		  }
	  }
	  if(framecounter >= 370 && framecounter <= 420)
	  {
		  console->draw(43,4,subdrawarray[7].c_str(),0x1A);
		  if(isKeyPressed(VK_UP) && (framecounter >= 370 && framecounter <=420))
		  {
			  console->draw(43,4,subdrawarray[6].c_str(),0xB2);
			  higherscore++;
		  }
	  }
	  if(framecounter >= 410 && framecounter <= 450)
	  {
		  console->draw(80,4,subdrawarray[7].c_str(),0x1A);
		  if(isKeyPressed(VK_RIGHT) && (framecounter >= 410 && framecounter <=450))
		  {
			  console->draw(80,4,subdrawarray[6].c_str(),0xB2);
			  higherscore++;
		  }
	  }
 }

void playsubgamemain(Graphics* console) 
{
	playsubcontrolsmechanics(console);
	playgamestate(console);
	console->draw(5,30,subdrawarray[1].c_str(),0x1A);
	console->draw(43,30,subdrawarray[1].c_str(),0x1A);
	console->draw(80,30,subdrawarray[1].c_str(),0x1A);
}

