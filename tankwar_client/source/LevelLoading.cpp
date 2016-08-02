#include "LevelLoading.h"
#include "Player.h"
#include "GameWall.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
void SetBit(int number, int index, bool value)
{
	number ^= (-value ^ number) & (1 << index);
}
bool CheckBit(int number, int index)
{
	return (number >> index) & 1;
}

bool FileLookup(const std::string& name)
{
	std::cout << "\tLooking for: " << name << std::endl;
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

std::vector<GameWall*> BitsToLevel(std::bitset<448> bits, Player** players)
{
	std::vector<GameWall*> pGameWalls;
	int x = 1, y = 1;
	for (int i = 0; i < bits.size() - 1; i += 2)
	{
		if (bits[i] == 0)
		{
			if (bits[i + 1] == 0)
			{
			}
			else if (bits[i + 1] == 1)
			{
				for (int k = 0; k < 4; k++)
				{
					if (players[k]->GetPos().x < 0)
					{
						players[k]->SetPos(Maths::Vector2((const float)x * 64 - 32, (const float)y * 64 - 32));
						break;
					}
				}
			}
		}
		else if (bits[i] == 1)
		{
			if (bits[i + 1] == 0)
			{
			}
			else if (bits[i + 1] == 1)
			{
				pGameWalls.push_back(new GameWall(x, y));
			}
		}
		x++;
		if (x > 16)
		{
			x = 1;
			y++;
		}
	}
	return pGameWalls;
}

std::vector<GameWall*> LoadLevel(const char* fileName, Player** players)
{
	std::cout << "\n\n\tLoading Level: " << fileName << "\n" << std::endl;

	std::vector<GameWall*> pReturnWalls;

	char cBuffer256[256] = "";
	strcat(cBuffer256, "./levels_bin/");
	strcat(cBuffer256, fileName);
	strcat(cBuffer256, ".bin");
	if (FileLookup(cBuffer256))
	{
		std::bitset<448> bits; // 56 bytes!
		std::ifstream input(cBuffer256, std::ios::binary);
		input.read(reinterpret_cast<char*>(&bits), sizeof(bits));
		std::cout << "\nReading in binary data:\n";
		for (int i = 0; i < bits.size(); i++)
		{
			std::cout << " " << bits[i];
		}
		input.close();
		return BitsToLevel(bits, players);
	}
	else
	{
		memset(cBuffer256, NULL, 256);
		strcat(cBuffer256, "./levels/");
		strcat(cBuffer256, fileName);
		strcat(cBuffer256, ".bmp");
		if (FileLookup(cBuffer256))
		{
			int imageBuffer[256][3];
			FILE* file = fopen(cBuffer256, "r");
			for (int i = 0; i < 256; i++)
			{
				if (i >= 18)
				{
					imageBuffer[i - 18][2] = getc(file);
					imageBuffer[i - 18][1] = getc(file);
					imageBuffer[i - 18][0] = getc(file);
				}
				else //skip the header
				{
					getc(file);	getc(file);	getc(file);
				}
			}
			std::cout << "\n\nChar Format: " << std::endl;
			std::vector<char> vecBuffer;
			for (int i = 0; i < 244; i++)
			{
				if (imageBuffer[i][0] == 255 && imageBuffer[i][1] == 255 && imageBuffer[i][2] == 255) // if pixel is white
				{
					vecBuffer.push_back('w');
					std::cout << "W ";
				}
				if (imageBuffer[i][0] == 0 && imageBuffer[i][1] == 0 && imageBuffer[i][2] == 0) // if pixel is black
				{
					vecBuffer.push_back('b');
					std::cout << "B ";
				}
				if (imageBuffer[i][0] == 0 && imageBuffer[i][1] == 255 && imageBuffer[i][2] == 0) // if pixel is black
				{
					vecBuffer.push_back('g');
					std::cout << "G ";
				}
			}
			std::cout << "\n";

			std::bitset<448> bits; // 56 bytes!
			for (int i = 0, j = 0; i < vecBuffer.size(); i++, j += 2)
			{
				if (vecBuffer[i] == 'b')
				{
					bits[j] = 1;
					bits[j + 1] = 1;
				}
				if (vecBuffer[i] == 'w')
				{
					bits[j] = 0;
					bits[j + 1] = 0;
				}
				if (vecBuffer[i] == 'g')
				{
					bits[j] = 0;
					bits[j + 1] = 1;
				}
				if (vecBuffer[i] == 'y')
				{
					bits[j] = 1;
					bits[j + 1] = 0;
				}
			}
			std::cout << "\n\nConverted into optimised binary format (630 bytes -> 56 bytes):\n";
			for (int i = 0; i < bits.size(); i++)
			{
				std::cout << " " << bits[i];
			}
			fclose(file);
			memset(cBuffer256, 0, 256);
			strcat(cBuffer256, "./levels_bin/");
			strcat(cBuffer256, fileName);
			strcat(cBuffer256, ".bin");
			std::ofstream fileOut(cBuffer256, std::ios::out | std::ios::binary);
			fileOut.write(reinterpret_cast<const char*>(&bits), sizeof(bits));
			fileOut.close();
			return BitsToLevel(bits, players);
		}
		else
		{
			std::cout << cBuffer256 << " NOT FOUND!" << std::endl;
		}
	}
	return pReturnWalls;
}