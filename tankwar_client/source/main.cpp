#include "main.h"
#include "NetworkGame.h"
#include "LocalGame.h"
#include "LevelLoading.h"
#include "Enumerations.h"
#include "MenuButton.h"
#include <iostream>
#include <time.h>
#include <bitset>

int main()
{
	//Seed the random value
	srand((unsigned int)time(0));

	//GameStates classed used to determine the screen of the game
	enum class GameStates
	{
		Game_Local, Game_Networked, Menu_System
	} currentGameState = GameStates::Game_Local; //Change this to see the multiplayer version in action

	Maths::Vector2 screenSize = Maths::Vector2(1024, 768);

	if (UG::Create((int)screenSize.x, (int)screenSize.y, false, "Tank Wars!", 0, 0))
	{
		UG::AddFont("./fonts/invaders.fnt");

		//Create Menu Buttons
		MenuButton QuickStartGame = MenuButton("./images/buttons/QuickGame.png", screenSize * 0.5f, Maths::Vector2(512, 128), UG::SColour(255, 255, 255, 255));
		MenuButton QuitGame = MenuButton("./images/buttons/Quit.png", screenSize * 0.25f, Maths::Vector2(512, 128), UG::SColour(255, 255, 255, 255));

		do {
			UG::ClearScreen();

			switch (currentGameState)
			{
			case GameStates::Menu_System:
				QuickStartGame.StartDrawing();
				QuitGame.StartDrawing();
				do
				{
					UG::ClearScreen();
				} while (UG::Process() && currentGameState == GameStates::Menu_System);
				QuickStartGame.StopDrawing();
				QuitGame.StopDrawing();
				break;
			case GameStates::Game_Local:
				LocalGame::Instance()->Update();
				break;
			case GameStates::Game_Networked:
				NetworkGame::Instance()->Update();
				break;
			default:
				break;
			}
		} while (UG::Process());
		UG::Dispose();
	}
	return 1;
}

/*
/*	Code for mouse clicks on Menu Systems
/* 
bool canClick = true;
do
{
	UG::ClearScreen();
	bool isClicked = false;
	if (!isClicked && canClick && UG::GetMouseButtonDown(0))
	{
		isClicked = true;
		canClick = false;
	}
	if (UG::GetMouseButtonReleased(0))
	{
		canClick = true;
	}
	std::cout << isClicked << std::endl;
} while (UG::Process());
*/