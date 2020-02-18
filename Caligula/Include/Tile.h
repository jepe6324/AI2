//TILE_H_INCLUDED

#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <SDL.h>
#include "Sprite.h"

struct Tile {
	enum class TileType
	{
		EMPTY,
		BLOCKED,
		TRADING,
		SPACESHIP,
		STAR,
	};
	SDL_Rect bounds_;
	Sprite* currentSprite_;
	TileType currentType_;

   SDL_Color borderColor_;

	void Create(int xPos, int yPos, int height, int width);
	void Render(SDL_Renderer* renderer_);
	void SwitchTileType(TileType newType);
};

#endif // !TILE_H_INCLUDED
