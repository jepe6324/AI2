#include "..\Include\SleepState.h"

#include "Agent.h"
#include "WalkState.h"

SleepState::SleepState(Agent* agent)
   :alarmClock_(5.0f)
{
}

bool SleepState::Update(float dt)
{
   if (alarmClock_.IsDone())
   {
      agent_->SwitchState(new WalkState(agent_));
      alarmClock_.Reset();
   }
   return true;
}

void SleepState::Exit()
{
   agent_->stamina_ = agent_->maxStamina_;
   agent_->Sense();
}
