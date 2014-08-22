/****************************************************************************************** 
 *	Chili DirectX Framework Version 11.12.17											  *	
 *	Game.cpp																			  *
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
#include "Game.h"

Game::Game( HWND hWnd,const KeyboardServer& kServer,const MouseServer& mServer )
:	gfx( hWnd ),
	kbd( kServer ),
	audio( hWnd ),
	mouse( mServer ),
	board(BOARDFILE)
{
	srand( (unsigned int)time( NULL ) );
	fart = audio.CreateSound( "farty.wav" );
	ting = audio.CreateSound( "tinkle.wav" );
	ResetGame();
}

Game::~Game()
{
}

void Game::Go()
{
	if( kbd.UpIsPressed() )
	{
		LoadGame();
	}
	else if( !gameIsOver )
	{
		if( kbd.DownIsPressed() )
		{
			SaveGame();
		}
		UpdateFace();
		UpdatePoo();
		UpdateCamera();
	}
	else
	{
		if( kbd.EnterIsPressed() )
		{
			ResetGame();
		}
	}

	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::DrawFaceClipped( int x,int y )
{
	gfx.PutPixelClipped( 7 + x,0 + y,0,0,0 );
	gfx.PutPixelClipped( 8 + x,0 + y,0,0,0 );
	gfx.PutPixelClipped( 9 + x,0 + y,0,0,0 );
	gfx.PutPixelClipped( 10 + x,0 + y,0,0,0 );
	gfx.PutPixelClipped( 11 + x,0 + y,0,0,0 );
	gfx.PutPixelClipped( 12 + x,0 + y,0,0,0 );
	gfx.PutPixelClipped( 5 + x,1 + y,0,0,0 );
	gfx.PutPixelClipped( 6 + x,1 + y,0,0,0 );
	gfx.PutPixelClipped( 7 + x,1 + y,254,221,88 );
	gfx.PutPixelClipped( 8 + x,1 + y,254,221,88 );
	gfx.PutPixelClipped( 9 + x,1 + y,254,221,88 );
	gfx.PutPixelClipped( 10 + x,1 + y,254,221,88 );
	gfx.PutPixelClipped( 11 + x,1 + y,254,221,88 );
	gfx.PutPixelClipped( 12 + x,1 + y,254,221,88 );
	gfx.PutPixelClipped( 13 + x,1 + y,0,0,0 );
	gfx.PutPixelClipped( 14 + x,1 + y,0,0,0 );
	gfx.PutPixelClipped( 3 + x,2 + y,0,0,0 );
	gfx.PutPixelClipped( 4 + x,2 + y,0,0,0 );
	gfx.PutPixelClipped( 5 + x,2 + y,254,221,88 );
	gfx.PutPixelClipped( 6 + x,2 + y,254,221,88 );
	gfx.PutPixelClipped( 7 + x,2 + y,254,221,88 );
	gfx.PutPixelClipped( 8 + x,2 + y,254,221,88 );
	gfx.PutPixelClipped( 9 + x,2 + y,254,221,88 );
	gfx.PutPixelClipped( 10 + x,2 + y,254,221,88 );
	gfx.PutPixelClipped( 11 + x,2 + y,254,221,88 );
	gfx.PutPixelClipped( 12 + x,2 + y,254,221,88 );
	gfx.PutPixelClipped( 13 + x,2 + y,254,221,88 );
	gfx.PutPixelClipped( 14 + x,2 + y,254,221,88 );
	gfx.PutPixelClipped( 15 + x,2 + y,0,0,0 );
	gfx.PutPixelClipped( 16 + x,2 + y,0,0,0 );
	gfx.PutPixelClipped( 2 + x,3 + y,0,0,0 );
	gfx.PutPixelClipped( 3 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 4 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 5 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 6 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 7 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 8 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 9 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 10 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 11 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 12 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 13 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 14 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 15 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 16 + x,3 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,3 + y,0,0,0 );
	gfx.PutPixelClipped( 2 + x,4 + y,0,0,0 );
	gfx.PutPixelClipped( 3 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 4 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 5 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 6 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 7 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 8 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 9 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 10 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 11 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 12 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 13 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 14 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 15 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 16 + x,4 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,4 + y,0,0,0 );
	gfx.PutPixelClipped( 1 + x,5 + y,0,0,0 );
	gfx.PutPixelClipped( 2 + x,5 + y,254,221,88 );
	gfx.PutPixelClipped( 3 + x,5 + y,0,0,0 );
	gfx.PutPixelClipped( 4 + x,5 + y,0,0,0 );
	gfx.PutPixelClipped( 5 + x,5 + y,254,221,88 );
	gfx.PutPixelClipped( 6 + x,5 + y,254,221,88 );
	gfx.PutPixelClipped( 7 + x,5 + y,254,221,88 );
	gfx.PutPixelClipped( 8 + x,5 + y,254,221,88 );
	gfx.PutPixelClipped( 9 + x,5 + y,254,221,88 );
	gfx.PutPixelClipped( 10 + x,5 + y,254,221,88 );
	gfx.PutPixelClipped( 11 + x,5 + y,0,0,0 );
	gfx.PutPixelClipped( 12 + x,5 + y,0,0,0 );
	gfx.PutPixelClipped( 13 + x,5 + y,0,0,0 );
	gfx.PutPixelClipped( 14 + x,5 + y,0,0,0 );
	gfx.PutPixelClipped( 15 + x,5 + y,254,221,88 );
	gfx.PutPixelClipped( 16 + x,5 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,5 + y,254,221,88 );
	gfx.PutPixelClipped( 18 + x,5 + y,0,0,0 );
	gfx.PutPixelClipped( 1 + x,6 + y,0,0,0 );
	gfx.PutPixelClipped( 2 + x,6 + y,0,0,0 );
	gfx.PutPixelClipped( 3 + x,6 + y,255,255,255 );
	gfx.PutPixelClipped( 4 + x,6 + y,0,0,0 );
	gfx.PutPixelClipped( 5 + x,6 + y,0,0,0 );
	gfx.PutPixelClipped( 6 + x,6 + y,254,221,88 );
	gfx.PutPixelClipped( 7 + x,6 + y,254,221,88 );
	gfx.PutPixelClipped( 8 + x,6 + y,254,221,88 );
	gfx.PutPixelClipped( 9 + x,6 + y,254,221,88 );
	gfx.PutPixelClipped( 10 + x,6 + y,0,0,0 );
	gfx.PutPixelClipped( 11 + x,6 + y,255,255,255 );
	gfx.PutPixelClipped( 12 + x,6 + y,255,255,255 );
	gfx.PutPixelClipped( 13 + x,6 + y,0,0,0 );
	gfx.PutPixelClipped( 14 + x,6 + y,0,0,0 );
	gfx.PutPixelClipped( 15 + x,6 + y,0,0,0 );
	gfx.PutPixelClipped( 16 + x,6 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,6 + y,254,221,88 );
	gfx.PutPixelClipped( 18 + x,6 + y,0,0,0 );
	gfx.PutPixelClipped( 0 + x,7 + y,0,0,0 );
	gfx.PutPixelClipped( 1 + x,7 + y,0,0,0 );
	gfx.PutPixelClipped( 2 + x,7 + y,255,255,255 );
	gfx.PutPixelClipped( 3 + x,7 + y,255,255,255 );
	gfx.PutPixelClipped( 4 + x,7 + y,0,0,0 );
	gfx.PutPixelClipped( 5 + x,7 + y,0,0,0 );
	gfx.PutPixelClipped( 6 + x,7 + y,254,221,88 );
	gfx.PutPixelClipped( 7 + x,7 + y,254,221,88 );
	gfx.PutPixelClipped( 8 + x,7 + y,254,221,88 );
	gfx.PutPixelClipped( 9 + x,7 + y,254,221,88 );
	gfx.PutPixelClipped( 10 + x,7 + y,0,0,0 );
	gfx.PutPixelClipped( 11 + x,7 + y,255,255,255 );
	gfx.PutPixelClipped( 12 + x,7 + y,255,255,255 );
	gfx.PutPixelClipped( 13 + x,7 + y,0,0,0 );
	gfx.PutPixelClipped( 14 + x,7 + y,0,0,0 );
	gfx.PutPixelClipped( 15 + x,7 + y,0,0,0 );
	gfx.PutPixelClipped( 16 + x,7 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,7 + y,254,221,88 );
	gfx.PutPixelClipped( 18 + x,7 + y,254,221,88 );
	gfx.PutPixelClipped( 19 + x,7 + y,0,0,0 );
	gfx.PutPixelClipped( 0 + x,8 + y,0,0,0 );
	gfx.PutPixelClipped( 1 + x,8 + y,0,0,0 );
	gfx.PutPixelClipped( 2 + x,8 + y,255,255,255 );
	gfx.PutPixelClipped( 3 + x,8 + y,255,255,255 );
	gfx.PutPixelClipped( 4 + x,8 + y,255,255,255 );
	gfx.PutPixelClipped( 5 + x,8 + y,0,0,0 );
	gfx.PutPixelClipped( 6 + x,8 + y,254,221,88 );
	gfx.PutPixelClipped( 7 + x,8 + y,254,221,88 );
	gfx.PutPixelClipped( 8 + x,8 + y,254,221,88 );
	gfx.PutPixelClipped( 9 + x,8 + y,254,221,88 );
	gfx.PutPixelClipped( 10 + x,8 + y,0,0,0 );
	gfx.PutPixelClipped( 11 + x,8 + y,255,255,255 );
	gfx.PutPixelClipped( 12 + x,8 + y,255,255,255 );
	gfx.PutPixelClipped( 13 + x,8 + y,255,255,255 );
	gfx.PutPixelClipped( 14 + x,8 + y,255,255,255 );
	gfx.PutPixelClipped( 15 + x,8 + y,0,0,0 );
	gfx.PutPixelClipped( 16 + x,8 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,8 + y,254,221,88 );
	gfx.PutPixelClipped( 18 + x,8 + y,254,221,88 );
	gfx.PutPixelClipped( 19 + x,8 + y,0,0,0 );
	gfx.PutPixelClipped( 0 + x,9 + y,0,0,0 );
	gfx.PutPixelClipped( 1 + x,9 + y,254,221,88 );
	gfx.PutPixelClipped( 2 + x,9 + y,0,0,0 );
	gfx.PutPixelClipped( 3 + x,9 + y,0,0,0 );
	gfx.PutPixelClipped( 4 + x,9 + y,0,0,0 );
	gfx.PutPixelClipped( 5 + x,9 + y,0,0,0 );
	gfx.PutPixelClipped( 6 + x,9 + y,254,221,88 );
	gfx.PutPixelClipped( 7 + x,9 + y,254,221,88 );
	gfx.PutPixelClipped( 8 + x,9 + y,254,221,88 );
	gfx.PutPixelClipped( 9 + x,9 + y,254,221,88 );
	gfx.PutPixelClipped( 10 + x,9 + y,254,221,88 );
	gfx.PutPixelClipped( 11 + x,9 + y,0,0,0 );
	gfx.PutPixelClipped( 12 + x,9 + y,0,0,0 );
	gfx.PutPixelClipped( 13 + x,9 + y,0,0,0 );
	gfx.PutPixelClipped( 14 + x,9 + y,0,0,0 );
	gfx.PutPixelClipped( 15 + x,9 + y,254,221,88 );
	gfx.PutPixelClipped( 16 + x,9 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,9 + y,254,221,88 );
	gfx.PutPixelClipped( 18 + x,9 + y,254,221,88 );
	gfx.PutPixelClipped( 19 + x,9 + y,0,0,0 );
	gfx.PutPixelClipped( 0 + x,10 + y,0,0,0 );
	gfx.PutPixelClipped( 1 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 2 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 3 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 4 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 5 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 6 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 7 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 8 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 9 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 10 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 11 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 12 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 13 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 14 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 15 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 16 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 18 + x,10 + y,254,221,88 );
	gfx.PutPixelClipped( 19 + x,10 + y,0,0,0 );
	gfx.PutPixelClipped( 0 + x,11 + y,0,0,0 );
	gfx.PutPixelClipped( 1 + x,11 + y,254,221,88 );
	gfx.PutPixelClipped( 2 + x,11 + y,254,221,88 );
	gfx.PutPixelClipped( 3 + x,11 + y,254,221,88 );
	gfx.PutPixelClipped( 4 + x,11 + y,254,221,88 );
	gfx.PutPixelClipped( 5 + x,11 + y,254,221,88 );
	gfx.PutPixelClipped( 6 + x,11 + y,254,221,88 );
	gfx.PutPixelClipped( 7 + x,11 + y,20,14,18 );
	gfx.PutPixelClipped( 8 + x,11 + y,18,11,14 );
	gfx.PutPixelClipped( 9 + x,11 + y,18,12,14 );
	gfx.PutPixelClipped( 10 + x,11 + y,18,12,14 );
	gfx.PutPixelClipped( 11 + x,11 + y,21,13,16 );
	gfx.PutPixelClipped( 12 + x,11 + y,24,11,15 );
	gfx.PutPixelClipped( 13 + x,11 + y,0,0,0 );
	gfx.PutPixelClipped( 14 + x,11 + y,254,221,88 );
	gfx.PutPixelClipped( 15 + x,11 + y,254,221,88 );
	gfx.PutPixelClipped( 16 + x,11 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,11 + y,254,221,88 );
	gfx.PutPixelClipped( 18 + x,11 + y,254,221,88 );
	gfx.PutPixelClipped( 19 + x,11 + y,0,0,0 );
	gfx.PutPixelClipped( 0 + x,12 + y,0,0,0 );
	gfx.PutPixelClipped( 1 + x,12 + y,254,221,88 );
	gfx.PutPixelClipped( 2 + x,12 + y,254,221,88 );
	gfx.PutPixelClipped( 3 + x,12 + y,254,221,88 );
	gfx.PutPixelClipped( 4 + x,12 + y,254,221,88 );
	gfx.PutPixelClipped( 5 + x,12 + y,254,221,88 );
	gfx.PutPixelClipped( 6 + x,12 + y,23,9,23 );
	gfx.PutPixelClipped( 7 + x,12 + y,135,26,68 );
	gfx.PutPixelClipped( 8 + x,12 + y,135,26,68 );
	gfx.PutPixelClipped( 9 + x,12 + y,135,26,68 );
	gfx.PutPixelClipped( 10 + x,12 + y,135,26,68 );
	gfx.PutPixelClipped( 11 + x,12 + y,135,26,68 );
	gfx.PutPixelClipped( 12 + x,12 + y,135,26,68 );
	gfx.PutPixelClipped( 13 + x,12 + y,135,26,68 );
	gfx.PutPixelClipped( 14 + x,12 + y,0,0,0 );
	gfx.PutPixelClipped( 15 + x,12 + y,254,221,88 );
	gfx.PutPixelClipped( 16 + x,12 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,12 + y,254,221,88 );
	gfx.PutPixelClipped( 18 + x,12 + y,254,221,88 );
	gfx.PutPixelClipped( 19 + x,12 + y,0,0,0 );
	gfx.PutPixelClipped( 1 + x,13 + y,0,0,0 );
	gfx.PutPixelClipped( 2 + x,13 + y,254,221,88 );
	gfx.PutPixelClipped( 3 + x,13 + y,254,221,88 );
	gfx.PutPixelClipped( 4 + x,13 + y,254,221,88 );
	gfx.PutPixelClipped( 5 + x,13 + y,0,0,0 );
	gfx.PutPixelClipped( 6 + x,13 + y,135,26,68 );
	gfx.PutPixelClipped( 7 + x,13 + y,135,26,68 );
	gfx.PutPixelClipped( 8 + x,13 + y,135,26,68 );
	gfx.PutPixelClipped( 9 + x,13 + y,135,26,68 );
	gfx.PutPixelClipped( 10 + x,13 + y,135,26,68 );
	gfx.PutPixelClipped( 11 + x,13 + y,135,26,68 );
	gfx.PutPixelClipped( 12 + x,13 + y,135,26,68 );
	gfx.PutPixelClipped( 13 + x,13 + y,135,26,68 );
	gfx.PutPixelClipped( 14 + x,13 + y,135,26,68 );
	gfx.PutPixelClipped( 15 + x,13 + y,0,0,0 );
	gfx.PutPixelClipped( 16 + x,13 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,13 + y,254,221,88 );
	gfx.PutPixelClipped( 18 + x,13 + y,0,0,0 );
	gfx.PutPixelClipped( 1 + x,14 + y,0,0,0 );
	gfx.PutPixelClipped( 2 + x,14 + y,254,221,88 );
	gfx.PutPixelClipped( 3 + x,14 + y,254,221,88 );
	gfx.PutPixelClipped( 4 + x,14 + y,0,0,0 );
	gfx.PutPixelClipped( 5 + x,14 + y,135,26,68 );
	gfx.PutPixelClipped( 6 + x,14 + y,135,26,68 );
	gfx.PutPixelClipped( 7 + x,14 + y,135,26,68 );
	gfx.PutPixelClipped( 8 + x,14 + y,135,26,68 );
	gfx.PutPixelClipped( 9 + x,14 + y,251,192,224 );
	gfx.PutPixelClipped( 10 + x,14 + y,251,192,224 );
	gfx.PutPixelClipped( 11 + x,14 + y,251,192,224 );
	gfx.PutPixelClipped( 12 + x,14 + y,251,192,224 );
	gfx.PutPixelClipped( 13 + x,14 + y,135,26,68 );
	gfx.PutPixelClipped( 14 + x,14 + y,135,26,68 );
	gfx.PutPixelClipped( 15 + x,14 + y,0,0,0 );
	gfx.PutPixelClipped( 16 + x,14 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,14 + y,254,221,88 );
	gfx.PutPixelClipped( 18 + x,14 + y,0,0,0 );
	gfx.PutPixelClipped( 2 + x,15 + y,0,0,0 );
	gfx.PutPixelClipped( 3 + x,15 + y,254,221,88 );
	gfx.PutPixelClipped( 4 + x,15 + y,0,0,0 );
	gfx.PutPixelClipped( 5 + x,15 + y,135,26,68 );
	gfx.PutPixelClipped( 6 + x,15 + y,135,26,68 );
	gfx.PutPixelClipped( 7 + x,15 + y,135,26,68 );
	gfx.PutPixelClipped( 8 + x,15 + y,251,192,224 );
	gfx.PutPixelClipped( 9 + x,15 + y,251,192,224 );
	gfx.PutPixelClipped( 10 + x,15 + y,251,192,224 );
	gfx.PutPixelClipped( 11 + x,15 + y,251,192,224 );
	gfx.PutPixelClipped( 12 + x,15 + y,251,192,224 );
	gfx.PutPixelClipped( 13 + x,15 + y,251,192,224 );
	gfx.PutPixelClipped( 14 + x,15 + y,135,26,68 );
	gfx.PutPixelClipped( 15 + x,15 + y,0,0,0 );
	gfx.PutPixelClipped( 16 + x,15 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,15 + y,0,0,0 );
	gfx.PutPixelClipped( 2 + x,16 + y,0,0,0 );
	gfx.PutPixelClipped( 3 + x,16 + y,254,221,88 );
	gfx.PutPixelClipped( 4 + x,16 + y,0,0,0 );
	gfx.PutPixelClipped( 5 + x,16 + y,135,26,68 );
	gfx.PutPixelClipped( 6 + x,16 + y,135,26,68 );
	gfx.PutPixelClipped( 7 + x,16 + y,135,26,68 );
	gfx.PutPixelClipped( 8 + x,16 + y,251,192,224 );
	gfx.PutPixelClipped( 9 + x,16 + y,251,192,224 );
	gfx.PutPixelClipped( 10 + x,16 + y,251,192,224 );
	gfx.PutPixelClipped( 11 + x,16 + y,251,192,224 );
	gfx.PutPixelClipped( 12 + x,16 + y,251,192,224 );
	gfx.PutPixelClipped( 13 + x,16 + y,251,192,224 );
	gfx.PutPixelClipped( 14 + x,16 + y,135,26,68 );
	gfx.PutPixelClipped( 15 + x,16 + y,0,0,0 );
	gfx.PutPixelClipped( 16 + x,16 + y,254,221,88 );
	gfx.PutPixelClipped( 17 + x,16 + y,0,0,0 );
	gfx.PutPixelClipped( 3 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 4 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 5 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 6 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 7 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 8 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 9 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 10 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 11 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 12 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 13 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 14 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 15 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 16 + x,17 + y,0,0,0 );
	gfx.PutPixelClipped( 5 + x,18 + y,0,0,0 );
	gfx.PutPixelClipped( 6 + x,18 + y,0,0,0 );
	gfx.PutPixelClipped( 7 + x,18 + y,254,221,88 );
	gfx.PutPixelClipped( 8 + x,18 + y,254,221,88 );
	gfx.PutPixelClipped( 9 + x,18 + y,254,221,88 );
	gfx.PutPixelClipped( 10 + x,18 + y,254,221,88 );
	gfx.PutPixelClipped( 11 + x,18 + y,254,221,88 );
	gfx.PutPixelClipped( 12 + x,18 + y,254,221,88 );
	gfx.PutPixelClipped( 13 + x,18 + y,0,0,0 );
	gfx.PutPixelClipped( 14 + x,18 + y,0,0,0 );
	gfx.PutPixelClipped( 7 + x,19 + y,0,0,0 );
	gfx.PutPixelClipped( 8 + x,19 + y,0,0,0 );
	gfx.PutPixelClipped( 9 + x,19 + y,0,0,0 );
	gfx.PutPixelClipped( 10 + x,19 + y,0,0,0 );
	gfx.PutPixelClipped( 11 + x,19 + y,0,0,0 );
	gfx.PutPixelClipped( 12 + x,19 + y,0,0,0 );
}

// we have an unclipped version of DrawPoo because there can be
// many poo to draw and it would pay to draw some of them without
// the per-pixel clipping test if the those poo were entirely in
// the screen
void Game::DrawPooUnclipped( int x,int y )
{
	gfx.PutPixel( 14 + x,0 + y,138,77,0 );
	gfx.PutPixel( 7 + x,1 + y,138,77,0 );
	gfx.PutPixel( 13 + x,1 + y,138,77,0 );
	gfx.PutPixel( 20 + x,1 + y,138,77,0 );
	gfx.PutPixel( 6 + x,2 + y,138,77,0 );
	gfx.PutPixel( 13 + x,2 + y,138,77,0 );
	gfx.PutPixel( 20 + x,2 + y,138,77,0 );
	gfx.PutPixel( 6 + x,3 + y,138,77,0 );
	gfx.PutPixel( 6 + x,4 + y,138,77,0 );
	gfx.PutPixel( 14 + x,4 + y,138,77,0 );
	gfx.PutPixel( 21 + x,4 + y,138,77,0 );
	gfx.PutPixel( 7 + x,5 + y,138,77,0 );
	gfx.PutPixel( 13 + x,5 + y,138,77,0 );
	gfx.PutPixel( 21 + x,5 + y,138,77,0 );
	gfx.PutPixel( 7 + x,6 + y,138,77,0 );
	gfx.PutPixel( 20 + x,6 + y,138,77,0 );
	gfx.PutPixel( 6 + x,7 + y,138,77,0 );
	gfx.PutPixel( 14 + x,7 + y,51,28,0 );
	gfx.PutPixel( 15 + x,7 + y,51,28,0 );
	gfx.PutPixel( 20 + x,7 + y,138,77,0 );
	gfx.PutPixel( 12 + x,8 + y,51,28,0 );
	gfx.PutPixel( 13 + x,8 + y,51,28,0 );
	gfx.PutPixel( 14 + x,8 + y,51,28,0 );
	gfx.PutPixel( 7 + x,9 + y,138,77,0 );
	gfx.PutPixel( 11 + x,9 + y,51,28,0 );
	gfx.PutPixel( 12 + x,9 + y,102,57,0 );
	gfx.PutPixel( 13 + x,9 + y,138,77,0 );
	gfx.PutPixel( 14 + x,9 + y,138,77,0 );
	gfx.PutPixel( 15 + x,9 + y,51,28,0 );
	gfx.PutPixel( 21 + x,9 + y,138,77,0 );
	gfx.PutPixel( 10 + x,10 + y,51,28,0 );
	gfx.PutPixel( 11 + x,10 + y,51,28,0 );
	gfx.PutPixel( 12 + x,10 + y,102,57,0 );
	gfx.PutPixel( 13 + x,10 + y,138,77,0 );
	gfx.PutPixel( 14 + x,10 + y,138,77,0 );
	gfx.PutPixel( 15 + x,10 + y,51,28,0 );
	gfx.PutPixel( 20 + x,10 + y,138,77,0 );
	gfx.PutPixel( 9 + x,11 + y,51,28,0 );
	gfx.PutPixel( 10 + x,11 + y,138,77,0 );
	gfx.PutPixel( 11 + x,11 + y,138,77,0 );
	gfx.PutPixel( 12 + x,11 + y,51,28,0 );
	gfx.PutPixel( 13 + x,11 + y,51,28,0 );
	gfx.PutPixel( 14 + x,11 + y,51,28,0 );
	gfx.PutPixel( 15 + x,11 + y,51,28,0 );
	gfx.PutPixel( 16 + x,11 + y,51,28,0 );
	gfx.PutPixel( 9 + x,12 + y,51,28,0 );
	gfx.PutPixel( 10 + x,12 + y,138,77,0 );
	gfx.PutPixel( 11 + x,12 + y,138,77,0 );
	gfx.PutPixel( 12 + x,12 + y,111,62,0 );
	gfx.PutPixel( 13 + x,12 + y,102,57,0 );
	gfx.PutPixel( 14 + x,12 + y,102,57,0 );
	gfx.PutPixel( 15 + x,12 + y,102,57,0 );
	gfx.PutPixel( 16 + x,12 + y,51,28,0 );
	gfx.PutPixel( 9 + x,13 + y,51,28,0 );
	gfx.PutPixel( 10 + x,13 + y,109,61,0 );
	gfx.PutPixel( 11 + x,13 + y,138,77,0 );
	gfx.PutPixel( 12 + x,13 + y,138,77,0 );
	gfx.PutPixel( 13 + x,13 + y,138,77,0 );
	gfx.PutPixel( 14 + x,13 + y,138,77,0 );
	gfx.PutPixel( 15 + x,13 + y,138,77,0 );
	gfx.PutPixel( 16 + x,13 + y,51,28,0 );
	gfx.PutPixel( 5 + x,14 + y,51,28,0 );
	gfx.PutPixel( 7 + x,14 + y,51,28,0 );
	gfx.PutPixel( 8 + x,14 + y,51,28,0 );
	gfx.PutPixel( 9 + x,14 + y,51,28,0 );
	gfx.PutPixel( 10 + x,14 + y,51,28,0 );
	gfx.PutPixel( 11 + x,14 + y,138,77,0 );
	gfx.PutPixel( 12 + x,14 + y,138,77,0 );
	gfx.PutPixel( 13 + x,14 + y,138,77,0 );
	gfx.PutPixel( 14 + x,14 + y,138,77,0 );
	gfx.PutPixel( 15 + x,14 + y,138,77,0 );
	gfx.PutPixel( 16 + x,14 + y,51,28,0 );
	gfx.PutPixel( 4 + x,15 + y,51,28,0 );
	gfx.PutPixel( 5 + x,15 + y,138,77,0 );
	gfx.PutPixel( 6 + x,15 + y,51,28,0 );
	gfx.PutPixel( 7 + x,15 + y,116,65,0 );
	gfx.PutPixel( 8 + x,15 + y,138,77,0 );
	gfx.PutPixel( 9 + x,15 + y,138,77,0 );
	gfx.PutPixel( 10 + x,15 + y,138,77,0 );
	gfx.PutPixel( 11 + x,15 + y,51,28,0 );
	gfx.PutPixel( 12 + x,15 + y,51,28,0 );
	gfx.PutPixel( 13 + x,15 + y,51,28,0 );
	gfx.PutPixel( 14 + x,15 + y,51,28,0 );
	gfx.PutPixel( 15 + x,15 + y,51,28,0 );
	gfx.PutPixel( 16 + x,15 + y,51,28,0 );
	gfx.PutPixel( 17 + x,15 + y,51,28,0 );
	gfx.PutPixel( 18 + x,15 + y,51,28,0 );
	gfx.PutPixel( 1 + x,16 + y,51,28,0 );
	gfx.PutPixel( 2 + x,16 + y,51,28,0 );
	gfx.PutPixel( 3 + x,16 + y,51,28,0 );
	gfx.PutPixel( 4 + x,16 + y,51,28,0 );
	gfx.PutPixel( 5 + x,16 + y,138,77,0 );
	gfx.PutPixel( 6 + x,16 + y,51,28,0 );
	gfx.PutPixel( 7 + x,16 + y,116,65,0 );
	gfx.PutPixel( 8 + x,16 + y,138,77,0 );
	gfx.PutPixel( 9 + x,16 + y,138,77,0 );
	gfx.PutPixel( 10 + x,16 + y,138,77,0 );
	gfx.PutPixel( 11 + x,16 + y,138,77,0 );
	gfx.PutPixel( 12 + x,16 + y,138,77,0 );
	gfx.PutPixel( 13 + x,16 + y,109,61,0 );
	gfx.PutPixel( 14 + x,16 + y,51,28,0 );
	gfx.PutPixel( 15 + x,16 + y,138,77,0 );
	gfx.PutPixel( 16 + x,16 + y,138,77,0 );
	gfx.PutPixel( 17 + x,16 + y,138,77,0 );
	gfx.PutPixel( 18 + x,16 + y,123,69,0 );
	gfx.PutPixel( 19 + x,16 + y,51,28,0 );
	gfx.PutPixel( 0 + x,17 + y,51,28,0 );
	gfx.PutPixel( 1 + x,17 + y,87,49,0 );
	gfx.PutPixel( 2 + x,17 + y,87,49,0 );
	gfx.PutPixel( 3 + x,17 + y,87,49,0 );
	gfx.PutPixel( 4 + x,17 + y,87,49,0 );
	gfx.PutPixel( 5 + x,17 + y,51,28,0 );
	gfx.PutPixel( 6 + x,17 + y,51,28,0 );
	gfx.PutPixel( 7 + x,17 + y,43,24,0 );
	gfx.PutPixel( 8 + x,17 + y,51,28,0 );
	gfx.PutPixel( 9 + x,17 + y,51,28,0 );
	gfx.PutPixel( 10 + x,17 + y,51,28,0 );
	gfx.PutPixel( 11 + x,17 + y,51,28,0 );
	gfx.PutPixel( 12 + x,17 + y,51,28,0 );
	gfx.PutPixel( 13 + x,17 + y,40,22,0 );
	gfx.PutPixel( 14 + x,17 + y,51,28,0 );
	gfx.PutPixel( 15 + x,17 + y,138,77,0 );
	gfx.PutPixel( 16 + x,17 + y,138,77,0 );
	gfx.PutPixel( 17 + x,17 + y,138,77,0 );
	gfx.PutPixel( 18 + x,17 + y,123,69,0 );
	gfx.PutPixel( 19 + x,17 + y,51,28,0 );
	gfx.PutPixel( 0 + x,18 + y,51,28,0 );
	gfx.PutPixel( 1 + x,18 + y,138,77,0 );
	gfx.PutPixel( 2 + x,18 + y,138,77,0 );
	gfx.PutPixel( 3 + x,18 + y,138,77,0 );
	gfx.PutPixel( 4 + x,18 + y,138,77,0 );
	gfx.PutPixel( 5 + x,18 + y,51,28,0 );
	gfx.PutPixel( 6 + x,18 + y,51,28,0 );
	gfx.PutPixel( 7 + x,18 + y,51,28,0 );
	gfx.PutPixel( 8 + x,18 + y,51,28,0 );
	gfx.PutPixel( 9 + x,18 + y,51,28,0 );
	gfx.PutPixel( 10 + x,18 + y,51,28,0 );
	gfx.PutPixel( 11 + x,18 + y,51,28,0 );
	gfx.PutPixel( 12 + x,18 + y,51,28,0 );
	gfx.PutPixel( 13 + x,18 + y,51,28,0 );
	gfx.PutPixel( 14 + x,18 + y,51,28,0 );
	gfx.PutPixel( 15 + x,18 + y,138,77,0 );
	gfx.PutPixel( 16 + x,18 + y,138,77,0 );
	gfx.PutPixel( 17 + x,18 + y,138,77,0 );
	gfx.PutPixel( 18 + x,18 + y,123,69,0 );
	gfx.PutPixel( 19 + x,18 + y,51,28,0 );
	gfx.PutPixel( 20 + x,18 + y,51,28,0 );
	gfx.PutPixel( 21 + x,18 + y,51,28,0 );
	gfx.PutPixel( 22 + x,18 + y,51,28,0 );
	gfx.PutPixel( 0 + x,19 + y,51,28,0 );
	gfx.PutPixel( 1 + x,19 + y,138,77,0 );
	gfx.PutPixel( 2 + x,19 + y,138,77,0 );
	gfx.PutPixel( 3 + x,19 + y,138,77,0 );
	gfx.PutPixel( 4 + x,19 + y,138,77,0 );
	gfx.PutPixel( 5 + x,19 + y,51,28,0 );
	gfx.PutPixel( 6 + x,19 + y,138,77,0 );
	gfx.PutPixel( 7 + x,19 + y,138,77,0 );
	gfx.PutPixel( 8 + x,19 + y,138,77,0 );
	gfx.PutPixel( 9 + x,19 + y,138,77,0 );
	gfx.PutPixel( 10 + x,19 + y,138,77,0 );
	gfx.PutPixel( 11 + x,19 + y,138,77,0 );
	gfx.PutPixel( 12 + x,19 + y,138,77,0 );
	gfx.PutPixel( 13 + x,19 + y,138,77,0 );
	gfx.PutPixel( 14 + x,19 + y,138,77,0 );
	gfx.PutPixel( 15 + x,19 + y,138,77,0 );
	gfx.PutPixel( 16 + x,19 + y,138,77,0 );
	gfx.PutPixel( 17 + x,19 + y,138,77,0 );
	gfx.PutPixel( 18 + x,19 + y,123,69,0 );
	gfx.PutPixel( 19 + x,19 + y,51,28,0 );
	gfx.PutPixel( 20 + x,19 + y,138,77,0 );
	gfx.PutPixel( 21 + x,19 + y,138,77,0 );
	gfx.PutPixel( 22 + x,19 + y,65,36,0 );
	gfx.PutPixel( 23 + x,19 + y,51,28,0 );
	gfx.PutPixel( 1 + x,20 + y,51,28,0 );
	gfx.PutPixel( 2 + x,20 + y,51,28,0 );
	gfx.PutPixel( 3 + x,20 + y,51,28,0 );
	gfx.PutPixel( 4 + x,20 + y,51,28,0 );
	gfx.PutPixel( 5 + x,20 + y,51,28,0 );
	gfx.PutPixel( 6 + x,20 + y,138,77,0 );
	gfx.PutPixel( 7 + x,20 + y,138,77,0 );
	gfx.PutPixel( 8 + x,20 + y,138,77,0 );
	gfx.PutPixel( 9 + x,20 + y,138,77,0 );
	gfx.PutPixel( 10 + x,20 + y,138,77,0 );
	gfx.PutPixel( 11 + x,20 + y,138,77,0 );
	gfx.PutPixel( 12 + x,20 + y,138,77,0 );
	gfx.PutPixel( 13 + x,20 + y,138,77,0 );
	gfx.PutPixel( 14 + x,20 + y,138,77,0 );
	gfx.PutPixel( 15 + x,20 + y,138,77,0 );
	gfx.PutPixel( 16 + x,20 + y,138,77,0 );
	gfx.PutPixel( 17 + x,20 + y,138,77,0 );
	gfx.PutPixel( 18 + x,20 + y,123,69,0 );
	gfx.PutPixel( 19 + x,20 + y,51,28,0 );
	gfx.PutPixel( 20 + x,20 + y,138,77,0 );
	gfx.PutPixel( 21 + x,20 + y,138,77,0 );
	gfx.PutPixel( 22 + x,20 + y,65,36,0 );
	gfx.PutPixel( 23 + x,20 + y,51,28,0 );
	gfx.PutPixel( 0 + x,21 + y,51,28,0 );
	gfx.PutPixel( 1 + x,21 + y,138,77,0 );
	gfx.PutPixel( 2 + x,21 + y,138,77,0 );
	gfx.PutPixel( 3 + x,21 + y,138,77,0 );
	gfx.PutPixel( 4 + x,21 + y,138,77,0 );
	gfx.PutPixel( 5 + x,21 + y,138,77,0 );
	gfx.PutPixel( 6 + x,21 + y,51,28,0 );
	gfx.PutPixel( 7 + x,21 + y,51,28,0 );
	gfx.PutPixel( 8 + x,21 + y,51,28,0 );
	gfx.PutPixel( 9 + x,21 + y,51,28,0 );
	gfx.PutPixel( 10 + x,21 + y,51,28,0 );
	gfx.PutPixel( 11 + x,21 + y,51,28,0 );
	gfx.PutPixel( 12 + x,21 + y,51,28,0 );
	gfx.PutPixel( 13 + x,21 + y,51,28,0 );
	gfx.PutPixel( 14 + x,21 + y,51,28,0 );
	gfx.PutPixel( 15 + x,21 + y,51,28,0 );
	gfx.PutPixel( 16 + x,21 + y,51,28,0 );
	gfx.PutPixel( 17 + x,21 + y,51,28,0 );
	gfx.PutPixel( 18 + x,21 + y,51,28,0 );
	gfx.PutPixel( 20 + x,21 + y,51,28,0 );
	gfx.PutPixel( 21 + x,21 + y,51,28,0 );
	gfx.PutPixel( 22 + x,21 + y,51,28,0 );
	gfx.PutPixel( 0 + x,22 + y,51,28,0 );
	gfx.PutPixel( 1 + x,22 + y,65,36,0 );
	gfx.PutPixel( 2 + x,22 + y,65,36,0 );
	gfx.PutPixel( 3 + x,22 + y,65,36,0 );
	gfx.PutPixel( 4 + x,22 + y,65,36,0 );
	gfx.PutPixel( 5 + x,22 + y,65,36,0 );
	gfx.PutPixel( 6 + x,22 + y,51,28,0 );
	gfx.PutPixel( 1 + x,23 + y,51,28,0 );
	gfx.PutPixel( 2 + x,23 + y,51,28,0 );
	gfx.PutPixel( 3 + x,23 + y,51,28,0 );
	gfx.PutPixel( 4 + x,23 + y,51,28,0 );
	gfx.PutPixel( 5 + x,23 + y,51,28,0 );
	gfx.PutPixel( 6 + x,23 + y,51,28,0 );
}

void Game::DrawPooClipped( int x,int y )
{
	gfx.PutPixelClipped( 14 + x,0 + y,138,77,0 );
	gfx.PutPixelClipped( 7 + x,1 + y,138,77,0 );
	gfx.PutPixelClipped( 13 + x,1 + y,138,77,0 );
	gfx.PutPixelClipped( 20 + x,1 + y,138,77,0 );
	gfx.PutPixelClipped( 6 + x,2 + y,138,77,0 );
	gfx.PutPixelClipped( 13 + x,2 + y,138,77,0 );
	gfx.PutPixelClipped( 20 + x,2 + y,138,77,0 );
	gfx.PutPixelClipped( 6 + x,3 + y,138,77,0 );
	gfx.PutPixelClipped( 6 + x,4 + y,138,77,0 );
	gfx.PutPixelClipped( 14 + x,4 + y,138,77,0 );
	gfx.PutPixelClipped( 21 + x,4 + y,138,77,0 );
	gfx.PutPixelClipped( 7 + x,5 + y,138,77,0 );
	gfx.PutPixelClipped( 13 + x,5 + y,138,77,0 );
	gfx.PutPixelClipped( 21 + x,5 + y,138,77,0 );
	gfx.PutPixelClipped( 7 + x,6 + y,138,77,0 );
	gfx.PutPixelClipped( 20 + x,6 + y,138,77,0 );
	gfx.PutPixelClipped( 6 + x,7 + y,138,77,0 );
	gfx.PutPixelClipped( 14 + x,7 + y,51,28,0 );
	gfx.PutPixelClipped( 15 + x,7 + y,51,28,0 );
	gfx.PutPixelClipped( 20 + x,7 + y,138,77,0 );
	gfx.PutPixelClipped( 12 + x,8 + y,51,28,0 );
	gfx.PutPixelClipped( 13 + x,8 + y,51,28,0 );
	gfx.PutPixelClipped( 14 + x,8 + y,51,28,0 );
	gfx.PutPixelClipped( 7 + x,9 + y,138,77,0 );
	gfx.PutPixelClipped( 11 + x,9 + y,51,28,0 );
	gfx.PutPixelClipped( 12 + x,9 + y,102,57,0 );
	gfx.PutPixelClipped( 13 + x,9 + y,138,77,0 );
	gfx.PutPixelClipped( 14 + x,9 + y,138,77,0 );
	gfx.PutPixelClipped( 15 + x,9 + y,51,28,0 );
	gfx.PutPixelClipped( 21 + x,9 + y,138,77,0 );
	gfx.PutPixelClipped( 10 + x,10 + y,51,28,0 );
	gfx.PutPixelClipped( 11 + x,10 + y,51,28,0 );
	gfx.PutPixelClipped( 12 + x,10 + y,102,57,0 );
	gfx.PutPixelClipped( 13 + x,10 + y,138,77,0 );
	gfx.PutPixelClipped( 14 + x,10 + y,138,77,0 );
	gfx.PutPixelClipped( 15 + x,10 + y,51,28,0 );
	gfx.PutPixelClipped( 20 + x,10 + y,138,77,0 );
	gfx.PutPixelClipped( 9 + x,11 + y,51,28,0 );
	gfx.PutPixelClipped( 10 + x,11 + y,138,77,0 );
	gfx.PutPixelClipped( 11 + x,11 + y,138,77,0 );
	gfx.PutPixelClipped( 12 + x,11 + y,51,28,0 );
	gfx.PutPixelClipped( 13 + x,11 + y,51,28,0 );
	gfx.PutPixelClipped( 14 + x,11 + y,51,28,0 );
	gfx.PutPixelClipped( 15 + x,11 + y,51,28,0 );
	gfx.PutPixelClipped( 16 + x,11 + y,51,28,0 );
	gfx.PutPixelClipped( 9 + x,12 + y,51,28,0 );
	gfx.PutPixelClipped( 10 + x,12 + y,138,77,0 );
	gfx.PutPixelClipped( 11 + x,12 + y,138,77,0 );
	gfx.PutPixelClipped( 12 + x,12 + y,111,62,0 );
	gfx.PutPixelClipped( 13 + x,12 + y,102,57,0 );
	gfx.PutPixelClipped( 14 + x,12 + y,102,57,0 );
	gfx.PutPixelClipped( 15 + x,12 + y,102,57,0 );
	gfx.PutPixelClipped( 16 + x,12 + y,51,28,0 );
	gfx.PutPixelClipped( 9 + x,13 + y,51,28,0 );
	gfx.PutPixelClipped( 10 + x,13 + y,109,61,0 );
	gfx.PutPixelClipped( 11 + x,13 + y,138,77,0 );
	gfx.PutPixelClipped( 12 + x,13 + y,138,77,0 );
	gfx.PutPixelClipped( 13 + x,13 + y,138,77,0 );
	gfx.PutPixelClipped( 14 + x,13 + y,138,77,0 );
	gfx.PutPixelClipped( 15 + x,13 + y,138,77,0 );
	gfx.PutPixelClipped( 16 + x,13 + y,51,28,0 );
	gfx.PutPixelClipped( 5 + x,14 + y,51,28,0 );
	gfx.PutPixelClipped( 7 + x,14 + y,51,28,0 );
	gfx.PutPixelClipped( 8 + x,14 + y,51,28,0 );
	gfx.PutPixelClipped( 9 + x,14 + y,51,28,0 );
	gfx.PutPixelClipped( 10 + x,14 + y,51,28,0 );
	gfx.PutPixelClipped( 11 + x,14 + y,138,77,0 );
	gfx.PutPixelClipped( 12 + x,14 + y,138,77,0 );
	gfx.PutPixelClipped( 13 + x,14 + y,138,77,0 );
	gfx.PutPixelClipped( 14 + x,14 + y,138,77,0 );
	gfx.PutPixelClipped( 15 + x,14 + y,138,77,0 );
	gfx.PutPixelClipped( 16 + x,14 + y,51,28,0 );
	gfx.PutPixelClipped( 4 + x,15 + y,51,28,0 );
	gfx.PutPixelClipped( 5 + x,15 + y,138,77,0 );
	gfx.PutPixelClipped( 6 + x,15 + y,51,28,0 );
	gfx.PutPixelClipped( 7 + x,15 + y,116,65,0 );
	gfx.PutPixelClipped( 8 + x,15 + y,138,77,0 );
	gfx.PutPixelClipped( 9 + x,15 + y,138,77,0 );
	gfx.PutPixelClipped( 10 + x,15 + y,138,77,0 );
	gfx.PutPixelClipped( 11 + x,15 + y,51,28,0 );
	gfx.PutPixelClipped( 12 + x,15 + y,51,28,0 );
	gfx.PutPixelClipped( 13 + x,15 + y,51,28,0 );
	gfx.PutPixelClipped( 14 + x,15 + y,51,28,0 );
	gfx.PutPixelClipped( 15 + x,15 + y,51,28,0 );
	gfx.PutPixelClipped( 16 + x,15 + y,51,28,0 );
	gfx.PutPixelClipped( 17 + x,15 + y,51,28,0 );
	gfx.PutPixelClipped( 18 + x,15 + y,51,28,0 );
	gfx.PutPixelClipped( 1 + x,16 + y,51,28,0 );
	gfx.PutPixelClipped( 2 + x,16 + y,51,28,0 );
	gfx.PutPixelClipped( 3 + x,16 + y,51,28,0 );
	gfx.PutPixelClipped( 4 + x,16 + y,51,28,0 );
	gfx.PutPixelClipped( 5 + x,16 + y,138,77,0 );
	gfx.PutPixelClipped( 6 + x,16 + y,51,28,0 );
	gfx.PutPixelClipped( 7 + x,16 + y,116,65,0 );
	gfx.PutPixelClipped( 8 + x,16 + y,138,77,0 );
	gfx.PutPixelClipped( 9 + x,16 + y,138,77,0 );
	gfx.PutPixelClipped( 10 + x,16 + y,138,77,0 );
	gfx.PutPixelClipped( 11 + x,16 + y,138,77,0 );
	gfx.PutPixelClipped( 12 + x,16 + y,138,77,0 );
	gfx.PutPixelClipped( 13 + x,16 + y,109,61,0 );
	gfx.PutPixelClipped( 14 + x,16 + y,51,28,0 );
	gfx.PutPixelClipped( 15 + x,16 + y,138,77,0 );
	gfx.PutPixelClipped( 16 + x,16 + y,138,77,0 );
	gfx.PutPixelClipped( 17 + x,16 + y,138,77,0 );
	gfx.PutPixelClipped( 18 + x,16 + y,123,69,0 );
	gfx.PutPixelClipped( 19 + x,16 + y,51,28,0 );
	gfx.PutPixelClipped( 0 + x,17 + y,51,28,0 );
	gfx.PutPixelClipped( 1 + x,17 + y,87,49,0 );
	gfx.PutPixelClipped( 2 + x,17 + y,87,49,0 );
	gfx.PutPixelClipped( 3 + x,17 + y,87,49,0 );
	gfx.PutPixelClipped( 4 + x,17 + y,87,49,0 );
	gfx.PutPixelClipped( 5 + x,17 + y,51,28,0 );
	gfx.PutPixelClipped( 6 + x,17 + y,51,28,0 );
	gfx.PutPixelClipped( 7 + x,17 + y,43,24,0 );
	gfx.PutPixelClipped( 8 + x,17 + y,51,28,0 );
	gfx.PutPixelClipped( 9 + x,17 + y,51,28,0 );
	gfx.PutPixelClipped( 10 + x,17 + y,51,28,0 );
	gfx.PutPixelClipped( 11 + x,17 + y,51,28,0 );
	gfx.PutPixelClipped( 12 + x,17 + y,51,28,0 );
	gfx.PutPixelClipped( 13 + x,17 + y,40,22,0 );
	gfx.PutPixelClipped( 14 + x,17 + y,51,28,0 );
	gfx.PutPixelClipped( 15 + x,17 + y,138,77,0 );
	gfx.PutPixelClipped( 16 + x,17 + y,138,77,0 );
	gfx.PutPixelClipped( 17 + x,17 + y,138,77,0 );
	gfx.PutPixelClipped( 18 + x,17 + y,123,69,0 );
	gfx.PutPixelClipped( 19 + x,17 + y,51,28,0 );
	gfx.PutPixelClipped( 0 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 1 + x,18 + y,138,77,0 );
	gfx.PutPixelClipped( 2 + x,18 + y,138,77,0 );
	gfx.PutPixelClipped( 3 + x,18 + y,138,77,0 );
	gfx.PutPixelClipped( 4 + x,18 + y,138,77,0 );
	gfx.PutPixelClipped( 5 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 6 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 7 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 8 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 9 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 10 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 11 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 12 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 13 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 14 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 15 + x,18 + y,138,77,0 );
	gfx.PutPixelClipped( 16 + x,18 + y,138,77,0 );
	gfx.PutPixelClipped( 17 + x,18 + y,138,77,0 );
	gfx.PutPixelClipped( 18 + x,18 + y,123,69,0 );
	gfx.PutPixelClipped( 19 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 20 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 21 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 22 + x,18 + y,51,28,0 );
	gfx.PutPixelClipped( 0 + x,19 + y,51,28,0 );
	gfx.PutPixelClipped( 1 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 2 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 3 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 4 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 5 + x,19 + y,51,28,0 );
	gfx.PutPixelClipped( 6 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 7 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 8 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 9 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 10 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 11 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 12 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 13 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 14 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 15 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 16 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 17 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 18 + x,19 + y,123,69,0 );
	gfx.PutPixelClipped( 19 + x,19 + y,51,28,0 );
	gfx.PutPixelClipped( 20 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 21 + x,19 + y,138,77,0 );
	gfx.PutPixelClipped( 22 + x,19 + y,65,36,0 );
	gfx.PutPixelClipped( 23 + x,19 + y,51,28,0 );
	gfx.PutPixelClipped( 1 + x,20 + y,51,28,0 );
	gfx.PutPixelClipped( 2 + x,20 + y,51,28,0 );
	gfx.PutPixelClipped( 3 + x,20 + y,51,28,0 );
	gfx.PutPixelClipped( 4 + x,20 + y,51,28,0 );
	gfx.PutPixelClipped( 5 + x,20 + y,51,28,0 );
	gfx.PutPixelClipped( 6 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 7 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 8 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 9 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 10 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 11 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 12 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 13 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 14 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 15 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 16 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 17 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 18 + x,20 + y,123,69,0 );
	gfx.PutPixelClipped( 19 + x,20 + y,51,28,0 );
	gfx.PutPixelClipped( 20 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 21 + x,20 + y,138,77,0 );
	gfx.PutPixelClipped( 22 + x,20 + y,65,36,0 );
	gfx.PutPixelClipped( 23 + x,20 + y,51,28,0 );
	gfx.PutPixelClipped( 0 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 1 + x,21 + y,138,77,0 );
	gfx.PutPixelClipped( 2 + x,21 + y,138,77,0 );
	gfx.PutPixelClipped( 3 + x,21 + y,138,77,0 );
	gfx.PutPixelClipped( 4 + x,21 + y,138,77,0 );
	gfx.PutPixelClipped( 5 + x,21 + y,138,77,0 );
	gfx.PutPixelClipped( 6 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 7 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 8 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 9 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 10 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 11 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 12 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 13 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 14 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 15 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 16 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 17 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 18 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 20 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 21 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 22 + x,21 + y,51,28,0 );
	gfx.PutPixelClipped( 0 + x,22 + y,51,28,0 );
	gfx.PutPixelClipped( 1 + x,22 + y,65,36,0 );
	gfx.PutPixelClipped( 2 + x,22 + y,65,36,0 );
	gfx.PutPixelClipped( 3 + x,22 + y,65,36,0 );
	gfx.PutPixelClipped( 4 + x,22 + y,65,36,0 );
	gfx.PutPixelClipped( 5 + x,22 + y,65,36,0 );
	gfx.PutPixelClipped( 6 + x,22 + y,51,28,0 );
	gfx.PutPixelClipped( 1 + x,23 + y,51,28,0 );
	gfx.PutPixelClipped( 2 + x,23 + y,51,28,0 );
	gfx.PutPixelClipped( 3 + x,23 + y,51,28,0 );
	gfx.PutPixelClipped( 4 + x,23 + y,51,28,0 );
	gfx.PutPixelClipped( 5 + x,23 + y,51,28,0 );
	gfx.PutPixelClipped( 6 + x,23 + y,51,28,0 );
}

void Game::DrawGameOver( int x,int y )
{
	gfx.PutPixel( 49 + x,0 + y,0,146,14 );
	gfx.PutPixel( 50 + x,0 + y,0,146,14 );
	gfx.PutPixel( 51 + x,0 + y,0,146,14 );
	gfx.PutPixel( 49 + x,1 + y,0,146,14 );
	gfx.PutPixel( 50 + x,1 + y,0,146,14 );
	gfx.PutPixel( 51 + x,1 + y,0,146,14 );
	gfx.PutPixel( 52 + x,1 + y,0,146,14 );
	gfx.PutPixel( 38 + x,2 + y,0,146,14 );
	gfx.PutPixel( 39 + x,2 + y,0,146,14 );
	gfx.PutPixel( 40 + x,2 + y,0,146,14 );
	gfx.PutPixel( 41 + x,2 + y,0,146,14 );
	gfx.PutPixel( 50 + x,2 + y,0,146,14 );
	gfx.PutPixel( 51 + x,2 + y,0,146,14 );
	gfx.PutPixel( 52 + x,2 + y,0,146,14 );
	gfx.PutPixel( 36 + x,3 + y,0,146,14 );
	gfx.PutPixel( 37 + x,3 + y,0,146,14 );
	gfx.PutPixel( 38 + x,3 + y,0,146,14 );
	gfx.PutPixel( 39 + x,3 + y,0,146,14 );
	gfx.PutPixel( 40 + x,3 + y,0,146,14 );
	gfx.PutPixel( 41 + x,3 + y,0,146,14 );
	gfx.PutPixel( 42 + x,3 + y,0,146,14 );
	gfx.PutPixel( 43 + x,3 + y,0,146,14 );
	gfx.PutPixel( 50 + x,3 + y,0,146,14 );
	gfx.PutPixel( 51 + x,3 + y,0,146,14 );
	gfx.PutPixel( 52 + x,3 + y,0,146,14 );
	gfx.PutPixel( 53 + x,3 + y,0,146,14 );
	gfx.PutPixel( 35 + x,4 + y,0,146,14 );
	gfx.PutPixel( 36 + x,4 + y,0,146,14 );
	gfx.PutPixel( 37 + x,4 + y,0,146,14 );
	gfx.PutPixel( 38 + x,4 + y,0,146,14 );
	gfx.PutPixel( 39 + x,4 + y,0,146,14 );
	gfx.PutPixel( 40 + x,4 + y,0,146,14 );
	gfx.PutPixel( 41 + x,4 + y,0,146,14 );
	gfx.PutPixel( 42 + x,4 + y,0,146,14 );
	gfx.PutPixel( 43 + x,4 + y,0,146,14 );
	gfx.PutPixel( 44 + x,4 + y,0,146,14 );
	gfx.PutPixel( 51 + x,4 + y,0,146,14 );
	gfx.PutPixel( 52 + x,4 + y,0,146,14 );
	gfx.PutPixel( 53 + x,4 + y,0,146,14 );
	gfx.PutPixel( 68 + x,4 + y,0,146,14 );
	gfx.PutPixel( 69 + x,4 + y,0,146,14 );
	gfx.PutPixel( 70 + x,4 + y,0,146,14 );
	gfx.PutPixel( 71 + x,4 + y,0,146,14 );
	gfx.PutPixel( 72 + x,4 + y,0,146,14 );
	gfx.PutPixel( 73 + x,4 + y,0,146,14 );
	gfx.PutPixel( 74 + x,4 + y,0,146,14 );
	gfx.PutPixel( 75 + x,4 + y,0,146,14 );
	gfx.PutPixel( 76 + x,4 + y,0,146,14 );
	gfx.PutPixel( 77 + x,4 + y,0,146,14 );
	gfx.PutPixel( 78 + x,4 + y,0,146,14 );
	gfx.PutPixel( 79 + x,4 + y,0,146,14 );
	gfx.PutPixel( 34 + x,5 + y,0,118,11 );
	gfx.PutPixel( 35 + x,5 + y,0,146,14 );
	gfx.PutPixel( 36 + x,5 + y,0,146,14 );
	gfx.PutPixel( 37 + x,5 + y,0,146,14 );
	gfx.PutPixel( 38 + x,5 + y,0,146,14 );
	gfx.PutPixel( 39 + x,5 + y,0,146,14 );
	gfx.PutPixel( 40 + x,5 + y,0,146,14 );
	gfx.PutPixel( 41 + x,5 + y,0,146,14 );
	gfx.PutPixel( 42 + x,5 + y,0,146,14 );
	gfx.PutPixel( 43 + x,5 + y,0,146,14 );
	gfx.PutPixel( 44 + x,5 + y,0,146,14 );
	gfx.PutPixel( 51 + x,5 + y,0,142,13 );
	gfx.PutPixel( 52 + x,5 + y,0,146,14 );
	gfx.PutPixel( 53 + x,5 + y,0,146,14 );
	gfx.PutPixel( 54 + x,5 + y,0,146,14 );
	gfx.PutPixel( 66 + x,5 + y,0,146,14 );
	gfx.PutPixel( 67 + x,5 + y,0,146,14 );
	gfx.PutPixel( 68 + x,5 + y,0,146,14 );
	gfx.PutPixel( 69 + x,5 + y,0,146,14 );
	gfx.PutPixel( 70 + x,5 + y,0,146,14 );
	gfx.PutPixel( 71 + x,5 + y,0,146,14 );
	gfx.PutPixel( 72 + x,5 + y,0,146,14 );
	gfx.PutPixel( 73 + x,5 + y,0,146,14 );
	gfx.PutPixel( 74 + x,5 + y,0,146,14 );
	gfx.PutPixel( 75 + x,5 + y,0,146,14 );
	gfx.PutPixel( 76 + x,5 + y,0,146,14 );
	gfx.PutPixel( 77 + x,5 + y,0,146,14 );
	gfx.PutPixel( 78 + x,5 + y,0,146,14 );
	gfx.PutPixel( 79 + x,5 + y,0,146,14 );
	gfx.PutPixel( 80 + x,5 + y,0,146,14 );
	gfx.PutPixel( 34 + x,6 + y,0,146,14 );
	gfx.PutPixel( 35 + x,6 + y,0,146,14 );
	gfx.PutPixel( 36 + x,6 + y,0,146,14 );
	gfx.PutPixel( 37 + x,6 + y,0,146,14 );
	gfx.PutPixel( 38 + x,6 + y,0,146,14 );
	gfx.PutPixel( 39 + x,6 + y,0,146,14 );
	gfx.PutPixel( 40 + x,6 + y,0,146,14 );
	gfx.PutPixel( 41 + x,6 + y,0,146,14 );
	gfx.PutPixel( 42 + x,6 + y,0,146,14 );
	gfx.PutPixel( 43 + x,6 + y,0,146,14 );
	gfx.PutPixel( 44 + x,6 + y,0,146,14 );
	gfx.PutPixel( 45 + x,6 + y,0,146,14 );
	gfx.PutPixel( 52 + x,6 + y,0,146,14 );
	gfx.PutPixel( 53 + x,6 + y,0,146,14 );
	gfx.PutPixel( 54 + x,6 + y,0,146,14 );
	gfx.PutPixel( 55 + x,6 + y,0,146,14 );
	gfx.PutPixel( 65 + x,6 + y,0,146,14 );
	gfx.PutPixel( 66 + x,6 + y,0,146,14 );
	gfx.PutPixel( 67 + x,6 + y,0,146,14 );
	gfx.PutPixel( 68 + x,6 + y,0,146,14 );
	gfx.PutPixel( 69 + x,6 + y,0,146,14 );
	gfx.PutPixel( 70 + x,6 + y,0,146,14 );
	gfx.PutPixel( 71 + x,6 + y,0,146,14 );
	gfx.PutPixel( 72 + x,6 + y,0,146,14 );
	gfx.PutPixel( 73 + x,6 + y,0,146,14 );
	gfx.PutPixel( 74 + x,6 + y,0,146,14 );
	gfx.PutPixel( 75 + x,6 + y,0,146,14 );
	gfx.PutPixel( 76 + x,6 + y,0,146,14 );
	gfx.PutPixel( 77 + x,6 + y,0,146,14 );
	gfx.PutPixel( 78 + x,6 + y,0,146,14 );
	gfx.PutPixel( 79 + x,6 + y,0,146,14 );
	gfx.PutPixel( 80 + x,6 + y,0,146,14 );
	gfx.PutPixel( 81 + x,6 + y,0,146,14 );
	gfx.PutPixel( 34 + x,7 + y,0,146,14 );
	gfx.PutPixel( 35 + x,7 + y,0,146,14 );
	gfx.PutPixel( 36 + x,7 + y,0,146,14 );
	gfx.PutPixel( 37 + x,7 + y,0,146,14 );
	gfx.PutPixel( 38 + x,7 + y,0,146,14 );
	gfx.PutPixel( 39 + x,7 + y,0,146,14 );
	gfx.PutPixel( 40 + x,7 + y,0,146,14 );
	gfx.PutPixel( 41 + x,7 + y,0,146,14 );
	gfx.PutPixel( 42 + x,7 + y,0,146,14 );
	gfx.PutPixel( 43 + x,7 + y,0,146,14 );
	gfx.PutPixel( 44 + x,7 + y,0,146,14 );
	gfx.PutPixel( 45 + x,7 + y,0,146,14 );
	gfx.PutPixel( 53 + x,7 + y,0,146,14 );
	gfx.PutPixel( 54 + x,7 + y,0,146,14 );
	gfx.PutPixel( 55 + x,7 + y,0,146,14 );
	gfx.PutPixel( 65 + x,7 + y,0,146,14 );
	gfx.PutPixel( 66 + x,7 + y,0,146,14 );
	gfx.PutPixel( 67 + x,7 + y,0,146,14 );
	gfx.PutPixel( 68 + x,7 + y,0,142,13 );
	gfx.PutPixel( 79 + x,7 + y,0,146,14 );
	gfx.PutPixel( 80 + x,7 + y,0,146,14 );
	gfx.PutPixel( 81 + x,7 + y,0,146,14 );
	gfx.PutPixel( 82 + x,7 + y,0,146,14 );
	gfx.PutPixel( 34 + x,8 + y,0,146,14 );
	gfx.PutPixel( 35 + x,8 + y,0,146,14 );
	gfx.PutPixel( 36 + x,8 + y,0,146,14 );
	gfx.PutPixel( 37 + x,8 + y,0,146,14 );
	gfx.PutPixel( 38 + x,8 + y,0,146,14 );
	gfx.PutPixel( 39 + x,8 + y,0,146,14 );
	gfx.PutPixel( 40 + x,8 + y,0,146,14 );
	gfx.PutPixel( 41 + x,8 + y,0,146,14 );
	gfx.PutPixel( 42 + x,8 + y,0,146,14 );
	gfx.PutPixel( 43 + x,8 + y,0,146,14 );
	gfx.PutPixel( 44 + x,8 + y,0,146,14 );
	gfx.PutPixel( 45 + x,8 + y,0,146,14 );
	gfx.PutPixel( 53 + x,8 + y,0,146,14 );
	gfx.PutPixel( 54 + x,8 + y,0,146,14 );
	gfx.PutPixel( 55 + x,8 + y,0,146,14 );
	gfx.PutPixel( 56 + x,8 + y,0,146,14 );
	gfx.PutPixel( 64 + x,8 + y,0,146,14 );
	gfx.PutPixel( 65 + x,8 + y,0,146,14 );
	gfx.PutPixel( 66 + x,8 + y,0,146,14 );
	gfx.PutPixel( 67 + x,8 + y,0,146,14 );
	gfx.PutPixel( 80 + x,8 + y,0,146,14 );
	gfx.PutPixel( 81 + x,8 + y,0,146,14 );
	gfx.PutPixel( 82 + x,8 + y,0,146,14 );
	gfx.PutPixel( 34 + x,9 + y,0,146,14 );
	gfx.PutPixel( 35 + x,9 + y,0,146,14 );
	gfx.PutPixel( 36 + x,9 + y,0,146,14 );
	gfx.PutPixel( 37 + x,9 + y,0,146,14 );
	gfx.PutPixel( 38 + x,9 + y,0,146,14 );
	gfx.PutPixel( 39 + x,9 + y,0,146,14 );
	gfx.PutPixel( 40 + x,9 + y,0,146,14 );
	gfx.PutPixel( 41 + x,9 + y,0,146,14 );
	gfx.PutPixel( 42 + x,9 + y,0,146,14 );
	gfx.PutPixel( 43 + x,9 + y,0,146,14 );
	gfx.PutPixel( 44 + x,9 + y,0,146,14 );
	gfx.PutPixel( 45 + x,9 + y,0,146,14 );
	gfx.PutPixel( 54 + x,9 + y,0,146,14 );
	gfx.PutPixel( 55 + x,9 + y,0,146,14 );
	gfx.PutPixel( 56 + x,9 + y,0,146,14 );
	gfx.PutPixel( 57 + x,9 + y,0,146,14 );
	gfx.PutPixel( 64 + x,9 + y,0,146,14 );
	gfx.PutPixel( 65 + x,9 + y,0,146,14 );
	gfx.PutPixel( 66 + x,9 + y,0,146,14 );
	gfx.PutPixel( 80 + x,9 + y,0,146,14 );
	gfx.PutPixel( 81 + x,9 + y,0,146,14 );
	gfx.PutPixel( 82 + x,9 + y,0,146,14 );
	gfx.PutPixel( 83 + x,9 + y,0,118,11 );
	gfx.PutPixel( 34 + x,10 + y,0,146,14 );
	gfx.PutPixel( 35 + x,10 + y,0,146,14 );
	gfx.PutPixel( 36 + x,10 + y,0,146,14 );
	gfx.PutPixel( 37 + x,10 + y,0,146,14 );
	gfx.PutPixel( 38 + x,10 + y,0,146,14 );
	gfx.PutPixel( 39 + x,10 + y,0,146,14 );
	gfx.PutPixel( 40 + x,10 + y,0,146,14 );
	gfx.PutPixel( 41 + x,10 + y,0,146,14 );
	gfx.PutPixel( 42 + x,10 + y,0,146,14 );
	gfx.PutPixel( 43 + x,10 + y,0,146,14 );
	gfx.PutPixel( 44 + x,10 + y,0,146,14 );
	gfx.PutPixel( 45 + x,10 + y,0,146,14 );
	gfx.PutPixel( 55 + x,10 + y,0,146,14 );
	gfx.PutPixel( 56 + x,10 + y,0,146,14 );
	gfx.PutPixel( 57 + x,10 + y,0,146,14 );
	gfx.PutPixel( 64 + x,10 + y,0,146,14 );
	gfx.PutPixel( 65 + x,10 + y,0,146,14 );
	gfx.PutPixel( 66 + x,10 + y,0,146,14 );
	gfx.PutPixel( 81 + x,10 + y,0,146,14 );
	gfx.PutPixel( 82 + x,10 + y,0,146,14 );
	gfx.PutPixel( 83 + x,10 + y,0,146,14 );
	gfx.PutPixel( 28 + x,11 + y,0,146,14 );
	gfx.PutPixel( 29 + x,11 + y,0,146,14 );
	gfx.PutPixel( 30 + x,11 + y,0,146,14 );
	gfx.PutPixel( 31 + x,11 + y,0,146,14 );
	gfx.PutPixel( 32 + x,11 + y,0,146,14 );
	gfx.PutPixel( 35 + x,11 + y,0,146,14 );
	gfx.PutPixel( 36 + x,11 + y,0,146,14 );
	gfx.PutPixel( 37 + x,11 + y,0,146,14 );
	gfx.PutPixel( 38 + x,11 + y,0,146,14 );
	gfx.PutPixel( 39 + x,11 + y,0,146,14 );
	gfx.PutPixel( 40 + x,11 + y,0,146,14 );
	gfx.PutPixel( 41 + x,11 + y,0,146,14 );
	gfx.PutPixel( 42 + x,11 + y,0,146,14 );
	gfx.PutPixel( 43 + x,11 + y,0,146,14 );
	gfx.PutPixel( 44 + x,11 + y,0,146,14 );
	gfx.PutPixel( 55 + x,11 + y,0,146,14 );
	gfx.PutPixel( 56 + x,11 + y,0,146,14 );
	gfx.PutPixel( 57 + x,11 + y,0,146,14 );
	gfx.PutPixel( 58 + x,11 + y,0,146,14 );
	gfx.PutPixel( 64 + x,11 + y,0,146,14 );
	gfx.PutPixel( 65 + x,11 + y,0,146,14 );
	gfx.PutPixel( 66 + x,11 + y,0,146,14 );
	gfx.PutPixel( 81 + x,11 + y,0,146,14 );
	gfx.PutPixel( 82 + x,11 + y,0,146,14 );
	gfx.PutPixel( 83 + x,11 + y,0,146,14 );
	gfx.PutPixel( 27 + x,12 + y,0,146,14 );
	gfx.PutPixel( 28 + x,12 + y,0,146,14 );
	gfx.PutPixel( 29 + x,12 + y,0,146,14 );
	gfx.PutPixel( 30 + x,12 + y,0,146,14 );
	gfx.PutPixel( 31 + x,12 + y,0,146,14 );
	gfx.PutPixel( 32 + x,12 + y,0,146,14 );
	gfx.PutPixel( 33 + x,12 + y,0,146,14 );
	gfx.PutPixel( 35 + x,12 + y,0,142,13 );
	gfx.PutPixel( 36 + x,12 + y,0,146,14 );
	gfx.PutPixel( 37 + x,12 + y,0,146,14 );
	gfx.PutPixel( 38 + x,12 + y,0,146,14 );
	gfx.PutPixel( 39 + x,12 + y,0,146,14 );
	gfx.PutPixel( 40 + x,12 + y,0,146,14 );
	gfx.PutPixel( 41 + x,12 + y,0,146,14 );
	gfx.PutPixel( 42 + x,12 + y,0,146,14 );
	gfx.PutPixel( 43 + x,12 + y,0,146,14 );
	gfx.PutPixel( 56 + x,12 + y,0,146,14 );
	gfx.PutPixel( 57 + x,12 + y,0,146,14 );
	gfx.PutPixel( 58 + x,12 + y,0,146,14 );
	gfx.PutPixel( 64 + x,12 + y,0,146,14 );
	gfx.PutPixel( 65 + x,12 + y,0,146,14 );
	gfx.PutPixel( 66 + x,12 + y,0,146,14 );
	gfx.PutPixel( 67 + x,12 + y,0,146,14 );
	gfx.PutPixel( 68 + x,12 + y,0,146,14 );
	gfx.PutPixel( 69 + x,12 + y,0,146,14 );
	gfx.PutPixel( 70 + x,12 + y,0,146,14 );
	gfx.PutPixel( 71 + x,12 + y,0,146,14 );
	gfx.PutPixel( 72 + x,12 + y,0,146,14 );
	gfx.PutPixel( 73 + x,12 + y,0,146,14 );
	gfx.PutPixel( 74 + x,12 + y,0,146,14 );
	gfx.PutPixel( 75 + x,12 + y,0,146,14 );
	gfx.PutPixel( 76 + x,12 + y,0,146,14 );
	gfx.PutPixel( 77 + x,12 + y,0,146,14 );
	gfx.PutPixel( 78 + x,12 + y,0,146,14 );
	gfx.PutPixel( 79 + x,12 + y,0,146,14 );
	gfx.PutPixel( 80 + x,12 + y,0,146,14 );
	gfx.PutPixel( 81 + x,12 + y,0,146,14 );
	gfx.PutPixel( 82 + x,12 + y,0,146,14 );
	gfx.PutPixel( 83 + x,12 + y,0,146,14 );
	gfx.PutPixel( 26 + x,13 + y,0,146,14 );
	gfx.PutPixel( 27 + x,13 + y,0,146,14 );
	gfx.PutPixel( 28 + x,13 + y,0,146,14 );
	gfx.PutPixel( 29 + x,13 + y,0,146,14 );
	gfx.PutPixel( 30 + x,13 + y,0,146,14 );
	gfx.PutPixel( 31 + x,13 + y,0,146,14 );
	gfx.PutPixel( 32 + x,13 + y,0,146,14 );
	gfx.PutPixel( 33 + x,13 + y,0,146,14 );
	gfx.PutPixel( 34 + x,13 + y,0,146,14 );
	gfx.PutPixel( 37 + x,13 + y,0,146,14 );
	gfx.PutPixel( 38 + x,13 + y,0,146,14 );
	gfx.PutPixel( 39 + x,13 + y,0,146,14 );
	gfx.PutPixel( 40 + x,13 + y,0,146,14 );
	gfx.PutPixel( 41 + x,13 + y,0,146,14 );
	gfx.PutPixel( 42 + x,13 + y,0,146,14 );
	gfx.PutPixel( 56 + x,13 + y,0,142,13 );
	gfx.PutPixel( 57 + x,13 + y,0,146,14 );
	gfx.PutPixel( 58 + x,13 + y,0,146,14 );
	gfx.PutPixel( 59 + x,13 + y,0,146,14 );
	gfx.PutPixel( 64 + x,13 + y,0,146,14 );
	gfx.PutPixel( 65 + x,13 + y,0,146,14 );
	gfx.PutPixel( 66 + x,13 + y,0,146,14 );
	gfx.PutPixel( 67 + x,13 + y,0,146,14 );
	gfx.PutPixel( 68 + x,13 + y,0,146,14 );
	gfx.PutPixel( 69 + x,13 + y,0,146,14 );
	gfx.PutPixel( 70 + x,13 + y,0,146,14 );
	gfx.PutPixel( 71 + x,13 + y,0,146,14 );
	gfx.PutPixel( 72 + x,13 + y,0,146,14 );
	gfx.PutPixel( 73 + x,13 + y,0,146,14 );
	gfx.PutPixel( 74 + x,13 + y,0,146,14 );
	gfx.PutPixel( 75 + x,13 + y,0,146,14 );
	gfx.PutPixel( 76 + x,13 + y,0,146,14 );
	gfx.PutPixel( 77 + x,13 + y,0,146,14 );
	gfx.PutPixel( 78 + x,13 + y,0,146,14 );
	gfx.PutPixel( 79 + x,13 + y,0,146,14 );
	gfx.PutPixel( 80 + x,13 + y,0,146,14 );
	gfx.PutPixel( 81 + x,13 + y,0,146,14 );
	gfx.PutPixel( 82 + x,13 + y,0,146,14 );
	gfx.PutPixel( 83 + x,13 + y,0,146,14 );
	gfx.PutPixel( 25 + x,14 + y,0,146,14 );
	gfx.PutPixel( 26 + x,14 + y,0,146,14 );
	gfx.PutPixel( 27 + x,14 + y,0,146,14 );
	gfx.PutPixel( 28 + x,14 + y,0,146,14 );
	gfx.PutPixel( 29 + x,14 + y,0,146,14 );
	gfx.PutPixel( 30 + x,14 + y,0,146,14 );
	gfx.PutPixel( 31 + x,14 + y,0,146,14 );
	gfx.PutPixel( 32 + x,14 + y,0,146,14 );
	gfx.PutPixel( 33 + x,14 + y,0,146,14 );
	gfx.PutPixel( 34 + x,14 + y,0,146,14 );
	gfx.PutPixel( 57 + x,14 + y,0,146,14 );
	gfx.PutPixel( 58 + x,14 + y,0,146,14 );
	gfx.PutPixel( 59 + x,14 + y,0,146,14 );
	gfx.PutPixel( 60 + x,14 + y,0,146,14 );
	gfx.PutPixel( 64 + x,14 + y,0,146,14 );
	gfx.PutPixel( 65 + x,14 + y,0,146,14 );
	gfx.PutPixel( 66 + x,14 + y,0,146,14 );
	gfx.PutPixel( 67 + x,14 + y,0,146,14 );
	gfx.PutPixel( 68 + x,14 + y,0,146,14 );
	gfx.PutPixel( 69 + x,14 + y,0,146,14 );
	gfx.PutPixel( 70 + x,14 + y,0,146,14 );
	gfx.PutPixel( 71 + x,14 + y,0,146,14 );
	gfx.PutPixel( 72 + x,14 + y,0,146,14 );
	gfx.PutPixel( 73 + x,14 + y,0,146,14 );
	gfx.PutPixel( 74 + x,14 + y,0,146,14 );
	gfx.PutPixel( 75 + x,14 + y,0,146,14 );
	gfx.PutPixel( 76 + x,14 + y,0,146,14 );
	gfx.PutPixel( 77 + x,14 + y,0,146,14 );
	gfx.PutPixel( 78 + x,14 + y,0,146,14 );
	gfx.PutPixel( 79 + x,14 + y,0,146,14 );
	gfx.PutPixel( 80 + x,14 + y,0,146,14 );
	gfx.PutPixel( 81 + x,14 + y,0,146,14 );
	gfx.PutPixel( 82 + x,14 + y,0,146,14 );
	gfx.PutPixel( 83 + x,14 + y,0,146,14 );
	gfx.PutPixel( 24 + x,15 + y,0,25,2 );
	gfx.PutPixel( 25 + x,15 + y,0,146,14 );
	gfx.PutPixel( 26 + x,15 + y,0,146,14 );
	gfx.PutPixel( 27 + x,15 + y,0,146,14 );
	gfx.PutPixel( 28 + x,15 + y,0,146,14 );
	gfx.PutPixel( 29 + x,15 + y,0,146,14 );
	gfx.PutPixel( 30 + x,15 + y,0,146,14 );
	gfx.PutPixel( 31 + x,15 + y,0,146,14 );
	gfx.PutPixel( 32 + x,15 + y,0,146,14 );
	gfx.PutPixel( 33 + x,15 + y,0,146,14 );
	gfx.PutPixel( 34 + x,15 + y,0,146,14 );
	gfx.PutPixel( 58 + x,15 + y,0,146,14 );
	gfx.PutPixel( 59 + x,15 + y,0,146,14 );
	gfx.PutPixel( 60 + x,15 + y,0,146,14 );
	gfx.PutPixel( 64 + x,15 + y,0,146,14 );
	gfx.PutPixel( 65 + x,15 + y,0,146,14 );
	gfx.PutPixel( 66 + x,15 + y,0,146,14 );
	gfx.PutPixel( 81 + x,15 + y,0,146,14 );
	gfx.PutPixel( 82 + x,15 + y,0,146,14 );
	gfx.PutPixel( 83 + x,15 + y,0,146,14 );
	gfx.PutPixel( 24 + x,16 + y,0,146,14 );
	gfx.PutPixel( 25 + x,16 + y,0,146,14 );
	gfx.PutPixel( 26 + x,16 + y,0,146,14 );
	gfx.PutPixel( 27 + x,16 + y,0,146,14 );
	gfx.PutPixel( 28 + x,16 + y,0,146,14 );
	gfx.PutPixel( 29 + x,16 + y,0,146,14 );
	gfx.PutPixel( 30 + x,16 + y,0,146,14 );
	gfx.PutPixel( 31 + x,16 + y,0,146,14 );
	gfx.PutPixel( 32 + x,16 + y,0,146,14 );
	gfx.PutPixel( 33 + x,16 + y,0,146,14 );
	gfx.PutPixel( 34 + x,16 + y,0,146,14 );
	gfx.PutPixel( 58 + x,16 + y,0,146,14 );
	gfx.PutPixel( 59 + x,16 + y,0,146,14 );
	gfx.PutPixel( 60 + x,16 + y,0,146,14 );
	gfx.PutPixel( 61 + x,16 + y,0,146,14 );
	gfx.PutPixel( 64 + x,16 + y,0,146,14 );
	gfx.PutPixel( 65 + x,16 + y,0,146,14 );
	gfx.PutPixel( 66 + x,16 + y,0,146,14 );
	gfx.PutPixel( 81 + x,16 + y,0,146,14 );
	gfx.PutPixel( 82 + x,16 + y,0,146,14 );
	gfx.PutPixel( 83 + x,16 + y,0,146,14 );
	gfx.PutPixel( 23 + x,17 + y,0,146,14 );
	gfx.PutPixel( 24 + x,17 + y,0,146,14 );
	gfx.PutPixel( 25 + x,17 + y,0,146,14 );
	gfx.PutPixel( 26 + x,17 + y,0,146,14 );
	gfx.PutPixel( 27 + x,17 + y,0,146,14 );
	gfx.PutPixel( 28 + x,17 + y,0,146,14 );
	gfx.PutPixel( 29 + x,17 + y,0,146,14 );
	gfx.PutPixel( 30 + x,17 + y,0,146,14 );
	gfx.PutPixel( 31 + x,17 + y,0,146,14 );
	gfx.PutPixel( 32 + x,17 + y,0,146,14 );
	gfx.PutPixel( 33 + x,17 + y,0,146,14 );
	gfx.PutPixel( 34 + x,17 + y,0,146,14 );
	gfx.PutPixel( 59 + x,17 + y,0,146,14 );
	gfx.PutPixel( 60 + x,17 + y,0,146,14 );
	gfx.PutPixel( 61 + x,17 + y,0,146,14 );
	gfx.PutPixel( 62 + x,17 + y,0,146,14 );
	gfx.PutPixel( 64 + x,17 + y,0,146,14 );
	gfx.PutPixel( 65 + x,17 + y,0,146,14 );
	gfx.PutPixel( 66 + x,17 + y,0,146,14 );
	gfx.PutPixel( 81 + x,17 + y,0,146,14 );
	gfx.PutPixel( 82 + x,17 + y,0,146,14 );
	gfx.PutPixel( 83 + x,17 + y,0,146,14 );
	gfx.PutPixel( 22 + x,18 + y,0,146,14 );
	gfx.PutPixel( 23 + x,18 + y,0,146,14 );
	gfx.PutPixel( 24 + x,18 + y,0,146,14 );
	gfx.PutPixel( 25 + x,18 + y,0,146,14 );
	gfx.PutPixel( 26 + x,18 + y,0,146,14 );
	gfx.PutPixel( 27 + x,18 + y,0,146,14 );
	gfx.PutPixel( 28 + x,18 + y,0,146,14 );
	gfx.PutPixel( 29 + x,18 + y,0,146,14 );
	gfx.PutPixel( 30 + x,18 + y,0,146,14 );
	gfx.PutPixel( 31 + x,18 + y,0,146,14 );
	gfx.PutPixel( 32 + x,18 + y,0,146,14 );
	gfx.PutPixel( 33 + x,18 + y,0,146,14 );
	gfx.PutPixel( 34 + x,18 + y,0,146,14 );
	gfx.PutPixel( 60 + x,18 + y,0,146,14 );
	gfx.PutPixel( 61 + x,18 + y,0,146,14 );
	gfx.PutPixel( 62 + x,18 + y,0,146,14 );
	gfx.PutPixel( 64 + x,18 + y,0,146,14 );
	gfx.PutPixel( 65 + x,18 + y,0,146,14 );
	gfx.PutPixel( 66 + x,18 + y,0,146,14 );
	gfx.PutPixel( 81 + x,18 + y,0,146,14 );
	gfx.PutPixel( 82 + x,18 + y,0,146,14 );
	gfx.PutPixel( 83 + x,18 + y,0,146,14 );
	gfx.PutPixel( 21 + x,19 + y,0,146,14 );
	gfx.PutPixel( 22 + x,19 + y,0,146,14 );
	gfx.PutPixel( 23 + x,19 + y,0,146,14 );
	gfx.PutPixel( 24 + x,19 + y,0,146,14 );
	gfx.PutPixel( 25 + x,19 + y,0,146,14 );
	gfx.PutPixel( 26 + x,19 + y,0,146,14 );
	gfx.PutPixel( 27 + x,19 + y,0,146,14 );
	gfx.PutPixel( 28 + x,19 + y,0,146,14 );
	gfx.PutPixel( 29 + x,19 + y,0,146,14 );
	gfx.PutPixel( 30 + x,19 + y,0,146,14 );
	gfx.PutPixel( 31 + x,19 + y,0,146,14 );
	gfx.PutPixel( 32 + x,19 + y,0,146,14 );
	gfx.PutPixel( 33 + x,19 + y,0,146,14 );
	gfx.PutPixel( 34 + x,19 + y,0,146,14 );
	gfx.PutPixel( 60 + x,19 + y,0,146,14 );
	gfx.PutPixel( 61 + x,19 + y,0,146,14 );
	gfx.PutPixel( 62 + x,19 + y,0,146,14 );
	gfx.PutPixel( 63 + x,19 + y,0,146,14 );
	gfx.PutPixel( 64 + x,19 + y,0,146,14 );
	gfx.PutPixel( 65 + x,19 + y,0,146,14 );
	gfx.PutPixel( 66 + x,19 + y,0,146,14 );
	gfx.PutPixel( 81 + x,19 + y,0,146,14 );
	gfx.PutPixel( 82 + x,19 + y,0,146,14 );
	gfx.PutPixel( 83 + x,19 + y,0,146,14 );
	gfx.PutPixel( 20 + x,20 + y,0,146,14 );
	gfx.PutPixel( 21 + x,20 + y,0,146,14 );
	gfx.PutPixel( 22 + x,20 + y,0,146,14 );
	gfx.PutPixel( 23 + x,20 + y,0,146,14 );
	gfx.PutPixel( 24 + x,20 + y,0,146,14 );
	gfx.PutPixel( 25 + x,20 + y,0,146,14 );
	gfx.PutPixel( 26 + x,20 + y,0,146,14 );
	gfx.PutPixel( 27 + x,20 + y,0,146,14 );
	gfx.PutPixel( 28 + x,20 + y,0,146,14 );
	gfx.PutPixel( 29 + x,20 + y,0,146,14 );
	gfx.PutPixel( 30 + x,20 + y,0,146,14 );
	gfx.PutPixel( 31 + x,20 + y,0,146,14 );
	gfx.PutPixel( 32 + x,20 + y,0,146,14 );
	gfx.PutPixel( 33 + x,20 + y,0,146,14 );
	gfx.PutPixel( 34 + x,20 + y,0,146,14 );
	gfx.PutPixel( 61 + x,20 + y,0,146,14 );
	gfx.PutPixel( 62 + x,20 + y,0,146,14 );
	gfx.PutPixel( 63 + x,20 + y,0,146,14 );
	gfx.PutPixel( 64 + x,20 + y,0,146,14 );
	gfx.PutPixel( 65 + x,20 + y,0,146,14 );
	gfx.PutPixel( 66 + x,20 + y,0,146,14 );
	gfx.PutPixel( 81 + x,20 + y,0,146,14 );
	gfx.PutPixel( 82 + x,20 + y,0,146,14 );
	gfx.PutPixel( 83 + x,20 + y,0,146,14 );
	gfx.PutPixel( 19 + x,21 + y,0,146,14 );
	gfx.PutPixel( 20 + x,21 + y,0,146,14 );
	gfx.PutPixel( 21 + x,21 + y,0,146,14 );
	gfx.PutPixel( 22 + x,21 + y,0,146,14 );
	gfx.PutPixel( 23 + x,21 + y,0,146,14 );
	gfx.PutPixel( 24 + x,21 + y,0,146,14 );
	gfx.PutPixel( 25 + x,21 + y,0,146,14 );
	gfx.PutPixel( 26 + x,21 + y,0,146,14 );
	gfx.PutPixel( 27 + x,21 + y,0,146,14 );
	gfx.PutPixel( 28 + x,21 + y,0,146,14 );
	gfx.PutPixel( 29 + x,21 + y,0,146,14 );
	gfx.PutPixel( 30 + x,21 + y,0,146,14 );
	gfx.PutPixel( 31 + x,21 + y,0,146,14 );
	gfx.PutPixel( 32 + x,21 + y,0,146,14 );
	gfx.PutPixel( 33 + x,21 + y,0,146,14 );
	gfx.PutPixel( 34 + x,21 + y,0,146,14 );
	gfx.PutPixel( 61 + x,21 + y,0,146,14 );
	gfx.PutPixel( 62 + x,21 + y,0,146,14 );
	gfx.PutPixel( 63 + x,21 + y,0,146,14 );
	gfx.PutPixel( 64 + x,21 + y,0,146,14 );
	gfx.PutPixel( 65 + x,21 + y,0,146,14 );
	gfx.PutPixel( 66 + x,21 + y,0,146,14 );
	gfx.PutPixel( 81 + x,21 + y,0,146,14 );
	gfx.PutPixel( 82 + x,21 + y,0,146,14 );
	gfx.PutPixel( 83 + x,21 + y,0,146,14 );
	gfx.PutPixel( 18 + x,22 + y,0,146,14 );
	gfx.PutPixel( 19 + x,22 + y,0,146,14 );
	gfx.PutPixel( 20 + x,22 + y,0,146,14 );
	gfx.PutPixel( 21 + x,22 + y,0,146,14 );
	gfx.PutPixel( 22 + x,22 + y,0,146,14 );
	gfx.PutPixel( 23 + x,22 + y,0,146,14 );
	gfx.PutPixel( 24 + x,22 + y,0,146,14 );
	gfx.PutPixel( 25 + x,22 + y,0,146,14 );
	gfx.PutPixel( 26 + x,22 + y,0,146,14 );
	gfx.PutPixel( 27 + x,22 + y,0,146,14 );
	gfx.PutPixel( 28 + x,22 + y,0,146,14 );
	gfx.PutPixel( 29 + x,22 + y,0,146,14 );
	gfx.PutPixel( 30 + x,22 + y,0,146,14 );
	gfx.PutPixel( 31 + x,22 + y,0,146,14 );
	gfx.PutPixel( 32 + x,22 + y,0,146,14 );
	gfx.PutPixel( 33 + x,22 + y,0,146,14 );
	gfx.PutPixel( 34 + x,22 + y,0,146,14 );
	gfx.PutPixel( 35 + x,22 + y,0,25,2 );
	gfx.PutPixel( 62 + x,22 + y,0,146,14 );
	gfx.PutPixel( 63 + x,22 + y,0,146,14 );
	gfx.PutPixel( 64 + x,22 + y,0,146,14 );
	gfx.PutPixel( 65 + x,22 + y,0,146,14 );
	gfx.PutPixel( 66 + x,22 + y,0,146,14 );
	gfx.PutPixel( 81 + x,22 + y,0,146,14 );
	gfx.PutPixel( 82 + x,22 + y,0,146,14 );
	gfx.PutPixel( 83 + x,22 + y,0,146,14 );
	gfx.PutPixel( 17 + x,23 + y,0,3,0 );
	gfx.PutPixel( 18 + x,23 + y,0,146,14 );
	gfx.PutPixel( 19 + x,23 + y,0,146,14 );
	gfx.PutPixel( 20 + x,23 + y,0,146,14 );
	gfx.PutPixel( 21 + x,23 + y,0,146,14 );
	gfx.PutPixel( 22 + x,23 + y,0,146,14 );
	gfx.PutPixel( 23 + x,23 + y,0,146,14 );
	gfx.PutPixel( 24 + x,23 + y,0,146,14 );
	gfx.PutPixel( 25 + x,23 + y,0,146,14 );
	gfx.PutPixel( 26 + x,23 + y,0,146,14 );
	gfx.PutPixel( 27 + x,23 + y,0,146,14 );
	gfx.PutPixel( 28 + x,23 + y,0,146,14 );
	gfx.PutPixel( 30 + x,23 + y,0,146,14 );
	gfx.PutPixel( 31 + x,23 + y,0,146,14 );
	gfx.PutPixel( 32 + x,23 + y,0,146,14 );
	gfx.PutPixel( 33 + x,23 + y,0,146,14 );
	gfx.PutPixel( 34 + x,23 + y,0,146,14 );
	gfx.PutPixel( 35 + x,23 + y,0,25,2 );
	gfx.PutPixel( 63 + x,23 + y,0,146,14 );
	gfx.PutPixel( 64 + x,23 + y,0,146,14 );
	gfx.PutPixel( 65 + x,23 + y,0,146,14 );
	gfx.PutPixel( 66 + x,23 + y,0,146,14 );
	gfx.PutPixel( 81 + x,23 + y,0,146,14 );
	gfx.PutPixel( 82 + x,23 + y,0,146,14 );
	gfx.PutPixel( 83 + x,23 + y,0,146,14 );
	gfx.PutPixel( 17 + x,24 + y,0,146,14 );
	gfx.PutPixel( 18 + x,24 + y,0,146,14 );
	gfx.PutPixel( 19 + x,24 + y,0,146,14 );
	gfx.PutPixel( 20 + x,24 + y,0,146,14 );
	gfx.PutPixel( 21 + x,24 + y,0,146,14 );
	gfx.PutPixel( 22 + x,24 + y,0,146,14 );
	gfx.PutPixel( 23 + x,24 + y,0,146,14 );
	gfx.PutPixel( 24 + x,24 + y,0,146,14 );
	gfx.PutPixel( 25 + x,24 + y,0,146,14 );
	gfx.PutPixel( 26 + x,24 + y,0,146,14 );
	gfx.PutPixel( 27 + x,24 + y,0,146,14 );
	gfx.PutPixel( 30 + x,24 + y,0,146,14 );
	gfx.PutPixel( 31 + x,24 + y,0,146,14 );
	gfx.PutPixel( 32 + x,24 + y,0,146,14 );
	gfx.PutPixel( 33 + x,24 + y,0,146,14 );
	gfx.PutPixel( 34 + x,24 + y,0,146,14 );
	gfx.PutPixel( 35 + x,24 + y,0,146,14 );
	gfx.PutPixel( 36 + x,24 + y,0,146,14 );
	gfx.PutPixel( 37 + x,24 + y,0,146,14 );
	gfx.PutPixel( 38 + x,24 + y,0,146,14 );
	gfx.PutPixel( 39 + x,24 + y,0,146,14 );
	gfx.PutPixel( 40 + x,24 + y,0,146,14 );
	gfx.PutPixel( 41 + x,24 + y,0,146,14 );
	gfx.PutPixel( 42 + x,24 + y,0,146,14 );
	gfx.PutPixel( 43 + x,24 + y,0,146,14 );
	gfx.PutPixel( 44 + x,24 + y,0,146,14 );
	gfx.PutPixel( 45 + x,24 + y,0,146,14 );
	gfx.PutPixel( 46 + x,24 + y,0,146,14 );
	gfx.PutPixel( 47 + x,24 + y,0,146,14 );
	gfx.PutPixel( 48 + x,24 + y,0,146,14 );
	gfx.PutPixel( 49 + x,24 + y,0,146,14 );
	gfx.PutPixel( 50 + x,24 + y,0,146,14 );
	gfx.PutPixel( 51 + x,24 + y,0,146,14 );
	gfx.PutPixel( 52 + x,24 + y,0,146,14 );
	gfx.PutPixel( 53 + x,24 + y,0,146,14 );
	gfx.PutPixel( 54 + x,24 + y,0,146,14 );
	gfx.PutPixel( 55 + x,24 + y,0,146,14 );
	gfx.PutPixel( 56 + x,24 + y,0,146,14 );
	gfx.PutPixel( 57 + x,24 + y,0,146,14 );
	gfx.PutPixel( 58 + x,24 + y,0,146,14 );
	gfx.PutPixel( 59 + x,24 + y,0,146,14 );
	gfx.PutPixel( 60 + x,24 + y,0,146,14 );
	gfx.PutPixel( 61 + x,24 + y,0,146,14 );
	gfx.PutPixel( 62 + x,24 + y,0,146,14 );
	gfx.PutPixel( 63 + x,24 + y,0,146,14 );
	gfx.PutPixel( 64 + x,24 + y,0,146,14 );
	gfx.PutPixel( 65 + x,24 + y,0,146,14 );
	gfx.PutPixel( 66 + x,24 + y,0,146,14 );
	gfx.PutPixel( 81 + x,24 + y,0,146,14 );
	gfx.PutPixel( 82 + x,24 + y,0,146,14 );
	gfx.PutPixel( 83 + x,24 + y,0,146,14 );
	gfx.PutPixel( 16 + x,25 + y,0,146,14 );
	gfx.PutPixel( 17 + x,25 + y,0,146,14 );
	gfx.PutPixel( 18 + x,25 + y,0,146,14 );
	gfx.PutPixel( 19 + x,25 + y,0,146,14 );
	gfx.PutPixel( 20 + x,25 + y,0,146,14 );
	gfx.PutPixel( 21 + x,25 + y,0,146,14 );
	gfx.PutPixel( 22 + x,25 + y,0,146,14 );
	gfx.PutPixel( 23 + x,25 + y,0,146,14 );
	gfx.PutPixel( 24 + x,25 + y,0,146,14 );
	gfx.PutPixel( 25 + x,25 + y,0,146,14 );
	gfx.PutPixel( 26 + x,25 + y,0,146,14 );
	gfx.PutPixel( 30 + x,25 + y,0,146,14 );
	gfx.PutPixel( 31 + x,25 + y,0,146,14 );
	gfx.PutPixel( 32 + x,25 + y,0,146,14 );
	gfx.PutPixel( 33 + x,25 + y,0,146,14 );
	gfx.PutPixel( 34 + x,25 + y,0,146,14 );
	gfx.PutPixel( 35 + x,25 + y,0,146,14 );
	gfx.PutPixel( 36 + x,25 + y,0,146,14 );
	gfx.PutPixel( 37 + x,25 + y,0,146,14 );
	gfx.PutPixel( 38 + x,25 + y,0,146,14 );
	gfx.PutPixel( 39 + x,25 + y,0,146,14 );
	gfx.PutPixel( 40 + x,25 + y,0,146,14 );
	gfx.PutPixel( 41 + x,25 + y,0,146,14 );
	gfx.PutPixel( 42 + x,25 + y,0,146,14 );
	gfx.PutPixel( 43 + x,25 + y,0,146,14 );
	gfx.PutPixel( 44 + x,25 + y,0,146,14 );
	gfx.PutPixel( 45 + x,25 + y,0,146,14 );
	gfx.PutPixel( 46 + x,25 + y,0,146,14 );
	gfx.PutPixel( 47 + x,25 + y,0,146,14 );
	gfx.PutPixel( 48 + x,25 + y,0,146,14 );
	gfx.PutPixel( 49 + x,25 + y,0,146,14 );
	gfx.PutPixel( 50 + x,25 + y,0,146,14 );
	gfx.PutPixel( 51 + x,25 + y,0,146,14 );
	gfx.PutPixel( 52 + x,25 + y,0,146,14 );
	gfx.PutPixel( 53 + x,25 + y,0,146,14 );
	gfx.PutPixel( 54 + x,25 + y,0,146,14 );
	gfx.PutPixel( 55 + x,25 + y,0,146,14 );
	gfx.PutPixel( 56 + x,25 + y,0,146,14 );
	gfx.PutPixel( 57 + x,25 + y,0,146,14 );
	gfx.PutPixel( 58 + x,25 + y,0,146,14 );
	gfx.PutPixel( 59 + x,25 + y,0,146,14 );
	gfx.PutPixel( 60 + x,25 + y,0,146,14 );
	gfx.PutPixel( 61 + x,25 + y,0,146,14 );
	gfx.PutPixel( 62 + x,25 + y,0,146,14 );
	gfx.PutPixel( 63 + x,25 + y,0,146,14 );
	gfx.PutPixel( 64 + x,25 + y,0,146,14 );
	gfx.PutPixel( 65 + x,25 + y,0,146,14 );
	gfx.PutPixel( 66 + x,25 + y,0,146,14 );
	gfx.PutPixel( 81 + x,25 + y,0,146,14 );
	gfx.PutPixel( 82 + x,25 + y,0,146,14 );
	gfx.PutPixel( 83 + x,25 + y,0,146,14 );
	gfx.PutPixel( 15 + x,26 + y,0,146,14 );
	gfx.PutPixel( 16 + x,26 + y,0,146,14 );
	gfx.PutPixel( 17 + x,26 + y,0,146,14 );
	gfx.PutPixel( 18 + x,26 + y,0,146,14 );
	gfx.PutPixel( 19 + x,26 + y,0,146,14 );
	gfx.PutPixel( 20 + x,26 + y,0,146,14 );
	gfx.PutPixel( 21 + x,26 + y,0,146,14 );
	gfx.PutPixel( 22 + x,26 + y,0,146,14 );
	gfx.PutPixel( 23 + x,26 + y,0,146,14 );
	gfx.PutPixel( 24 + x,26 + y,0,146,14 );
	gfx.PutPixel( 25 + x,26 + y,0,146,14 );
	gfx.PutPixel( 30 + x,26 + y,0,146,14 );
	gfx.PutPixel( 31 + x,26 + y,0,146,14 );
	gfx.PutPixel( 32 + x,26 + y,0,146,14 );
	gfx.PutPixel( 33 + x,26 + y,0,146,14 );
	gfx.PutPixel( 34 + x,26 + y,0,146,14 );
	gfx.PutPixel( 35 + x,26 + y,0,146,14 );
	gfx.PutPixel( 36 + x,26 + y,0,146,14 );
	gfx.PutPixel( 37 + x,26 + y,0,146,14 );
	gfx.PutPixel( 38 + x,26 + y,0,146,14 );
	gfx.PutPixel( 39 + x,26 + y,0,146,14 );
	gfx.PutPixel( 40 + x,26 + y,0,146,14 );
	gfx.PutPixel( 41 + x,26 + y,0,146,14 );
	gfx.PutPixel( 42 + x,26 + y,0,146,14 );
	gfx.PutPixel( 43 + x,26 + y,0,146,14 );
	gfx.PutPixel( 44 + x,26 + y,0,146,14 );
	gfx.PutPixel( 45 + x,26 + y,0,146,14 );
	gfx.PutPixel( 46 + x,26 + y,0,146,14 );
	gfx.PutPixel( 47 + x,26 + y,0,146,14 );
	gfx.PutPixel( 48 + x,26 + y,0,146,14 );
	gfx.PutPixel( 49 + x,26 + y,0,146,14 );
	gfx.PutPixel( 50 + x,26 + y,0,146,14 );
	gfx.PutPixel( 51 + x,26 + y,0,146,14 );
	gfx.PutPixel( 52 + x,26 + y,0,146,14 );
	gfx.PutPixel( 53 + x,26 + y,0,146,14 );
	gfx.PutPixel( 54 + x,26 + y,0,146,14 );
	gfx.PutPixel( 55 + x,26 + y,0,146,14 );
	gfx.PutPixel( 56 + x,26 + y,0,146,14 );
	gfx.PutPixel( 57 + x,26 + y,0,146,14 );
	gfx.PutPixel( 58 + x,26 + y,0,146,14 );
	gfx.PutPixel( 59 + x,26 + y,0,146,14 );
	gfx.PutPixel( 60 + x,26 + y,0,146,14 );
	gfx.PutPixel( 61 + x,26 + y,0,146,14 );
	gfx.PutPixel( 62 + x,26 + y,0,146,14 );
	gfx.PutPixel( 63 + x,26 + y,0,146,14 );
	gfx.PutPixel( 64 + x,26 + y,0,146,14 );
	gfx.PutPixel( 65 + x,26 + y,0,146,14 );
	gfx.PutPixel( 66 + x,26 + y,0,146,14 );
	gfx.PutPixel( 81 + x,26 + y,0,146,14 );
	gfx.PutPixel( 82 + x,26 + y,0,146,14 );
	gfx.PutPixel( 83 + x,26 + y,0,146,14 );
	gfx.PutPixel( 14 + x,27 + y,0,146,14 );
	gfx.PutPixel( 15 + x,27 + y,0,146,14 );
	gfx.PutPixel( 16 + x,27 + y,0,146,14 );
	gfx.PutPixel( 17 + x,27 + y,0,146,14 );
	gfx.PutPixel( 18 + x,27 + y,0,146,14 );
	gfx.PutPixel( 19 + x,27 + y,0,146,14 );
	gfx.PutPixel( 20 + x,27 + y,0,146,14 );
	gfx.PutPixel( 21 + x,27 + y,0,146,14 );
	gfx.PutPixel( 22 + x,27 + y,0,146,14 );
	gfx.PutPixel( 23 + x,27 + y,0,146,14 );
	gfx.PutPixel( 24 + x,27 + y,0,146,14 );
	gfx.PutPixel( 30 + x,27 + y,0,146,14 );
	gfx.PutPixel( 31 + x,27 + y,0,146,14 );
	gfx.PutPixel( 32 + x,27 + y,0,146,14 );
	gfx.PutPixel( 33 + x,27 + y,0,146,14 );
	gfx.PutPixel( 34 + x,27 + y,0,146,14 );
	gfx.PutPixel( 35 + x,27 + y,0,146,14 );
	gfx.PutPixel( 36 + x,27 + y,0,146,14 );
	gfx.PutPixel( 37 + x,27 + y,0,146,14 );
	gfx.PutPixel( 38 + x,27 + y,0,146,14 );
	gfx.PutPixel( 39 + x,27 + y,0,146,14 );
	gfx.PutPixel( 40 + x,27 + y,0,146,14 );
	gfx.PutPixel( 41 + x,27 + y,0,146,14 );
	gfx.PutPixel( 42 + x,27 + y,0,146,14 );
	gfx.PutPixel( 43 + x,27 + y,0,146,14 );
	gfx.PutPixel( 44 + x,27 + y,0,146,14 );
	gfx.PutPixel( 45 + x,27 + y,0,146,14 );
	gfx.PutPixel( 46 + x,27 + y,0,146,14 );
	gfx.PutPixel( 64 + x,27 + y,0,146,14 );
	gfx.PutPixel( 65 + x,27 + y,0,146,14 );
	gfx.PutPixel( 66 + x,27 + y,0,146,14 );
	gfx.PutPixel( 81 + x,27 + y,0,146,14 );
	gfx.PutPixel( 82 + x,27 + y,0,146,14 );
	gfx.PutPixel( 83 + x,27 + y,0,146,14 );
	gfx.PutPixel( 13 + x,28 + y,0,146,14 );
	gfx.PutPixel( 14 + x,28 + y,0,146,14 );
	gfx.PutPixel( 15 + x,28 + y,0,146,14 );
	gfx.PutPixel( 16 + x,28 + y,0,146,14 );
	gfx.PutPixel( 17 + x,28 + y,0,146,14 );
	gfx.PutPixel( 18 + x,28 + y,0,146,14 );
	gfx.PutPixel( 19 + x,28 + y,0,146,14 );
	gfx.PutPixel( 20 + x,28 + y,0,146,14 );
	gfx.PutPixel( 21 + x,28 + y,0,146,14 );
	gfx.PutPixel( 22 + x,28 + y,0,146,14 );
	gfx.PutPixel( 23 + x,28 + y,0,146,14 );
	gfx.PutPixel( 30 + x,28 + y,0,146,14 );
	gfx.PutPixel( 31 + x,28 + y,0,146,14 );
	gfx.PutPixel( 32 + x,28 + y,0,146,14 );
	gfx.PutPixel( 33 + x,28 + y,0,146,14 );
	gfx.PutPixel( 34 + x,28 + y,0,146,14 );
	gfx.PutPixel( 35 + x,28 + y,0,146,14 );
	gfx.PutPixel( 36 + x,28 + y,0,146,14 );
	gfx.PutPixel( 37 + x,28 + y,0,146,14 );
	gfx.PutPixel( 38 + x,28 + y,0,146,14 );
	gfx.PutPixel( 39 + x,28 + y,0,146,14 );
	gfx.PutPixel( 40 + x,28 + y,0,146,14 );
	gfx.PutPixel( 41 + x,28 + y,0,146,14 );
	gfx.PutPixel( 42 + x,28 + y,0,146,14 );
	gfx.PutPixel( 43 + x,28 + y,0,146,14 );
	gfx.PutPixel( 44 + x,28 + y,0,146,14 );
	gfx.PutPixel( 45 + x,28 + y,0,146,14 );
	gfx.PutPixel( 46 + x,28 + y,0,146,14 );
	gfx.PutPixel( 47 + x,28 + y,0,146,14 );
	gfx.PutPixel( 64 + x,28 + y,0,146,14 );
	gfx.PutPixel( 65 + x,28 + y,0,146,14 );
	gfx.PutPixel( 66 + x,28 + y,0,146,14 );
	gfx.PutPixel( 81 + x,28 + y,0,146,14 );
	gfx.PutPixel( 82 + x,28 + y,0,146,14 );
	gfx.PutPixel( 83 + x,28 + y,0,146,14 );
	gfx.PutPixel( 12 + x,29 + y,0,146,14 );
	gfx.PutPixel( 13 + x,29 + y,0,146,14 );
	gfx.PutPixel( 14 + x,29 + y,0,146,14 );
	gfx.PutPixel( 15 + x,29 + y,0,146,14 );
	gfx.PutPixel( 16 + x,29 + y,0,146,14 );
	gfx.PutPixel( 17 + x,29 + y,0,146,14 );
	gfx.PutPixel( 18 + x,29 + y,0,146,14 );
	gfx.PutPixel( 19 + x,29 + y,0,146,14 );
	gfx.PutPixel( 20 + x,29 + y,0,146,14 );
	gfx.PutPixel( 21 + x,29 + y,0,146,14 );
	gfx.PutPixel( 22 + x,29 + y,0,146,14 );
	gfx.PutPixel( 23 + x,29 + y,0,146,14 );
	gfx.PutPixel( 30 + x,29 + y,0,146,14 );
	gfx.PutPixel( 31 + x,29 + y,0,146,14 );
	gfx.PutPixel( 32 + x,29 + y,0,146,14 );
	gfx.PutPixel( 33 + x,29 + y,0,146,14 );
	gfx.PutPixel( 34 + x,29 + y,0,146,14 );
	gfx.PutPixel( 35 + x,29 + y,0,146,14 );
	gfx.PutPixel( 36 + x,29 + y,0,146,14 );
	gfx.PutPixel( 37 + x,29 + y,0,146,14 );
	gfx.PutPixel( 38 + x,29 + y,0,146,14 );
	gfx.PutPixel( 39 + x,29 + y,0,146,14 );
	gfx.PutPixel( 40 + x,29 + y,0,146,14 );
	gfx.PutPixel( 41 + x,29 + y,0,146,14 );
	gfx.PutPixel( 42 + x,29 + y,0,146,14 );
	gfx.PutPixel( 43 + x,29 + y,0,146,14 );
	gfx.PutPixel( 44 + x,29 + y,0,146,14 );
	gfx.PutPixel( 45 + x,29 + y,0,146,14 );
	gfx.PutPixel( 46 + x,29 + y,0,146,14 );
	gfx.PutPixel( 47 + x,29 + y,0,146,14 );
	gfx.PutPixel( 63 + x,29 + y,0,25,2 );
	gfx.PutPixel( 64 + x,29 + y,0,146,14 );
	gfx.PutPixel( 65 + x,29 + y,0,146,14 );
	gfx.PutPixel( 66 + x,29 + y,0,146,14 );
	gfx.PutPixel( 81 + x,29 + y,0,146,14 );
	gfx.PutPixel( 82 + x,29 + y,0,146,14 );
	gfx.PutPixel( 83 + x,29 + y,0,146,14 );
	gfx.PutPixel( 11 + x,30 + y,0,146,14 );
	gfx.PutPixel( 12 + x,30 + y,0,146,14 );
	gfx.PutPixel( 13 + x,30 + y,0,146,14 );
	gfx.PutPixel( 14 + x,30 + y,0,146,14 );
	gfx.PutPixel( 15 + x,30 + y,0,146,14 );
	gfx.PutPixel( 16 + x,30 + y,0,146,14 );
	gfx.PutPixel( 17 + x,30 + y,0,146,14 );
	gfx.PutPixel( 18 + x,30 + y,0,146,14 );
	gfx.PutPixel( 19 + x,30 + y,0,146,14 );
	gfx.PutPixel( 20 + x,30 + y,0,146,14 );
	gfx.PutPixel( 21 + x,30 + y,0,146,14 );
	gfx.PutPixel( 22 + x,30 + y,0,146,14 );
	gfx.PutPixel( 30 + x,30 + y,0,146,14 );
	gfx.PutPixel( 31 + x,30 + y,0,146,14 );
	gfx.PutPixel( 32 + x,30 + y,0,146,14 );
	gfx.PutPixel( 33 + x,30 + y,0,146,14 );
	gfx.PutPixel( 34 + x,30 + y,0,146,14 );
	gfx.PutPixel( 35 + x,30 + y,0,146,14 );
	gfx.PutPixel( 36 + x,30 + y,0,146,14 );
	gfx.PutPixel( 37 + x,30 + y,0,146,14 );
	gfx.PutPixel( 38 + x,30 + y,0,146,14 );
	gfx.PutPixel( 39 + x,30 + y,0,146,14 );
	gfx.PutPixel( 40 + x,30 + y,0,146,14 );
	gfx.PutPixel( 41 + x,30 + y,0,146,14 );
	gfx.PutPixel( 42 + x,30 + y,0,146,14 );
	gfx.PutPixel( 43 + x,30 + y,0,146,14 );
	gfx.PutPixel( 44 + x,30 + y,0,146,14 );
	gfx.PutPixel( 45 + x,30 + y,0,146,14 );
	gfx.PutPixel( 46 + x,30 + y,0,146,14 );
	gfx.PutPixel( 47 + x,30 + y,0,146,14 );
	gfx.PutPixel( 63 + x,30 + y,0,146,14 );
	gfx.PutPixel( 64 + x,30 + y,0,146,14 );
	gfx.PutPixel( 65 + x,30 + y,0,146,14 );
	gfx.PutPixel( 66 + x,30 + y,0,146,14 );
	gfx.PutPixel( 80 + x,30 + y,0,25,2 );
	gfx.PutPixel( 81 + x,30 + y,0,146,14 );
	gfx.PutPixel( 82 + x,30 + y,0,146,14 );
	gfx.PutPixel( 83 + x,30 + y,0,146,14 );
	gfx.PutPixel( 10 + x,31 + y,0,70,6 );
	gfx.PutPixel( 11 + x,31 + y,0,146,14 );
	gfx.PutPixel( 12 + x,31 + y,0,146,14 );
	gfx.PutPixel( 13 + x,31 + y,0,146,14 );
	gfx.PutPixel( 14 + x,31 + y,0,146,14 );
	gfx.PutPixel( 15 + x,31 + y,0,146,14 );
	gfx.PutPixel( 16 + x,31 + y,0,146,14 );
	gfx.PutPixel( 17 + x,31 + y,0,146,14 );
	gfx.PutPixel( 18 + x,31 + y,0,146,14 );
	gfx.PutPixel( 19 + x,31 + y,0,146,14 );
	gfx.PutPixel( 20 + x,31 + y,0,146,14 );
	gfx.PutPixel( 21 + x,31 + y,0,146,14 );
	gfx.PutPixel( 30 + x,31 + y,0,146,14 );
	gfx.PutPixel( 31 + x,31 + y,0,146,14 );
	gfx.PutPixel( 32 + x,31 + y,0,146,14 );
	gfx.PutPixel( 33 + x,31 + y,0,146,14 );
	gfx.PutPixel( 34 + x,31 + y,0,146,14 );
	gfx.PutPixel( 35 + x,31 + y,0,146,14 );
	gfx.PutPixel( 36 + x,31 + y,0,146,14 );
	gfx.PutPixel( 37 + x,31 + y,0,146,14 );
	gfx.PutPixel( 38 + x,31 + y,0,146,14 );
	gfx.PutPixel( 39 + x,31 + y,0,146,14 );
	gfx.PutPixel( 40 + x,31 + y,0,146,14 );
	gfx.PutPixel( 41 + x,31 + y,0,146,14 );
	gfx.PutPixel( 42 + x,31 + y,0,146,14 );
	gfx.PutPixel( 43 + x,31 + y,0,146,14 );
	gfx.PutPixel( 44 + x,31 + y,0,146,14 );
	gfx.PutPixel( 45 + x,31 + y,0,146,14 );
	gfx.PutPixel( 46 + x,31 + y,0,146,14 );
	gfx.PutPixel( 47 + x,31 + y,0,146,14 );
	gfx.PutPixel( 63 + x,31 + y,0,146,14 );
	gfx.PutPixel( 64 + x,31 + y,0,146,14 );
	gfx.PutPixel( 65 + x,31 + y,0,146,14 );
	gfx.PutPixel( 66 + x,31 + y,0,146,14 );
	gfx.PutPixel( 67 + x,31 + y,0,146,14 );
	gfx.PutPixel( 80 + x,31 + y,0,146,14 );
	gfx.PutPixel( 81 + x,31 + y,0,146,14 );
	gfx.PutPixel( 82 + x,31 + y,0,146,14 );
	gfx.PutPixel( 10 + x,32 + y,0,146,14 );
	gfx.PutPixel( 11 + x,32 + y,0,146,14 );
	gfx.PutPixel( 12 + x,32 + y,0,146,14 );
	gfx.PutPixel( 13 + x,32 + y,0,146,14 );
	gfx.PutPixel( 14 + x,32 + y,0,146,14 );
	gfx.PutPixel( 15 + x,32 + y,0,146,14 );
	gfx.PutPixel( 16 + x,32 + y,0,146,14 );
	gfx.PutPixel( 17 + x,32 + y,0,146,14 );
	gfx.PutPixel( 18 + x,32 + y,0,146,14 );
	gfx.PutPixel( 19 + x,32 + y,0,146,14 );
	gfx.PutPixel( 20 + x,32 + y,0,146,14 );
	gfx.PutPixel( 32 + x,32 + y,0,146,14 );
	gfx.PutPixel( 33 + x,32 + y,0,146,14 );
	gfx.PutPixel( 34 + x,32 + y,0,146,14 );
	gfx.PutPixel( 35 + x,32 + y,0,146,14 );
	gfx.PutPixel( 36 + x,32 + y,0,146,14 );
	gfx.PutPixel( 37 + x,32 + y,0,146,14 );
	gfx.PutPixel( 38 + x,32 + y,0,146,14 );
	gfx.PutPixel( 39 + x,32 + y,0,146,14 );
	gfx.PutPixel( 40 + x,32 + y,0,146,14 );
	gfx.PutPixel( 41 + x,32 + y,0,146,14 );
	gfx.PutPixel( 42 + x,32 + y,0,146,14 );
	gfx.PutPixel( 43 + x,32 + y,0,146,14 );
	gfx.PutPixel( 44 + x,32 + y,0,146,14 );
	gfx.PutPixel( 45 + x,32 + y,0,146,14 );
	gfx.PutPixel( 46 + x,32 + y,0,118,11 );
	gfx.PutPixel( 62 + x,32 + y,0,146,14 );
	gfx.PutPixel( 63 + x,32 + y,0,146,14 );
	gfx.PutPixel( 64 + x,32 + y,0,146,14 );
	gfx.PutPixel( 65 + x,32 + y,0,146,14 );
	gfx.PutPixel( 66 + x,32 + y,0,146,14 );
	gfx.PutPixel( 67 + x,32 + y,0,146,14 );
	gfx.PutPixel( 68 + x,32 + y,0,25,2 );
	gfx.PutPixel( 79 + x,32 + y,0,146,14 );
	gfx.PutPixel( 80 + x,32 + y,0,146,14 );
	gfx.PutPixel( 81 + x,32 + y,0,146,14 );
	gfx.PutPixel( 82 + x,32 + y,0,146,14 );
	gfx.PutPixel( 9 + x,33 + y,0,146,14 );
	gfx.PutPixel( 10 + x,33 + y,0,146,14 );
	gfx.PutPixel( 11 + x,33 + y,0,146,14 );
	gfx.PutPixel( 12 + x,33 + y,0,146,14 );
	gfx.PutPixel( 13 + x,33 + y,0,146,14 );
	gfx.PutPixel( 14 + x,33 + y,0,146,14 );
	gfx.PutPixel( 15 + x,33 + y,0,146,14 );
	gfx.PutPixel( 16 + x,33 + y,0,146,14 );
	gfx.PutPixel( 17 + x,33 + y,0,146,14 );
	gfx.PutPixel( 18 + x,33 + y,0,146,14 );
	gfx.PutPixel( 19 + x,33 + y,0,146,14 );
	gfx.PutPixel( 35 + x,33 + y,0,146,14 );
	gfx.PutPixel( 36 + x,33 + y,0,146,14 );
	gfx.PutPixel( 37 + x,33 + y,0,146,14 );
	gfx.PutPixel( 62 + x,33 + y,0,146,14 );
	gfx.PutPixel( 63 + x,33 + y,0,146,14 );
	gfx.PutPixel( 64 + x,33 + y,0,146,14 );
	gfx.PutPixel( 65 + x,33 + y,0,146,14 );
	gfx.PutPixel( 66 + x,33 + y,0,146,14 );
	gfx.PutPixel( 67 + x,33 + y,0,146,14 );
	gfx.PutPixel( 68 + x,33 + y,0,146,14 );
	gfx.PutPixel( 69 + x,33 + y,0,146,14 );
	gfx.PutPixel( 70 + x,33 + y,0,146,14 );
	gfx.PutPixel( 71 + x,33 + y,0,146,14 );
	gfx.PutPixel( 72 + x,33 + y,0,146,14 );
	gfx.PutPixel( 73 + x,33 + y,0,146,14 );
	gfx.PutPixel( 74 + x,33 + y,0,146,14 );
	gfx.PutPixel( 75 + x,33 + y,0,146,14 );
	gfx.PutPixel( 76 + x,33 + y,0,146,14 );
	gfx.PutPixel( 77 + x,33 + y,0,146,14 );
	gfx.PutPixel( 78 + x,33 + y,0,146,14 );
	gfx.PutPixel( 79 + x,33 + y,0,146,14 );
	gfx.PutPixel( 80 + x,33 + y,0,146,14 );
	gfx.PutPixel( 81 + x,33 + y,0,146,14 );
	gfx.PutPixel( 82 + x,33 + y,0,25,2 );
	gfx.PutPixel( 8 + x,34 + y,0,146,14 );
	gfx.PutPixel( 9 + x,34 + y,0,146,14 );
	gfx.PutPixel( 10 + x,34 + y,0,146,14 );
	gfx.PutPixel( 11 + x,34 + y,0,146,14 );
	gfx.PutPixel( 12 + x,34 + y,0,146,14 );
	gfx.PutPixel( 13 + x,34 + y,0,146,14 );
	gfx.PutPixel( 14 + x,34 + y,0,146,14 );
	gfx.PutPixel( 15 + x,34 + y,0,146,14 );
	gfx.PutPixel( 16 + x,34 + y,0,146,14 );
	gfx.PutPixel( 17 + x,34 + y,0,146,14 );
	gfx.PutPixel( 18 + x,34 + y,0,146,14 );
	gfx.PutPixel( 35 + x,34 + y,0,146,14 );
	gfx.PutPixel( 36 + x,34 + y,0,146,14 );
	gfx.PutPixel( 37 + x,34 + y,0,146,14 );
	gfx.PutPixel( 38 + x,34 + y,0,146,14 );
	gfx.PutPixel( 61 + x,34 + y,0,146,14 );
	gfx.PutPixel( 62 + x,34 + y,0,146,14 );
	gfx.PutPixel( 63 + x,34 + y,0,146,14 );
	gfx.PutPixel( 64 + x,34 + y,0,146,14 );
	gfx.PutPixel( 65 + x,34 + y,0,146,14 );
	gfx.PutPixel( 66 + x,34 + y,0,146,14 );
	gfx.PutPixel( 67 + x,34 + y,0,146,14 );
	gfx.PutPixel( 68 + x,34 + y,0,146,14 );
	gfx.PutPixel( 69 + x,34 + y,0,146,14 );
	gfx.PutPixel( 70 + x,34 + y,0,146,14 );
	gfx.PutPixel( 71 + x,34 + y,0,146,14 );
	gfx.PutPixel( 72 + x,34 + y,0,146,14 );
	gfx.PutPixel( 73 + x,34 + y,0,146,14 );
	gfx.PutPixel( 74 + x,34 + y,0,146,14 );
	gfx.PutPixel( 75 + x,34 + y,0,146,14 );
	gfx.PutPixel( 76 + x,34 + y,0,146,14 );
	gfx.PutPixel( 77 + x,34 + y,0,146,14 );
	gfx.PutPixel( 78 + x,34 + y,0,146,14 );
	gfx.PutPixel( 79 + x,34 + y,0,146,14 );
	gfx.PutPixel( 80 + x,34 + y,0,146,14 );
	gfx.PutPixel( 81 + x,34 + y,0,146,14 );
	gfx.PutPixel( 8 + x,35 + y,0,146,14 );
	gfx.PutPixel( 9 + x,35 + y,0,146,14 );
	gfx.PutPixel( 10 + x,35 + y,0,146,14 );
	gfx.PutPixel( 11 + x,35 + y,0,146,14 );
	gfx.PutPixel( 12 + x,35 + y,0,146,14 );
	gfx.PutPixel( 13 + x,35 + y,0,146,14 );
	gfx.PutPixel( 14 + x,35 + y,0,146,14 );
	gfx.PutPixel( 15 + x,35 + y,0,146,14 );
	gfx.PutPixel( 16 + x,35 + y,0,146,14 );
	gfx.PutPixel( 17 + x,35 + y,0,146,14 );
	gfx.PutPixel( 36 + x,35 + y,0,146,14 );
	gfx.PutPixel( 37 + x,35 + y,0,146,14 );
	gfx.PutPixel( 38 + x,35 + y,0,146,14 );
	gfx.PutPixel( 39 + x,35 + y,0,146,14 );
	gfx.PutPixel( 60 + x,35 + y,0,146,14 );
	gfx.PutPixel( 61 + x,35 + y,0,146,14 );
	gfx.PutPixel( 62 + x,35 + y,0,146,14 );
	gfx.PutPixel( 63 + x,35 + y,0,146,14 );
	gfx.PutPixel( 64 + x,35 + y,0,146,14 );
	gfx.PutPixel( 65 + x,35 + y,0,146,14 );
	gfx.PutPixel( 66 + x,35 + y,0,146,14 );
	gfx.PutPixel( 67 + x,35 + y,0,146,14 );
	gfx.PutPixel( 68 + x,35 + y,0,146,14 );
	gfx.PutPixel( 69 + x,35 + y,0,146,14 );
	gfx.PutPixel( 70 + x,35 + y,0,146,14 );
	gfx.PutPixel( 71 + x,35 + y,0,146,14 );
	gfx.PutPixel( 72 + x,35 + y,0,146,14 );
	gfx.PutPixel( 73 + x,35 + y,0,146,14 );
	gfx.PutPixel( 74 + x,35 + y,0,146,14 );
	gfx.PutPixel( 75 + x,35 + y,0,146,14 );
	gfx.PutPixel( 76 + x,35 + y,0,146,14 );
	gfx.PutPixel( 77 + x,35 + y,0,146,14 );
	gfx.PutPixel( 78 + x,35 + y,0,146,14 );
	gfx.PutPixel( 79 + x,35 + y,0,146,14 );
	gfx.PutPixel( 8 + x,36 + y,0,146,14 );
	gfx.PutPixel( 9 + x,36 + y,0,146,14 );
	gfx.PutPixel( 10 + x,36 + y,0,146,14 );
	gfx.PutPixel( 11 + x,36 + y,0,146,14 );
	gfx.PutPixel( 12 + x,36 + y,0,146,14 );
	gfx.PutPixel( 13 + x,36 + y,0,146,14 );
	gfx.PutPixel( 14 + x,36 + y,0,146,14 );
	gfx.PutPixel( 15 + x,36 + y,0,146,14 );
	gfx.PutPixel( 16 + x,36 + y,0,146,14 );
	gfx.PutPixel( 17 + x,36 + y,0,146,14 );
	gfx.PutPixel( 18 + x,36 + y,0,146,14 );
	gfx.PutPixel( 37 + x,36 + y,0,146,14 );
	gfx.PutPixel( 38 + x,36 + y,0,146,14 );
	gfx.PutPixel( 39 + x,36 + y,0,146,14 );
	gfx.PutPixel( 40 + x,36 + y,0,146,14 );
	gfx.PutPixel( 59 + x,36 + y,0,146,14 );
	gfx.PutPixel( 60 + x,36 + y,0,146,14 );
	gfx.PutPixel( 61 + x,36 + y,0,146,14 );
	gfx.PutPixel( 62 + x,36 + y,0,146,14 );
	gfx.PutPixel( 63 + x,36 + y,0,146,14 );
	gfx.PutPixel( 64 + x,36 + y,0,146,14 );
	gfx.PutPixel( 65 + x,36 + y,0,146,14 );
	gfx.PutPixel( 66 + x,36 + y,0,146,14 );
	gfx.PutPixel( 67 + x,36 + y,0,146,14 );
	gfx.PutPixel( 68 + x,36 + y,0,146,14 );
	gfx.PutPixel( 69 + x,36 + y,0,146,14 );
	gfx.PutPixel( 70 + x,36 + y,0,146,14 );
	gfx.PutPixel( 71 + x,36 + y,0,146,14 );
	gfx.PutPixel( 72 + x,36 + y,0,146,14 );
	gfx.PutPixel( 73 + x,36 + y,0,146,14 );
	gfx.PutPixel( 74 + x,36 + y,0,146,14 );
	gfx.PutPixel( 9 + x,37 + y,0,146,14 );
	gfx.PutPixel( 10 + x,37 + y,0,146,14 );
	gfx.PutPixel( 11 + x,37 + y,0,146,14 );
	gfx.PutPixel( 12 + x,37 + y,0,146,14 );
	gfx.PutPixel( 13 + x,37 + y,0,146,14 );
	gfx.PutPixel( 14 + x,37 + y,0,146,14 );
	gfx.PutPixel( 15 + x,37 + y,0,146,14 );
	gfx.PutPixel( 16 + x,37 + y,0,146,14 );
	gfx.PutPixel( 17 + x,37 + y,0,146,14 );
	gfx.PutPixel( 18 + x,37 + y,0,146,14 );
	gfx.PutPixel( 19 + x,37 + y,0,146,14 );
	gfx.PutPixel( 37 + x,37 + y,0,70,6 );
	gfx.PutPixel( 38 + x,37 + y,0,146,14 );
	gfx.PutPixel( 39 + x,37 + y,0,146,14 );
	gfx.PutPixel( 40 + x,37 + y,0,146,14 );
	gfx.PutPixel( 41 + x,37 + y,0,146,14 );
	gfx.PutPixel( 58 + x,37 + y,0,146,14 );
	gfx.PutPixel( 59 + x,37 + y,0,146,14 );
	gfx.PutPixel( 60 + x,37 + y,0,146,14 );
	gfx.PutPixel( 61 + x,37 + y,0,146,14 );
	gfx.PutPixel( 62 + x,37 + y,0,146,14 );
	gfx.PutPixel( 63 + x,37 + y,0,146,14 );
	gfx.PutPixel( 64 + x,37 + y,0,146,14 );
	gfx.PutPixel( 65 + x,37 + y,0,146,14 );
	gfx.PutPixel( 66 + x,37 + y,0,146,14 );
	gfx.PutPixel( 67 + x,37 + y,0,146,14 );
	gfx.PutPixel( 68 + x,37 + y,0,146,14 );
	gfx.PutPixel( 69 + x,37 + y,0,146,14 );
	gfx.PutPixel( 70 + x,37 + y,0,146,14 );
	gfx.PutPixel( 71 + x,37 + y,0,146,14 );
	gfx.PutPixel( 72 + x,37 + y,0,146,14 );
	gfx.PutPixel( 73 + x,37 + y,0,146,14 );
	gfx.PutPixel( 74 + x,37 + y,0,146,14 );
	gfx.PutPixel( 9 + x,38 + y,0,146,14 );
	gfx.PutPixel( 10 + x,38 + y,0,146,14 );
	gfx.PutPixel( 11 + x,38 + y,0,146,14 );
	gfx.PutPixel( 12 + x,38 + y,0,146,14 );
	gfx.PutPixel( 13 + x,38 + y,0,146,14 );
	gfx.PutPixel( 14 + x,38 + y,0,146,14 );
	gfx.PutPixel( 15 + x,38 + y,0,146,14 );
	gfx.PutPixel( 16 + x,38 + y,0,146,14 );
	gfx.PutPixel( 17 + x,38 + y,0,146,14 );
	gfx.PutPixel( 18 + x,38 + y,0,146,14 );
	gfx.PutPixel( 19 + x,38 + y,0,146,14 );
	gfx.PutPixel( 20 + x,38 + y,0,146,14 );
	gfx.PutPixel( 38 + x,38 + y,0,70,6 );
	gfx.PutPixel( 39 + x,38 + y,0,146,14 );
	gfx.PutPixel( 40 + x,38 + y,0,146,14 );
	gfx.PutPixel( 41 + x,38 + y,0,146,14 );
	gfx.PutPixel( 42 + x,38 + y,0,146,14 );
	gfx.PutPixel( 43 + x,38 + y,0,146,14 );
	gfx.PutPixel( 56 + x,38 + y,0,146,14 );
	gfx.PutPixel( 57 + x,38 + y,0,146,14 );
	gfx.PutPixel( 58 + x,38 + y,0,146,14 );
	gfx.PutPixel( 59 + x,38 + y,0,146,14 );
	gfx.PutPixel( 60 + x,38 + y,0,146,14 );
	gfx.PutPixel( 61 + x,38 + y,0,146,14 );
	gfx.PutPixel( 62 + x,38 + y,0,146,14 );
	gfx.PutPixel( 63 + x,38 + y,0,146,14 );
	gfx.PutPixel( 64 + x,38 + y,0,146,14 );
	gfx.PutPixel( 65 + x,38 + y,0,146,14 );
	gfx.PutPixel( 66 + x,38 + y,0,146,14 );
	gfx.PutPixel( 67 + x,38 + y,0,146,14 );
	gfx.PutPixel( 68 + x,38 + y,0,146,14 );
	gfx.PutPixel( 69 + x,38 + y,0,146,14 );
	gfx.PutPixel( 70 + x,38 + y,0,146,14 );
	gfx.PutPixel( 71 + x,38 + y,0,146,14 );
	gfx.PutPixel( 72 + x,38 + y,0,146,14 );
	gfx.PutPixel( 73 + x,38 + y,0,146,14 );
	gfx.PutPixel( 74 + x,38 + y,0,146,14 );
	gfx.PutPixel( 10 + x,39 + y,0,146,14 );
	gfx.PutPixel( 11 + x,39 + y,0,146,14 );
	gfx.PutPixel( 12 + x,39 + y,0,146,14 );
	gfx.PutPixel( 13 + x,39 + y,0,146,14 );
	gfx.PutPixel( 14 + x,39 + y,0,146,14 );
	gfx.PutPixel( 15 + x,39 + y,0,146,14 );
	gfx.PutPixel( 16 + x,39 + y,0,146,14 );
	gfx.PutPixel( 17 + x,39 + y,0,146,14 );
	gfx.PutPixel( 18 + x,39 + y,0,146,14 );
	gfx.PutPixel( 19 + x,39 + y,0,146,14 );
	gfx.PutPixel( 20 + x,39 + y,0,146,14 );
	gfx.PutPixel( 21 + x,39 + y,0,146,14 );
	gfx.PutPixel( 40 + x,39 + y,0,146,14 );
	gfx.PutPixel( 41 + x,39 + y,0,146,14 );
	gfx.PutPixel( 42 + x,39 + y,0,146,14 );
	gfx.PutPixel( 43 + x,39 + y,0,146,14 );
	gfx.PutPixel( 44 + x,39 + y,0,146,14 );
	gfx.PutPixel( 45 + x,39 + y,0,146,14 );
	gfx.PutPixel( 46 + x,39 + y,0,146,14 );
	gfx.PutPixel( 53 + x,39 + y,0,146,14 );
	gfx.PutPixel( 54 + x,39 + y,0,146,14 );
	gfx.PutPixel( 55 + x,39 + y,0,146,14 );
	gfx.PutPixel( 56 + x,39 + y,0,146,14 );
	gfx.PutPixel( 57 + x,39 + y,0,146,14 );
	gfx.PutPixel( 58 + x,39 + y,0,146,14 );
	gfx.PutPixel( 59 + x,39 + y,0,146,14 );
	gfx.PutPixel( 60 + x,39 + y,0,146,14 );
	gfx.PutPixel( 61 + x,39 + y,0,146,14 );
	gfx.PutPixel( 62 + x,39 + y,0,146,14 );
	gfx.PutPixel( 63 + x,39 + y,0,146,14 );
	gfx.PutPixel( 64 + x,39 + y,0,146,14 );
	gfx.PutPixel( 65 + x,39 + y,0,146,14 );
	gfx.PutPixel( 66 + x,39 + y,0,146,14 );
	gfx.PutPixel( 67 + x,39 + y,0,146,14 );
	gfx.PutPixel( 68 + x,39 + y,0,146,14 );
	gfx.PutPixel( 69 + x,39 + y,0,146,14 );
	gfx.PutPixel( 70 + x,39 + y,0,146,14 );
	gfx.PutPixel( 71 + x,39 + y,0,146,14 );
	gfx.PutPixel( 72 + x,39 + y,0,146,14 );
	gfx.PutPixel( 73 + x,39 + y,0,146,14 );
	gfx.PutPixel( 74 + x,39 + y,0,146,14 );
	gfx.PutPixel( 11 + x,40 + y,0,146,14 );
	gfx.PutPixel( 12 + x,40 + y,0,146,14 );
	gfx.PutPixel( 13 + x,40 + y,0,146,14 );
	gfx.PutPixel( 14 + x,40 + y,0,146,14 );
	gfx.PutPixel( 15 + x,40 + y,0,146,14 );
	gfx.PutPixel( 16 + x,40 + y,0,146,14 );
	gfx.PutPixel( 17 + x,40 + y,0,146,14 );
	gfx.PutPixel( 18 + x,40 + y,0,146,14 );
	gfx.PutPixel( 19 + x,40 + y,0,146,14 );
	gfx.PutPixel( 20 + x,40 + y,0,146,14 );
	gfx.PutPixel( 21 + x,40 + y,0,146,14 );
	gfx.PutPixel( 22 + x,40 + y,0,146,14 );
	gfx.PutPixel( 41 + x,40 + y,0,146,14 );
	gfx.PutPixel( 42 + x,40 + y,0,146,14 );
	gfx.PutPixel( 43 + x,40 + y,0,146,14 );
	gfx.PutPixel( 44 + x,40 + y,0,146,14 );
	gfx.PutPixel( 45 + x,40 + y,0,146,14 );
	gfx.PutPixel( 46 + x,40 + y,0,146,14 );
	gfx.PutPixel( 47 + x,40 + y,0,146,14 );
	gfx.PutPixel( 48 + x,40 + y,0,146,14 );
	gfx.PutPixel( 49 + x,40 + y,0,146,14 );
	gfx.PutPixel( 50 + x,40 + y,0,146,14 );
	gfx.PutPixel( 51 + x,40 + y,0,146,14 );
	gfx.PutPixel( 52 + x,40 + y,0,146,14 );
	gfx.PutPixel( 53 + x,40 + y,0,146,14 );
	gfx.PutPixel( 54 + x,40 + y,0,146,14 );
	gfx.PutPixel( 55 + x,40 + y,0,146,14 );
	gfx.PutPixel( 56 + x,40 + y,0,146,14 );
	gfx.PutPixel( 57 + x,40 + y,0,146,14 );
	gfx.PutPixel( 58 + x,40 + y,0,146,14 );
	gfx.PutPixel( 59 + x,40 + y,0,146,14 );
	gfx.PutPixel( 60 + x,40 + y,0,146,14 );
	gfx.PutPixel( 61 + x,40 + y,0,146,14 );
	gfx.PutPixel( 62 + x,40 + y,0,146,14 );
	gfx.PutPixel( 63 + x,40 + y,0,146,14 );
	gfx.PutPixel( 64 + x,40 + y,0,146,14 );
	gfx.PutPixel( 65 + x,40 + y,0,146,14 );
	gfx.PutPixel( 66 + x,40 + y,0,146,14 );
	gfx.PutPixel( 67 + x,40 + y,0,146,14 );
	gfx.PutPixel( 68 + x,40 + y,0,146,14 );
	gfx.PutPixel( 69 + x,40 + y,0,146,14 );
	gfx.PutPixel( 70 + x,40 + y,0,146,14 );
	gfx.PutPixel( 71 + x,40 + y,0,146,14 );
	gfx.PutPixel( 72 + x,40 + y,0,146,14 );
	gfx.PutPixel( 73 + x,40 + y,0,146,14 );
	gfx.PutPixel( 74 + x,40 + y,0,146,14 );
	gfx.PutPixel( 75 + x,40 + y,0,146,14 );
	gfx.PutPixel( 76 + x,40 + y,0,146,14 );
	gfx.PutPixel( 77 + x,40 + y,0,70,6 );
	gfx.PutPixel( 12 + x,41 + y,0,146,14 );
	gfx.PutPixel( 13 + x,41 + y,0,146,14 );
	gfx.PutPixel( 14 + x,41 + y,0,146,14 );
	gfx.PutPixel( 15 + x,41 + y,0,146,14 );
	gfx.PutPixel( 16 + x,41 + y,0,146,14 );
	gfx.PutPixel( 17 + x,41 + y,0,146,14 );
	gfx.PutPixel( 18 + x,41 + y,0,146,14 );
	gfx.PutPixel( 19 + x,41 + y,0,146,14 );
	gfx.PutPixel( 20 + x,41 + y,0,146,14 );
	gfx.PutPixel( 21 + x,41 + y,0,146,14 );
	gfx.PutPixel( 22 + x,41 + y,0,146,14 );
	gfx.PutPixel( 23 + x,41 + y,0,146,14 );
	gfx.PutPixel( 40 + x,41 + y,0,146,14 );
	gfx.PutPixel( 41 + x,41 + y,0,146,14 );
	gfx.PutPixel( 42 + x,41 + y,0,146,14 );
	gfx.PutPixel( 43 + x,41 + y,0,146,14 );
	gfx.PutPixel( 44 + x,41 + y,0,146,14 );
	gfx.PutPixel( 45 + x,41 + y,0,146,14 );
	gfx.PutPixel( 46 + x,41 + y,0,146,14 );
	gfx.PutPixel( 47 + x,41 + y,0,146,14 );
	gfx.PutPixel( 48 + x,41 + y,0,146,14 );
	gfx.PutPixel( 49 + x,41 + y,0,146,14 );
	gfx.PutPixel( 50 + x,41 + y,0,146,14 );
	gfx.PutPixel( 51 + x,41 + y,0,146,14 );
	gfx.PutPixel( 52 + x,41 + y,0,146,14 );
	gfx.PutPixel( 53 + x,41 + y,0,146,14 );
	gfx.PutPixel( 54 + x,41 + y,0,146,14 );
	gfx.PutPixel( 55 + x,41 + y,0,146,14 );
	gfx.PutPixel( 56 + x,41 + y,0,146,14 );
	gfx.PutPixel( 57 + x,41 + y,0,146,14 );
	gfx.PutPixel( 58 + x,41 + y,0,146,14 );
	gfx.PutPixel( 59 + x,41 + y,0,146,14 );
	gfx.PutPixel( 60 + x,41 + y,0,146,14 );
	gfx.PutPixel( 61 + x,41 + y,0,146,14 );
	gfx.PutPixel( 62 + x,41 + y,0,146,14 );
	gfx.PutPixel( 63 + x,41 + y,0,146,14 );
	gfx.PutPixel( 64 + x,41 + y,0,146,14 );
	gfx.PutPixel( 65 + x,41 + y,0,146,14 );
	gfx.PutPixel( 66 + x,41 + y,0,146,14 );
	gfx.PutPixel( 67 + x,41 + y,0,146,14 );
	gfx.PutPixel( 68 + x,41 + y,0,146,14 );
	gfx.PutPixel( 69 + x,41 + y,0,146,14 );
	gfx.PutPixel( 70 + x,41 + y,0,146,14 );
	gfx.PutPixel( 71 + x,41 + y,0,146,14 );
	gfx.PutPixel( 72 + x,41 + y,0,146,14 );
	gfx.PutPixel( 73 + x,41 + y,0,146,14 );
	gfx.PutPixel( 74 + x,41 + y,0,146,14 );
	gfx.PutPixel( 75 + x,41 + y,0,146,14 );
	gfx.PutPixel( 76 + x,41 + y,0,146,14 );
	gfx.PutPixel( 77 + x,41 + y,0,146,14 );
	gfx.PutPixel( 78 + x,41 + y,0,146,14 );
	gfx.PutPixel( 3 + x,42 + y,0,25,2 );
	gfx.PutPixel( 4 + x,42 + y,0,146,14 );
	gfx.PutPixel( 5 + x,42 + y,0,146,14 );
	gfx.PutPixel( 6 + x,42 + y,0,25,2 );
	gfx.PutPixel( 13 + x,42 + y,0,146,14 );
	gfx.PutPixel( 14 + x,42 + y,0,146,14 );
	gfx.PutPixel( 15 + x,42 + y,0,146,14 );
	gfx.PutPixel( 16 + x,42 + y,0,146,14 );
	gfx.PutPixel( 17 + x,42 + y,0,146,14 );
	gfx.PutPixel( 18 + x,42 + y,0,146,14 );
	gfx.PutPixel( 19 + x,42 + y,0,146,14 );
	gfx.PutPixel( 20 + x,42 + y,0,146,14 );
	gfx.PutPixel( 21 + x,42 + y,0,146,14 );
	gfx.PutPixel( 22 + x,42 + y,0,146,14 );
	gfx.PutPixel( 23 + x,42 + y,0,146,14 );
	gfx.PutPixel( 24 + x,42 + y,0,146,14 );
	gfx.PutPixel( 39 + x,42 + y,0,146,14 );
	gfx.PutPixel( 40 + x,42 + y,0,146,14 );
	gfx.PutPixel( 41 + x,42 + y,0,146,14 );
	gfx.PutPixel( 42 + x,42 + y,0,146,14 );
	gfx.PutPixel( 43 + x,42 + y,0,146,14 );
	gfx.PutPixel( 44 + x,42 + y,0,146,14 );
	gfx.PutPixel( 45 + x,42 + y,0,146,14 );
	gfx.PutPixel( 46 + x,42 + y,0,146,14 );
	gfx.PutPixel( 47 + x,42 + y,0,146,14 );
	gfx.PutPixel( 48 + x,42 + y,0,146,14 );
	gfx.PutPixel( 49 + x,42 + y,0,146,14 );
	gfx.PutPixel( 50 + x,42 + y,0,146,14 );
	gfx.PutPixel( 51 + x,42 + y,0,146,14 );
	gfx.PutPixel( 52 + x,42 + y,0,146,14 );
	gfx.PutPixel( 53 + x,42 + y,0,146,14 );
	gfx.PutPixel( 54 + x,42 + y,0,146,14 );
	gfx.PutPixel( 55 + x,42 + y,0,146,14 );
	gfx.PutPixel( 56 + x,42 + y,0,146,14 );
	gfx.PutPixel( 57 + x,42 + y,0,146,14 );
	gfx.PutPixel( 58 + x,42 + y,0,146,14 );
	gfx.PutPixel( 59 + x,42 + y,0,146,14 );
	gfx.PutPixel( 60 + x,42 + y,0,146,14 );
	gfx.PutPixel( 61 + x,42 + y,0,146,14 );
	gfx.PutPixel( 62 + x,42 + y,0,146,14 );
	gfx.PutPixel( 63 + x,42 + y,0,146,14 );
	gfx.PutPixel( 64 + x,42 + y,0,146,14 );
	gfx.PutPixel( 65 + x,42 + y,0,146,14 );
	gfx.PutPixel( 66 + x,42 + y,0,146,14 );
	gfx.PutPixel( 67 + x,42 + y,0,146,14 );
	gfx.PutPixel( 68 + x,42 + y,0,146,14 );
	gfx.PutPixel( 69 + x,42 + y,0,146,14 );
	gfx.PutPixel( 70 + x,42 + y,0,146,14 );
	gfx.PutPixel( 71 + x,42 + y,0,146,14 );
	gfx.PutPixel( 72 + x,42 + y,0,146,14 );
	gfx.PutPixel( 73 + x,42 + y,0,146,14 );
	gfx.PutPixel( 74 + x,42 + y,0,146,14 );
	gfx.PutPixel( 75 + x,42 + y,0,146,14 );
	gfx.PutPixel( 76 + x,42 + y,0,146,14 );
	gfx.PutPixel( 77 + x,42 + y,0,146,14 );
	gfx.PutPixel( 78 + x,42 + y,0,146,14 );
	gfx.PutPixel( 79 + x,42 + y,0,146,14 );
	gfx.PutPixel( 1 + x,43 + y,0,146,14 );
	gfx.PutPixel( 2 + x,43 + y,0,146,14 );
	gfx.PutPixel( 3 + x,43 + y,0,146,14 );
	gfx.PutPixel( 4 + x,43 + y,0,146,14 );
	gfx.PutPixel( 5 + x,43 + y,0,146,14 );
	gfx.PutPixel( 6 + x,43 + y,0,146,14 );
	gfx.PutPixel( 7 + x,43 + y,0,146,14 );
	gfx.PutPixel( 8 + x,43 + y,0,146,14 );
	gfx.PutPixel( 9 + x,43 + y,0,146,14 );
	gfx.PutPixel( 10 + x,43 + y,0,146,14 );
	gfx.PutPixel( 11 + x,43 + y,0,146,14 );
	gfx.PutPixel( 12 + x,43 + y,0,146,14 );
	gfx.PutPixel( 13 + x,43 + y,0,146,14 );
	gfx.PutPixel( 14 + x,43 + y,0,146,14 );
	gfx.PutPixel( 15 + x,43 + y,0,146,14 );
	gfx.PutPixel( 16 + x,43 + y,0,146,14 );
	gfx.PutPixel( 17 + x,43 + y,0,146,14 );
	gfx.PutPixel( 18 + x,43 + y,0,146,14 );
	gfx.PutPixel( 19 + x,43 + y,0,146,14 );
	gfx.PutPixel( 20 + x,43 + y,0,146,14 );
	gfx.PutPixel( 21 + x,43 + y,0,146,14 );
	gfx.PutPixel( 22 + x,43 + y,0,146,14 );
	gfx.PutPixel( 23 + x,43 + y,0,146,14 );
	gfx.PutPixel( 24 + x,43 + y,0,146,14 );
	gfx.PutPixel( 25 + x,43 + y,0,146,14 );
	gfx.PutPixel( 38 + x,43 + y,0,146,14 );
	gfx.PutPixel( 39 + x,43 + y,0,146,14 );
	gfx.PutPixel( 40 + x,43 + y,0,146,14 );
	gfx.PutPixel( 41 + x,43 + y,0,146,14 );
	gfx.PutPixel( 77 + x,43 + y,0,146,14 );
	gfx.PutPixel( 78 + x,43 + y,0,146,14 );
	gfx.PutPixel( 79 + x,43 + y,0,146,14 );
	gfx.PutPixel( 0 + x,44 + y,0,146,14 );
	gfx.PutPixel( 1 + x,44 + y,0,146,14 );
	gfx.PutPixel( 2 + x,44 + y,0,146,14 );
	gfx.PutPixel( 3 + x,44 + y,0,146,14 );
	gfx.PutPixel( 4 + x,44 + y,0,146,14 );
	gfx.PutPixel( 5 + x,44 + y,0,146,14 );
	gfx.PutPixel( 6 + x,44 + y,0,146,14 );
	gfx.PutPixel( 7 + x,44 + y,0,146,14 );
	gfx.PutPixel( 8 + x,44 + y,0,146,14 );
	gfx.PutPixel( 9 + x,44 + y,0,146,14 );
	gfx.PutPixel( 10 + x,44 + y,0,146,14 );
	gfx.PutPixel( 11 + x,44 + y,0,146,14 );
	gfx.PutPixel( 12 + x,44 + y,0,146,14 );
	gfx.PutPixel( 13 + x,44 + y,0,146,14 );
	gfx.PutPixel( 14 + x,44 + y,0,146,14 );
	gfx.PutPixel( 15 + x,44 + y,0,146,14 );
	gfx.PutPixel( 16 + x,44 + y,0,146,14 );
	gfx.PutPixel( 17 + x,44 + y,0,146,14 );
	gfx.PutPixel( 18 + x,44 + y,0,146,14 );
	gfx.PutPixel( 19 + x,44 + y,0,146,14 );
	gfx.PutPixel( 20 + x,44 + y,0,146,14 );
	gfx.PutPixel( 21 + x,44 + y,0,146,14 );
	gfx.PutPixel( 22 + x,44 + y,0,146,14 );
	gfx.PutPixel( 23 + x,44 + y,0,146,14 );
	gfx.PutPixel( 24 + x,44 + y,0,146,14 );
	gfx.PutPixel( 25 + x,44 + y,0,146,14 );
	gfx.PutPixel( 26 + x,44 + y,0,146,14 );
	gfx.PutPixel( 38 + x,44 + y,0,146,14 );
	gfx.PutPixel( 39 + x,44 + y,0,146,14 );
	gfx.PutPixel( 40 + x,44 + y,0,146,14 );
	gfx.PutPixel( 77 + x,44 + y,0,3,0 );
	gfx.PutPixel( 78 + x,44 + y,0,146,14 );
	gfx.PutPixel( 79 + x,44 + y,0,146,14 );
	gfx.PutPixel( 80 + x,44 + y,0,146,14 );
	gfx.PutPixel( 0 + x,45 + y,0,146,14 );
	gfx.PutPixel( 1 + x,45 + y,0,146,14 );
	gfx.PutPixel( 2 + x,45 + y,0,146,14 );
	gfx.PutPixel( 3 + x,45 + y,0,146,14 );
	gfx.PutPixel( 4 + x,45 + y,0,146,14 );
	gfx.PutPixel( 5 + x,45 + y,0,146,14 );
	gfx.PutPixel( 6 + x,45 + y,0,146,14 );
	gfx.PutPixel( 7 + x,45 + y,0,146,14 );
	gfx.PutPixel( 8 + x,45 + y,0,146,14 );
	gfx.PutPixel( 9 + x,45 + y,0,146,14 );
	gfx.PutPixel( 10 + x,45 + y,0,146,14 );
	gfx.PutPixel( 11 + x,45 + y,0,146,14 );
	gfx.PutPixel( 12 + x,45 + y,0,146,14 );
	gfx.PutPixel( 13 + x,45 + y,0,146,14 );
	gfx.PutPixel( 14 + x,45 + y,0,146,14 );
	gfx.PutPixel( 15 + x,45 + y,0,146,14 );
	gfx.PutPixel( 16 + x,45 + y,0,146,14 );
	gfx.PutPixel( 17 + x,45 + y,0,146,14 );
	gfx.PutPixel( 18 + x,45 + y,0,146,14 );
	gfx.PutPixel( 19 + x,45 + y,0,146,14 );
	gfx.PutPixel( 20 + x,45 + y,0,146,14 );
	gfx.PutPixel( 21 + x,45 + y,0,146,14 );
	gfx.PutPixel( 22 + x,45 + y,0,146,14 );
	gfx.PutPixel( 23 + x,45 + y,0,146,14 );
	gfx.PutPixel( 24 + x,45 + y,0,146,14 );
	gfx.PutPixel( 25 + x,45 + y,0,146,14 );
	gfx.PutPixel( 26 + x,45 + y,0,146,14 );
	gfx.PutPixel( 27 + x,45 + y,0,118,11 );
	gfx.PutPixel( 38 + x,45 + y,0,146,14 );
	gfx.PutPixel( 39 + x,45 + y,0,146,14 );
	gfx.PutPixel( 40 + x,45 + y,0,146,14 );
	gfx.PutPixel( 78 + x,45 + y,0,146,14 );
	gfx.PutPixel( 79 + x,45 + y,0,146,14 );
	gfx.PutPixel( 80 + x,45 + y,0,146,14 );
	gfx.PutPixel( 0 + x,46 + y,0,146,14 );
	gfx.PutPixel( 1 + x,46 + y,0,146,14 );
	gfx.PutPixel( 2 + x,46 + y,0,146,14 );
	gfx.PutPixel( 3 + x,46 + y,0,146,14 );
	gfx.PutPixel( 4 + x,46 + y,0,146,14 );
	gfx.PutPixel( 5 + x,46 + y,0,146,14 );
	gfx.PutPixel( 6 + x,46 + y,0,146,14 );
	gfx.PutPixel( 7 + x,46 + y,0,146,14 );
	gfx.PutPixel( 8 + x,46 + y,0,146,14 );
	gfx.PutPixel( 9 + x,46 + y,0,146,14 );
	gfx.PutPixel( 10 + x,46 + y,0,146,14 );
	gfx.PutPixel( 11 + x,46 + y,0,146,14 );
	gfx.PutPixel( 12 + x,46 + y,0,146,14 );
	gfx.PutPixel( 13 + x,46 + y,0,146,14 );
	gfx.PutPixel( 14 + x,46 + y,0,146,14 );
	gfx.PutPixel( 15 + x,46 + y,0,146,14 );
	gfx.PutPixel( 16 + x,46 + y,0,146,14 );
	gfx.PutPixel( 17 + x,46 + y,0,146,14 );
	gfx.PutPixel( 18 + x,46 + y,0,146,14 );
	gfx.PutPixel( 19 + x,46 + y,0,146,14 );
	gfx.PutPixel( 20 + x,46 + y,0,146,14 );
	gfx.PutPixel( 21 + x,46 + y,0,146,14 );
	gfx.PutPixel( 22 + x,46 + y,0,146,14 );
	gfx.PutPixel( 23 + x,46 + y,0,146,14 );
	gfx.PutPixel( 24 + x,46 + y,0,146,14 );
	gfx.PutPixel( 25 + x,46 + y,0,146,14 );
	gfx.PutPixel( 26 + x,46 + y,0,146,14 );
	gfx.PutPixel( 27 + x,46 + y,0,146,14 );
	gfx.PutPixel( 38 + x,46 + y,0,146,14 );
	gfx.PutPixel( 39 + x,46 + y,0,146,14 );
	gfx.PutPixel( 40 + x,46 + y,0,146,14 );
	gfx.PutPixel( 77 + x,46 + y,0,118,11 );
	gfx.PutPixel( 78 + x,46 + y,0,146,14 );
	gfx.PutPixel( 79 + x,46 + y,0,146,14 );
	gfx.PutPixel( 80 + x,46 + y,0,146,14 );
	gfx.PutPixel( 0 + x,47 + y,0,146,14 );
	gfx.PutPixel( 1 + x,47 + y,0,146,14 );
	gfx.PutPixel( 2 + x,47 + y,0,146,14 );
	gfx.PutPixel( 3 + x,47 + y,0,146,14 );
	gfx.PutPixel( 4 + x,47 + y,0,146,14 );
	gfx.PutPixel( 5 + x,47 + y,0,146,14 );
	gfx.PutPixel( 6 + x,47 + y,0,146,14 );
	gfx.PutPixel( 7 + x,47 + y,0,146,14 );
	gfx.PutPixel( 8 + x,47 + y,0,146,14 );
	gfx.PutPixel( 9 + x,47 + y,0,146,14 );
	gfx.PutPixel( 10 + x,47 + y,0,146,14 );
	gfx.PutPixel( 11 + x,47 + y,0,146,14 );
	gfx.PutPixel( 12 + x,47 + y,0,146,14 );
	gfx.PutPixel( 13 + x,47 + y,0,146,14 );
	gfx.PutPixel( 14 + x,47 + y,0,146,14 );
	gfx.PutPixel( 15 + x,47 + y,0,146,14 );
	gfx.PutPixel( 16 + x,47 + y,0,146,14 );
	gfx.PutPixel( 17 + x,47 + y,0,146,14 );
	gfx.PutPixel( 18 + x,47 + y,0,146,14 );
	gfx.PutPixel( 19 + x,47 + y,0,146,14 );
	gfx.PutPixel( 20 + x,47 + y,0,146,14 );
	gfx.PutPixel( 21 + x,47 + y,0,146,14 );
	gfx.PutPixel( 22 + x,47 + y,0,146,14 );
	gfx.PutPixel( 23 + x,47 + y,0,146,14 );
	gfx.PutPixel( 24 + x,47 + y,0,146,14 );
	gfx.PutPixel( 25 + x,47 + y,0,146,14 );
	gfx.PutPixel( 26 + x,47 + y,0,146,14 );
	gfx.PutPixel( 27 + x,47 + y,0,146,14 );
	gfx.PutPixel( 38 + x,47 + y,0,146,14 );
	gfx.PutPixel( 39 + x,47 + y,0,146,14 );
	gfx.PutPixel( 40 + x,47 + y,0,146,14 );
	gfx.PutPixel( 41 + x,47 + y,0,146,14 );
	gfx.PutPixel( 77 + x,47 + y,0,146,14 );
	gfx.PutPixel( 78 + x,47 + y,0,146,14 );
	gfx.PutPixel( 79 + x,47 + y,0,146,14 );
	gfx.PutPixel( 0 + x,48 + y,0,146,14 );
	gfx.PutPixel( 1 + x,48 + y,0,146,14 );
	gfx.PutPixel( 2 + x,48 + y,0,146,14 );
	gfx.PutPixel( 3 + x,48 + y,0,146,14 );
	gfx.PutPixel( 4 + x,48 + y,0,146,14 );
	gfx.PutPixel( 5 + x,48 + y,0,146,14 );
	gfx.PutPixel( 6 + x,48 + y,0,146,14 );
	gfx.PutPixel( 7 + x,48 + y,0,146,14 );
	gfx.PutPixel( 8 + x,48 + y,0,146,14 );
	gfx.PutPixel( 9 + x,48 + y,0,146,14 );
	gfx.PutPixel( 10 + x,48 + y,0,146,14 );
	gfx.PutPixel( 11 + x,48 + y,0,146,14 );
	gfx.PutPixel( 12 + x,48 + y,0,146,14 );
	gfx.PutPixel( 13 + x,48 + y,0,146,14 );
	gfx.PutPixel( 14 + x,48 + y,0,146,14 );
	gfx.PutPixel( 15 + x,48 + y,0,146,14 );
	gfx.PutPixel( 16 + x,48 + y,0,146,14 );
	gfx.PutPixel( 17 + x,48 + y,0,146,14 );
	gfx.PutPixel( 18 + x,48 + y,0,146,14 );
	gfx.PutPixel( 19 + x,48 + y,0,146,14 );
	gfx.PutPixel( 20 + x,48 + y,0,146,14 );
	gfx.PutPixel( 21 + x,48 + y,0,146,14 );
	gfx.PutPixel( 22 + x,48 + y,0,146,14 );
	gfx.PutPixel( 23 + x,48 + y,0,146,14 );
	gfx.PutPixel( 24 + x,48 + y,0,146,14 );
	gfx.PutPixel( 25 + x,48 + y,0,146,14 );
	gfx.PutPixel( 26 + x,48 + y,0,146,14 );
	gfx.PutPixel( 39 + x,48 + y,0,146,14 );
	gfx.PutPixel( 40 + x,48 + y,0,146,14 );
	gfx.PutPixel( 41 + x,48 + y,0,146,14 );
	gfx.PutPixel( 42 + x,48 + y,0,146,14 );
	gfx.PutPixel( 43 + x,48 + y,0,146,14 );
	gfx.PutPixel( 44 + x,48 + y,0,146,14 );
	gfx.PutPixel( 45 + x,48 + y,0,146,14 );
	gfx.PutPixel( 46 + x,48 + y,0,146,14 );
	gfx.PutPixel( 47 + x,48 + y,0,146,14 );
	gfx.PutPixel( 48 + x,48 + y,0,146,14 );
	gfx.PutPixel( 49 + x,48 + y,0,146,14 );
	gfx.PutPixel( 50 + x,48 + y,0,146,14 );
	gfx.PutPixel( 51 + x,48 + y,0,146,14 );
	gfx.PutPixel( 52 + x,48 + y,0,146,14 );
	gfx.PutPixel( 53 + x,48 + y,0,146,14 );
	gfx.PutPixel( 54 + x,48 + y,0,146,14 );
	gfx.PutPixel( 55 + x,48 + y,0,146,14 );
	gfx.PutPixel( 56 + x,48 + y,0,146,14 );
	gfx.PutPixel( 57 + x,48 + y,0,146,14 );
	gfx.PutPixel( 58 + x,48 + y,0,146,14 );
	gfx.PutPixel( 59 + x,48 + y,0,146,14 );
	gfx.PutPixel( 60 + x,48 + y,0,146,14 );
	gfx.PutPixel( 61 + x,48 + y,0,146,14 );
	gfx.PutPixel( 62 + x,48 + y,0,146,14 );
	gfx.PutPixel( 63 + x,48 + y,0,146,14 );
	gfx.PutPixel( 64 + x,48 + y,0,146,14 );
	gfx.PutPixel( 65 + x,48 + y,0,146,14 );
	gfx.PutPixel( 66 + x,48 + y,0,146,14 );
	gfx.PutPixel( 67 + x,48 + y,0,146,14 );
	gfx.PutPixel( 68 + x,48 + y,0,146,14 );
	gfx.PutPixel( 69 + x,48 + y,0,146,14 );
	gfx.PutPixel( 70 + x,48 + y,0,146,14 );
	gfx.PutPixel( 71 + x,48 + y,0,146,14 );
	gfx.PutPixel( 72 + x,48 + y,0,146,14 );
	gfx.PutPixel( 73 + x,48 + y,0,146,14 );
	gfx.PutPixel( 74 + x,48 + y,0,146,14 );
	gfx.PutPixel( 75 + x,48 + y,0,146,14 );
	gfx.PutPixel( 76 + x,48 + y,0,146,14 );
	gfx.PutPixel( 77 + x,48 + y,0,146,14 );
	gfx.PutPixel( 78 + x,48 + y,0,146,14 );
	gfx.PutPixel( 79 + x,48 + y,0,146,14 );
	gfx.PutPixel( 0 + x,49 + y,0,142,13 );
	gfx.PutPixel( 1 + x,49 + y,0,146,14 );
	gfx.PutPixel( 2 + x,49 + y,0,146,14 );
	gfx.PutPixel( 3 + x,49 + y,0,146,14 );
	gfx.PutPixel( 4 + x,49 + y,0,146,14 );
	gfx.PutPixel( 5 + x,49 + y,0,146,14 );
	gfx.PutPixel( 6 + x,49 + y,0,146,14 );
	gfx.PutPixel( 7 + x,49 + y,0,146,14 );
	gfx.PutPixel( 8 + x,49 + y,0,146,14 );
	gfx.PutPixel( 9 + x,49 + y,0,146,14 );
	gfx.PutPixel( 10 + x,49 + y,0,146,14 );
	gfx.PutPixel( 11 + x,49 + y,0,146,14 );
	gfx.PutPixel( 12 + x,49 + y,0,146,14 );
	gfx.PutPixel( 13 + x,49 + y,0,146,14 );
	gfx.PutPixel( 14 + x,49 + y,0,146,14 );
	gfx.PutPixel( 15 + x,49 + y,0,146,14 );
	gfx.PutPixel( 16 + x,49 + y,0,146,14 );
	gfx.PutPixel( 17 + x,49 + y,0,146,14 );
	gfx.PutPixel( 18 + x,49 + y,0,146,14 );
	gfx.PutPixel( 19 + x,49 + y,0,146,14 );
	gfx.PutPixel( 20 + x,49 + y,0,146,14 );
	gfx.PutPixel( 21 + x,49 + y,0,146,14 );
	gfx.PutPixel( 22 + x,49 + y,0,146,14 );
	gfx.PutPixel( 23 + x,49 + y,0,146,14 );
	gfx.PutPixel( 24 + x,49 + y,0,146,14 );
	gfx.PutPixel( 25 + x,49 + y,0,146,14 );
	gfx.PutPixel( 26 + x,49 + y,0,146,14 );
	gfx.PutPixel( 40 + x,49 + y,0,146,14 );
	gfx.PutPixel( 41 + x,49 + y,0,146,14 );
	gfx.PutPixel( 42 + x,49 + y,0,146,14 );
	gfx.PutPixel( 43 + x,49 + y,0,146,14 );
	gfx.PutPixel( 44 + x,49 + y,0,146,14 );
	gfx.PutPixel( 45 + x,49 + y,0,146,14 );
	gfx.PutPixel( 46 + x,49 + y,0,146,14 );
	gfx.PutPixel( 47 + x,49 + y,0,146,14 );
	gfx.PutPixel( 48 + x,49 + y,0,146,14 );
	gfx.PutPixel( 49 + x,49 + y,0,146,14 );
	gfx.PutPixel( 50 + x,49 + y,0,146,14 );
	gfx.PutPixel( 51 + x,49 + y,0,146,14 );
	gfx.PutPixel( 52 + x,49 + y,0,146,14 );
	gfx.PutPixel( 53 + x,49 + y,0,146,14 );
	gfx.PutPixel( 54 + x,49 + y,0,146,14 );
	gfx.PutPixel( 55 + x,49 + y,0,146,14 );
	gfx.PutPixel( 56 + x,49 + y,0,146,14 );
	gfx.PutPixel( 57 + x,49 + y,0,146,14 );
	gfx.PutPixel( 58 + x,49 + y,0,146,14 );
	gfx.PutPixel( 59 + x,49 + y,0,146,14 );
	gfx.PutPixel( 60 + x,49 + y,0,146,14 );
	gfx.PutPixel( 61 + x,49 + y,0,146,14 );
	gfx.PutPixel( 62 + x,49 + y,0,146,14 );
	gfx.PutPixel( 63 + x,49 + y,0,146,14 );
	gfx.PutPixel( 64 + x,49 + y,0,146,14 );
	gfx.PutPixel( 65 + x,49 + y,0,146,14 );
	gfx.PutPixel( 66 + x,49 + y,0,146,14 );
	gfx.PutPixel( 67 + x,49 + y,0,146,14 );
	gfx.PutPixel( 68 + x,49 + y,0,146,14 );
	gfx.PutPixel( 69 + x,49 + y,0,146,14 );
	gfx.PutPixel( 70 + x,49 + y,0,146,14 );
	gfx.PutPixel( 71 + x,49 + y,0,146,14 );
	gfx.PutPixel( 72 + x,49 + y,0,146,14 );
	gfx.PutPixel( 73 + x,49 + y,0,146,14 );
	gfx.PutPixel( 74 + x,49 + y,0,146,14 );
	gfx.PutPixel( 75 + x,49 + y,0,146,14 );
	gfx.PutPixel( 76 + x,49 + y,0,146,14 );
	gfx.PutPixel( 77 + x,49 + y,0,146,14 );
	gfx.PutPixel( 78 + x,49 + y,0,146,14 );
	gfx.PutPixel( 2 + x,50 + y,0,146,14 );
	gfx.PutPixel( 3 + x,50 + y,0,146,14 );
	gfx.PutPixel( 4 + x,50 + y,0,146,14 );
	gfx.PutPixel( 5 + x,50 + y,0,146,14 );
	gfx.PutPixel( 6 + x,50 + y,0,146,14 );
	gfx.PutPixel( 7 + x,50 + y,0,146,14 );
	gfx.PutPixel( 8 + x,50 + y,0,146,14 );
	gfx.PutPixel( 9 + x,50 + y,0,146,14 );
	gfx.PutPixel( 10 + x,50 + y,0,146,14 );
	gfx.PutPixel( 11 + x,50 + y,0,146,14 );
	gfx.PutPixel( 12 + x,50 + y,0,146,14 );
	gfx.PutPixel( 13 + x,50 + y,0,146,14 );
	gfx.PutPixel( 14 + x,50 + y,0,146,14 );
	gfx.PutPixel( 15 + x,50 + y,0,146,14 );
	gfx.PutPixel( 16 + x,50 + y,0,146,14 );
	gfx.PutPixel( 17 + x,50 + y,0,146,14 );
	gfx.PutPixel( 18 + x,50 + y,0,146,14 );
	gfx.PutPixel( 19 + x,50 + y,0,146,14 );
	gfx.PutPixel( 20 + x,50 + y,0,146,14 );
	gfx.PutPixel( 21 + x,50 + y,0,146,14 );
	gfx.PutPixel( 22 + x,50 + y,0,146,14 );
	gfx.PutPixel( 23 + x,50 + y,0,146,14 );
	gfx.PutPixel( 24 + x,50 + y,0,146,14 );
	gfx.PutPixel( 25 + x,50 + y,0,142,13 );
	gfx.PutPixel( 41 + x,50 + y,0,146,14 );
	gfx.PutPixel( 42 + x,50 + y,0,146,14 );
	gfx.PutPixel( 43 + x,50 + y,0,146,14 );
	gfx.PutPixel( 44 + x,50 + y,0,146,14 );
	gfx.PutPixel( 45 + x,50 + y,0,146,14 );
	gfx.PutPixel( 46 + x,50 + y,0,146,14 );
	gfx.PutPixel( 47 + x,50 + y,0,146,14 );
	gfx.PutPixel( 48 + x,50 + y,0,146,14 );
	gfx.PutPixel( 49 + x,50 + y,0,146,14 );
	gfx.PutPixel( 50 + x,50 + y,0,146,14 );
	gfx.PutPixel( 51 + x,50 + y,0,146,14 );
	gfx.PutPixel( 52 + x,50 + y,0,146,14 );
	gfx.PutPixel( 53 + x,50 + y,0,146,14 );
	gfx.PutPixel( 54 + x,50 + y,0,146,14 );
	gfx.PutPixel( 55 + x,50 + y,0,146,14 );
	gfx.PutPixel( 56 + x,50 + y,0,146,14 );
	gfx.PutPixel( 57 + x,50 + y,0,146,14 );
	gfx.PutPixel( 58 + x,50 + y,0,146,14 );
	gfx.PutPixel( 59 + x,50 + y,0,146,14 );
	gfx.PutPixel( 60 + x,50 + y,0,146,14 );
	gfx.PutPixel( 61 + x,50 + y,0,146,14 );
	gfx.PutPixel( 62 + x,50 + y,0,146,14 );
	gfx.PutPixel( 63 + x,50 + y,0,146,14 );
	gfx.PutPixel( 64 + x,50 + y,0,146,14 );
	gfx.PutPixel( 65 + x,50 + y,0,146,14 );
	gfx.PutPixel( 66 + x,50 + y,0,146,14 );
	gfx.PutPixel( 67 + x,50 + y,0,146,14 );
	gfx.PutPixel( 68 + x,50 + y,0,146,14 );
	gfx.PutPixel( 69 + x,50 + y,0,146,14 );
	gfx.PutPixel( 70 + x,50 + y,0,146,14 );
	gfx.PutPixel( 71 + x,50 + y,0,146,14 );
	gfx.PutPixel( 72 + x,50 + y,0,146,14 );
	gfx.PutPixel( 73 + x,50 + y,0,146,14 );
	gfx.PutPixel( 74 + x,50 + y,0,146,14 );
	gfx.PutPixel( 75 + x,50 + y,0,146,14 );
	gfx.PutPixel( 76 + x,50 + y,0,146,14 );
	gfx.PutPixel( 2 + x,55 + y,0,146,14 );
	gfx.PutPixel( 3 + x,55 + y,0,146,14 );
	gfx.PutPixel( 4 + x,55 + y,0,146,14 );
	gfx.PutPixel( 5 + x,55 + y,0,146,14 );
	gfx.PutPixel( 6 + x,55 + y,0,146,14 );
	gfx.PutPixel( 7 + x,55 + y,0,146,14 );
	gfx.PutPixel( 12 + x,55 + y,0,146,14 );
	gfx.PutPixel( 13 + x,55 + y,0,146,14 );
	gfx.PutPixel( 14 + x,55 + y,0,146,14 );
	gfx.PutPixel( 19 + x,55 + y,0,146,14 );
	gfx.PutPixel( 20 + x,55 + y,0,146,14 );
	gfx.PutPixel( 25 + x,55 + y,0,146,14 );
	gfx.PutPixel( 26 + x,55 + y,0,146,14 );
	gfx.PutPixel( 28 + x,55 + y,0,146,14 );
	gfx.PutPixel( 29 + x,55 + y,0,146,14 );
	gfx.PutPixel( 30 + x,55 + y,0,146,14 );
	gfx.PutPixel( 31 + x,55 + y,0,146,14 );
	gfx.PutPixel( 32 + x,55 + y,0,146,14 );
	gfx.PutPixel( 33 + x,55 + y,0,146,14 );
	gfx.PutPixel( 34 + x,55 + y,0,146,14 );
	gfx.PutPixel( 35 + x,55 + y,0,146,14 );
	gfx.PutPixel( 36 + x,55 + y,0,146,14 );
	gfx.PutPixel( 48 + x,55 + y,0,118,11 );
	gfx.PutPixel( 49 + x,55 + y,0,146,14 );
	gfx.PutPixel( 50 + x,55 + y,0,146,14 );
	gfx.PutPixel( 51 + x,55 + y,0,146,14 );
	gfx.PutPixel( 52 + x,55 + y,0,146,14 );
	gfx.PutPixel( 53 + x,55 + y,0,146,14 );
	gfx.PutPixel( 54 + x,55 + y,0,146,14 );
	gfx.PutPixel( 57 + x,55 + y,0,146,14 );
	gfx.PutPixel( 58 + x,55 + y,0,146,14 );
	gfx.PutPixel( 63 + x,55 + y,0,146,14 );
	gfx.PutPixel( 64 + x,55 + y,0,146,14 );
	gfx.PutPixel( 66 + x,55 + y,0,3,0 );
	gfx.PutPixel( 67 + x,55 + y,0,146,14 );
	gfx.PutPixel( 68 + x,55 + y,0,146,14 );
	gfx.PutPixel( 69 + x,55 + y,0,146,14 );
	gfx.PutPixel( 70 + x,55 + y,0,146,14 );
	gfx.PutPixel( 71 + x,55 + y,0,146,14 );
	gfx.PutPixel( 72 + x,55 + y,0,146,14 );
	gfx.PutPixel( 73 + x,55 + y,0,146,14 );
	gfx.PutPixel( 74 + x,55 + y,0,146,14 );
	gfx.PutPixel( 76 + x,55 + y,0,146,14 );
	gfx.PutPixel( 77 + x,55 + y,0,146,14 );
	gfx.PutPixel( 78 + x,55 + y,0,146,14 );
	gfx.PutPixel( 79 + x,55 + y,0,146,14 );
	gfx.PutPixel( 80 + x,55 + y,0,146,14 );
	gfx.PutPixel( 81 + x,55 + y,0,146,14 );
	gfx.PutPixel( 82 + x,55 + y,0,146,14 );
	gfx.PutPixel( 1 + x,56 + y,0,146,14 );
	gfx.PutPixel( 2 + x,56 + y,0,146,14 );
	gfx.PutPixel( 3 + x,56 + y,0,146,14 );
	gfx.PutPixel( 4 + x,56 + y,0,146,14 );
	gfx.PutPixel( 5 + x,56 + y,0,146,14 );
	gfx.PutPixel( 6 + x,56 + y,0,146,14 );
	gfx.PutPixel( 7 + x,56 + y,0,146,14 );
	gfx.PutPixel( 11 + x,56 + y,0,146,14 );
	gfx.PutPixel( 12 + x,56 + y,0,146,14 );
	gfx.PutPixel( 13 + x,56 + y,0,146,14 );
	gfx.PutPixel( 14 + x,56 + y,0,146,14 );
	gfx.PutPixel( 15 + x,56 + y,0,146,14 );
	gfx.PutPixel( 16 + x,56 + y,0,142,13 );
	gfx.PutPixel( 19 + x,56 + y,0,146,14 );
	gfx.PutPixel( 20 + x,56 + y,0,146,14 );
	gfx.PutPixel( 21 + x,56 + y,0,146,14 );
	gfx.PutPixel( 24 + x,56 + y,0,146,14 );
	gfx.PutPixel( 25 + x,56 + y,0,146,14 );
	gfx.PutPixel( 26 + x,56 + y,0,146,14 );
	gfx.PutPixel( 28 + x,56 + y,0,146,14 );
	gfx.PutPixel( 29 + x,56 + y,0,146,14 );
	gfx.PutPixel( 30 + x,56 + y,0,146,14 );
	gfx.PutPixel( 31 + x,56 + y,0,146,14 );
	gfx.PutPixel( 32 + x,56 + y,0,146,14 );
	gfx.PutPixel( 33 + x,56 + y,0,146,14 );
	gfx.PutPixel( 34 + x,56 + y,0,146,14 );
	gfx.PutPixel( 35 + x,56 + y,0,146,14 );
	gfx.PutPixel( 36 + x,56 + y,0,142,13 );
	gfx.PutPixel( 47 + x,56 + y,0,146,14 );
	gfx.PutPixel( 48 + x,56 + y,0,146,14 );
	gfx.PutPixel( 49 + x,56 + y,0,146,14 );
	gfx.PutPixel( 50 + x,56 + y,0,25,2 );
	gfx.PutPixel( 51 + x,56 + y,0,25,2 );
	gfx.PutPixel( 52 + x,56 + y,0,146,14 );
	gfx.PutPixel( 53 + x,56 + y,0,146,14 );
	gfx.PutPixel( 54 + x,56 + y,0,146,14 );
	gfx.PutPixel( 55 + x,56 + y,0,146,14 );
	gfx.PutPixel( 57 + x,56 + y,0,146,14 );
	gfx.PutPixel( 58 + x,56 + y,0,146,14 );
	gfx.PutPixel( 63 + x,56 + y,0,146,14 );
	gfx.PutPixel( 64 + x,56 + y,0,146,14 );
	gfx.PutPixel( 65 + x,56 + y,0,146,14 );
	gfx.PutPixel( 66 + x,56 + y,0,146,14 );
	gfx.PutPixel( 67 + x,56 + y,0,146,14 );
	gfx.PutPixel( 68 + x,56 + y,0,146,14 );
	gfx.PutPixel( 69 + x,56 + y,0,146,14 );
	gfx.PutPixel( 70 + x,56 + y,0,146,14 );
	gfx.PutPixel( 71 + x,56 + y,0,146,14 );
	gfx.PutPixel( 72 + x,56 + y,0,146,14 );
	gfx.PutPixel( 73 + x,56 + y,0,146,14 );
	gfx.PutPixel( 74 + x,56 + y,0,146,14 );
	gfx.PutPixel( 76 + x,56 + y,0,146,14 );
	gfx.PutPixel( 77 + x,56 + y,0,146,14 );
	gfx.PutPixel( 78 + x,56 + y,0,146,14 );
	gfx.PutPixel( 79 + x,56 + y,0,25,2 );
	gfx.PutPixel( 80 + x,56 + y,0,146,14 );
	gfx.PutPixel( 81 + x,56 + y,0,146,14 );
	gfx.PutPixel( 82 + x,56 + y,0,146,14 );
	gfx.PutPixel( 83 + x,56 + y,0,146,14 );
	gfx.PutPixel( 0 + x,57 + y,0,146,14 );
	gfx.PutPixel( 1 + x,57 + y,0,146,14 );
	gfx.PutPixel( 9 + x,57 + y,0,25,2 );
	gfx.PutPixel( 10 + x,57 + y,0,146,14 );
	gfx.PutPixel( 11 + x,57 + y,0,146,14 );
	gfx.PutPixel( 15 + x,57 + y,0,146,14 );
	gfx.PutPixel( 16 + x,57 + y,0,146,14 );
	gfx.PutPixel( 17 + x,57 + y,0,118,11 );
	gfx.PutPixel( 19 + x,57 + y,0,146,14 );
	gfx.PutPixel( 20 + x,57 + y,0,146,14 );
	gfx.PutPixel( 21 + x,57 + y,0,146,14 );
	gfx.PutPixel( 22 + x,57 + y,0,146,14 );
	gfx.PutPixel( 23 + x,57 + y,0,146,14 );
	gfx.PutPixel( 24 + x,57 + y,0,146,14 );
	gfx.PutPixel( 25 + x,57 + y,0,146,14 );
	gfx.PutPixel( 26 + x,57 + y,0,146,14 );
	gfx.PutPixel( 28 + x,57 + y,0,146,14 );
	gfx.PutPixel( 29 + x,57 + y,0,146,14 );
	gfx.PutPixel( 30 + x,57 + y,0,146,14 );
	gfx.PutPixel( 47 + x,57 + y,0,146,14 );
	gfx.PutPixel( 48 + x,57 + y,0,146,14 );
	gfx.PutPixel( 49 + x,57 + y,0,146,14 );
	gfx.PutPixel( 54 + x,57 + y,0,146,14 );
	gfx.PutPixel( 55 + x,57 + y,0,146,14 );
	gfx.PutPixel( 57 + x,57 + y,0,146,14 );
	gfx.PutPixel( 58 + x,57 + y,0,146,14 );
	gfx.PutPixel( 63 + x,57 + y,0,146,14 );
	gfx.PutPixel( 64 + x,57 + y,0,146,14 );
	gfx.PutPixel( 65 + x,57 + y,0,25,2 );
	gfx.PutPixel( 66 + x,57 + y,0,146,14 );
	gfx.PutPixel( 67 + x,57 + y,0,146,14 );
	gfx.PutPixel( 68 + x,57 + y,0,146,14 );
	gfx.PutPixel( 76 + x,57 + y,0,146,14 );
	gfx.PutPixel( 77 + x,57 + y,0,146,14 );
	gfx.PutPixel( 82 + x,57 + y,0,146,14 );
	gfx.PutPixel( 83 + x,57 + y,0,146,14 );
	gfx.PutPixel( 0 + x,58 + y,0,146,14 );
	gfx.PutPixel( 1 + x,58 + y,0,146,14 );
	gfx.PutPixel( 9 + x,58 + y,0,146,14 );
	gfx.PutPixel( 10 + x,58 + y,0,146,14 );
	gfx.PutPixel( 11 + x,58 + y,0,118,11 );
	gfx.PutPixel( 15 + x,58 + y,0,25,2 );
	gfx.PutPixel( 16 + x,58 + y,0,146,14 );
	gfx.PutPixel( 17 + x,58 + y,0,146,14 );
	gfx.PutPixel( 19 + x,58 + y,0,146,14 );
	gfx.PutPixel( 20 + x,58 + y,0,146,14 );
	gfx.PutPixel( 21 + x,58 + y,0,146,14 );
	gfx.PutPixel( 22 + x,58 + y,0,146,14 );
	gfx.PutPixel( 23 + x,58 + y,0,146,14 );
	gfx.PutPixel( 24 + x,58 + y,0,146,14 );
	gfx.PutPixel( 25 + x,58 + y,0,146,14 );
	gfx.PutPixel( 26 + x,58 + y,0,146,14 );
	gfx.PutPixel( 28 + x,58 + y,0,146,14 );
	gfx.PutPixel( 29 + x,58 + y,0,146,14 );
	gfx.PutPixel( 30 + x,58 + y,0,146,14 );
	gfx.PutPixel( 47 + x,58 + y,0,146,14 );
	gfx.PutPixel( 48 + x,58 + y,0,146,14 );
	gfx.PutPixel( 49 + x,58 + y,0,146,14 );
	gfx.PutPixel( 54 + x,58 + y,0,146,14 );
	gfx.PutPixel( 55 + x,58 + y,0,146,14 );
	gfx.PutPixel( 57 + x,58 + y,0,146,14 );
	gfx.PutPixel( 58 + x,58 + y,0,146,14 );
	gfx.PutPixel( 63 + x,58 + y,0,146,14 );
	gfx.PutPixel( 64 + x,58 + y,0,146,14 );
	gfx.PutPixel( 65 + x,58 + y,0,25,2 );
	gfx.PutPixel( 66 + x,58 + y,0,146,14 );
	gfx.PutPixel( 67 + x,58 + y,0,146,14 );
	gfx.PutPixel( 68 + x,58 + y,0,146,14 );
	gfx.PutPixel( 76 + x,58 + y,0,146,14 );
	gfx.PutPixel( 77 + x,58 + y,0,146,14 );
	gfx.PutPixel( 82 + x,58 + y,0,146,14 );
	gfx.PutPixel( 83 + x,58 + y,0,146,14 );
	gfx.PutPixel( 0 + x,59 + y,0,146,14 );
	gfx.PutPixel( 1 + x,59 + y,0,146,14 );
	gfx.PutPixel( 5 + x,59 + y,0,146,14 );
	gfx.PutPixel( 6 + x,59 + y,0,146,14 );
	gfx.PutPixel( 7 + x,59 + y,0,146,14 );
	gfx.PutPixel( 9 + x,59 + y,0,146,14 );
	gfx.PutPixel( 10 + x,59 + y,0,146,14 );
	gfx.PutPixel( 11 + x,59 + y,0,25,2 );
	gfx.PutPixel( 15 + x,59 + y,0,70,6 );
	gfx.PutPixel( 16 + x,59 + y,0,146,14 );
	gfx.PutPixel( 17 + x,59 + y,0,146,14 );
	gfx.PutPixel( 19 + x,59 + y,0,146,14 );
	gfx.PutPixel( 20 + x,59 + y,0,146,14 );
	gfx.PutPixel( 22 + x,59 + y,0,146,14 );
	gfx.PutPixel( 23 + x,59 + y,0,146,14 );
	gfx.PutPixel( 24 + x,59 + y,0,25,2 );
	gfx.PutPixel( 25 + x,59 + y,0,146,14 );
	gfx.PutPixel( 26 + x,59 + y,0,146,14 );
	gfx.PutPixel( 28 + x,59 + y,0,146,14 );
	gfx.PutPixel( 29 + x,59 + y,0,146,14 );
	gfx.PutPixel( 30 + x,59 + y,0,146,14 );
	gfx.PutPixel( 31 + x,59 + y,0,146,14 );
	gfx.PutPixel( 32 + x,59 + y,0,146,14 );
	gfx.PutPixel( 33 + x,59 + y,0,146,14 );
	gfx.PutPixel( 34 + x,59 + y,0,146,14 );
	gfx.PutPixel( 35 + x,59 + y,0,146,14 );
	gfx.PutPixel( 47 + x,59 + y,0,146,14 );
	gfx.PutPixel( 48 + x,59 + y,0,146,14 );
	gfx.PutPixel( 49 + x,59 + y,0,146,14 );
	gfx.PutPixel( 54 + x,59 + y,0,146,14 );
	gfx.PutPixel( 55 + x,59 + y,0,146,14 );
	gfx.PutPixel( 57 + x,59 + y,0,146,14 );
	gfx.PutPixel( 58 + x,59 + y,0,146,14 );
	gfx.PutPixel( 59 + x,59 + y,0,146,14 );
	gfx.PutPixel( 63 + x,59 + y,0,146,14 );
	gfx.PutPixel( 64 + x,59 + y,0,146,14 );
	gfx.PutPixel( 65 + x,59 + y,0,25,2 );
	gfx.PutPixel( 66 + x,59 + y,0,146,14 );
	gfx.PutPixel( 67 + x,59 + y,0,146,14 );
	gfx.PutPixel( 68 + x,59 + y,0,146,14 );
	gfx.PutPixel( 69 + x,59 + y,0,146,14 );
	gfx.PutPixel( 70 + x,59 + y,0,146,14 );
	gfx.PutPixel( 71 + x,59 + y,0,146,14 );
	gfx.PutPixel( 72 + x,59 + y,0,146,14 );
	gfx.PutPixel( 73 + x,59 + y,0,146,14 );
	gfx.PutPixel( 76 + x,59 + y,0,146,14 );
	gfx.PutPixel( 77 + x,59 + y,0,146,14 );
	gfx.PutPixel( 82 + x,59 + y,0,146,14 );
	gfx.PutPixel( 83 + x,59 + y,0,146,14 );
	gfx.PutPixel( 0 + x,60 + y,0,146,14 );
	gfx.PutPixel( 1 + x,60 + y,0,146,14 );
	gfx.PutPixel( 6 + x,60 + y,0,146,14 );
	gfx.PutPixel( 7 + x,60 + y,0,146,14 );
	gfx.PutPixel( 9 + x,60 + y,0,146,14 );
	gfx.PutPixel( 10 + x,60 + y,0,146,14 );
	gfx.PutPixel( 11 + x,60 + y,0,146,14 );
	gfx.PutPixel( 12 + x,60 + y,0,146,14 );
	gfx.PutPixel( 13 + x,60 + y,0,146,14 );
	gfx.PutPixel( 14 + x,60 + y,0,146,14 );
	gfx.PutPixel( 15 + x,60 + y,0,146,14 );
	gfx.PutPixel( 16 + x,60 + y,0,146,14 );
	gfx.PutPixel( 17 + x,60 + y,0,146,14 );
	gfx.PutPixel( 19 + x,60 + y,0,146,14 );
	gfx.PutPixel( 20 + x,60 + y,0,146,14 );
	gfx.PutPixel( 25 + x,60 + y,0,146,14 );
	gfx.PutPixel( 26 + x,60 + y,0,146,14 );
	gfx.PutPixel( 28 + x,60 + y,0,146,14 );
	gfx.PutPixel( 29 + x,60 + y,0,146,14 );
	gfx.PutPixel( 30 + x,60 + y,0,146,14 );
	gfx.PutPixel( 47 + x,60 + y,0,146,14 );
	gfx.PutPixel( 48 + x,60 + y,0,146,14 );
	gfx.PutPixel( 49 + x,60 + y,0,146,14 );
	gfx.PutPixel( 54 + x,60 + y,0,146,14 );
	gfx.PutPixel( 55 + x,60 + y,0,146,14 );
	gfx.PutPixel( 57 + x,60 + y,0,146,14 );
	gfx.PutPixel( 58 + x,60 + y,0,146,14 );
	gfx.PutPixel( 59 + x,60 + y,0,146,14 );
	gfx.PutPixel( 60 + x,60 + y,0,146,14 );
	gfx.PutPixel( 61 + x,60 + y,0,146,14 );
	gfx.PutPixel( 62 + x,60 + y,0,146,14 );
	gfx.PutPixel( 63 + x,60 + y,0,146,14 );
	gfx.PutPixel( 64 + x,60 + y,0,146,14 );
	gfx.PutPixel( 66 + x,60 + y,0,146,14 );
	gfx.PutPixel( 67 + x,60 + y,0,146,14 );
	gfx.PutPixel( 68 + x,60 + y,0,146,14 );
	gfx.PutPixel( 76 + x,60 + y,0,146,14 );
	gfx.PutPixel( 77 + x,60 + y,0,146,14 );
	gfx.PutPixel( 78 + x,60 + y,0,146,14 );
	gfx.PutPixel( 80 + x,60 + y,0,146,14 );
	gfx.PutPixel( 81 + x,60 + y,0,146,14 );
	gfx.PutPixel( 82 + x,60 + y,0,146,14 );
	gfx.PutPixel( 83 + x,60 + y,0,146,14 );
	gfx.PutPixel( 0 + x,61 + y,0,146,14 );
	gfx.PutPixel( 1 + x,61 + y,0,146,14 );
	gfx.PutPixel( 6 + x,61 + y,0,146,14 );
	gfx.PutPixel( 7 + x,61 + y,0,146,14 );
	gfx.PutPixel( 9 + x,61 + y,0,146,14 );
	gfx.PutPixel( 10 + x,61 + y,0,146,14 );
	gfx.PutPixel( 11 + x,61 + y,0,146,14 );
	gfx.PutPixel( 12 + x,61 + y,0,146,14 );
	gfx.PutPixel( 13 + x,61 + y,0,146,14 );
	gfx.PutPixel( 14 + x,61 + y,0,146,14 );
	gfx.PutPixel( 15 + x,61 + y,0,146,14 );
	gfx.PutPixel( 16 + x,61 + y,0,146,14 );
	gfx.PutPixel( 17 + x,61 + y,0,146,14 );
	gfx.PutPixel( 19 + x,61 + y,0,146,14 );
	gfx.PutPixel( 20 + x,61 + y,0,146,14 );
	gfx.PutPixel( 25 + x,61 + y,0,146,14 );
	gfx.PutPixel( 26 + x,61 + y,0,146,14 );
	gfx.PutPixel( 28 + x,61 + y,0,146,14 );
	gfx.PutPixel( 29 + x,61 + y,0,146,14 );
	gfx.PutPixel( 30 + x,61 + y,0,146,14 );
	gfx.PutPixel( 47 + x,61 + y,0,146,14 );
	gfx.PutPixel( 48 + x,61 + y,0,146,14 );
	gfx.PutPixel( 49 + x,61 + y,0,146,14 );
	gfx.PutPixel( 54 + x,61 + y,0,146,14 );
	gfx.PutPixel( 55 + x,61 + y,0,146,14 );
	gfx.PutPixel( 58 + x,61 + y,0,146,14 );
	gfx.PutPixel( 59 + x,61 + y,0,146,14 );
	gfx.PutPixel( 60 + x,61 + y,0,146,14 );
	gfx.PutPixel( 61 + x,61 + y,0,146,14 );
	gfx.PutPixel( 62 + x,61 + y,0,146,14 );
	gfx.PutPixel( 63 + x,61 + y,0,146,14 );
	gfx.PutPixel( 66 + x,61 + y,0,146,14 );
	gfx.PutPixel( 67 + x,61 + y,0,146,14 );
	gfx.PutPixel( 68 + x,61 + y,0,146,14 );
	gfx.PutPixel( 76 + x,61 + y,0,146,14 );
	gfx.PutPixel( 77 + x,61 + y,0,146,14 );
	gfx.PutPixel( 78 + x,61 + y,0,146,14 );
	gfx.PutPixel( 79 + x,61 + y,0,146,14 );
	gfx.PutPixel( 80 + x,61 + y,0,146,14 );
	gfx.PutPixel( 81 + x,61 + y,0,146,14 );
	gfx.PutPixel( 82 + x,61 + y,0,146,14 );
	gfx.PutPixel( 0 + x,62 + y,0,142,13 );
	gfx.PutPixel( 1 + x,62 + y,0,146,14 );
	gfx.PutPixel( 2 + x,62 + y,0,146,14 );
	gfx.PutPixel( 6 + x,62 + y,0,146,14 );
	gfx.PutPixel( 7 + x,62 + y,0,146,14 );
	gfx.PutPixel( 9 + x,62 + y,0,146,14 );
	gfx.PutPixel( 10 + x,62 + y,0,146,14 );
	gfx.PutPixel( 11 + x,62 + y,0,146,14 );
	gfx.PutPixel( 15 + x,62 + y,0,70,6 );
	gfx.PutPixel( 16 + x,62 + y,0,146,14 );
	gfx.PutPixel( 17 + x,62 + y,0,146,14 );
	gfx.PutPixel( 19 + x,62 + y,0,146,14 );
	gfx.PutPixel( 20 + x,62 + y,0,146,14 );
	gfx.PutPixel( 25 + x,62 + y,0,146,14 );
	gfx.PutPixel( 26 + x,62 + y,0,146,14 );
	gfx.PutPixel( 28 + x,62 + y,0,146,14 );
	gfx.PutPixel( 29 + x,62 + y,0,146,14 );
	gfx.PutPixel( 30 + x,62 + y,0,146,14 );
	gfx.PutPixel( 47 + x,62 + y,0,146,14 );
	gfx.PutPixel( 48 + x,62 + y,0,146,14 );
	gfx.PutPixel( 49 + x,62 + y,0,146,14 );
	gfx.PutPixel( 53 + x,62 + y,0,3,0 );
	gfx.PutPixel( 54 + x,62 + y,0,146,14 );
	gfx.PutPixel( 55 + x,62 + y,0,146,14 );
	gfx.PutPixel( 59 + x,62 + y,0,146,14 );
	gfx.PutPixel( 60 + x,62 + y,0,146,14 );
	gfx.PutPixel( 61 + x,62 + y,0,146,14 );
	gfx.PutPixel( 62 + x,62 + y,0,146,14 );
	gfx.PutPixel( 66 + x,62 + y,0,146,14 );
	gfx.PutPixel( 67 + x,62 + y,0,146,14 );
	gfx.PutPixel( 68 + x,62 + y,0,146,14 );
	gfx.PutPixel( 76 + x,62 + y,0,146,14 );
	gfx.PutPixel( 77 + x,62 + y,0,146,14 );
	gfx.PutPixel( 80 + x,62 + y,0,146,14 );
	gfx.PutPixel( 81 + x,62 + y,0,146,14 );
	gfx.PutPixel( 82 + x,62 + y,0,146,14 );
	gfx.PutPixel( 83 + x,62 + y,0,70,6 );
	gfx.PutPixel( 1 + x,63 + y,0,142,13 );
	gfx.PutPixel( 2 + x,63 + y,0,146,14 );
	gfx.PutPixel( 3 + x,63 + y,0,146,14 );
	gfx.PutPixel( 4 + x,63 + y,0,146,14 );
	gfx.PutPixel( 5 + x,63 + y,0,146,14 );
	gfx.PutPixel( 6 + x,63 + y,0,146,14 );
	gfx.PutPixel( 7 + x,63 + y,0,146,14 );
	gfx.PutPixel( 9 + x,63 + y,0,146,14 );
	gfx.PutPixel( 10 + x,63 + y,0,146,14 );
	gfx.PutPixel( 11 + x,63 + y,0,146,14 );
	gfx.PutPixel( 15 + x,63 + y,0,25,2 );
	gfx.PutPixel( 16 + x,63 + y,0,146,14 );
	gfx.PutPixel( 17 + x,63 + y,0,146,14 );
	gfx.PutPixel( 19 + x,63 + y,0,146,14 );
	gfx.PutPixel( 20 + x,63 + y,0,146,14 );
	gfx.PutPixel( 25 + x,63 + y,0,146,14 );
	gfx.PutPixel( 26 + x,63 + y,0,146,14 );
	gfx.PutPixel( 28 + x,63 + y,0,146,14 );
	gfx.PutPixel( 29 + x,63 + y,0,146,14 );
	gfx.PutPixel( 30 + x,63 + y,0,146,14 );
	gfx.PutPixel( 31 + x,63 + y,0,146,14 );
	gfx.PutPixel( 32 + x,63 + y,0,146,14 );
	gfx.PutPixel( 33 + x,63 + y,0,146,14 );
	gfx.PutPixel( 34 + x,63 + y,0,146,14 );
	gfx.PutPixel( 35 + x,63 + y,0,146,14 );
	gfx.PutPixel( 36 + x,63 + y,0,146,14 );
	gfx.PutPixel( 48 + x,63 + y,0,146,14 );
	gfx.PutPixel( 49 + x,63 + y,0,146,14 );
	gfx.PutPixel( 50 + x,63 + y,0,146,14 );
	gfx.PutPixel( 51 + x,63 + y,0,146,14 );
	gfx.PutPixel( 52 + x,63 + y,0,146,14 );
	gfx.PutPixel( 53 + x,63 + y,0,146,14 );
	gfx.PutPixel( 54 + x,63 + y,0,146,14 );
	gfx.PutPixel( 60 + x,63 + y,0,146,14 );
	gfx.PutPixel( 61 + x,63 + y,0,146,14 );
	gfx.PutPixel( 66 + x,63 + y,0,146,14 );
	gfx.PutPixel( 67 + x,63 + y,0,146,14 );
	gfx.PutPixel( 68 + x,63 + y,0,146,14 );
	gfx.PutPixel( 69 + x,63 + y,0,146,14 );
	gfx.PutPixel( 70 + x,63 + y,0,146,14 );
	gfx.PutPixel( 71 + x,63 + y,0,146,14 );
	gfx.PutPixel( 72 + x,63 + y,0,146,14 );
	gfx.PutPixel( 73 + x,63 + y,0,146,14 );
	gfx.PutPixel( 74 + x,63 + y,0,146,14 );
	gfx.PutPixel( 76 + x,63 + y,0,146,14 );
	gfx.PutPixel( 77 + x,63 + y,0,146,14 );
	gfx.PutPixel( 82 + x,63 + y,0,146,14 );
	gfx.PutPixel( 83 + x,63 + y,0,146,14 );
}

// Draw a simple grid for the background clipped to the view
void Game::DrawBackgroundClipped( int cameraX,int cameraY )
{
	// horizontal lines (rows)
	// we calculate the offset of the first row from the top of the
	// screen using cameraY % GRIDRESOLUTION, and then we just keep drawing rows every
	// GRIDRESOLUTION pixels until we reach the bottom of the screen
	for( int y = GRIDRESOLUTION - cameraY % GRIDRESOLUTION; y < SCREENHEIGHT; y += GRIDRESOLUTION )
	{
		gfx.DrawLine( 0,y,SCREENWIDTH-1,y,63,63,95 );
	}

	// vertical lines (columns)
	for( int x = GRIDRESOLUTION - cameraX % GRIDRESOLUTION; x < SCREENWIDTH; x += GRIDRESOLUTION )
	{
		gfx.DrawLine( x,0,x,SCREENHEIGHT-1,63,63,95 );
	}

	// world borders
	if( cameraY == 0 )
	{
		gfx.DrawLine( 0,0,SCREENWIDTH-1,0,255,0,0 );
	}
	if( cameraX == 0 )
	{
		gfx.DrawLine( 0,0,0,SCREENHEIGHT-1,255,0,0 );
	}
	if( cameraY == WORLDHEIGHT - SCREENHEIGHT )
	{
		gfx.DrawLine( 0,SCREENHEIGHT-1,SCREENWIDTH-1,SCREENHEIGHT-1,255,0,0 );
	}
	if( cameraX == WORLDWIDTH - SCREENWIDTH )
	{
		gfx.DrawLine( SCREENWIDTH-1,0,SCREENWIDTH-1,SCREENHEIGHT-1,255,0,0 );
	}
}

void Game::UpdateFace()
{
	int speed = FACESPEED;

	// move poo using mouse
	if( mouse.IsInWindow() && mouse.LeftIsPressed() )
	{
		if( mouse.GetMouseX() + cameraX > faceX + 10 )
		{
			// check to see if face is very close to destination
			// and if so just set it to destination coordinates
			if( abs( faceX + 10 - (mouse.GetMouseX() + cameraX) ) < speed )
			{
				faceX = mouse.GetMouseX() + cameraX - 10;
			}
			else
			{
				faceX += speed;
			}
		}
		else if( mouse.GetMouseX() + cameraX < faceX + 10 )
		{
			if( abs( faceX + 10 - (mouse.GetMouseX() + cameraX) ) < speed )
			{
				faceX = mouse.GetMouseX() + cameraX - 10;
			}
			else
			{
				faceX -= speed;
			}
		}
		if( mouse.GetMouseY() + cameraY > faceY + 10 )
		{
			if( abs( faceY + 10 - (mouse.GetMouseY() + cameraY) ) < speed )
			{
				faceY = mouse.GetMouseY() + cameraY - 10;
			}
			else
			{
				faceY += speed;
			}
		}
		else if( mouse.GetMouseY() + cameraY < faceY + 10 )
		{
			if( abs( faceY + 10 - (mouse.GetMouseY() + cameraY) ) < speed )
			{
				faceY = mouse.GetMouseY() + cameraY - 10;
			}
			else
			{
				faceY -= speed;
			}
		}
	}

	// clamp to world
	if( faceX < 0 )
	{
		faceX = 0;
	}

	if( faceX + 20 > WORLDWIDTH )
	{
		faceX = WORLDWIDTH - 20;
	}
	
	if( faceY < 0 )
	{
		faceY = 0;
	}

	if( faceY + 20 > WORLDHEIGHT )
	{
		faceY = WORLDHEIGHT - 20;
	}

	int cx = faceX + 10;
	int cy = faceY + 10;

	// check if poo colliding with goal
	if( sqrt( (float)( (cx - goalX)*(cx - goalX) 
		+ (cy - goalY)*(cy - goalY) ) ) < 10 + GOALRAD )
	{
		ResetGoal();
		ting.Play();
	}
}

// update camera position based on position of face
void Game::UpdateCamera()
{
	// convert face world coordinates to screen coordinates
	int facesx = faceX - cameraX;
	int facesy = faceY - cameraY;

	// scroll camera if face is out of tracking rectangle
	if( facesx < CTRKOFFHOR )
	{
		cameraX = faceX - CTRKOFFHOR;
	}
	if( facesx + 24 > SCREENWIDTH - CTRKOFFHOR )
	{
		cameraX = faceX + 24 + CTRKOFFHOR - SCREENWIDTH;
	}
	if( facesy < CTRKOFFVERT )
	{
		cameraY = faceY - CTRKOFFVERT;
	}
	if( facesy + 24 > SCREENHEIGHT - CTRKOFFVERT )
	{
		cameraY = faceY + 24 + CTRKOFFVERT - SCREENHEIGHT;
	}

	// clamp camera so that the screen does not exceed
	// the edge of the world
	if( cameraX < 0 )
	{
		cameraX = 0;
	}
	else if( cameraX + SCREENWIDTH > WORLDWIDTH )
	{
		cameraX = WORLDWIDTH - SCREENWIDTH;
	}
	if( cameraY < 0 )
	{
		cameraY = 0;
	}
	else if( cameraY + SCREENHEIGHT > WORLDHEIGHT )
	{
		cameraY = WORLDHEIGHT - SCREENHEIGHT;
	}
}

void Game::UpdatePoo()
{
	int lottery = rand() % 200;

	for( int index = 0; index < nPoo; index++ )
	{
		if( index == lottery )
		{			
			RandomizePooVelocity( index );
		}

		poo[ index ].x += poo[ index ].vx;
		poo[ index ].y += poo[ index ].vy;

		if( poo[ index ].x < 0 )
		{
			poo[ index ].x = 0;
			poo[ index ].vx = -poo[ index ].vx;
		}
		else if( poo[ index ].x + 24 > (WORLDWIDTH-1) )
		{			
			poo[ index ].x = (WORLDWIDTH-1) - 24;
			poo[ index ].vx = -poo[ index ].vx;
		}

		if( poo[ index ].y < 0 )
		{
			poo[ index ].y = 0;
			poo[ index ].vy = -poo[ index ].vy;
		}
		else if( poo[ index ].y + 24 > (WORLDHEIGHT-1) )
		{			
			poo[ index ].y = (WORLDHEIGHT-1) - 24;
			poo[ index ].vy = -poo[ index ].vy;
		}

		// poo collision circular and centered more around the actual
		// 'poo' portion of the sprite
		int fcx = faceX + 10;
		int fcy = faceY + 10;
		int pcx = (int)poo[ index ].x + 12;
		int pcy = (int)poo[ index ].y + 14;
		if( sqrt( (float)( (fcx - pcx)*(fcx - pcx) 
			+ (fcy - pcy)*(fcy - pcy) ) ) < 10 + 10 )
		{
			board.AddScore(nGoal);
			gameIsOver = true;
			fart.Play( -1000 );
		}
	}
}

void Game::ResetGoal()
{
	goalX = (rand() % ((WORLDWIDTH-1) - GOALRAD * 2)) + GOALRAD;
	goalY = (rand() % ((WORLDHEIGHT-1) - GOALRAD * 2)) + GOALRAD;
	
	int nPooOld = nPoo;
	nPoo += 3;
	nGoal += 1;
	// cap nPoo at NPOO
	nPoo = min( nPoo,NPOO );

	// center of face
	int fcx = faceX + 10;
	int fcy = faceY + 10;
	// make sure newly revealed poo are not too close to face
	for( int index = nPooOld; index < nPoo; index++ )
	{
		// center of poo
		int pcx = (int)poo[ index ].x + 12;
		int pcy = (int)poo[ index ].y + 12;
		while( sqrt( (float)( (fcx - pcx)*(fcx - pcx) 
			+ (fcy - pcy)*(fcy - pcy) ) ) < MINAPPEARDIST )
		{
			RandomizePooPosition( index );
		}
	}
}

void Game::RandomizePooVelocity( int index )
{	
	poo[ index ].vx = (rand() % ((int)(MAXPOOSPEED * 2000) + 1)) / 1000.0f - MAXPOOSPEED;
	poo[ index ].vy = (rand() % ((int)(MAXPOOSPEED * 2000) + 1)) / 1000.0f - MAXPOOSPEED;
}

void Game::RandomizePooPosition( int index )
{	
	poo[ index ].x = (float)(rand() % (WORLDWIDTH - 24));
	poo[ index ].y = (float)(rand() % (WORLDHEIGHT - 24));
}

void Game::ResetGame()
{
	for( int index = 0; index < NPOO; index++ )
	{
		RandomizePooVelocity( index );
		RandomizePooPosition( index );
	}
	// incremented to become 3 after ResetGoal is called
	nPoo = 0;
	// incremented to become 0 after ResetGoal is called
	nGoal = -1;
	ResetGoal();
	faceX = 390;
	faceY = 290;
	gameIsOver = false;
	cameraX = 0;
	cameraY = 0;
}

void Game::ComposeFrame()
{
	// draw the background clipped to the screen
	DrawBackgroundClipped( cameraX,cameraY );

	// disc always drawn clipped whether necessary or not
	// not worth the bother for just one disc
	gfx.DrawDiscClipped( goalX-cameraX,goalY-cameraY,GOALRAD,255,255,0 );

	// poo is drawn with a non-clipped version of the function
	// if the poo is completely on-screen
	// this is because there are many poo so it makes sense to
	// be as efficient as possible here
	for( int index = 0; index < nPoo; index++ )
	{
		// calculate screen coordinates of poo
		int poosx = (int)poo[ index ].x - cameraX;
		int poosy = (int)poo[ index ].y - cameraY;

		if( poosx + 24 < 0 ||
			poosx > SCREENWIDTH - 1 ||
			poosy + 24 < 0 ||
			poosy > SCREENHEIGHT - 1 )
		{
			// offscreen so do nothing
		}
		else if( poosx < 0 ||
				 poosx + 24 > SCREENWIDTH - 1 ||
				 poosy < 0 ||
				 poosy + 24 > SCREENHEIGHT - 1 )
		{
			// partially on-screen so draw clipped
			DrawPooClipped( poosx,poosy );
		}
		else
		{
			// completely on-screen so draw unclipped
			DrawPooUnclipped( poosx,poosy );
		}
	}

	// face always drawn clipped whether necessary or not
	// not worth the bother for just one face
	DrawFaceClipped( faceX-cameraX,faceY-cameraY );

	// no need to clip; always in center of screen
	if( gameIsOver )
	{
		DrawGameOver( 375,275 );
	}
}

void Game::SaveGame()
{
	FILE* pFile = fopen( "save.dat","wb" );

	fwrite( &nPoo,sizeof( int ),1,pFile );
	fwrite( &nGoal,sizeof( int ),1,pFile );
	fwrite( &faceX,sizeof( int ),1,pFile );
	fwrite( &faceY,sizeof( int ),1,pFile );
	fwrite( &goalX,sizeof( int ),1,pFile );
	fwrite( &goalY,sizeof( int ),1,pFile );
	fwrite( &cameraX,sizeof( int ),1,pFile );
	fwrite( &cameraY,sizeof( int ),1,pFile );

	fwrite( poo,sizeof( Poo ),NPOO,pFile );

	fclose( pFile );
}

void Game::LoadGame()
{
	FILE* pFile = fopen( "save.dat","rb" );

	if( pFile )
	{
		fread( &nPoo,sizeof( int ),1,pFile );
		fread( &nGoal,sizeof( int ),1,pFile );
		fread( &faceX,sizeof( int ),1,pFile );
		fread( &faceY,sizeof( int ),1,pFile );
		fread( &goalX,sizeof( int ),1,pFile );
		fread( &goalY,sizeof( int ),1,pFile );
		fread( &cameraX,sizeof( int ),1,pFile );
		fread( &cameraY,sizeof( int ),1,pFile );
		gameIsOver = false;

		fread( poo,sizeof( Poo ),NPOO,pFile );

		fclose( pFile );
	}
}