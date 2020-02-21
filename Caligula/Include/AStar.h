// AStar.h

#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED

#include "Vector.h"
#include <vector>

struct AStarNode
{
   AStarNode();
   AStarNode(Vector2 cell, Vector2 goal, AStarNode* parent);

   int h_; // heuristics   // Health?
   int g_; // ???          // Global?
   int f_; // ???          // Friends?

   Vector2 cell_;
   AStarNode* parent_ = nullptr;
};

struct AStar
{
   std::vector<AStarNode*> open_;
   std::vector<AStarNode*> closed_;
   Vector2 goal_;

   std::vector<Vector2> PathFindStart(Vector2 startPos, Vector2 goalPos);
   bool PathFind(std::vector<Vector2>* path, AStarNode* node);
   AStarNode* GetNextNode();
};
#endif // !ASTAR_H_INCLUDED