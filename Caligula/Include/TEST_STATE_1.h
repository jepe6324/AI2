#pragma once

#include "State.h"
#include <array>
#include "DeltaTime.h"
#include "AStar.h"
#include "Agent.h"
#include "Player.h"

struct SDL_Renderer;
class Sound;

class TEST_STATE_1 : public State
{

	SDL_Renderer* m_renderer;
	Sound* m_sound;
   DeltaTime deltaTime_;
   Agent dude_;
   Player player_;
   AStar aStar_;
	std::vector<Vector2> path_;

public:
   enum GameState {
      EDIT,
      SIMULATE
   };

   GameState currentState_;

	TEST_STATE_1(SDL_Renderer& p_renderer); 
	void Enter();
	bool Update();
	void Exit();

   void changeState(GameState newState);
};
