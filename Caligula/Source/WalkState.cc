#include "..\Include\WalkState.h"
#include "Agent.h"

#include "Service.h"
#include "Grid.h"
#include "TEST_STATE_1.h"
#include "SleepState.h"

WalkState::WalkState(Agent* agent)
   : actTimer_(0.5f)
{
   agent_ = agent;
}
void WalkState::Enter()
{
   newPath();
   target_ = agent_->target_;
	actTimer_.currentValue_ = actTimer_.initialValue_ / 2.0f;
}

void WalkState::Exit()
{
	path_.clear();
   Service<Grid>::Get()->ClearTileColour();
}

bool WalkState::MoveTowardsTarget()
{
   if (!path_.empty())
   {
	   agent_->Move(path_.at(path_.size() - 1));
	   path_.pop_back();
   }
   if (agent_->position_ == Service<Grid>::Get()->GetSpecialTilePos(target_))
   {
	   return true;
   }
   return false;
}

bool WalkState::Update(float dt)
{
	if (actTimer_.IsDone())
	{
		if (MoveTowardsTarget())
		{
			switch (agent_->target_)
			{
			case Tile::TileType::STAR:
				agent_->hasStar_ = true;	//remove star from grid
            Service<Grid>::Get()->DeSpawnSpecialTile(Tile::TileType::STAR);
				break;
			case Tile::TileType::TRADING:
				agent_->hasStar_ = false;	//add star to grid
            Service<Grid>::Get()->SpawnSpecialTile(Tile::TileType::STAR);
				break;
			case Tile::TileType::SPACESHIP:
            agent_->SwitchState(new SleepState(agent_));
            return true;

				break;
			}
		}
      else if (path_.empty())
      {
         newPath();
      }

		actTimer_.Reset();
	}
	//move timer

   if (target_ != agent_->target_)
   {
      path_.clear();
      newPath();
      target_ = agent_->target_;
   }

   agent_->stamina_ -= dt;


   return true;
}

void WalkState::newPath()
{
   Service<Grid>::Get()->ClearTileColour();
	path_ = aStar_.PathFindStart(agent_->position_, Service<Grid>::Get()->GetSpecialTilePos(agent_->target_));
   if (path_.empty())
   {
      Service<TEST_STATE_1>::Get()->changeState(TEST_STATE_1::GameState::EDIT);
   }
}
