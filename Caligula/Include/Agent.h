// Agent.h

#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

#include "FSM.h"
#include "State.h"
#include "Vector.h"
#include "Timer.h"
#include "Tile.h"

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
	float stamina_;
	float maxStamina_;
	

   AgentState* currentState_;

   Tile::TileType target_;
   bool hasStar_;
   Sprite* starSprite_;

   Grid* grid_;

   Agent(const char* filepath,
         int x,
         int y,
         AgentState* startState,
         Vector2 startPos);
   ~Agent();

	void Render(SDL_Renderer* renderer_);
   void Update(float dt);
   void SwitchState(AgentState* newState);
	
   void Sense();
   void Decide();

   void Move(Vector2 newPos);
   void MoveInDirection(Vector2 direction);

   void DropStar();
};

#endif //!AGENT_H_INCLUDED