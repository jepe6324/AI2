#include "TEST_STATE_1.h"
#include "Service.h"
#include "SoundHandler.h"
#include "InputHandler.h"
#include "Grid.h"
#include "Sound.h"
#include <iostream>
#include "Config.h"
#include <time.h>
#include "Random.h"


TEST_STATE_1::TEST_STATE_1(SDL_Renderer& p_renderer) : m_renderer(&p_renderer)
{
	m_sound = Service<SoundHandler>::Get()->CreateSound("../Assets/plopp.wav");
}

void TEST_STATE_1::Enter()
{
	srand(time(NULL));
   Service<Grid>::Get()->Create();

	//int size = grid_.tiles_.size();
}

bool TEST_STATE_1::Update()
{
   deltaTime_.Update();
   player_.Update();

   Vector2 ship = Service<Grid>::Get()->GetSpecialTilePos(Tile::TileType::SPACESHIP);
   Vector2 star = Service<Grid>::Get()->GetSpecialTilePos(Tile::TileType::STAR);

   aStar_.PathFindStart(ship, star);

   Service<Grid>::Get()->Render(m_renderer);
	return true;
}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}
