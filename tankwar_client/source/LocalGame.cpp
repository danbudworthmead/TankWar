#include "LocalGame.h"
#include "XboxController.h"
#include "Player.h"
#include "dirent.h"
#include "AABBCollisionManager2D.h"
#include <iostream>
int LocalGame::RunLocalGame()
{
	Maths::AABBCollisionManager2D::instance();
	InitialiseGamepads();
	ConnectGamepads();
	InitialisePlayers();
	LoadRandomLevel();
	StartDrawing();
	UpdateGame();
	StopDrawing();
	UpdateScores();
	return 1;
}
int LocalGame::UpdateGame()
{
	do
	{
		UG::ClearScreen();
		float fDeltaTime = UG::GetDeltaTime();
		for (unsigned int i = 0; i < numberOfConnectedGamepads; i++)
			pPlayers[i]->Update(fDeltaTime, *pXboxControllers[i + 1]);
		for (int i = 0; i < 10000; i++)
			Maths::AABBCollisionManager2D::instance()->UpdatePhysics(false);
		for (unsigned int i = 0; i < numberOfConnectedGamepads; i++)
			pPlayers[i]->UpdateSprite();
		DrawHitboxes();
	} while (UG::Process());
	return 1;
}
int LocalGame::InitialiseGamepads()
{
	//Initialise the xbox controllers
	for (unsigned int i = 0; i < MAX_PLAYERS; i++)
		pXboxControllers[i] = new XboxController(i);
	return 1;
}
int LocalGame::ConnectGamepads()
{
	//See how many game pads are connected to the machine
	numberOfConnectedGamepads = 0;
	for (auto pController : pXboxControllers)
	{
		if (pController->IsConnected())
			numberOfConnectedGamepads++;
	}
	return 1;
}
int LocalGame::InitialisePlayers()
{
	//Initialise enough players for the amount of controllers we have connected
	for (unsigned int i = 0; i < numberOfConnectedGamepads; i++)
		pPlayers[i] = new Player();
	return 1;
}
int LocalGame::LoadRandomLevel()
{
	//Gets names of levels in /levels/ directory
	std::vector<std::string> levelNames = GetLevelNames();
	
	//Loads a random level
	LoadLevel(levelNames[rand() % levelNames.size()]);

	//I wonder if I could make an online folder. Will experiment with this idea later.
	return 1;
}
std::vector<std::string> LocalGame::GetLevelNames()
{
	//=====================================================
	//Load a random level from the "levels" folder
	//=====================================================
	std::cout << "\n\n\tSearching levels folder...\n";
	std::vector<std::string> levelNames;
	DIR *dir;
	struct dirent *entry;
	if ((dir = opendir("./levels/")) != NULL)
	{
		/* print all the files and directories within directory */
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_type != 16384) // no file type, for some reason "." and ".." were showing as files
			{
				std::string tempString = entry->d_name;
				//Let's make sure it's a .bmp file
				if (tempString.substr(tempString.find_last_of("."), 3).compare(".bmp"))
				{
					std::cout << "\t-> " << entry->d_name << std::endl;
					levelNames.push_back(tempString);
				}
			}
		}
		closedir(dir);
	}
	return levelNames;
}
int LocalGame::LoadLevel(std::string a_sLevelName)
{
	char cBuffer256[256];
	memset(cBuffer256, 0, 256);
	strcat(cBuffer256, "./levels/");
	strcat(cBuffer256, a_sLevelName.c_str());
	FILE* file = fopen(cBuffer256, "r");

	char header[54];
	fread(header, sizeof(unsigned char), 54, file);

	//Get the height and width of the image
	Maths::Vector2 mapSize(*(int*)&header[18], *(int*)&header[22]);

	//Min and Max map sizes
	Maths::Vector2 MAP_SIZE_MIN(10, 10);
	Maths::Vector2 MAP_SIZE_MAX(24, 24);

	//Make sure the map fits our requirements
	if (mapSize.x < MAP_SIZE_MIN.x)
		return 0;
	if (mapSize.x > MAP_SIZE_MAX.x)
		return 0;
	if (mapSize.y < MAP_SIZE_MIN.y)
		return 0;
	if (mapSize.y > MAP_SIZE_MAX.y)
		return 0;
	
	//Struct pixel with RGB value
	struct Pixel
	{
		Pixel(const int a_r, const int a_g, const int a_b)
		{
			R = a_r;
			G = a_g;
			B = a_b;
		}
		int R, G, B;
		bool operator==(const Pixel other)
		{
			if (other.R == R && other.G == G && other.B == B)
				return true;
			return false;
		}
	};
	//Array of pixels
	std::vector<Pixel> pixels;
	int pixelCount = mapSize.x * mapSize.y;
	for (int i = 0; i < pixelCount; i++)
	{
		//make new pixel and set RGB values
		Pixel pixel(getc(file), getc(file), getc(file));
		//add new pixel to array
		pixels.push_back(pixel);
	}

	//255, 255, 255 will be empty space
	Pixel pixel_white(255, 255, 255);
	//0, 0, 0 will be a wall
	Pixel pixel_black(0, 0, 0);
	//0, 255, 0 will be player spawn
	Pixel pixel_green(0, 255, 0);
	//0, 255, 255 will be power ups
	Pixel pixel_yellow(0, 255, 255);

	//each tile will be the screen size divided by the map size
	Maths::Vector2 tileSize = UG::GetScreenSize() / mapSize;
	Maths::Vector2 currentPixel(1, 1);
	for (unsigned int i = 0; i < pixelCount; i++)
	{
		if (pixels[i] == pixel_black)
		{
			//add wall to gameTiles
			gameTiles.push_back(new Actor("Wall", "./images/wall.png", tileSize, (currentPixel * tileSize) - tileSize * 0.5f, true));
		}
		else if (pixels[i] == pixel_green)
		{
			possiblePlayerSpawns.push_back(Maths::Vector2(currentPixel * tileSize - tileSize * 0.5f));
		}
		else if (pixels[i] == pixel_yellow)
		{
			//gameTiles.pushback(new PowerupSpawn(currentPixel));
		}
		else if (pixels[i] == pixel_white)
		{
			//do nothing because empty
		}
		currentPixel.x++;
		if (currentPixel.x > mapSize.x)
		{
			currentPixel.x = 1;
			currentPixel.y++;
		}
	}
	//find 2D in 1D -> width * (y - 1) + x
	fclose(file); //close the file

	for (unsigned int i = 0; i < numberOfConnectedGamepads; i++)
	{
		int randSpawn = rand() % possiblePlayerSpawns.size();
		pPlayers[i]->SetPos(possiblePlayerSpawns[randSpawn]);
		possiblePlayerSpawns.erase(possiblePlayerSpawns.begin() + randSpawn);

		Maths::Vector2 playerSize = tileSize * 0.7f;

		pPlayers[i]->SetSize(playerSize);
		UG::SetSpriteScale(pPlayers[i]->turret_, playerSize.x, playerSize.y * 1.35f);
		pPlayers[i]->SetSpeed(tileSize.Magnitude() * 2.4f);
	}
	return 1;
}
int LocalGame::StartDrawing()
{
	for (auto gameTile : gameTiles)
		gameTile->StartDrawing();
	for (unsigned int i = 0; i < numberOfConnectedGamepads; i++)
		pPlayers[i]->StartDrawing();
	return 1;
}
int LocalGame::StopDrawing()
{
	return 1;
}
int LocalGame::UpdateScores()
{
	return 1;
}
int LocalGame::Terminate()
{
	//Delete xbox controllers
	for (unsigned int i = 0; i < MAX_PLAYERS; i++)
		delete pXboxControllers[i];

	//Delete players
	for (unsigned int i = 0; i < MAX_PLAYERS; i++)
		delete pPlayers[i];
	return 1;
}

int LocalGame::DrawHitboxes()
{
	//Draws hitboxes
	for (auto pCollider : Maths::AABBCollisionManager2D::instance()->colliders)
	{
		float corners[8];
		pCollider->GetCorners2D(corners);

		UG::DrawLine(corners[0], corners[1], corners[2], corners[3], UG::SColour(255, 0, 0, 255));
		UG::DrawLine(corners[2], corners[3], corners[4], corners[5], UG::SColour(255, 0, 0, 255));
		UG::DrawLine(corners[4], corners[5], corners[6], corners[7], UG::SColour(255, 0, 0, 255));
		UG::DrawLine(corners[6], corners[7], corners[0], corners[1], UG::SColour(255, 0, 0, 255));
	}
	return 0;
}
