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


TEST_STATE_1::TEST_STATE_1(SDL_Renderer& p_renderer) 
   : m_renderer(&p_renderer)
   , dude_ ("../Assets/astronaut.png", 32,32, nullptr, {0,0})
{
	m_sound = Service<SoundHandler>::Get()->CreateSound("../Assets/plopp.wav");
}

void TEST_STATE_1::Enter()
{
	srand(time(NULL));
   Service<Grid>::Get()->Create();
   dude_.Move(Service<Grid>::Get()->GetSpecialTilePos(Tile::TileType::SPACESHIP));

	//int size = grid_.tiles_.size();
}

bool TEST_STATE_1::Update()
{
   deltaTime_.Update();

   Service<Grid>::Get()->ClearTileColour();

   dude_.Update(deltaTime_.AsSeconds());
   player_.Update();

	Vector2 ship = Service<Grid>::Get()->GetSpecialTilePos(Tile::TileType::SPACESHIP);
	Vector2 star = Service<Grid>::Get()->GetSpecialTilePos(Tile::TileType::STAR);

	path_ = aStar_.PathFindStart(ship, star);

   Service<Grid>::Get()->Render(m_renderer);
   dude_.Render(m_renderer);
	return true;
}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}
