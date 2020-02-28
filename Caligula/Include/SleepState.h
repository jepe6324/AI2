// SleepState.h

#ifndef SLEEPSTATE__H_INCLUDED
#define SLEEPSTATE__H_INCLUDED

#include "State.h"
#include "Timer.h"

struct agent;

struct SleepState : AgentState
{
   Timer alarmClock_;

   SleepState(Agent* agent);

   bool Update(float dt);
   void Exit();
};

#endif // !SLEEPSTATE__H_INCLUDED
