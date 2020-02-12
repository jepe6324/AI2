//Grid.cc
#include "Grid.h"
#include "Config.h"
#include <iostream>

Grid::Grid()
{
}

void Grid::Create()
{
	int posX = 0;
	int posY = 0;
	int difference = Config::TILE_SIZE;
	for (int i = 0; i < Config::INTERNAL_HEIGHT / Config::TILE_SIZE; i++)
	{
		for (int j = 0; j < Config::INTERNAL_WIDTH / Config::TILE_SIZE; j++)
		{
			Tile* tmp = new Tile;
			tmp->Create(posX, posY, difference, difference);
			tiles_.push_back(tmp);
			posX += difference;
		}
		posY += difference;
		posX = 0;
	}
};

void Grid::Render(SDL_Renderer* renderer_) {
	for (Tile* tile : tiles_)
	{
		tile->Render(renderer_);
	}
}

int Grid::GetTileIndex(int x, int y)
{
   int index = 0;

   int maxX = Config::INTERNAL_WIDTH  / Config::TILE_SIZE;
   int maxY = Config::INTERNAL_HEIGHT / Config::TILE_SIZE;

   if (x < maxX && x >= 0 && y < maxY && y >= 0)
   {
      index = y * (maxX);
      index += x;
   }
   else
      return -1; // Assume -1 error

   return index;
}

int Grid::GetTileIndex(Vector2 pos)
{
   return GetTileIndex(pos.x_, pos.y_);
}

Vector2 Grid::GetTilePos(int index)
{
   Vector2 returnVector;
   if (index >= tiles_.size())
   {
      return Vector2(-1, -1);
   }

   int maxX = Config::INTERNAL_WIDTH / Config::TILE_SIZE;
   int maxY = Config::INTERNAL_HEIGHT / Config::TILE_SIZE;

   returnVector.x_ = index % maxX;
   returnVector.y_ = index / maxX;
   return returnVector;
}