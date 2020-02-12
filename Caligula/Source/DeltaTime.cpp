#include "DeltaTime.h"

DeltaTime::DeltaTime()
{
   tick = 0;
}

void DeltaTime::Update()
{
   int64 prevTick = tick;
   tick = SDL_GetTicks();

   dt = tick - prevTick;

   //std::cout << dt << std::endl;
}

float DeltaTime::AsMilliseconds()
{
   return dt;
}

float DeltaTime::AsSeconds()
{
   return float(dt) / 1000;
}
