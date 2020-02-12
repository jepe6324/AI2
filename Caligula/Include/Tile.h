//TILE_H_INCLUDED

#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <SDL.h>
#include "Sprite.h"

struct Tile {
	enum class TileType
	{
		STARS,
		BLOCKED,
		TRADING,
		SPACESHIP,
	};
	SDL_Rect bounds_;
	Sprite* currentSprite_;
	TileType currentType_;

	void Create(int xPos, int yPos, int height, int width);
	void Render(SDL_Renderer* renderer_);
};

#endif // !TILE_H_INCLUDED
