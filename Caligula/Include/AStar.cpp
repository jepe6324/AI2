#include "AStar.h"
#include <math.h>

#include "Service.h"
#include "Grid.h"

int GetHeuristic(Vector2 currentPos, Vector2 goalPos)
{
   int x = abs(goalPos.x_ - currentPos.x_);
   int y = abs(goalPos.y_ - currentPos.y_);

   return x + y;
}

int GetNodeIndex(Vector2 node, std::vector<AStarNode*> list)
{
   for (int i = 0; i < list.size(); i++)
   {
      if (list.at(i)->cell_ == node)
      {
         return i;
      }
   }

   return -1;  // didn't find the thing
}

std::vector<Vector2> AStar::PathFindStart(Vector2 currentPos, Vector2 goalPos)
{
   std::vector<Vector2> path;
   goal_ = goalPos;

   AStarNode* startNode = new AStarNode(currentPos, goal_, nullptr);
   
   open_.push_back(startNode);

   PathFind(&path, startNode);

   return path;
}

bool AStar::PathFind(std::vector<Vector2>* path, AStarNode* node)
{
   AStarNode* nextNode = nullptr;

   // Have we reached the goal
   if (node->cell_ == goal_)
   {
      path->push_back(node->cell_);

      Service<Grid>::Get()->ChangeTileColour(node->cell_, { 0,255,0,255 });

      return true;
   }

   // Get all valid adjacent tiles
   std::vector<Vector2> adjacent = Service<Grid>::Get()->GetAdjacentTilePositions(node->cell_);

   // See if those tiles already are in open_ or closed_
   for (int i = 0; i < adjacent.size(); i++)
   {
      if (GetNodeIndex(adjacent.at(i), closed_) == -1 && GetNodeIndex(adjacent.at(i), open_) == -1)
      {
         AStarNode* tmp = new AStarNode(adjacent.at(i), goal_, node);
         open_.push_back(tmp);
      }
   }

   // Move this node from open_ to closed_
   int index = GetNodeIndex(node->cell_, open_);
   open_.erase(open_.begin() + index);
   closed_.push_back(node);

   // Decide nextNode
   nextNode = GetNextNode();
   if (nextNode == nullptr)
   {
      return false;
   }

   // Recurse the path
   if (PathFind(path, nextNode) == true)
   {
      path->push_back(node->cell_);
      return true;
   }
   return false;
}

AStarNode* AStar::GetNextNode()
{
   AStarNode* tmp = nullptr;
   for (int i = 0; i < open_.size(); i++)
   {
      if (tmp == nullptr)
      {
         tmp = open_.at(i);
      }
      else
      {
         if (tmp->f_ > open_.at(i)->f_)
         {
            tmp = open_.at(i);
         }
         else if (tmp->f_ == open_.at(i)->f_ && tmp->h_ > open_.at(i)->h_)
         {
            tmp = open_.at(i);
         }
      }
   }
   return tmp;
}

AStarNode::AStarNode()
{
}

AStarNode::AStarNode(Vector2 cell, Vector2 goal, AStarNode* parent)
{
   cell_ = cell;
   parent_ = parent;
   h_ = GetHeuristic(cell, goal);

   if (parent != nullptr)
   {
      g_ = parent->g_ + 10;
   }
   else {
      g_ = 0;
   }
   f_ = g_ + h_;
}
