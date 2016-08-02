#ifndef __NETWORK_GAME_H_
#define __NETWORK_GAME_H_
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include "Vector2.h"
class NetworkPlayer;
class NetworkGame
{
	static NetworkGame* s_instance;
	NetworkGame();
	~NetworkGame();
	SOCKET _socket;
	NetworkPlayer* _networkPlayers[4];
	static void ClientThread();

	struct PlayerData
	{
		short int x, y;
		short int baseRot, turretRot;
		int ID = 0;
		bool isAlive;
	};

	//Started at 24
	//Down to 16 by using short ints instead of ints
	//Down to 12 by removing LY as it's not needed
	struct Data
	{
		unsigned short int buttons;
		unsigned char triggers[2];
		short int turretRot, LX;
	} data;

	char bitsetSendBuffer[5];

	HANDLE thread_;

public:
	int Update();
	static NetworkGame* Instance();
};

#endif //__NETWORK_GAME_H_