#include "Tile.h"
#include "Service.h"
#include "SpriteHandler.h"
#include "Config.h"

void Tile::Create(const char* p_textureFilePath, int xPos, int yPos, int height, int width)
{
	bounds_.x = xPos;
	bounds_.y = yPos;
	bounds_.h = height;
	bounds_.w = width;

	currentSprite_ = Service<SpriteHandler>::Get()->CreateSprite(p_textureFilePath, 0, 0, height, width);
}

void Tile::Render(SDL_Renderer* renderer_)
{
	SDL_Rect dst = { bounds_.x,  bounds_.y, currentSprite_->GetArea().w, currentSprite_->GetArea().h };
	SDL_RenderCopy(renderer_, currentSprite_->GetTexture(), &currentSprite_->GetArea(), &dst);

	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 0);
	if (Config::DEBUGRENDER == TRUE)
		SDL_RenderDrawRect(renderer_, &bounds_);

}