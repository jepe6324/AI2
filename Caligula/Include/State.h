#pragma once

#include <string>
#include <vector>
#include <SDL.h>

struct Agent;

struct State
{
	std::vector<State*> subStates_;
   State* nextState;

	State() {};
	virtual ~State() {};
	
   virtual void Enter() {};
	virtual bool Update() = 0; /*Should return false if state should be changed*/
	virtual void Exit() {};
};

struct AgentState : State
{
   Agent* agent_;
   const char* stateID;
   SDL_Color color_;

   ~AgentState() {};

   virtual bool Update(float dt) = 0;
};