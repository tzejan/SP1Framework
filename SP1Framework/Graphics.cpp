#include "Graphics.h"

Graphics::Graphics()
	:
hConsole(GetStdHandle( STD_OUTPUT_HANDLE )),
screenX(100),
screenY(50),
cursorsize(1),
cursorvisible(false),
title(L"Our awesome game")
{
	rect.Bottom = 0;
	rect.Left = 0;
	rect.Right = screenX - 1;
	rect.Top = screenY - 1;
	bufferSize.X = screenX;
	bufferSize.Y = screenY;
	cursorinfo.dwSize = cursorsize;
	cursorinfo.bVisible = cursorvisible;
	SetConsoleTitle(title);
	SetConsoleWindowInfo(hConsole,true,&rect);
	SetConsoleScreenBufferSize(hConsole, bufferSize);
	SetConsoleCursorInfo(hConsole,&cursorinfo);
	GetConsoleScreenBufferInfo(hConsole,&csbi);

	screenbuffer = new CHAR_INFO[screenX * screenY];
	clearbuffer();
}

Graphics::~Graphics()
{
	delete [] screenbuffer;
}

void Graphics::draw(const int x, const int y, const char c, const int color)
{
	screenbuffer[x + y * screenX].Char.AsciiChar = c;
	screenbuffer[x + y * screenX].Char.UnicodeChar = c;
	screenbuffer[x + y * screenX].Attributes = color;
}

void Graphics::draw(const int x, const int y, const char* string, const int color)
{
	int xoff = 0;
	int yoff = 0;
	for(int index = 0; string[index]; index++)
	{
		if(string[index] == '\n')
		{
			xoff = 0;
			yoff++;
			continue;
		}
		draw(x + xoff, y + yoff, string[index], color);
		xoff++;
		if(xoff == screenX)
		{
			xoff = 0;
			yoff++;
		}
	}
}

void Graphics::drawtoconsole()
{
	SMALL_RECT rect = {0,0,screenX - 1,screenY - 1};
	WriteConsoleOutput(hConsole,screenbuffer,csbi.dwSize,csbi.dwCursorPosition,&rect);
}

void Graphics::clearbuffer()
{
	for(int index = 0; index < (screenX * screenY); index++)
	{
		screenbuffer[index].Char.AsciiChar = ' ';
		screenbuffer[index].Attributes = 0x0000;
	}
}

void Graphics::updateconsole()
{
	drawtoconsole();
	clearbuffer();
}