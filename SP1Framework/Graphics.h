#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <windows.h>

class Graphics
{
private:
	//functions
	void clearbuffer();
	void drawtoconsole();
	//variables
	const HANDLE hConsole;
	const int screenX;
	const int screenY;
	const wchar_t* title;
	const int cursorsize;
	const bool cursorvisible;
	SMALL_RECT rect;
	COORD bufferSize;
	CONSOLE_CURSOR_INFO cursorinfo;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CHAR_INFO* screenbuffer;
public:
	Graphics();
	~Graphics();
	void draw( const int x, const int y, const char c, const int color);
	void draw( const int x, const int y, const char* string, const int color);
	void updateconsole();
};

#endif