#include "NetworkGame.h"
#include "NetworkPlayer.h"
#include "XboxController.h"
#include "LevelLoading.h"
#include "UGFW++.h"
#include "Enumerations.h"
#include <iostream>
#include <bitset>

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

NetworkGame* NetworkGame::s_instance = nullptr;

NetworkGame* NetworkGame::Instance()
{
	if (!s_instance)
		s_instance = new NetworkGame();
	return s_instance;
}

NetworkGame::NetworkGame()
{ 
	for (int i = 0; i < 4; ++i)
	{
		_networkPlayers[i] = new NetworkPlayer();
	}
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		std::cout << "Winsock failed to startup!" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Address = localhost (this pc)
	addr.sin_port = htons(1111); //Port = 1111
	addr.sin_family = AF_INET; //IPv4 Socket

	_socket = socket(AF_INET, SOCK_STREAM, NULL); //Set Connection socket
	if (connect(_socket, (SOCKADDR*)&addr, sizeofaddr) != 0) //If we are unable to connect...
	{
		std::cout << "Failed to Connect" << std::endl;
	}
	std::cout << "Connected!" << std::endl;
	thread_ = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL); // Create a thread for each client

}

NetworkGame::~NetworkGame()
{
	TerminateThread(thread_, NULL);
	for (int i = 0; i < 4; ++i)
		delete _networkPlayers[i];
	s_instance = nullptr;
}

int NetworkGame::Update()
{
	XboxController xboxController(1);
	//=============================================
	// If Xbox Controller is connected
	//=============================================
	if (xboxController.IsConnected())
	{
		XINPUT_STATE xState;
		xState = xboxController.GetState();

		data.buttons = xState.Gamepad.wButtons;
		data.triggers[0] = xState.Gamepad.bRightTrigger;
		data.triggers[1] = xState.Gamepad.bLeftTrigger;

		if (abs(xState.Gamepad.sThumbLX) > INPUT_LEFT_THUMB_DEADZONE)
			data.LX = xState.Gamepad.sThumbLX;
		else
			data.LX = 0;

		float RX = xState.Gamepad.sThumbRX;
		float RY = xState.Gamepad.sThumbRY;
		float magnitude = sqrt(RX*RX + RY*RY);
		float normalizedRX = RX / magnitude;
		float normalizedRY = RY / magnitude;
		float normalizedMagnitude = 0;

		//check if the controller is outside a circular dead zone
		if (magnitude > INPUT_RIGHT_THUMB_DEADZONE)
		{
			//clip the magnitude at its expected maximum value
			if (magnitude > 32767) magnitude = 32767;

			//adjust magnitude relative to the end of the dead zone
			magnitude -= INPUT_RIGHT_THUMB_DEADZONE;

			//optionally normalize the magnitude with respect to its expected range
			//giving a magnitude value of 0.0 to 1.0
			normalizedMagnitude = magnitude / (32767 - INPUT_RIGHT_THUMB_DEADZONE);

			data.turretRot = Maths::Vector2(xState.Gamepad.sThumbRX, xState.Gamepad.sThumbRY).Bearing() * Maths::RAD2DEG + 180;

			//data.RX = xState.Gamepad.sThumbRX;
			//data.RY = xState.Gamepad.sThumbRY;
		}
		else //if the controller is in the deadzone zero out the magnitude
		{
			magnitude = 0.0;
			normalizedMagnitude = 0.0;

			//data.turretRot = 0;

			//data.RX = 0;
			//data.RY = 0;
		}
	}
	//=============================================
	// If Xbox Controller is not connected
	//=============================================
	else
	{
		if (UG::IsKeyDown(UG::KEY_W))
		{
			data.triggers[0] = 255;
		}
		else
		{
			data.triggers[0] = 0;
		}

	
		if (UG::IsKeyDown(UG::KEY_S))
		{
			data.triggers[1] = 255;
		}
		else
		{
			data.triggers[1] = 0;
		}

		data.LX = 0;
		if (UG::IsKeyDown(UG::KEY_A))
		{
			data.LX += -32767;
		}
		if (UG::IsKeyDown(UG::KEY_D))
		{
			data.LX += 32767;
		}
		data.turretRot = (UG::GetMousePos() - _networkPlayers[0]->GetPos()).Bearing() * Maths::RAD2DEG + 180;
		
		data.buttons = 0;
		if (UG::GetMouseButtonDown(0))
		{
			data.buttons += XINPUT_GAMEPAD_RIGHT_SHOULDER;
		}
		if (UG::GetMouseButtonDown(1))
		{
			data.buttons += XINPUT_GAMEPAD_LEFT_SHOULDER;
		}
	}

	//===========SEND_DATA=============
	//	16 bits for buttons
	//	4 bits for left trigger
	//	4 bits for right trigger
	//	9 bits for turretRot
	//	7 bits for LX
	//  40 bits / 5 bytes
	//=================================
	std::bitset<40> bitsetSendData;

	data.LX = ((data.LX >> 10) + 32) * 0.5f;

	int pointer = 0;
	for (int i = 0; i < 16; ++i, ++pointer)
		bitsetSendData[pointer] = CheckBit(data.buttons, i);
	for (int i = 0; i < 4; ++i, ++pointer)
		bitsetSendData[pointer] = CheckBit(data.triggers[0], i);
	for (int i = 0; i < 4; ++i, ++pointer)
		bitsetSendData[pointer] = CheckBit(data.triggers[1], i);
	for (int i = 0; i < 9; ++i, ++pointer)
		bitsetSendData[pointer] = CheckBit(data.turretRot, i);
	for (int i = 0; i < 5; ++i, ++pointer)
		bitsetSendData[pointer] = CheckBit(data.LX, i);

	std::cout << bitsetSendData << std::endl;

	memcpy(bitsetSendBuffer, &bitsetSendData, sizeof(bitsetSendData));
	send(_socket, bitsetSendBuffer, sizeof(bitsetSendBuffer));

	for (int i = 0; i < 4; ++i)
	{
		_networkPlayers[i]->Update();
	}
	return 1;
}

void NetworkGame::ClientThread()
{
	struct RecvData
	{
		short int x, y;
		short int baseRot, turretRot;
		int ID = 0;
		bool isAlive;
	} recvData;
	char recvBitsBuffer[6];
	do
	{
		SOCKET* socket = &NetworkGame::Instance()->_socket;
		NetworkPlayer** networkPlayers = NetworkGame::Instance()->_networkPlayers;
		int iRecv = recv(*socket, recvBitsBuffer, 6);
		if (iRecv == -1)
		{
			closesocket(*socket);
			std::cout << "Server has disconnected." << std::endl;
			break;
		}

		//===========RECV_DATA=============
		//	10 bits for X
		//	10 bits for Y
		//	9 bits for top rot
		//	9 bits for bot rot
		//	3 bits for ID
		//	1 bit for isAlive
		//	42 bits in total
		//	char array of 6 bytes!
		//=================================
		std::bitset<42> bitsetData;
		memcpy(&bitsetData, recvBitsBuffer, sizeof(bitsetData));
		//std::cout << bitsetData << std::endl;

		int pointer = 0;

		std::bitset<10> size10BitSet;
		for (int i = 0; i < 10; ++i, ++pointer)
			size10BitSet[i] = bitsetData[pointer];
		recvData.x = size10BitSet.to_ulong();

		for (int i = 0; i < 10; ++i, ++pointer)
			size10BitSet[i] = bitsetData[pointer];
		recvData.y = size10BitSet.to_ulong();

		std::bitset<9> size9BitSet;
		for (int i = 0; i < 9; ++i, ++pointer)
			size9BitSet[i] = bitsetData[pointer];
		recvData.baseRot = size9BitSet.to_ulong();

		for (int i = 0; i < 9; ++i, ++pointer)
			size9BitSet[i] = bitsetData[pointer];
		recvData.turretRot = size9BitSet.to_ulong();

		std::bitset<3> size3BitSet;
		for (int i = 0; i < 3; ++i, ++pointer)
			size3BitSet[i] = bitsetData[pointer];
		recvData.ID = size3BitSet.to_ulong();

		recvData.isAlive = bitsetData[bitsetData.size()-1];

		networkPlayers[recvData.ID]->SetPos(Maths::Vector2(recvData.x, recvData.y));
		networkPlayers[recvData.ID]->SetBaseRot(recvData.baseRot * Maths::DEG2RAD * Maths::PI);
		networkPlayers[recvData.ID]->SetTurretRot((recvData.turretRot - 180) * Maths::DEG2RAD * Maths::PI);
		networkPlayers[recvData.ID]->IsAlive(recvData.isAlive);

	} while (true);
}