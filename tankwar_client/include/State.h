#ifndef __STATE_H_
#define __STATE_H_

class State 
{
	State* currentState_ = nullptr;
public:
	virtual void Update() = 0;
	virtual void OnEnter() = 0;
	virtual void OnLeave() = 0;

	inline void SetState(State* state)
	{
		currentState_ = state;
	}

	inline State* GetState()
	{
		return currentState_;
	}
};

#endif //__STATE_H_