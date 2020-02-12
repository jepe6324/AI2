//Grid.cc
#include "Grid.h"
#include "Config.h"
#include "WanderState.h"
#include <iostream>

Grid::Grid()
   : grass_(new std::vector<Grass*>())
   , agents_(new std::vector<Agent*>())
{
}

void Grid::Create()
{
	int posX = 0;
	int posY = 0;
	int difference = Config::TILE_SIZE;
	for (int i = 0; i < Config::SCREEN_HEIGHT / Config::TILE_SIZE; i++)
	{
		for (int j = 0; j < Config::SCREEN_WIDTH / Config::TILE_SIZE; j++)
		{
			Tile* tmp = new Tile;
			tmp->Create("../Assets/dirt.png", posX, posY, difference, difference);
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

bool Grid::Spread(int x, int y) // The grid it wants to spread too
{
   const char * tile = LookAtTile(x, y);
   if (tile == "cbt")
   {
      return false;
   }

   if (rand() % 2 == 0)
   {
      if (tile == "Empty")
      {
         Grass* tmp = new Grass();
         tmp->Create("../Assets/grass.png", x * Config::TILE_SIZE, y * Config::TILE_SIZE);
         tmp->position_.x_ = x;
         tmp->position_.y_ = y;
         tmp->grid_ = this;
         grass_->push_back(tmp);
         tiles_.at(GetTileIndex(x, y))->grass_ = tmp;

         return true;
      }
   }
   return false;
}

bool Grid::Spread(Vector2 pos)
{
   return Spread(pos.x_, pos.y_);
}

bool Grid::Breed(Vector2 pos, Agent::Species species)
{
	const char* tile = LookAtTile(pos);
	if (tile == "cbt") //outside bounds
	{
		return false;
	}
	switch (species)
	{
		case Agent::WOLF:
			if (tile != "Wolf")
			{
				Agent* tmpWolf = new Agent("../Assets/wolf.png", new WanderState(), pos);

				tmpWolf->currentState_->agent_ = tmpWolf;
            tmpWolf->species_ = Agent::WOLF;
            tmpWolf->speed_ = 2;
				tmpWolf->grid_ = this;
				int index = GetTileIndex(pos);
				tiles_[index]->agents_[1] = tmpWolf;
				agents_->push_back(tmpWolf);
				return true;
			}
			break;
		case Agent::SHEEP:
			if (tile != "Sheep")
			{
				Agent* tmpSheep = new Agent("../Assets/sheep.png", new WanderState(), pos);
            tmpSheep->species_ = Agent::SHEEP;
            tmpSheep->speed_ = 1;
				tmpSheep->grid_ = this;
            tmpSheep->hunger_ = 7.5f; // Hardcoded to half hunger
				int index = GetTileIndex(pos);
				tiles_[index]->agents_[0] = tmpSheep;
				agents_->push_back(tmpSheep);
            
				return true;
			}
			break;
	}
	
	return false;
}

float Grid::EatGrass(float biteSize, Vector2 pos)
{
   int index = GetTileIndex(pos);
   if (tiles_.at(index)->grass_ == nullptr)
   {
      return -1.0f;
   }
   return tiles_.at(index)->grass_->Eaten(biteSize); // Bless you God for this boutiful harvest. Amen.
}

int Grid::GetTileIndex(int x, int y)
{
   int index = 0;

   int maxX = Config::SCREEN_WIDTH  / Config::TILE_SIZE;
   int maxY = Config::SCREEN_HEIGHT / Config::TILE_SIZE;

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

   int maxX = Config::SCREEN_WIDTH / Config::TILE_SIZE;
   int maxY = Config::SCREEN_HEIGHT / Config::TILE_SIZE;

   returnVector.x_ = index % maxX;
   returnVector.y_ = index / maxX;
   return returnVector;
}

const char* Grid::LookAtTile(int x, int y)
{
   int index = GetTileIndex(x, y);
   if (index == -1)
   {
      return "cbt";
   }
   return LookAtTile(index);
}

const char* Grid::LookAtTile(Vector2 pos)
{
   return LookAtTile(pos.x_, pos.y_);
}

const char* Grid::LookAtTile(int index)
{
   if (index > tiles_.size()){
      return "cbt";
   }
   else if (tiles_.at(index)->agents_[1] != nullptr) { // looks at the wolf
      return "Wolf";
   }
   else if (tiles_.at(index)->agents_[0] != nullptr) { // looks at the sheep
      return "Sheep";
   }
   else if (tiles_.at(index)->grass_ != nullptr) { // Looks at the grass
      return "Grass";
   }
   else {
      return "Empty";
   }
}

Vector2* Grid::SenseSheep(Vector2 pos, float radius)
{
   float distance = 0;
   float closestDst = -1;
   Vector2* result = nullptr;
   Vector2* tmp;
   for (int i = 0; i < agents_->size(); i++)
   {
      tmp = &agents_->at(i)->position_;
      
      if (agents_->at(i)->species_ == Agent::WOLF)
      {
         continue;
      }

      Vector2 distVect = *tmp - pos; // I don't know how to improve operator overloading
      distance = Magnitude(distVect);
      if ((distance < closestDst || closestDst == -1) && distance <= radius)
      {
         result = tmp;
         closestDst = distance;
      }
   }
   return result;
}

Vector2* Grid::SenseGrass(Vector2 pos, float radius)
{
   float distance = 0;
   float closestDst = -1;

   Vector2* result = nullptr;
   Vector2* tmp;
   for (int i = 0; i < grass_->size(); i++)
   {
      tmp = &grass_->at(i)->position_;

      Vector2 distVect = *tmp - pos; // I don't know how to improve operator overloading
      distance = Magnitude(distVect);
      if (distance < closestDst && distance <= radius
          || closestDst == -1 && distance <= radius)
      {
         result = tmp;
         closestDst = distance;
      }
   }
   return result;
}

Vector2 Grid::SenseWolves(Vector2 pos, float radius)
{
	float distance = 0;
	Vector2 result = { 0,0 };
	//radius = radius / 2;
	Vector2 tmp;
	for (int i = 0; i < agents_->size(); i++)
	{
		tmp = agents_->at(i)->position_;

		if (agents_->at(i)->species_ == Agent::SHEEP)
		{
			continue;
		}

		Vector2 distVect = tmp - pos; // I don't know how to improve operator overloading
		distance = Magnitude(distVect);
		if (distance <= radius)
		{
			result = result + distVect;
		}
	}
	return result * -1;
}

Vector2 Grid::SenseWall(Vector2 pos, float radius)
{
	Vector2 result = { 0,0 };
	radius = radius;
	float distLeft = fabs(pos.x_);
	float distRight = fabs(Config::SCREEN_WIDTH / Config::TILE_SIZE - pos.x_);
	float distUp = fabs(pos.y_);
	float distDown = fabs(Config::SCREEN_HEIGHT / Config::TILE_SIZE - pos.y_);
   
	if (distLeft < radius)
	{
		result.x_ = 1 / distLeft;
	}
	else if (distRight < radius)
	{
      result.x_ = -1 / distRight;
	}

	if (distUp < radius)
	{
		result.y_ = 1 / distUp;
	}
	else if (distDown < radius)
	{
		result.y_ = -1 / distDown;
	}
	return result;
}
