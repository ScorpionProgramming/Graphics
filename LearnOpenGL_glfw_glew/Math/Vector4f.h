#pragma once
#include "Vector3f.h"
class Vector4f
{
public:
	float x; 
	float y;
	float z;
	float w;
	Vector4f();
	Vector4f(float x, float y, float z, float w);
	Vector4f(Vector3f vec3f, float w);
	Vector4f operator*(float c) const;
};

