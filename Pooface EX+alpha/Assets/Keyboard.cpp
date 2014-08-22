/****************************************************************************************** 
 *	Chili DirectX Framework Version 11.12.17											  *	
 *	Keyboard.cpp																		  *
 *	Copyright 2011 PlanetChili.net														  *
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
#include "Keyboard.h"


KeyboardClient::KeyboardClient( const KeyboardServer& kServer )
	: server( kServer )
{}

bool KeyboardClient::UpIsPressed() const
{
	return server.upIsPressed;
}
bool KeyboardClient::DownIsPressed() const
{
	return server.downIsPressed;
}
bool KeyboardClient::LeftIsPressed() const
{
	return server.leftIsPressed;
}
bool KeyboardClient::RightIsPressed() const
{
	return server.rightIsPressed;
}
bool KeyboardClient::SpaceIsPressed() const
{
	return server.spaceIsPressed;
}
bool KeyboardClient::EnterIsPressed() const
{
	return server.enterIsPressed;
}



KeyboardServer::KeyboardServer()
:	upIsPressed( false ),
	downIsPressed( false ),
	leftIsPressed( false ),
	rightIsPressed( false ),
	spaceIsPressed( false ),
	enterIsPressed( false )
{}

void KeyboardServer::OnUpPressed()
{
	upIsPressed = true;
}
void KeyboardServer::OnDownPressed()
{
	downIsPressed = true;
}
void KeyboardServer::OnLeftPressed()
{
	leftIsPressed = true;
}
void KeyboardServer::OnRightPressed()
{
	rightIsPressed = true;
}
void KeyboardServer::OnSpacePressed()
{
	spaceIsPressed = true;
}
void KeyboardServer::OnEnterPressed()
{
	enterIsPressed = true;
}

void KeyboardServer::OnUpReleased()
{
	upIsPressed = false;
}
void KeyboardServer::OnDownReleased()
{
	downIsPressed = false;
}
void KeyboardServer::OnLeftReleased()
{
	leftIsPressed = false;
}
void KeyboardServer::OnRightReleased()
{
	rightIsPressed = false;
}
void KeyboardServer::OnSpaceReleased()
{
	spaceIsPressed = false;
}
void KeyboardServer::OnEnterReleased()
{
	enterIsPressed = false;
}