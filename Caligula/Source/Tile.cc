#include "Tile.h"
#include "Service.h"
#include "SpriteHandler.h"
#include "Config.h"
#include "Random.h"

void Tile::Create(int xPos, int yPos, int height, int width)
{
	bounds_.x = xPos;
	bounds_.y = yPos;
	bounds_.h = height;
	bounds_.w = width;

	int blocked = Random::Rand(-1,4);
	if (blocked <= 0)
	{
		currentType_ = TileType::BLOCKED;
		currentSprite_ = Service<SpriteHandler>::Get()->CreateSprite("../Assets/blocked.png", 0, 0, height, width);
	}
	else
	{
		currentType_ = TileType::EMPTY;
		currentSprite_ = Service<SpriteHandler>::Get()->CreateSprite("../Assets/stars.png", 0, 0, height, width);
	}
   borderColor_ = { 255,255,255,255 };
}

void Tile::Render(SDL_Renderer* renderer_)
{
	SDL_Rect dst = { bounds_.x,  bounds_.y, currentSprite_->GetArea().w, currentSprite_->GetArea().h };
	SDL_RenderCopy(renderer_, currentSprite_->GetTexture(), &currentSprite_->GetArea(), &dst);

	SDL_SetRenderDrawColor(renderer_, borderColor_.r, borderColor_.g, borderColor_.b, borderColor_.a);
	if (Config::DEBUGRENDER == TRUE)
		SDL_RenderDrawRect(renderer_, &bounds_);

}

void Tile::SwitchTileType(TileType newType)
{
	//change sprite
	switch (newType)
	{
	case TileType::STAR:
		currentSprite_ = Service<SpriteHandler>::Get()->CreateSprite("../Assets/fallen.png", 0, 0, bounds_.h, bounds_.w);
		break;
	case TileType::BLOCKED:
		currentSprite_ = Service<SpriteHandler>::Get()->CreateSprite("../Assets/blocked.png", 0, 0, bounds_.h, bounds_.w);
		break;
	case TileType::EMPTY:
		currentSprite_ = Service<SpriteHandler>::Get()->CreateSprite("../Assets/stars.png", 0, 0, bounds_.h, bounds_.w);
		break;
	case TileType::SPACESHIP:
		currentSprite_ = Service<SpriteHandler>::Get()->CreateSprite("../Assets/spaceStation.png", 0, 0, bounds_.h, bounds_.w);
		break;
	case TileType::TRADING:
		currentSprite_ = Service<SpriteHandler>::Get()->CreateSprite("../Assets/traderStation.png", 0, 0, bounds_.h, bounds_.w);
		break;
	}
	currentType_ = newType;
}
