#include<windows.h>
#include<iostream>
#include<chrono>
#include<thread>
#include<string>
#include<conio.h> //Keyboard Input
#include "Map.h"
#include "Entity.h"
#include "Position.h"
#include "Player.h"
#include "Rock.h"
#include "Wall.h"
#include "Pitfall.h"
#include "Lock.h"
#include "Key.h"
#include "Skeleton.h"
#include "Spikes.h"
#include "Relics.h"

int main(void)
{
    Entity* EntitiesArr[200] = {};
    int MapLevel = 0;
    std::cin >> MapLevel;
    int Moves = Map::GetMapMoves(MapLevel);
    std::string TextMap = Map::GetMapChosen(MapLevel);
    std::string TextMapCommaless = ""; 
    //Get TextMap Size
    int TextMapSize = 0;
    int TextMapBreadth = 0;
    int TextMapLength = 0;
    for (unsigned int i = 0; i < TextMap.length(); i++)  //Creates a text without commas
    {
        if (TextMap[i] == ',')
        {
            TextMapBreadth++;
        }
        else
        {
            TextMapCommaless += TextMap[i];
            TextMapSize++;
        }
    }
    TextMapBreadth++;
    TextMapLength = TextMapSize / TextMapBreadth;
    int NumberOfEntities = sizeof(EntitiesArr) / sizeof(int);
    for (int i = 0; i < NumberOfEntities; i++) //Intialise Objs pointer as nullptr
    {
        EntitiesArr[i] = nullptr;
    }
    int PCurrentx, PCurrenty;
    std::string TextOutput;
    bool Quit = false;
    int PlayerArrPos = 0,RelicArrPos = 0;
    while (Quit != true)
    {
        
        //Check Quit
        if (EntitiesArr[PlayerArrPos] == nullptr || Player::GetMoves() == 0 || EntitiesArr[RelicArrPos] == nullptr)
        {  //Clear the array and intialise with nullptr
            for (int i = 0; i < NumberOfEntities; i++) //Deleting of Objs
            {
                delete EntitiesArr[i];
                EntitiesArr[i] = nullptr;
            }
            //Auto Intialise 
            int Temp = 0,Intialx = 0, Intialy = 0;
            for (int i = 1; i <= TextMapSize; i++)
            {
                //Intialx stores Length
                Intialx = i - int(floor(i / TextMapLength)) * TextMapLength;
                if (Intialx == 0)
                {
                    Intialx = TextMapLength;
                }
                //Intialy stores Breadth
                Temp = i;
                Intialy = 0;
                while (Temp > TextMapLength)
                {
                    Temp -= TextMapLength;
                    Intialy += 1;
                    
                }
                Intialy++;
                if (TextMapCommaless[i  - 1] == 'R')
                {
                    EntitiesArr[i  - 1 ] = new Rock(Intialy,Intialx);
                }
                else if (TextMapCommaless[i - 1] == 'P')
                {
                    EntitiesArr[i  - 1] = new Player(Intialy, Intialx); //Breadth,Length
                    PlayerArrPos = i  - 1;
                }
                else if (TextMapCommaless[i  - 1] == 'W')
                {
                    EntitiesArr[i  - 1] = new Wall(Intialy, Intialx);
                }
                else if (TextMapCommaless[i  - 1] == 'L')
                {
                    EntitiesArr[i  - 1] = new Lock(Intialy, Intialx);
                }
                else if (TextMapCommaless[i  - 1] == 'K')
                {
                    EntitiesArr[i  - 1] = new Key(Intialy, Intialx);
                }
                else if (TextMapCommaless[i  - 1] == '0')
                {
                    EntitiesArr[i- 1] = new Pitfall(Intialy, Intialx);
                }
                else if (TextMapCommaless[i - 1] == 'S')
                {
                    EntitiesArr[i - 1] = new Skeleton(Intialy, Intialx);
                }
                else if (TextMapCommaless[i - 1] == 'i')
                {
                    EntitiesArr[i  - 1] = new Spikes(Intialy, Intialx, false);
                }
                else if (TextMapCommaless[i  - 1] == 'I')
                {
                    EntitiesArr[i  - 1] = new Spikes(Intialy, Intialx, true);
                }
                else if (TextMapCommaless[i  - 1] == 'T')
                {
                    EntitiesArr[i  - 1] = new Relics(Intialy, Intialx, MapLevel);
                    RelicArrPos = i  - 1;
                }
                else if (TextMapCommaless[i- 1] == ',' || TextMap[i - 1] == ' ')
                {//do nothing
                }
            }
            Player::SetMoves(Moves);
            TextOutput = "";
        }
        else if (EntitiesArr[0] != nullptr)
        {
            //Update Map
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            LockWindowUpdate(GetConsoleWindow());
            system("cls");
            Map* GameMap = new Map;
            for (int i = 0; i < TextMapSize; i++)
            {
               if (EntitiesArr[i] != nullptr) //Prevents the code trying to get data from something that doesnt exist
               {
                    GameMap->SetGameMap((EntitiesArr[i]->GetEntityPosition()).getx(), (EntitiesArr[i]->GetEntityPosition()).gety(), EntitiesArr[i]->GetSymbol());
               }
            }
            GameMap->PrintGameMap();
            std::cout << "Moves Left: " << Player::GetMoves();
            delete GameMap;
            LockWindowUpdate(NULL);

            //Prevents the code trying to get data from something that doesnt exist
            if (EntitiesArr[PlayerArrPos] != nullptr)
            {
                PCurrentx = (EntitiesArr[PlayerArrPos]->GetEntityPosition()).getx(); //Player current position
                PCurrenty = (EntitiesArr[PlayerArrPos]->GetEntityPosition()).gety();
            }
            int CurrentMoves = Player::GetMoves();
            EntitiesArr[PlayerArrPos]->move();
            //Spike Activity
            for (int i = 0; i < NumberOfEntities; i++)
            {
                if (EntitiesArr[PlayerArrPos] != nullptr)
                {
                    if (dynamic_cast<Spikes*>(EntitiesArr[i]) != 0 && Player::GetMoves() != CurrentMoves)
                    {
                        (static_cast<Spikes*>(EntitiesArr[i]))->SpikesActivity();
                    }
                }
            }
            int Tempx, Tempy;
            //Check Collision for skeleton with player, then see if there is pitfall, wall,rock,lock -die, not affected by spikes and can step on key
            for (int i = 0; i < NumberOfEntities; i++) //Go Through Skeletons
            {
                if ((EntitiesArr[i] != nullptr && EntitiesArr[PlayerArrPos] != nullptr) && dynamic_cast<Skeleton*>(EntitiesArr[i]) != 0) //Prevents the code trying to get data from something that doesnt exist and checks whether obj is skeleton
                {
                    if ((EntitiesArr[i]->GetEntityPosition()).getx() == (EntitiesArr[PlayerArrPos]->GetEntityPosition()).getx() && (EntitiesArr[i]->GetEntityPosition()).gety() == (EntitiesArr[PlayerArrPos]->GetEntityPosition()).gety())
                    {
                        //Make Skeleton Move
                        EntitiesArr[i]->move();
                        for (int i2 = 0; i2 < NumberOfEntities; i2++)   //Compare with all entities
                        {
                            if (EntitiesArr[i2] != nullptr && EntitiesArr[i] != nullptr) //Prevents the code trying to get data from something that doesnt exist, and also the deleted pointers
                            {
                                if (i != i2) //Prevents from comparing with itself and code trying to get data from something that doesnt exist
                                {
                                    if (dynamic_cast<Pitfall*>(EntitiesArr[i2]) != 0 && ((EntitiesArr[i]->GetEntityPosition()).getx() == (EntitiesArr[i2]->GetEntityPosition()).getx() && (EntitiesArr[i]->GetEntityPosition()).gety() == (EntitiesArr[i2]->GetEntityPosition()).gety()))
                                    { //Check if it is Pitfall, skeleton dies
                                        delete EntitiesArr[i];
                                        EntitiesArr[i] = nullptr;
                                    }
                                    else if ((dynamic_cast<Key*>(EntitiesArr[i2]) != 0 || dynamic_cast<Spikes*>(EntitiesArr[i2]) != 0) && ((EntitiesArr[i]->GetEntityPosition()).getx() == (EntitiesArr[i2]->GetEntityPosition()).getx() && (EntitiesArr[i]->GetEntityPosition()).gety() == (EntitiesArr[i2]->GetEntityPosition()).gety()))
                                    { //Allow Skeleton to OverLap Key
                                        //do nothing
                                    }
                                    else if (dynamic_cast<Spikes*>(EntitiesArr[i]) != 0 && ((EntitiesArr[0]->GetEntityPosition()).getx() == (EntitiesArr[i]->GetEntityPosition()).getx() && (EntitiesArr[0]->GetEntityPosition()).gety() == (EntitiesArr[i]->GetEntityPosition()).gety()))
                                    {//Allow skeleton to overlap with spikes
                                        //do nothing
                                    }
                                    else if ((EntitiesArr[i]->GetEntityPosition()).getx() == (EntitiesArr[i2]->GetEntityPosition()).getx() && (EntitiesArr[i]->GetEntityPosition()).gety() == (EntitiesArr[i2]->GetEntityPosition()).gety())
                                    { //Collide with anything else will be destroyed
                                        delete EntitiesArr[i];
                                        EntitiesArr[i] = nullptr;
                                    }
                                    else
                                    {
                                        EntitiesArr[PlayerArrPos]->SetEntityPosition(PCurrentx, PCurrenty);
                                    }
                                }
                            }
                        }
                        i = NumberOfEntities; //break out of for loop
                    }

                }
            }
            //Check Collision for rock with player, then see if there is pitfall key or others in its way
            for (int i = 0; i < NumberOfEntities; i++) //Go Through Rocks
            {
               if ((EntitiesArr[i] != nullptr && EntitiesArr[PlayerArrPos] != nullptr) && dynamic_cast<Rock*>(EntitiesArr[i]) != 0) //Prevents the code trying to get data from something that doesnt exist
               {
                   if ((EntitiesArr[i]->GetEntityPosition()).getx() == (EntitiesArr[PlayerArrPos]->GetEntityPosition()).getx() && (EntitiesArr[i]->GetEntityPosition()).gety() == (EntitiesArr[PlayerArrPos]->GetEntityPosition()).gety())
                   {
                       Tempx = (EntitiesArr[i]->GetEntityPosition()).getx();
                       Tempy = (EntitiesArr[i]->GetEntityPosition()).gety();
                       
                       //Make Rock Move
                       EntitiesArr[i]->move();
                       for (int i2 = 0; i2 < NumberOfEntities; i2++)   //Compare with all entities
                       {
                           if (EntitiesArr[i2] != nullptr && EntitiesArr[i] != nullptr) //Prevents the code trying to get data from something that doesnt exist, and also the deleted pointers
                           {
                               if (i != i2) //Prevents from comparing with itself and code trying to get data from something that doesnt exist
                               {
                                   if (dynamic_cast<Pitfall*>(EntitiesArr[i2]) != 0 && ((EntitiesArr[i]->GetEntityPosition()).getx() == (EntitiesArr[i2]->GetEntityPosition()).getx() && (EntitiesArr[i]->GetEntityPosition()).gety() == (EntitiesArr[i2]->GetEntityPosition()).gety()))
                                   { //Check if it is Pitfall, both rock and pitfall self-destruct
                                       delete EntitiesArr[i];
                                       EntitiesArr[i] = nullptr;
                                       delete EntitiesArr[i2];
                                       EntitiesArr[i2] = nullptr;
                                   } 
                                   else if (dynamic_cast<Key*>(EntitiesArr[i2]) != 0 &&((EntitiesArr[i]->GetEntityPosition()).getx() == (EntitiesArr[i2]->GetEntityPosition()).getx() && (EntitiesArr[i]->GetEntityPosition()).gety() == (EntitiesArr[i2]->GetEntityPosition()).gety()))
                                   { //Allow Rock to OverLap Key
                                       //do nothing
                                   }
                                   else if ((EntitiesArr[i]->GetEntityPosition()).getx() == (EntitiesArr[i2]->GetEntityPosition()).getx() && (EntitiesArr[i]->GetEntityPosition()).gety() == (EntitiesArr[i2]->GetEntityPosition()).gety())
                                   { //Prevent Rock from colliding with anything else
                                       EntitiesArr[i]->SetEntityPosition(Tempx, Tempy);
                                   }
                                   else
                                   {
                                       EntitiesArr[PlayerArrPos]->SetEntityPosition(PCurrentx, PCurrenty);
                                   }
                               }
                           }
                       }
                       i = NumberOfEntities; //break out of for loop
                   }
                   
               }
            }
            //Check Player Collision with Relic,Wall,Pitfall,Lock and Key
            for (int i = 0; i < NumberOfEntities; i++)
            {

                if (EntitiesArr[i] != nullptr && EntitiesArr[PlayerArrPos] != nullptr) //Prevents the code trying to get data from something that doesnt exist
                {
                    if (dynamic_cast<Pitfall*>(EntitiesArr[i]) != 0 && ((EntitiesArr[PlayerArrPos]->GetEntityPosition()).getx() == (EntitiesArr[i]->GetEntityPosition()).getx() && (EntitiesArr[PlayerArrPos]->GetEntityPosition()).gety() == (EntitiesArr[i]->GetEntityPosition()).gety()))
                    { //Check if it is Pitfall, Player died
                        delete EntitiesArr[PlayerArrPos];
                        EntitiesArr[PlayerArrPos] = nullptr;
                    }
                    else if (dynamic_cast<Wall*>(EntitiesArr[i]) != 0 && ((EntitiesArr[PlayerArrPos]->GetEntityPosition()).getx() == (EntitiesArr[i]->GetEntityPosition()).getx() && (EntitiesArr[PlayerArrPos]->GetEntityPosition()).gety() == (EntitiesArr[i]->GetEntityPosition()).gety()))
                    {  //Collision with wall
                        EntitiesArr[PlayerArrPos]->SetEntityPosition(PCurrentx, PCurrenty);
                    }
                    else if (dynamic_cast<Lock*>(EntitiesArr[i]) != 0 && ((EntitiesArr[PlayerArrPos]->GetEntityPosition()).getx() == (EntitiesArr[i]->GetEntityPosition()).getx() && (EntitiesArr[PlayerArrPos]->GetEntityPosition()).gety() == (EntitiesArr[i]->GetEntityPosition()).gety()))
                    {  //Collision with lock
                        if ((dynamic_cast<Player*>(EntitiesArr[PlayerArrPos]))->GetHaveKey() == true)
                        {
                            delete EntitiesArr[i];
                            EntitiesArr[i] = nullptr;

                        }
                        else //No key cannot move
                        {
                            EntitiesArr[PlayerArrPos]->SetEntityPosition(PCurrentx, PCurrenty);
                        }
                    }
                    else if (dynamic_cast<Key*>(EntitiesArr[i]) != 0 && ((EntitiesArr[PlayerArrPos]->GetEntityPosition()).getx() == (EntitiesArr[i]->GetEntityPosition()).getx() && (EntitiesArr[PlayerArrPos]->GetEntityPosition()).gety() == (EntitiesArr[i]->GetEntityPosition()).gety()))
                    { //Collision with key
                        delete EntitiesArr[i];
                        EntitiesArr[i] = nullptr;
                        (dynamic_cast<Player*>(EntitiesArr[PlayerArrPos]))->SetHaveKey(true);
                    }
                    else if (dynamic_cast<Spikes*>(EntitiesArr[i]) != 0 && ((EntitiesArr[PlayerArrPos]->GetEntityPosition()).getx() == (EntitiesArr[i]->GetEntityPosition()).getx() && (EntitiesArr[PlayerArrPos]->GetEntityPosition()).gety() == (EntitiesArr[i]->GetEntityPosition()).gety()))
                    {//Collision with spikes
                        if ((static_cast<Spikes*>(EntitiesArr[i]))->GetSymbol() == 'I')
                        { //Spike Active, User total number of Moves are decreased by 1
                            Player::MovesDecreaseByOne();
                        }
                        else //Spike inactive, therefore nothing happens
                        {//do nothing
                        }
                    }
                    else if (dynamic_cast<Relics*>(EntitiesArr[RelicArrPos]) != 0 && ((EntitiesArr[PlayerArrPos]->GetEntityPosition()).getx() == (EntitiesArr[RelicArrPos]->GetEntityPosition()).getx() && (EntitiesArr[PlayerArrPos]->GetEntityPosition()).gety() == (EntitiesArr[RelicArrPos]->GetEntityPosition()).gety()))
                    {
                        std::string TextOutput = (static_cast<Relics*>(EntitiesArr[RelicArrPos]))->RelicDialogue();
                        delete EntitiesArr[RelicArrPos];
                        EntitiesArr[RelicArrPos] = nullptr;
                        std::cout <<std::endl << TextOutput;
                        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                    }
                }
            }
        }
    }
    
    return 0;
}