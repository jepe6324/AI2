#pragma once

#include <vector>
#include <string>

struct State;

struct FSM // Finite State Machine
{
	State* currentState_;

	FSM();
   virtual ~FSM();

	virtual void Update();
   virtual void SwitchState(State* p_state);
};