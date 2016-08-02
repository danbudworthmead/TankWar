#ifndef __LOCAL_GAME_H_
#define __LOCAL_GAME_H_

#include <vector>
#include "Vector2.h"

class XboxController;
class Player;
class Bullet;
class GameWall;

namespace sf
{
	class SoundBuffer;
	class Sound;
}

class LocalGame
{
	static LocalGame* s_instance;
	LocalGame();
	~LocalGame();

	/*
	sf::SoundBuffer* countDownBeepBuffer; 
	sf::Sound* countDownBeep;
	*/

	sf::SoundBuffer* explodeSoundBuffer; 
	sf::Sound* explodeSound;

	sf::SoundBuffer* cannonSoundBuffer;
	sf::Sound* cannonSound;

	XboxController** pXboxControllers;
	Player** pPlayers;

	int amountOfPlayers;

	void BulletVsWall(Bullet* bullet, GameWall* wall, const float a_fDeltaTime);
	std::vector<Bullet*> FireBullet(const Maths::Vector2& a_pos, const Maths::Vector2& a_dir, std::vector<Bullet*> a_pBullets);

public:
	int Update();
	static LocalGame* Instance()
	{
		if (!s_instance)
			s_instance = new LocalGame();
		return s_instance;
	}
};

#endif //__LOCAL_GAME_H_