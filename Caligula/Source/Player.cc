#include "..\Include\Player.h"

#include "Tile.h"
#include "Config.h"

#include "Service.h"
#include "InputHandler.h"
#include "Grid.h"

void Player::Update()
{
   UpdateMouse();

   HoverTile();

   if (Service<InputHandler>::Get()->IsMouseButtonPressed(SDL_BUTTON_LEFT))
   {
      SelectTile();
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
   if (selected_ != nullptr)
      selected_->borderColor_ = { 255,255,255,255 };

   selected_ = Service<Grid>::Get()->GetTile(mousePos_);

   switch (selected_->currentType_)
   {
   case Tile::TileType::BLOCKED:
		selected_->SwitchTileType(Tile::TileType::EMPTY);
      break;
   case Tile::TileType::EMPTY:
		selected_->SwitchTileType(Tile::TileType::BLOCKED);
      break;
   case Tile::TileType::TRADING:
      break;
   case Tile::TileType::SPACESHIP:
      break;
   case Tile::TileType::STAR:
      break;

   default:
      break;
   }
   if (selected_ != nullptr)
      selected_->borderColor_ = { 0,255,0,255 };
}
