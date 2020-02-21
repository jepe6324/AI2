//VECTOR_H_INCLUDED 

// MADE BY PEACE

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cmath>
#include <iostream>

struct Vector2 {
	Vector2() { x_ = 0.0f; y_ = 0.0f; }
	Vector2(float x, float y) { x_ = x; y_ = y; }

	float x_;
	float y_;

   void Normalize() {
      float x = powf(x_, 2);
      float y = powf(y_, 2);
      float total = x + y;
      float magnitude = _CMATH_::sqrt(total);
      x_ /= magnitude;
      y_ /= magnitude;
   }
	float dot(Vector2 first, Vector2 second) {
		first.Normalize();
		second.Normalize();
		return first.x_ * second.x_ + first.y_, second.y_;
	}
	Vector2 operator+(Vector2 other) {
		return Vector2(x_ + other.x_, y_ + other.y_);
	}
	Vector2 operator-(Vector2 other) {
		return Vector2(x_ - other.x_, y_ - other.y_);
	}
	Vector2 operator/(float divider) {
		return Vector2(x_ / divider, y_ / divider);
	}
	Vector2 operator*(float multiplier) {
		return Vector2(x_ * multiplier, y_ * multiplier);
	}
	Vector2 operator*(Vector2 other) {
		return Vector2(x_ * other.x_, y_ * other.y_);
	}
	bool operator!=(Vector2 other) {
		return x_ == other.x_ && y_ == other.y_ ? x_ != other.x_ && y_ != other.y_ : false;
	}
   bool operator==(Vector2 other) {
      return x_ == other.x_ && y_ == other.y_;
   }
};


static float Magnitude(Vector2 vector) {
   vector.x_ = powf(vector.x_, 2);
   vector.y_ = powf(vector.y_, 2);
   float total = vector.x_ + vector.y_;
   return _CMATH_::sqrt(total);
}

static float Distance(Vector2 lhs, Vector2 rhs)
{
   return Magnitude(lhs - rhs);
}

static Vector2 Lerp(Vector2 lhs, Vector2 rhs, float percent)
{
   return ( lhs + ( rhs - lhs ) * percent);
}

#endif // !VECTOR_H_INCLUDED
