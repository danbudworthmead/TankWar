#ifndef __LOCAL_GAME_H_
#define __LOCAL_GAME_H_

//Additional header includes
#include <vector>
#include "Actor.h"

//Forward declaration
class XboxController;
class Player;

//Class local game
class LocalGame
{
	const static int MAX_PLAYERS = 4;
	XboxController* pXboxControllers[MAX_PLAYERS];
	Player* pPlayers[MAX_PLAYERS];
	int numberOfConnectedGamepads;

	std::vector<Actor*>gameTiles;
	std::vector<Maths::Vector2>possiblePlayerSpawns;

	//Other Methods
	int InitialiseGamepads();
	int ConnectGamepads();
	int InitialisePlayers();
	int StartDrawing();
	int LoadRandomLevel();
	std::vector<std::string> GetLevelNames();
	int LoadLevel(std::string a_sLevelName);
	int UpdateGame();
	int StopDrawing();
	int UpdateScores();
	int Terminate();
	int DrawHitboxes();

public:
	//Main Method
	int RunLocalGame();
};

#endif //__LOCAL_GAME_H_