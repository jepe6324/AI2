// Random.h

#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <random>
#include <time.h>

struct Random
{ // Assumes srand(time(NULL)); has been run at some point
   static float Randf(float min, float max);
   static int Rand(int min, int max);
};

#endif // !RANDOM_H_INCLUDED