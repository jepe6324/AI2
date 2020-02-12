//TIMER_H_INCLUDED
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include "DeltaTime.h"

struct Timer
{
   DeltaTime deltaTime_;
   float initialValue_;
   float currentValue_;
   bool paused_;

   Timer(float startValue, bool startPaused = false) { // Expects time as seconds
      initialValue_ = startValue;
      currentValue_ = startValue;
      paused_ = startPaused;
      deltaTime_.Update(); // I do this to makesure that the actually used dt values are accurate
   }

   bool IsDone() {
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
   void Reset() { currentValue_ = initialValue_; }
   void Pause() { paused_ = true; }
   void Start() { 
      paused_ = false;
      deltaTime_.Update();
   }
};

#endif // !TIMER_H_INCLUDED
