#pragma once
#include <math.h>

class Vector2f
{
public:
	float x; float y;
	Vector2f();
	Vector2f(float x, float y);
	Vector2f operator+(const Vector2f &v) const;
	Vector2f operator-(const Vector2f &v) const;
	Vector2f operator-();
	Vector2f operator+=(const Vector2f &v);
	Vector2f operator*(float c)const;
	
	float length() const;
	float lengthSquared() const;
};

