#ifndef __GAME_STATE_H_
#define __GAME_STATE_H_
#include "State.h"

class GameState : public State
{
	GameState();
public:
	void Update();
	void OnEnter();
	void OnLeave();
};

#endif //__GAME_STATE_H_