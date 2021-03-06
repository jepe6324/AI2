//Grid.cc
#include "Grid.h"
#include "Config.h"
#include <iostream>
#include "Random.h"

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

   SpawnSpecialTile(Tile::TileType::STAR);
   SpawnSpecialTile(Tile::TileType::TRADING);
   SpawnSpecialTile(Tile::TileType::SPACESHIP);

};

void Grid::Render(SDL_Renderer* renderer_) {
	for (Tile* tile : tiles_)
	{
		tile->Render(renderer_);
	}
}

Tile* Grid::GetTile(int x, int y)
{
   int index = GetTileIndex(x, y);

   if (index == -1)
   {
      return nullptr;
   }
   return tiles_.at(index);
}

Tile* Grid::GetTile(Vector2 pos)
{
   return GetTile(pos.x_, pos.y_);
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

bool Grid::IsBlocked(Vector2 pos)
{
   Tile* tmp = GetTile(pos);
   if (tmp != nullptr)
   {
      if (tmp->currentType_ != Tile::TileType::BLOCKED)
      {
         return false;
      }
   }
   return true;
}

std::vector<Vector2> Grid::GetAdjacentTilePositions(Vector2 pos)
{
   std::vector<Vector2> tiles;
   
   Vector2 tmp = pos;
   tmp.x_--;
   if (!IsBlocked(tmp))
   {
      tiles.push_back(tmp);
   }

   tmp.x_ += 2;
   if (!IsBlocked(tmp))
   {
      tiles.push_back(tmp);
   }

   tmp = pos;
   tmp.y_--;
   if (!IsBlocked(tmp))
   {
      tiles.push_back(tmp);
   }

   tmp.y_ += 2;
   if (!IsBlocked(tmp))
   {
      tiles.push_back(tmp);
   }

   return tiles;
}

void Grid::ChangeTileColor(Vector2 pos, SDL_Color color)
{
   GetTile(pos)->borderColor_ = color;
}

void Grid::ChangeTileColor(Tile* selected, SDL_Color color)
{
   if (selected != nullptr)
      selected->borderColor_ = color;
}

void Grid::ClearTileColour()
{
   for (auto tile : tiles_)
   {
      tile->borderColor_= { 255,255,255,255 };
   }
}

void Grid::SpawnSpecialTile(Tile::TileType type)
{
   if (GetSpecialTilePos(type).x_ >= 0.0f ||
       GetSpecialTilePos(type).y_ >= 0.0f)
   {
      return;
   }
   while (true)
   {
      int index = Random::Rand(0, tiles_.size() - 1);

      if (tiles_.at(index)->currentType_ == Tile::TileType::BLOCKED ||
          tiles_.at(index)->currentType_ == Tile::TileType::EMPTY)
      {
         tiles_.at(index)->SwitchTileType(type);
         return;
      }
   }
}

void Grid::SpawnSpecialTile(Tile::TileType type, Vector2 pos)
{
   if (GetTile(pos)->currentType_ == Tile::TileType::BLOCKED ||
       GetTile(pos)->currentType_ == Tile::TileType::EMPTY)
   {
      GetTile(pos)->SwitchTileType(type);
   }
   else
   {
      std::vector<Vector2> adj = GetAdjacentTilePositions(pos);

      for (int i = 0; i < adj.size(); i++)
      {
         if (GetTile(pos)->currentType_ == Tile::TileType::EMPTY)
         {
            GetTile(pos)->SwitchTileType(type);
            return;
         }
      }
   }
}

void Grid::DeSpawnSpecialTile(Tile::TileType type)
{
   Vector2 pos = GetSpecialTilePos(type);

   Tile* tile = GetTile(pos);
   if (tile != nullptr)
   {
      tile->SwitchTileType(Tile::TileType::EMPTY);
   }
}

Vector2 Grid::GetSpecialTilePos(Tile::TileType type)
{
   for (int i = 0; i < tiles_.size(); i++)
   {
      if (tiles_.at(i)->currentType_ == type)
      {
         return GetTilePos(i);
      }
   }
   return { -1,-1 };
}
