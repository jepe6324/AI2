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
   bool IsBlocked(Vector2 pos);

   // A* thing
   std::vector<Vector2> GetAdjacentTilePositions(Vector2 pos);

   // color thing
   void ChangeTileColor(Vector2 pos, SDL_Color color);
   void ChangeTileColor(Tile* selected, SDL_Color color);
   void ClearTileColour();

   void SpawnSpecialTile(Tile::TileType type);
   void SpawnSpecialTile(Tile::TileType type, Vector2 pos);
   void DeSpawnSpecialTile(Tile::TileType type);
   Vector2 GetSpecialTilePos(Tile::TileType type); // Will be wacky if you send in non special tile.

	std::vector<Tile*> tiles_;
};

#endif // !GRID_H_INCLUDED
