#ifndef __LEVEL_LOADING_H_
#define __LEVEL_LOADING_H_
#include <vector>
#include <bitset>
class Player;
class GameWall;

void SetBit(int number, int index, bool value);

bool CheckBit(int number, int index);

bool FileLookup(const std::string& name);

std::vector<GameWall*> BitsToLevel(std::bitset<448> bits, Player** players);

std::vector<GameWall*> LoadLevel(const char* fileName, Player** players);

#endif //__LEVEL_LOADING_H_