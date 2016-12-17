#include "Vector3f.h"

Vector3f::Vector3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3f::dot(const Vector3f & v) const
{
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector3f Vector3f::cross(const Vector3f & v) const
{
	Vector3f erg;
	erg.x = this->y * v.z - this->z * v.y;
	erg.y = this->z * v.x - this->x * v.z;
	erg.z = this->x * v.y - this->y * v.x;
	return erg;
}

Vector3f Vector3f::operator+(const Vector3f & v) const
{
	Vector3f erg;
	erg.x = this->x + v.x;
	erg.y = this->y + v.y;
	erg.z = this->z + v.z;
	return erg;
}

Vector3f Vector3f::operator-(const Vector3f & v) const
{
	Vector3f erg;
	erg.x = this->x - v.x;
	erg.y = this->y - v.y;
	erg.z = this->z - v.z;
	return erg;
}

Vector3f Vector3f::operator-()
{
	-this->x;
	-this->y;
	-this->z;
	return *this;
}

Vector3f & Vector3f::operator+=(const Vector3f & v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vector3f Vector3f::operator*(float c) const
{
	Vector3f erg;
	erg.x = this->x * c;
	erg.y = this->y * c;
	erg.z = this->z * c;
	return erg;
}

Vector3f Vector3f::normalize()
{
	float _length = length();
	this->x = this->x / _length;
	this->y = this->y / _length;
	this->z = this->z / _length;
	return *this;
}

float Vector3f::length() const
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vector3f::lengthSquared() const
{
	return length() * length();
}

