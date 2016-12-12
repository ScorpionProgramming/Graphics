#pragma once
#include <math.h>

class Vector3f
{
public:
	float x;
	float y;
	float z;

	Vector3f();
	Vector3f(float x, float y, float z);

	float dot(const Vector3f& v) const;
	Vector3f cross(const Vector3f& v) const;
	Vector3f operator+(const Vector3f& v) const;
	Vector3f Vector3f::operator-(const Vector3f & v) const;
	Vector3f operator-();
	Vector3f& operator+=(const Vector3f& v);
	Vector3f operator*(float c) const;
	Vector3f normalize();
	float length() const;
	float lengthSquared() const;
};

