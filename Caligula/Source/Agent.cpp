// Agent.cpp

#include "Agent.h"
#include "Sprite.h"
#include "Service.h"
#include "Spritehandler.h"
#include "Config.h"
#include "DeltaTime.h"
#include "Grid.h"
#include "Random.h"

Agent::Agent(const char* filepath,
             int x,
             int y,
             AgentState* startState,
             Vector2 startPos)
{
   sprite_ = Service<SpriteHandler>::Get()->CreateSprite(filepath, 0, 0, x, y);
   position_ = startPos;
   currentState_ = nullptr;
   ChangeState(startState);
}

Agent::~Agent()
{
}

void Agent::Render(SDL_Renderer* renderer_)
{
	SDL_RenderCopy(renderer_, sprite_->GetTexture(), &sprite_->GetArea(), &drawHelper_);

	if(Config::DEBUGRENDER == TRUE)
		SDL_RenderDrawRect(renderer_, &drawHelper_);
}

void Agent::Update(float dt) // As milliseconds
{
   Sense(); // Ad timers to make sure these happen at a proper time
   Decide();
   currentState_->Update(dt);
}

void Agent::Move(Vector2 newPos) {
   // These lines should be used when moving the agents
   Vector2 oldPos = position_;

   /*if (grid_->GetTileIndex(newPos) != -1) // This is going to have to use TileHandler instead
   {
      position_ = newPos;
   }*/
}

void Agent::MoveInDirection(Vector2 direction)
{
	Vector2 newPos = position_ + direction;
	Move(newPos);
}

void Agent::ChangeState(AgentState* newState)
{
   if (currentState_ != nullptr)
   {
      currentState_->Exit();
      delete currentState_;
      currentState_ = nullptr;
   }

   currentState_ = newState;
   currentState_->agent_ = this;
   currentState_->Enter();
}

void Agent::Sense()
{
}

void Agent::Decide()
{
}