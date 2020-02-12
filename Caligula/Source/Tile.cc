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
		currentType_ = TileType::STARS;
		currentSprite_ = Service<SpriteHandler>::Get()->CreateSprite("../Assets/stars.png", 0, 0, height, width);
	}
}

void Tile::Render(SDL_Renderer* renderer_)
{
	SDL_Rect dst = { bounds_.x,  bounds_.y, currentSprite_->GetArea().w, currentSprite_->GetArea().h };
	SDL_RenderCopy(renderer_, currentSprite_->GetTexture(), &currentSprite_->GetArea(), &dst);

	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 0);
	if (Config::DEBUGRENDER == TRUE)
		SDL_RenderDrawRect(renderer_, &bounds_);

}