
#pragma comment(lib, "../Dependencies/SDL2/lib/x64/SDL2.lib")
#pragma comment(lib, "../Dependencies/SDL2/lib/x64/SDL2main.lib")
#pragma comment(lib, "../Dependencies/SDL2_mixer/lib/x64/SDL2_mixer.lib")
#pragma comment(lib, "../Dependencies/SDL2_image/lib/x64/SDL2_image.lib")

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include "InputHandler.h"
#include "SpriteHandler.h"
#include "SoundHandler.h"
#include "Grid.h"
#include "Service.h"
#include "Config.h"

#include "FSM.h"
#include "TEST_STATE_1.h"

const float Config::SCALE_HEIGHT = float(Config::OUTPUT_HEIGHT) / float(Config::INTERNAL_HEIGHT);
const float Config::SCALE_WIDTH = float(Config::OUTPUT_WIDTH) / float(Config::INTERNAL_WIDTH);

int main(int ac, char** av)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s", SDL_GetError());

	if(Mix_Init(MIX_INIT_MP3) == 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL_mixer: %s", Mix_GetError());

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize OpenAudio: %s", Mix_GetError());
	
	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize IMG: %s", IMG_GetError());

	SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Config::OUTPUT_WIDTH, Config::OUTPUT_HEIGHT, 0);
	if(window == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create SDL_Window: %s", SDL_GetError());
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create SDL_Renderer: %s", SDL_GetError());

   SDL_RenderSetScale(renderer, Config::SCALE_WIDTH, Config::SCALE_HEIGHT);

	{ // Scope to add limited lifetime for out handlers and game loop
		SpriteHandler spriteHandler(renderer);
		InputHandler inputHandler;
		SoundHandler soundHandler;
      Grid grid;

		Service<SpriteHandler>::Set(&spriteHandler);
		Service<InputHandler>::Set(&inputHandler);
		Service<SoundHandler>::Set(&soundHandler);
      Service<Grid>::Set(&grid);

		FSM stateMachine;
		TEST_STATE_1 stateOne(*renderer);
		stateMachine.SwitchState(&stateOne);

      Tile* tile = nullptr;

		bool running = true;
		while (running)
		{
			// UPDATE INPUT AND HANDLE EVENTS
			inputHandler.HandleEvents();
			if (inputHandler.IsKeyDown(SDL_SCANCODE_ESCAPE))
			{
				running = false;
			}

         if (Config::DEBUGRENDER)
         {
            system("cls");
            Vector2 mousePos;
            mousePos.x_ = inputHandler.GetMousePositionX();
            mousePos.y_ = inputHandler.GetMousePositionY();

            mousePos = mousePos / Config::TILE_SIZE;
            mousePos.x_ /= Config::SCALE_WIDTH;
            mousePos.y_ /= Config::SCALE_HEIGHT;

            if (tile != nullptr)
               tile->borderColor_ = { 255,255,255,255 };

            tile = grid.GetTile(mousePos);
            if (tile != nullptr)
               tile->borderColor_ = { 255,5,0,255 };
         }

			// CLEARING SCREEN
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);

			// UPDATING FSM
			stateMachine.Update();

			// PRESENTING TO THE SCREEN
			SDL_RenderPresent(renderer);
		}
	}

	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	if (window != nullptr)
		SDL_DestroyWindow(window);

	IMG_Quit();

	Mix_CloseAudio();

	Mix_Quit();

	SDL_Quit();
	return 0;
}