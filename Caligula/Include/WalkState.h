//WALKSTATE_H_INCLUDED
#ifndef WALKSTATE_H_INCLUDED
#define WALKSTATE_H_INCLUDED

#include "State.h"
#include "Vector.h"
#include "AStar.h"
#include "Timer.h"
#include "Tile.h"

#include <vector>

struct WalkState : AgentState
{
	std::vector<Vector2> path_;
	AStar aStar_;
	Timer actTimer_;
	int currentPathIndex_;
   Tile::TileType target_;

   WalkState(Agent* agent);

	void Enter();
	void Exit();
	bool MoveTowardsTarget();
	bool Update(float dt);
	void newPath();
};


#endif // !WALKSTATE_H_INCLUDED
