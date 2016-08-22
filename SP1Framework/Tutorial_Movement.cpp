#include "Tutorial_Movement.h"

extern bool  g_abKeyPressed[K_COUNT];


void Movement_Tut()
{

	bool bSomethingHappened = false;
	if (g_dBounceTime > g_dElapsedTime)
		return;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
	if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
	{
		if (map[(g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] != (char)219)
		{
			if (map[(g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] != (char)186) //'D'
			{
				if ((map[(g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)254) && (map[(g_sChar.m_cLocation.Y - 2) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] != (char)219))
				{
					if (map[(g_sChar.m_cLocation.Y - 2) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)186)
					{
						g_sChar.m_cLocation.Y = g_sChar.m_cLocation.Y;
						bSomethingHappened = true;
					}
					else
					{
						map[(g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] = ' ';
						map[(g_sChar.m_cLocation.Y - 2) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] = (char)254;
						g_sChar.m_cLocation.Y--;
						bSomethingHappened = true;
					}
				}
				else if ((map[(g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)254) && (map[(g_sChar.m_cLocation.Y - 2) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)219))
				{
					g_sChar.m_cLocation.Y = g_sChar.m_cLocation.Y;
					bSomethingHappened = true;
				}
				else if (map[(g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)233) // checking for portal
				{
					returnNextPosition((g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight), (g_sChar.m_cLocation.X) - (90 - mapSizeWidth));
					bSomethingHappened = true;
				}
				else
				{
					g_sChar.m_cLocation.Y--;
					bSomethingHappened = true;
				}
			}

			//Beep(1440, 30);
			//g_sChar.m_cLocation.Y--;
			//bSomethingHappened = true;
		}

	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth)] != (char)219)
		{
			if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth)] != (char)186)
			{
				if ((map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth)] == (char)254) && (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 2) - (90 - mapSizeWidth)] != (char)219))
				{
					if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 2) - (90 - mapSizeWidth)] == (char)186)
					{
						g_sChar.m_cLocation.X = g_sChar.m_cLocation.X;
						bSomethingHappened = true;
					}
					else
					{
						map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth)] = ' ';
						map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 2) - (90 - mapSizeWidth)] = (char)254;
						g_sChar.m_cLocation.X--;
						bSomethingHappened = true;
					}

				}
				else if ((map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth)] == (char)254) && (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 2) - (90 - mapSizeWidth)] == (char)219))
				{
					g_sChar.m_cLocation.X = g_sChar.m_cLocation.X;
					bSomethingHappened = true;
				}
				else if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth)] == (char)233) // checking for portal)
				{
					returnNextPosition((g_sChar.m_cLocation.Y) - (25 - mapSizeHeight), (g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth));
					bSomethingHappened = true;
				}
				else
				{
					g_sChar.m_cLocation.X--;
					bSomethingHappened = true;
				}
			}

			//Beep(1440, 30);
			//g_sChar.m_cLocation.X--;
			//bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		if (map[(g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] != (char)219)
		{
			if (map[(g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] != (char)186)
			{
				if ((map[(g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)254) && (map[(g_sChar.m_cLocation.Y + 2) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] != (char)219))
				{
					if (map[(g_sChar.m_cLocation.Y + 2) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)186)
					{
						g_sChar.m_cLocation.Y = g_sChar.m_cLocation.Y;
						bSomethingHappened = true;
					}
					else
					{
						map[(g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] = ' ';
						map[(g_sChar.m_cLocation.Y + 2) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] = (char)254;
						g_sChar.m_cLocation.Y++;
						bSomethingHappened = true;
					}

				}
				else if ((map[(g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)254) && (map[(g_sChar.m_cLocation.Y + 2) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)219))
				{
					g_sChar.m_cLocation.Y = g_sChar.m_cLocation.Y;
					bSomethingHappened = true;
				}
				else if (map[(g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)233) // checking for portal
				{
					returnNextPosition((g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight), (g_sChar.m_cLocation.X) - (90 - mapSizeWidth));
					bSomethingHappened = true;
				}
				else
				{
					g_sChar.m_cLocation.Y++;
					bSomethingHappened = true;
				}
			}

			//Beep(1440, 30);
			//g_sChar.m_cLocation.Y++;
			//bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth)] != (char)219)
		{
			if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth)] != (char)186)
			{
				if ((map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth)] == (char)254) && (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 2) - (90 - mapSizeWidth)] != (char)219)) //if there is a block and nothing is blocking it
				{
					if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 2) - (90 - mapSizeWidth)] == (char)186)
					{
						g_sChar.m_cLocation.X = g_sChar.m_cLocation.X;
						bSomethingHappened = true;
					}
					else
					{
						map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth)] = ' ';
						map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 2) - (90 - mapSizeWidth)] = (char)254;
						g_sChar.m_cLocation.X++;
						bSomethingHappened = true;
					}
				}
				else if ((map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth)] == (char)254) && (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 2) - (90 - mapSizeWidth)] == (char)219)) //if something is blocking the block 
				{
					g_sChar.m_cLocation.X = g_sChar.m_cLocation.X;
					bSomethingHappened = true;
				}
				else if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth)] == (char)233) // checking for portal)
				{
					returnNextPosition((g_sChar.m_cLocation.Y) - (25 - mapSizeHeight), (g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth));
					bSomethingHappened = true;
				}
				else
				{
					g_sChar.m_cLocation.X++;
					bSomethingHappened = true;
				}
			}
			//Beep(1440, 30);
			//g_sChar.m_cLocation.X++;
			//bSomethingHappened = true;
		}
	}
	if (g_abKeyPressed[K_SPACE])
	{
		if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth)] == (char)48) //right
		{
			map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth)] = (char)49;
		}
		else if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth)] == (char)49) //right
		{
			map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth)] = (char)48;
		}
		else if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth)] == (char)48) //left
		{
			map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth)] = (char)49;
		}
		else if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth)] == (char)49) //left
		{
			map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth)] = (char)48;
		}
		else if (map[(g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)48) //down
		{
			map[(g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] = (char)49;
		}
		else if (map[(g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)49) //down
		{
			map[(g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] = (char)48;
		}
		else if (map[(g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)48) //up
		{
			map[(g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] = (char)49;
		}
		else if (map[(g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)49) //up
		{
			map[(g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] = (char)48;
		}
		else if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)48) //center
		{
			map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] = (char)49;
		}
		else if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] == (char)49) //center
		{
			map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] = (char)48;
		}

		bSomethingHappened = true;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
	}
}

void returnPosition(int currentPositionY, int currentPositionX)
{
	for (int portalcheck = 0; portalcheck < 26; portalcheck++)
	{
		if (portalPos[portalcheck].Portal_1_X == currentPositionY && portalPos[portalcheck].Portal_1_Y == currentPositionX)
		{
			g_sChar.m_cLocation.X = (portalPos[portalcheck].Portal_2_Y) + (90 - mapSizeWidth);
			g_sChar.m_cLocation.Y = (portalPos[portalcheck].Portal_2_X) + (25 - mapSizeHeight);
		}
		else if (portalPos[portalcheck].Portal_2_X == currentPositionY && portalPos[portalcheck].Portal_2_Y == currentPositionX)
		{
			g_sChar.m_cLocation.X = (portalPos[portalcheck].Portal_1_Y) + (90 - mapSizeWidth);
			g_sChar.m_cLocation.Y = (portalPos[portalcheck].Portal_1_X) + (25 - mapSizeHeight);
		}
	}
}