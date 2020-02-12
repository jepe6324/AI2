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

   Timer(float startValue, bool startPaused = false);

   bool IsDone();
   void Reset();
   void Pause();
   void Start();
};

#endif // !TIMER_H_INCLUDED
