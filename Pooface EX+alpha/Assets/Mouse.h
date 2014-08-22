/****************************************************************************************** 
 *	Chili DirectX Framework Version 12.04.24											  *	
 *	Mouse.h																			  *
 *	Copyright 2012 PlanetChili.net														  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

class MouseServer;

class MouseClient
{
public:
	MouseClient( const MouseServer& server );
	int GetMouseX() const;
	int GetMouseY() const;
	bool LeftIsPressed() const;
	bool RightIsPressed() const;
	bool IsInWindow() const;
private:
	const MouseServer& server;
};

class MouseServer
{
	friend MouseClient;
public:
	MouseServer();
	void OnMouseMove( int x,int y );
	void OnMouseLeave();
	void OnMouseEnter();
	void OnLeftPressed();
	void OnLeftReleased();
	void OnRightPressed();
	void OnRightReleased();
	bool IsInWindow() const;
private:
	int x;
	int y;
	bool leftIsPressed;
	bool rightIsPressed;
	bool isInWindow;
};