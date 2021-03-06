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

#include "WalkState.h"

TEST_STATE_1::TEST_STATE_1(SDL_Renderer& p_renderer) 
   : m_renderer(&p_renderer)
   , dude_ ("../Assets/astronaut.png", 32,32, nullptr, {0,0})
{
	m_sound = Service<SoundHandler>::Get()->CreateSound("../Assets/plopp.wav");
   currentState_ = GameState::EDIT;
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
   Service<Grid>::Get()->Render(m_renderer);

   switch (currentState_) {
   case GameState::EDIT:
      player_.Update();
      break;
   case GameState::SIMULATE:
      dude_.Update(deltaTime_.AsSeconds());
      dude_.Render(m_renderer);
      break;
   }

	return true;
}

void TEST_STATE_1::Exit()
{
	std::cout << "TEST_STATE_1::Exit" << std::endl;
}

void TEST_STATE_1::changeState(GameState newState)
{
   switch (newState)
   {
   case GameState::EDIT:
      if (Service<Grid>::Get()->GetSpecialTilePos(Tile::TileType::STAR).x_ < 0.0f ||
          Service<Grid>::Get()->GetSpecialTilePos(Tile::TileType::STAR).y_ < 0.0f)
      {
         Service<Grid>::Get()->SpawnSpecialTile(Tile::TileType::STAR);
      }
      break;
   case GameState::SIMULATE:
      dude_.position_ = Service<Grid>::Get()->GetSpecialTilePos(Tile::TileType::SPACESHIP);
      dude_.SwitchState(new WalkState(&dude_));
      dude_.hasStar_ = false;
      break;
   }
   currentState_ = newState;
}
