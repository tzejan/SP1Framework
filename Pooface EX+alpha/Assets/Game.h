/****************************************************************************************** 
 *	Chili DirectX Framework Version 11.12.17											  *	
 *	Game.h																				  *
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
#pragma once

#include "D3DGraphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Sound.h"
#include "string.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NPOO 25
#define GOALRAD 25
#define NSCORE 10
#define TIMEBUFLEN 20
#define MAXPOOSPEED 4.0f
#define MINAPPEARDIST 30.0f
#define FACESPEED 7
#define WORLDHEIGHT 1199
#define WORLDWIDTH 1599
// resolution of background grid
#define GRIDRESOLUTION 50
// camera tracking offset vertical/horizontal
// is the offset from the edge off the screen 
// to the camera tracking rectangle
#define CTRKOFFVERT 180
#define CTRKOFFHOR 240
#define BOARDFILE "highscore.txt"

class Game
{
private:
	class ScoreBoard
	{
	private:
		class Score
		{
		public:
			Score(int score)
			{
				this->score = score;

				char buffer[TIMEBUFLEN];
				time_t curTime = ::time(NULL);
				strftime(buffer, TIMEBUFLEN, "%X/%x", localtime(&curTime));
				time = (char*)malloc(strlen(buffer) + 1);
				strcpy(time, buffer);
				NextScore = NULL;
			}
			Score(FILE* file)
			{
				char buffer[TIMEBUFLEN];
				fscanf(file, "%d %s", &score, buffer);
				time = (char*)malloc(strlen(buffer) + 1);
				strcpy(time, buffer);

				fseek(file, 4, SEEK_CUR);
				fgetc(file);

				if (!feof(file))
				{
					NextScore = new Score(file);
				}
				else
				{
					NextScore = NULL;
				}
			}
			void serialize(FILE* file, int index)
			{
				fprintf(file, "%d.\t%d\t%s\n", index, score, time);
				if (NextScore)
				{
					NextScore->serialize(file, (index + 1));
				}
			}
			bool Insert(Score* inScore)
			{
				if (inScore->score <= score)
				{
					if (NextScore == NULL)
					{
						NextScore = inScore;
						return false;
					}
					else{
						if (NextScore->Insert(inScore))
						{
							NextScore = inScore;
							return false;
						}
						else
						{
							return false;
						}
					}
				}
				else
				{
					inScore->NextScore = this;
					return true;
				}
			}
			void Test()
			{
				printf("%d:%s", score, time);
				if (NextScore != NULL)
				{
					NextScore->Test();
				}
			}
			~Score()
			{
				free(time);
				if (NextScore != NULL)
				{
					delete NextScore;
					NextScore = NULL;
				}
			}
		private:
			int score;
			char* time;
			Score* NextScore;
		};
		Score* FirstScore;
		char* FileName;
		void Serialize()
		{
			FILE* pFile = fopen(FileName, "w");
			if (FirstScore)
			{
				FirstScore->serialize(pFile, 1);
			}
			fclose(pFile);
		}
	public:
		ScoreBoard(const char* FileName)
			:
			FirstScore(NULL)
		{
			FILE* pFile = fopen(FileName, "r");
			this->FileName = (char*)malloc(strlen(FileName) + 1);
			strcpy(this->FileName, FileName);
			if (pFile)
			{
				fseek(pFile, 2, SEEK_CUR);
				fgetc(pFile);
				if (!feof(pFile))
				{
					FirstScore = new Score(pFile);
				}
				else
				{
					FirstScore = NULL;
				}
				fclose(pFile);
			}
		}
		~ScoreBoard()
		{
			if (FirstScore != NULL)
			{
				Serialize();
				delete FirstScore;
				FirstScore = NULL;
			}
			free(FileName);
		}
		void AddScore(int score)
		{
			if (FirstScore == NULL)
			{
				FirstScore = new Score(score);
			}
			else
			{
				Score* NewScore = new Score(score);
				if (FirstScore->Insert(NewScore))
				{
					FirstScore = NewScore;
				}
			}
		}
	};
	struct Poo
	{
		float x;
		float y;
		float vx;
		float vy;
	};
public:
	Game( HWND hWnd,const KeyboardServer& kServer,const MouseServer& mServer );
	~Game();
	void Go();
private:
	void ComposeFrame();
	/********************************/
	/*  User Functions              */

	void DrawFaceClipped( int x,int y );
	void DrawPooClipped( int x,int y );
	void DrawPooUnclipped( int x,int y );
	void DrawGameOver( int x,int y );
	// unlike drawface and drawpoo, drawbackground works
	// in world space instead of screen space, so it needs
	// the camera coordinates
	void DrawBackgroundClipped( int cameraX,int cameraY );
	void UpdateFace();
	void UpdatePoo();
	void UpdateCamera();
	void RandomizePooVelocity( int index );
	void RandomizePooPosition( int index );
	void ResetGame();
	void ResetGoal();

	void SaveGame();
	void LoadGame();
	/********************************/
private:
	D3DGraphics gfx;
	KeyboardClient kbd;
	MouseClient mouse;
	DSound audio;
	/********************************/
	/*  User Variables              */
	int nPoo;
	int nGoal;
	bool gameIsOver;

	int faceX;
	int faceY;
	int goalX;
	int goalY;
	int cameraX;
	int cameraY;

	Poo poo[ NPOO ];

	ScoreBoard board;

	Sound fart;
	Sound ting;
	/********************************/
};