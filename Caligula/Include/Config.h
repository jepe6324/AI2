#pragma once

constexpr bool TRUE = true;
constexpr bool FALSE = false;

struct Config
{
	static const int INTERNAL_WIDTH = 640;
	static const int INTERNAL_HEIGHT = 480;
   
   static const int OUTPUT_WIDTH = 1280;
   static const int OUTPUT_HEIGHT = 960;

   static const int TILE_SIZE = 30;
	static const bool DEBUGRENDER = TRUE;
};