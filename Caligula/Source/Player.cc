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
   if (hovered_ != nullptr && hovered_ != tileToMove_)
      hovered_->borderColor_ = { 255,255,255,255 };

   hovered_ = Service<Grid>::Get()->GetTile(mousePos_);
   if (hovered_ != nullptr && hovered_ != tileToMove_)
      hovered_->borderColor_ = { 255,5,0,255 };
}

void Player::SelectTile()
{
   Tile* selected = nullptr;

   selected = Service<Grid>::Get()->GetTile(mousePos_);

   if (selected == nullptr)
      return;

   if (tileToMove_ != nullptr){
      tileToMove_->borderColor_ = { 255,255,255,255 };
      
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
   
   if (tileToMove_ != nullptr)
      tileToMove_->borderColor_ = { 0,255,0,255 };
}

void Player::SwitchTiles(Tile* lhs, Tile* rhs)
{
   Tile::TileType tmp = lhs->currentType_;
   
   lhs->SwitchTileType(rhs->currentType_);
   rhs->SwitchTileType(tmp);
}

void Player::HandleTile(Tile* selected)
{
   if (tileToMove_ != nullptr)
   {
      
      if (tileToMove_->currentType_ == selected->currentType_)
      {
         tileToMove_ = nullptr;
      }
      else
      {
         SwitchTiles(selected, tileToMove_);
         tileToMove_ = nullptr;
      }
   }
   else
   {
      tileToMove_ = selected;
   }
}