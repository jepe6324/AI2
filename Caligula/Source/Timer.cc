#include "Timer.h"

Timer::Timer(float startValue, bool startPaused)
{ // Expects time as seconds
   initialValue_ = startValue;
   currentValue_ = startValue;
   paused_ = startPaused;
   deltaTime_.Update(); // I do this to makesure that the actually used dt values are accurate
}

bool Timer::IsDone()
{
   deltaTime_.Update();

   if (!paused_) {
      float dt = deltaTime_.AsSeconds();
      currentValue_ -= dt;
      if (currentValue_ <= 0)
      {
         return true;
      }
   }
   return false;
}

void Timer::Reset()
{
   currentValue_ = initialValue_;
}

void Timer::Pause()
{
   paused_ = true;
}

void Timer::Start() 
{
   paused_ = false;
   deltaTime_.Update();
}