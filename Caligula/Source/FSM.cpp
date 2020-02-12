#include "FSM.h"
#include "State.h"
#include <SDL_log.h>
#include <SDL_error.h>

FSM::FSM() : currentState_(nullptr)
{
}

FSM::~FSM()
{
}

void FSM::SwitchState(State* state)
{
   if (state != nullptr){
	   if (currentState_ != nullptr)
	   	currentState_->Exit();
	   currentState_ = state;
	   currentState_->Enter();
	   return;
   }
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not switch states");
}

void FSM::Update()
{
	if (currentState_ == nullptr)
		return;

	if (currentState_->Update() == false) // Switch state
	{
		SwitchState(currentState_->nextState);
	}
}
