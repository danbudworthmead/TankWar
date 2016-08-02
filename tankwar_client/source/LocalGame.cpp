#include "LocalGame.h"
#include "XboxController.h"
#include "UGFW++.h"
#include "Player.h"
#include "dirent.h"
#include "GameWall.h"
#include "LevelLoading.h"
#include "Bullet.h"
#include "Emitter.h"
#include "Enumerations.h"
#include <iostream>
#include <string>
#include <SFML\Audio.hpp>

LocalGame* LocalGame::s_instance = nullptr;

LocalGame::LocalGame()
{
	//Load sounds & music
	/*
	countDownBeepBuffer = new sf::SoundBuffer;
	countDownBeepBuffer->loadFromFile("./sounds/beep.wav");
	countDownBeep = new sf::Sound;
	countDownBeep->setBuffer(*countDownBeepBuffer);
	countDownBeep->setVolume(20);
	*/
	explodeSoundBuffer = new sf::SoundBuffer;;
	explodeSoundBuffer->loadFromFile("./sounds/explode.wav");
	explodeSound = new sf::Sound;
	explodeSound->setBuffer(*explodeSoundBuffer);
	explodeSound->setVolume(20);

	cannonSoundBuffer = new sf::SoundBuffer;;
	cannonSoundBuffer->loadFromFile("./sounds/cannon.wav");
	cannonSound = new sf::Sound;
	cannonSound->setBuffer(*cannonSoundBuffer);
	cannonSound->setVolume(20);

	//sf::Music music;
	//music.openFromFile("./sounds/music/game.ogg");
	//music.setVolume(10);
	//music.play();

	//initialise xbox controllers
	pXboxControllers = new XboxController*[4];
	for (int i = 0; i < 4; ++i)
		pXboxControllers[i] = new XboxController(i + 1);

	//initialise players
	pPlayers = new Player*[4];	
	pPlayers[0] = new Player(UG::SColour(255, 0, 0, 255), UG::SColour(255, 0, 0, 255));
	pPlayers[1] = new Player(UG::SColour(0, 255, 0, 255), UG::SColour(0, 255, 0, 255));
	pPlayers[2] = new Player(UG::SColour(0, 0, 255, 255), UG::SColour(0, 0, 255, 255));
	pPlayers[3] = new Player(UG::SColour(255, 255, 0, 255), UG::SColour(255, 255, 0, 255));

	for (int i = 0; i < 4; i++)
	{
		pPlayers[i]->SetID(i);
	}
}

LocalGame::~LocalGame()
{
	delete[] pXboxControllers;
	delete[] pPlayers;
}

int LocalGame::Update()
{
	float timer = 6;
	int prevInt = 0;
//	countDownBeep->setPitch(1.0f);
	do
	{
		UG::SetFont("./fonts/invaders.fnt");
		UG::ClearScreen();
		timer -= UG::GetDeltaTime() * 3;
		std::string tempString = std::to_string((int)timer);
		UG::DrawString(tempString.c_str(), 440, 540, 10.0f, UG::SColour(255, 255, 255, 255)); // Gotta use magic numbers because 'someone' didn't make the strings draw from centre... and I cba to do the maths to find the centre

		std::string score = "Player 1: ";
		score.append(std::to_string(pPlayers[0]->GetScore()));
		UG::DrawString(score.c_str(), 20, (int)UG::GetScreenSize().y - 20 - (0 * 30), 1.0f, UG::SColour(255, 0, 0, 255));

		score = "Player 2: ";
		score.append(std::to_string(pPlayers[1]->GetScore()));
		UG::DrawString(score.c_str(), 20, (int)UG::GetScreenSize().y - 20 - (1 * 30), 1.0f, UG::SColour(0, 255, 0, 255));

		score = "Player 3: ";
		score.append(std::to_string(pPlayers[2]->GetScore()));
		UG::DrawString(score.c_str(), 20, (int)UG::GetScreenSize().y - 20 - (2 * 30), 1.0f, UG::SColour(0, 0, 255, 255));

		score = "Player 4: ";
		score.append(std::to_string(pPlayers[3]->GetScore()));
		UG::DrawString(score.c_str(), 20, (int)UG::GetScreenSize().y - 20 - (3 * 30), 1.0f, UG::SColour(255, 255, 0, 255));
		/*
		if ((int)timer != prevInt)
		{
			if ((int)timer == 0)
				countDownBeep->setPitch(1.2f);
			countDownBeep->play();
		}
		prevInt = (int)timer;
		*/
	} while (UG::Process() && timer > 0);

	//See how many controllers are connected
	unsigned int playersAlive = 0;
	while (UG::Process() && playersAlive < 2)
	{
		playersAlive = 0;
		for (int i = 0; i < 4; i++)
		{
			if (pXboxControllers[i]->IsConnected())
			{
				pPlayers[i]->IsAlive(true);
				playersAlive++;
			}
		}
		if (playersAlive < 2)
			UG::DrawString("Connect 2 or more controllers!", 100, 190, 2.2f);
	}

	for (int i = 0; i < 4; i++)
	{
		if (pPlayers[i]->IsAlive())
			pPlayers[i]->StartDrawing();
	}
	char buffer256[256] = "";

	//=====================================================
	//Load a random level from the "levels" folder
	//=====================================================
	std::cout << "\n\n\tSearching levels folder...\n";
	std::vector<std::string> levelNames;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("./levels/")) != NULL)
	{
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_type != 16384) // no file type, for some reason "." and ".." were showing as files
			{
				std::cout << "\t-> " << ent->d_name << std::endl;
				std::string tempString = ent->d_name;
				tempString.erase(tempString.find_last_of(".")); //get rid of the .bmp
				levelNames.push_back(tempString);
			}
		}
		closedir(dir);
	}
	else perror("Couldn't find the levels folder!");
	//std::vector<GameWall*> pGameWalls = LoadLevel("test", pPlayers);
	std::vector<GameWall*> pGameWalls = LoadLevel(levelNames[rand() % levelNames.size()].c_str(), pPlayers);
	for (auto pGameWall : pGameWalls) { pGameWall->StartDrawing(); }
	//=====================================================

	std::vector<Bullet*> pBullets;

	Emitter explosionEmitter(Maths::Vector2(UG::GetScreenSize().x * 0.75f, UG::GetScreenSize().y * 0.5f), new Particle("./images/particle.png", UG::SColour(255, 255, 0, 255), UG::SColour(255, 0, 0, 0),Maths::Vector2(10, 10),Maths::Vector2::UP,Maths::Vector2(-100, -100), 0.25f, 300.0f), "./images/particle.png", 30, 0, 2.f, 0.0f);
	float roundEndTimer = 2.0f;

	//=====================================================
	//	Main Game Loop!
	//=====================================================

	int background = UG::CreateSprite("./images/backgrounds/floorboard.png", 1024, 768);

	//int iRand = rand() % 2;
	//switch (iRand)
	//{
	//case 0:
	//	background = UG::CreateSprite("./images/backgrounds/floorboard.png", 1024, 768);
	//	break;
	//case 1:
	//	background = UG::CreateSprite("./images/backgrounds/grass.png", 1024, 768);
	//	break;
	//default:
	//	break;
	//}

	UG::MoveSprite(background, UG::GetScreenSize().x * 0.5f, UG::GetScreenSize().y * 0.5f);
	UG::SetSpriteLayer(background, 0);
	//UG::DrawSprite(background);

	do
	{
		float fDeltaTime = UG::GetDeltaTime();

		explosionEmitter.Update(fDeltaTime);
		UG::ClearScreen();

		for (auto pBullet : pBullets)
		{
			for (auto pWall : pGameWalls)
			{
				BulletVsWall(pBullet, pWall, fDeltaTime);
			}
		}

		for (int i = 0; i < 4; ++i)
		{
			Player* pPlayer = pPlayers[i];
			if (pPlayer->GetTurretCooldown() > 0)
			{
				pPlayer->SetTurretCooldown(pPlayer->GetTurretCooldown() - fDeltaTime);
			}
			for (auto pBullet : pBullets)
			{
				if (pBullet->IsAlive() && pPlayer->IsAlive())
				{
					/*
					if (BoxVsBox(pBullet->GetBoxCollider(), pPlayer->GetBoxCollider())) // if  bullet hits player
					{
						explosionEmitter.Emit(0.5f);
						explosionEmitter.SetPos(pPlayer->GetPos());

						switch (pPlayer->GetID())
						{
						case 0:
							explosionEmitter.SetParticle(Particle("./images/particle.png", UG::SColour(255, 0, 0, 255), UG::SColour(255, 0, 0, 0),Maths::Vector2(8, 8),Maths::Vector2::UP,Maths::Vector2(-100, -100), 0.25f, 300.0f));
							break;
						case 1:
							explosionEmitter.SetParticle(Particle("./images/particle.png", UG::SColour(0, 255, 0, 255), UG::SColour(0, 255, 0, 0),Maths::Vector2(8, 8),Maths::Vector2::UP,Maths::Vector2(-100, -100), 0.25f, 300.0f));
							break;
						case 2:
							explosionEmitter.SetParticle(Particle("./images/particle.png", UG::SColour(0, 0, 255, 255), UG::SColour(0, 0, 255, 0),Maths::Vector2(8, 8),Maths::Vector2::UP,Maths::Vector2(-100, -100), 0.25f, 300.0f));
							break;
						case 3:
							explosionEmitter.SetParticle(Particle("./images/particle.png", UG::SColour(255, 255, 0, 255), UG::SColour(255, 255, 0, 0),Maths::Vector2(8, 8),Maths::Vector2::UP,Maths::Vector2(-100, -100), 0.25f, 300.0f));
							break;
						default:
							break;
						}

						explodeSound->play();
						pPlayer->IsAlive(false);
						pBullet->IsAlive(false);
						pPlayer->StopDrawing();
						pBullet->StopDrawing();
						playersAlive--;
						if (playersAlive <= 1)
						{
							for (int j = 0; j < 4; ++j)
							{
								Player* p = pPlayers[j];
								if (p->IsAlive())
								{
									p->IncrementScore();
								}
							}
						}
					}*/
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (auto pWall : pGameWalls)
				//AABBvsAABB(pPlayers[i], pWall, deltaTime);

			//\==============================================================================
			//\ START Xbox Controller Input
			//\==============================================================================

			float deadzoneMagnitude = 0.5f;
			float RT = pXboxControllers[i]->GetState().Gamepad.bRightTrigger;
			if (RT > 16) pPlayers[i]->MoveForwards(RT, fDeltaTime);
			float LT = pXboxControllers[i]->GetState().Gamepad.bLeftTrigger;
			if (LT > 16) pPlayers[i]->MoveBackwards(LT, fDeltaTime);
			Maths::Vector2 leftThumb(pXboxControllers[i]->GetState().Gamepad.sThumbLX, pXboxControllers[i]->GetState().Gamepad.sThumbLY);
			if (leftThumb.Magnitude() > 25000)
			{
				if (leftThumb.x > 8192) pPlayers[i]->TurnRight(leftThumb.x, fDeltaTime);
				if (leftThumb.x < -8192) pPlayers[i]->TurnLeft(-leftThumb.x, fDeltaTime);
				//if (leftThumb.y > 25000)
				//{
				//	pPlayers[i]->MoveForwards(leftThumb.Normalise().y * 255);
				//}
			}
			Maths::Vector2 rightThumb(pXboxControllers[i]->GetState().Gamepad.sThumbRX, pXboxControllers[i]->GetState().Gamepad.sThumbRY);
			if (rightThumb.Magnitude() > 30000)
			{
				rightThumb = rightThumb.GetNormalised();
				pPlayers[i]->turret_->SetDir(-Maths::Vector2(rightThumb).Bearing());
			}
			if (pXboxControllers[i]->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_RIGHT_SHOULDER && pPlayers[i]->GetTurretCooldown() <= 0 && pPlayers[i]->IsAlive())
			{
				pBullets = FireBullet(pPlayers[i]->GetPos() + (pPlayers[i]->turret_->GetDir() * 48), pPlayers[i]->turret_->GetDir(), pBullets);
				pPlayers[i]->SetTurretCooldown(0.5f);
				cannonSound->play();
			}
			//\==============================================================================
			//\ END Xbox Controller Input
			//\==============================================================================

			pPlayers[i]->Update(fDeltaTime);

		}
		for (int i = 0; i < pBullets.size(); ++i)
		{
			int index = pBullets[i]->Update(pBullets, fDeltaTime);
			if (index > 0)
			{
				pBullets.erase(pBullets.begin() + index);
			}
		}
		if (playersAlive <= 1)
		{
			roundEndTimer -= fDeltaTime;
		}
	} while (UG::Process() && roundEndTimer >= 0 && !UG::IsKeyDown(UG::KEY_F5));
	//Stop drawing everything
	for (auto pGameWall : pGameWalls) { pGameWall->StopDrawing(); delete pGameWall; }
	for (auto pBullet : pBullets) { pBullet->StopDrawing(); delete pBullet; }
	for (int i = 0; i < 4; ++i)
	{
		Player* pPlayer = pPlayers[i];
		pPlayer->SetPos(Maths::Vector2(-100, -100));
		pPlayer->SetDir(Maths::Vector2::UP);
		pPlayer->turret_->SetDir(Maths::Vector2::UP);
		pPlayer->StopDrawing();
	}
	UG::StopDrawingSprite(background);
	UG::DestroySprite(background);
	//for (int i = 0; i < pGameWalls.size() - 1; ++i)
	//{
	//	UG::DestroySprite(pGameWalls[i]->GetSprite());
	//}
	return 1;
}

void LocalGame::BulletVsWall(Bullet * bullet, GameWall * wall, const float a_fDeltaTime)
{
	if (bullet->IsAlive() && wall->IsAlive())
	{
		int iClosest = -1;
		/*
		if (BoxVsBox(bullet->GetBoxCollider(), wall->GetBoxCollider()))
		{
			float distNearestWall = (float)ULLONG_MAX;

			for (int i = 0; i < 4; i++)
			{
				float distToWall = Maths::DistanceToWall(bullet->GetBoxCollider()->GetWall(i), wall->GetPos());
				if (distToWall < distNearestWall)
				{
					distNearestWall = distToWall;
					iClosest = i;
				}
			}
			//translating the player by the closest walls normal vector * half the size of the player
			bullet->Translate(wall->GetBoxCollider()->GetWall(iClosest).GetNormal() * (distNearestWall + 32), 1); //I know this is really unoptimised
		}
		if (iClosest != -1)
		{
			Maths::Vector2 bulletDir = bullet->GetDir();
			switch (iClosest)
			{
			case 0:
				bullet->SetDir(Maths::Vector2(bulletDir.x, bulletDir.y));
				break;
			case 1:
				bullet->SetDir(Maths::Vector2(-bulletDir.x, -bulletDir.y));
				break;
			case 2:
				bullet->SetDir(Maths::Vector2(bulletDir.x, bulletDir.y));
				break;
			case 3:
				bullet->SetDir(Maths::Vector2(-bulletDir.x, -bulletDir.y));
				break;
			default:
				break;
			}
		}
		*/
	}
}

std::vector<Bullet*> LocalGame::FireBullet(const Maths::Vector2& a_pos, const Maths::Vector2& a_dir, std::vector<Bullet*> a_pBullets)
{
	a_pBullets.push_back(new Bullet(a_pos, a_dir));
	return a_pBullets;
}