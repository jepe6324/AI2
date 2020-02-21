#pragma once

#include "State.h"
#include <array>
#include "DeltaTime.h"
#include "Player.h"
#include "AStar.h"


struct SDL_Renderer;
class Sound;
struct Agent;

class TEST_STATE_1 : public State
{
	SDL_Renderer* m_renderer;
	Sound* m_sound;
   DeltaTime deltaTime_;
   Player player_;
   AStar aStar_;
	std::vector<Vector2> path_;

public:
	TEST_STATE_1(SDL_Renderer& p_renderer); 
	void Enter();
	bool Update();
	void Exit();
};
