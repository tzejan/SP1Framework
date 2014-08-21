#include "ToiletRoll.h"

toiletroll::toiletroll()
{
	int CurrentFrame = 0;
	bool GameStarts = false;
	bool gameends = false;
	int y = 0;
	int rx = 60;
	int lx = 25;
	char score = '0';
	read();
}

gamestate toiletroll::update(Graphics& console)
{
	if(isKeyPressed(VK_ESCAPE))
	{
		return MAIN_MENU;
	}
	draw(console);
	play();
	
	if(CurrentFrame >= 728 && isKeyPressed(VK_RETURN))
	{
		return MAIN_MENU;
	}
	else
	{
	return TOILET_ROLL;
	}
}

void toiletroll::play()
{
	if (CurrentFrame >= 370)
	{
		if(isKeyPressed(VK_RIGHT))
		{
			rx = 55;
		}

		if(isKeyPressed(VK_LEFT))
		{
			lx = 30;
		}
	}

	if(CurrentFrame >= 370 && CurrentFrame <= 619)
	{
		if(rx == 55 && (y == 38) && lx == 30)
		{
			y = 0;
			CurrentFrame+=12;
			score+=1;
		}
	}

	if(CurrentFrame >= 620 && CurrentFrame <= 694)
	{
		if(rx == 55 && (y == 38) && lx == 30)
		{
			y = 0;
			CurrentFrame+=6;
			score+=1;
		}
	}

	if(CurrentFrame >= 695 && CurrentFrame <= 727)
	{
		if(rx == 55 && (y >= 35 && y <= 40) && lx == 30)
		{
			y = 0;
			CurrentFrame+=3;
			score+=1;
		}
	}
	CurrentFrame ++;
}

void toiletroll::read()
{
	tr.open("ascii/toiletroll.txt");
	while(!tr.eof())
	{
		trs.push_back(tr.get());
	}
	tr.close();
	trs.pop_back();

	rh.open("ascii/righthand.txt");
	while(!rh.eof())
	{
		rhs.push_back(rh.get());
	}
	rh.close();
	rhs.pop_back();

	lh.open("ascii/lefthand.txt");
	while(!lh.eof())
	{
		lhs.push_back(lh.get());
	}
	lh.close();
	lhs.pop_back();
}

void toiletroll::draw(Graphics& console)
{
	

	if(CurrentFrame >= 0 && CurrentFrame <= 60)
	{
		console.draw(45,20,"TOILET ROLL", 0x0F);
	}
	if(CurrentFrame >= 60 && CurrentFrame <= 230)
	{
		console.draw(45,20,"How to play", 0x0F);
		console.draw(38,22,"When the toiletroll falls\n  press the < and > keys\n     at the same time\n       to catch it", 0x0F);
	}

	if(CurrentFrame >= 230 && CurrentFrame <= 260)
	{	
		console.draw(47,20,"Ready?", 0x0F);
		console.draw(43,0, trs.c_str(), 0x0F);
		console.draw(60,40, rhs.c_str(), 0x0F);
		console.draw(25,40, lhs.c_str(), 0x0F);
	}

	if(CurrentFrame >= 260 && CurrentFrame <= 290)
	{	
		console.draw(50,20,"3", 0x0F);
		console.draw(43,0, trs.c_str(), 0x0F);
		console.draw(60,40, rhs.c_str(), 0x0F);
		console.draw(25,40, lhs.c_str(), 0x0F);
	}

	if(CurrentFrame >= 290 && CurrentFrame <= 320)
	{	
		console.draw(50,20,"2", 0x0F);
		console.draw(43,0, trs.c_str(), 0x0F);
		console.draw(60,40, rhs.c_str(), 0x0F);
		console.draw(25,40, lhs.c_str(), 0x0F);
	}

	if(CurrentFrame >= 320 && CurrentFrame <= 350)
	{	
		console.draw(50,20,"1", 0x0F);
		console.draw(43,0, trs.c_str(), 0x0F);
		console.draw(60,40, rhs.c_str(), 0x0F);
		console.draw(25,40, lhs.c_str(), 0x0F);
	}

	if(CurrentFrame >= 350 && CurrentFrame <= 370)
	{	
		console.draw(49,20,"GO!", 0x0F);
		console.draw(43,0, trs.c_str(), 0x0F);
		console.draw(60,40, rhs.c_str(), 0x0F);
		console.draw(25,40, lhs.c_str(), 0x0F);
	}

	if(CurrentFrame >= 370 && CurrentFrame <= 728)
	{
		console.draw(50,20, score, 0x0F);
	}

	if(CurrentFrame >= 370 && CurrentFrame <= 619)
	{	
		console.draw(43,y, trs.c_str(), 0x0F);
		console.draw(rx,40, rhs.c_str(), 0x0F);
		console.draw(lx,40, lhs.c_str(), 0x0F);
		y+=1;
		if(y == 50)
		{
			y = 0;
		}
	}

	if(CurrentFrame >= 620 && CurrentFrame <= 694)
	{	
		console.draw(43,y, trs.c_str(), 0x0F);
		console.draw(rx,40, rhs.c_str(), 0x0F);
		console.draw(lx,40, lhs.c_str(), 0x0F);
		y+=2;
		if(y == 50)
		{
			y = 0;
		}
	}

	if(CurrentFrame >= 695 && CurrentFrame <= 727)
	{	
		console.draw(43,y, trs.c_str(), 0x0F);
		console.draw(rx,40, rhs.c_str(), 0x0F);
		console.draw(lx,40, lhs.c_str(), 0x0F);
		y+=3;
		if(y == 51)
		{
			y = 0;
		}
	}

	if(CurrentFrame >= 728)
	{
		console.draw(41,20, "You have scored:", 0x0F);
		console.draw(59,20, score, 0x0F);
		console.draw(37,22, "Press Enter to continune...", 0x0F);
	}
	rx = 60;
	lx = 25;
}