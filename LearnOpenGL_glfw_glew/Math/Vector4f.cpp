#include "Vector4f.h"

Vector4f::Vector4f()
{
	this->x = 0; 
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

Vector4f::Vector4f(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4f::Vector4f(Vector3f vec3f, float w)
{
	this->x = vec3f.x;
	this->y = vec3f.y;
	this->z = vec3f.z;
	this->w = w;
}

Vector4f Vector4f::operator*(float c) const
{
	Vector4f erg;
	erg.x = this->x * c;
	erg.y = this->y * c;
	erg.z = this->z * c;
	erg.w = this->w * c;
	return erg;
}
