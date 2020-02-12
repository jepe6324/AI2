// DeltaTime.h

#ifndef DELTATIME_H_INCLUDED
#define DELTATIME_H_INCLUDED

#include <SDL.h>

typedef   signed long long int64;

struct DeltaTime {

   DeltaTime();

   //DeltaTime operator+(const DeltaTime& rhs) const;
   //DeltaTime operator-(const DeltaTime& rhs) const;
   //DeltaTime& operator+=(const DeltaTime& rhs);
   //DeltaTime& operator-=(const DeltaTime& rhs);

   //bool operator<(const DeltaTime& rhs) const;
   //bool operator>(const DeltaTime& rhs) const;
   //bool operator==(const DeltaTime& rhs) const;
   //bool operator!=(const DeltaTime& rhs) const;

   void Update();
   float AsMilliseconds();
   float AsSeconds();

   int64 tick;
   int64 dt;
};

#endif // !DELTATIME_H_INCLUDED
