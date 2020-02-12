//GRID_H_INCLUDED

#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "Tile.h"
#include "Vector.h"
#include <vector>

struct Grid {
   Grid();

	void Create();
	void Render(SDL_Renderer* renderer_);

   Tile* GetTile(int x, int y);
   Tile* GetTile(Vector2 pos);
   int GetTileIndex(int x, int y);
   int GetTileIndex(Vector2 pos);
   Vector2 GetTilePos(int index);

	std::vector<Tile*> tiles_;
};

#endif // !GRID_H_INCLUDED
