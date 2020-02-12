#pragma once

#include "State.h"
#include <array>
#include "Grid.h"
#include "Grass.h"
#include "DeltaTime.h"


struct SDL_Renderer;
class Sound;
struct Agent;

class TEST_STATE_1 : public State
{
	SDL_Renderer* m_renderer;
	Sound* m_sound;
	Grid grid_;
   DeltaTime deltaTime_;

public:
	TEST_STATE_1(SDL_Renderer& p_renderer); 
	void Enter();
	bool Update();
	void Exit();
};
