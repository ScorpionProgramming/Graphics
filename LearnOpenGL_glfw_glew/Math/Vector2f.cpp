#include "Vector2f.h"



Vector2f::Vector2f()
{
	this->x = 0;
	this->y = 0;
}

Vector2f::Vector2f(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2f Vector2f::operator+(const Vector2f & v) const
{
	Vector2f erg; 
	erg.x = this->x + v.x;
	erg.y = this->y + v.y;	
	return erg;
}

Vector2f Vector2f::operator-(const Vector2f & v) const
{
	Vector2f erg;
	erg.x = this->x - v.x;
	erg.y = this->y - v.y;
	return erg;
}

Vector2f Vector2f::operator-()
{
	-this->x;
	-this->y;
	return *this;
}

Vector2f Vector2f::operator+=(const Vector2f & v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2f Vector2f::operator*(float c) const
{
	Vector2f erg;
	erg.x = this->x * c;
	erg.y = this->y * c;
	return erg;
}

float Vector2f::length() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

float Vector2f::lengthSquared() const
{
	return length() * length();
}