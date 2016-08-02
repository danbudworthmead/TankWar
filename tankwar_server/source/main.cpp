#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#include <WinSock2.h>
#include "Vector2.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <bitset>

const float playerSpeed = 50.0f;
const float playerRot = 0.0006f;

int send(const SOCKET a_socket, const char* a_buffer, const int a_length)
{
	//std::cout << "Sending " << a_length << " bytes to " << (int)a_socket << std::endl;
	return send(a_socket, a_buffer, a_length, NULL);
}

int recv(const SOCKET a_socket, char* a_buffer, const int a_length)
{
	//std::cout << "Recieving " << a_length << " bytes from " << (int)a_socket << std::endl;
	return recv(a_socket, a_buffer, a_length, NULL);
}

struct PlayerData
{
	SOCKET socket;
	Vector2 pos = Vector2(101, 102);
	float baseRot = 0.0f, turretRot = 0.0f;
	bool isAlive = true;
} playerDatas[4];

int connectionCounter = 0;
const int maxConnections = sizeof(playerDatas) / sizeof(PlayerData);

bool CheckBit(int number, int index)
{
	return (number >> index) & 1;
}

void ClientHandlerThread(int index)
{
	struct RecvData
	{
		unsigned short int buttons;
		unsigned char triggers[2];
		short int turretRot, LX;
	} recvData;

	//===========SEND_DATA=============
	//	10 bits for X
	//	10 bits for Y
	//	9 bits for top rot
	//	9 bits for bot rot
	//	3 bits for ID
	//	1 bit for isAlive
	//	42 bits in total
	//	char array of 6 bytes!
	//=================================
	char sendBitsetBuffer[6]; // only 6 bytes for the bitsetData!
	std::bitset<42> bitsetData;
	struct SendData
	{
		short int x, y;
		short int baseRot, turretRot;
		int ID;
		bool isAlive;
	} sendData;
	sendData.ID = index;

	//===========SEND_DATA=============
	//	16 bits for buttons
	//	4 bits for left trigger
	//	4 bits for right trigger
	//	9 bits for turretRot
	//	7 bits for LX
	//  40 bits / 5 bytes
	//=================================
	std::bitset<40> bitsetRecvData;
	char bitsetRecvDataBuffer[5];

	int iRecv;
	while (recv(playerDatas[index].socket, bitsetRecvDataBuffer, sizeof(bitsetRecvDataBuffer)) > 0)
	{
		memcpy(&bitsetRecvData, bitsetRecvDataBuffer, sizeof(bitsetRecvDataBuffer));

		int pointer = 0;
		std::bitset<16> size16bitset;
		for (int i = 0; i < 16; ++i, ++pointer)
			size16bitset[i] = bitsetRecvData[pointer];
		recvData.buttons = size16bitset.to_ulong();

		std::bitset<4> size4bitset;
		for (int i = 0; i < 4; ++i, ++pointer)
			size4bitset[i] = bitsetRecvData[pointer];
		recvData.triggers[0] = size4bitset.to_ulong();

		for (int i = 0; i < 4; ++i, ++pointer)
			size4bitset[i] = bitsetRecvData[pointer];
		recvData.triggers[1] = size4bitset.to_ulong();

		std::bitset<9> size9bitset;
		for (int i = 0; i < 9; ++i, ++pointer)
			size9bitset[i] = bitsetRecvData[pointer];
		recvData.turretRot = size9bitset.to_ulong();

		std::bitset<5> size5bitset;
		for (int i = 0; i < 5; ++i, ++pointer)
			size5bitset[i] = bitsetRecvData[pointer];
		recvData.LX = size5bitset.to_ulong();
		
		//==============================================
		/// Begin Processing Input
		//==============================================
		//Handle Buttons
		for (int i = 0; i < 16; i++)
		{
			bool answer = CheckBit(recvData.buttons, i);
			switch (i)
			{
			case 9:
				//LB
				break;
			case 10:
				//RB
				break;
			case 12:
				//A
				break;
			case 13:
				//B
				break;
			case 14:
				//X
				break;
			case 15:
				//Y
				break;
			default:
				break;
			}
			//std::cout << CheckBit(data.buttons, i) << " ";
		}
		//std::cout << std::endl;

		float RT = recvData.triggers[0] / (float)UCHAR_MAX;
		float LT = recvData.triggers[1] / (float)UCHAR_MAX;
		float fwdback = RT - LT;
		float LX = recvData.LX - 16; //Max Int
		//float LY = recvData.thumbSticks[1] / (float)32767;

		
		//float RX = recvData.RX / (float) 32767; //Max Int
		//float RY = recvData.RY / (float) 32767;
		//===================================================================================
		/// Stop Processing Input
		//===================================================================================

		//Handle Base Rotation
		playerDatas[index].baseRot += LX * playerRot;
		//if (playerDatas[index].baseRot < -2.f)
		//	playerDatas[index].baseRot = 2.f;
		//if (playerDatas[index].baseRot > 2.f)
		//	playerDatas[index].baseRot = -2.f;
		//std::cout << playerDatas[index].baseRot << std::endl;		

		//Handle Turret Rotation
		playerDatas[index].turretRot = recvData.turretRot * DEG2RAD / PI + 135;
		//playerDatas[index].turretRot = Vector2(RX, RY).Normalise().Bearing() / PI;
		//std::cout << playerDatas[index].turretRot << std::endl;

		//Handle Position
		playerDatas[index].pos += Vector2(playerDatas[index].baseRot) * playerSpeed * fwdback;
		//std::cout << playerDatas[index].pos.x << " " << playerDatas[index].pos.y << std::endl;

		//Prepare the send data
		sendData.x				= playerDatas[index].pos.x;
		sendData.y				= playerDatas[index].pos.y;
		sendData.baseRot		= playerDatas[index].baseRot*RAD2DEG;
		sendData.turretRot		= playerDatas[index].turretRot*RAD2DEG + 180;
		sendData.isAlive		= playerDatas[index].isAlive;
		sendData.ID				= index;

		pointer = 0;
		for (int i = 0; i < 10; ++i, ++pointer)
			bitsetData[pointer] = CheckBit(sendData.x, i);
		for (int i = 0; i < 10; ++i, ++pointer)
			bitsetData[pointer] = CheckBit(sendData.y, i);
		for (int i = 0; i < 9; ++i, ++pointer)
			bitsetData[pointer] = CheckBit(sendData.baseRot, i);
		for (int i = 0; i < 9; ++i, ++pointer)
			bitsetData[pointer] = CheckBit(sendData.turretRot, i);
		for (int i = 0; i < 3; ++i, ++pointer)
			bitsetData[pointer] = CheckBit(sendData.ID, i);
		for (int i = 0; i < 1; ++i, ++pointer)
			bitsetData[pointer] = CheckBit(sendData.isAlive, i);

		//std::cout << bitsetData << std::endl;
		memcpy(sendBitsetBuffer, &bitsetData, sizeof(sendBitsetBuffer));

		for (int i = 0; i < connectionCounter; i++)
		{
			send(playerDatas[i].socket, sendBitsetBuffer, sizeof(sendBitsetBuffer));
		}

	}
	closesocket(playerDatas[index].socket);
	std::cout << "Client " << index << " has disconnected." << std::endl;
}

int main()
{
	//WinSock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr); //length of the address (required for accept call)
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Broadcast locally
	addr.sin_port = htons(1111); //Port
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //Create socket to listen for new connections
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //Bind the address to the socket
	listen(sListen, SOMAXCONN); //Places sListen socket in a state in which it is listening for an incoming connection. Note:SOMAXCONN = Socket Oustanding Max Connections

	SOCKET newConnection; //Socket to hold the client's connection

	for (int i = 0; i <= maxConnections; ++i)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); //Accept a new connection
		if (newConnection == 0) //If accepting the client connection failed
		{
			std::cout << "Failed to accept the client's connection." << std::endl;
		}
		else //If client connection properly accepted
		{
			std::cout << "Client Connected!" << std::endl;
			//char MOTD[256] = "You have connected to the Tank War Server!"; //Create buffer with message of the day
			//send(newConnection, MOTD, sizeof(MOTD), NULL); //Send MOTD buffer
			playerDatas[i].socket = newConnection;
			++connectionCounter;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandlerThread, (LPVOID)(i), NULL, NULL); // Create a thread for each client
		}
	}

	system("pause");

	return 0;
}