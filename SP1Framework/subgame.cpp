
#include "subgame.h"
using std::ifstream;
using std::ofstream;
std::string subdrawarray[4];
Directory Subfold(L"Submarine\\",L"*.txt");//Class

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

 void playsubcontrolsmechanics(Graphics* console)//
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

 void playgamestate()
 {

 }

void playsubgamemain(Graphics* console) 
{
	playsubcontrolsmechanics(console);
	console->draw(5,30,subdrawarray[1].c_str(),0x1A);
	console->draw(43,30,subdrawarray[1].c_str(),0x1A);
	console->draw(80,30,subdrawarray[1].c_str(),0x1A);



}

