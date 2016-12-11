#include "Color.h"

Color::Color()
{
	this->R = 0;
	this->G = 0;
	this->B = 0;
}

Color::Color(float r, float g, float b)
{
	this->R = r;
	this->G = g;
	this->B = b;
}

Color Color::operator*(const Color & c) const
{
	Color clr;
	clr.R = this->R * c.R;
	clr.G = this->G * c.G;
	clr.B = this->B * c.B;
	return clr;
}

Color Color::operator*(const float Factor) const
{
	Color clr;
	clr.R = this->R * Factor;
	clr.G = this->G * Factor;
	clr.B = this->B * Factor;
	return clr;
}

Color Color::operator+(const Color & c) const
{
	Color clr;
	clr.R = this->R + c.R;
	clr.G = this->G + c.G;
	clr.B = this->B + c.B;
	return clr;
}
Color & Color::operator+=(const Color & c)
{
	this->R += c.R;
	this->G += c.G;
	this->B += c.B;
	return *this;
}
