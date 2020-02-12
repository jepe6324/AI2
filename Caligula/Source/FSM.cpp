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

void FSM::AddState(State * p_state)
{
	if (p_state == nullptr)
		return;

	m_states.push_back(p_state);
}

void FSM::RemoveState(State * p_state)
{
	if (p_state == nullptr)
		return;

	int index = 0;
	for (int i = 0; i<m_states.size(); i++) 
	{
		if (m_states[i] == p_state)
		{
			if (m_currentState != nullptr)
			{
				if (m_currentState == m_states[i])
				{
					m_currentState->Exit();
					m_currentState = nullptr;
				}
			}
			m_states.erase(m_states.begin() + i);
			return;
		}
	}
}

void FSM::SetState(State * p_state)
{
	for (State* state : m_states)
	{
		if (state == p_state)
		{
			if (m_currentState != nullptr)
			{
				m_currentState->Exit();
			}
			m_currentState = state;
			m_currentState->Enter();
			return;
		}
	}
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not set state");
}
