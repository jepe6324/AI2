#include "Random.h"

float Random::Randf(float min, float max)
{
   float tmp = float(rand()) / float(RAND_MAX);
   float abs = max - min;
   return (tmp * abs) + min;
}

int Random::Rand(int min, int max)
{
   return min + (rand() %(max-min + 1));
}