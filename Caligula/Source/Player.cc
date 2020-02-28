#include "..\Include\Player.h"

#include "Tile.h"
#include "Config.h"

#include "Service.h"
#include "InputHandler.h"
#include "Grid.h"
#include "TEST_STATE_1.h"

void Player::Update()
{
   UpdateMouse();

   HoverTile();

   if (Service<InputHandler>::Get()->IsMouseButtonPressed(SDL_BUTTON_LEFT))
   {
      SelectTile();
   }
   Service<Grid>::Get()->ChangeTileColor(selected_, { 255,255,0,255 });
	if (Service<InputHandler>::Get()->IsKeyPressed(SDL_SCANCODE_SPACE))
	{
      Service<TEST_STATE_1>::Get()->changeState(TEST_STATE_1::GameState::SIMULATE);
	}
}

void Player::UpdateMouse()
{
   mousePos_.x_ = Service<InputHandler>::Get()->GetMousePositionX();
   mousePos_.y_ = Service<InputHandler>::Get()->GetMousePositionY();

   mousePos_ = mousePos_ / Config::TILE_SIZE;
   mousePos_.x_ /= Config::SCALE_WIDTH;
   mousePos_.y_ /= Config::SCALE_HEIGHT;
}

void Player::HoverTile()
{
   if (hovered_ != nullptr && hovered_ != selected_)
      hovered_->borderColor_ = { 255,255,255,255 };

   hovered_ = Service<Grid>::Get()->GetTile(mousePos_);
   if (hovered_ != nullptr && hovered_ != selected_)
      hovered_->borderColor_ = { 255,5,0,255 };
}

void Player::SelectTile()
{
   Tile* selected = nullptr;

   selected = Service<Grid>::Get()->GetTile(mousePos_);

   if (selected == nullptr)
      return;

   if (selected_ != nullptr){
      selected_->borderColor_ = { 255,255,255,255 };
      
      HandleTile(selected);
   }
   else
   {
      switch (selected->currentType_)
      {
      case Tile::TileType::BLOCKED:
         selected->SwitchTileType(Tile::TileType::EMPTY);
         break;
      case Tile::TileType::EMPTY:
         selected->SwitchTileType(Tile::TileType::BLOCKED);
         break;
      default:
         HandleTile(selected);
         break;
      }
   }
   
   if (selected_ != nullptr)
      selected_->borderColor_ = { 0,255,0,255 };
}

void Player::SwitchTiles(Tile* lhs, Tile* rhs)
{
   Tile::TileType tmp = lhs->currentType_;
   
   lhs->SwitchTileType(rhs->currentType_);
   rhs->SwitchTileType(tmp);
}

void Player::HandleTile(Tile* selected)
{
   if (selected_ != nullptr)
   {
      
      if (selected_->currentType_ == selected->currentType_)
      {
         selected_ = nullptr;
      }
      else
      {
         SwitchTiles(selected, selected_);
         selected_ = nullptr;
      }
   }
   else
   {
      selected_ = selected;
   }
}


