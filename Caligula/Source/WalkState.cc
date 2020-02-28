#include "..\Include\WalkState.h"
#include "Agent.h"

#include "Service.h"
#include "Grid.h"
void WalkState::Enter()
{
	path_ = aStar_.PathFindStart(agent_->position_, Service<Grid>::Get()->GetSpecialTilePos(agent_->target_));
	actTimer_.initialValue_ = 2;
	actTimer_.currentValue_ = 1;
}

void WalkState::Exit()
{
	path_.clear();
}

bool WalkState::MoveTowardsTarget()
{
	agent_->Move(path_.at(path_.size() - 1));
	path_.pop_back();
	
	return path_.empty();
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
				break;
			case Tile::TileType::TRADING:
				agent_->hasStar_ = false;	//add star to grid
				break;
			case Tile::TileType::SPACESHIP:
				//state switch?
				break;
			}
		}
		actTimer_.Reset();
	}
	//move timer

}

void WalkState::newPath()
{
	path_ = aStar_.PathFindStart(agent_->position_, Service<Grid>::Get()->GetSpecialTilePos(agent_->target_));
}
