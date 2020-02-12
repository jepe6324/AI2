// Agent.h

#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include "FSM.h"
#include "State.h"
#include "Vector.h"
#include "Timer.h"

#include <SDL_rect.h>

struct Sprite;
struct DeltaTime;
struct SDL_Renderer;
struct Grid;

struct Agent : FSM
{

   Sprite* sprite_;
   SDL_Rect drawHelper_;
   Vector2 position_;
   Vector2 direction_;

   AgentState* currentState_;

   Grid* grid_;

   Agent(const char* filepath,
         int x,
         int y,
         AgentState* startState,
         Vector2 startPos);
   ~Agent();

	void Render(SDL_Renderer* renderer_);
   void Update(float dt);
   void ChangeState(AgentState* newState);
	
   void Sense();
   void Decide();

   void Move(Vector2 newPos);
   void MoveInDirection(Vector2 direction);
};

#endif //!AGENT_H_INCLUDED