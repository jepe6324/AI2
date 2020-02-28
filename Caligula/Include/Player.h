// Player.h

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include"Vector.h"

struct Tile;
struct SDL_Color;

struct Player
{
   Tile* hovered_;
   Tile* selected_;
   Vector2 mousePos_;

   void Update();
   void UpdateMouse();
   void HoverTile();
   void SelectTile();
   void SwitchTiles(Tile* lhs, Tile* rhs);
   void HandleTile(Tile* selected);

};

#endif // !PLAYER_H_INCLUDED
