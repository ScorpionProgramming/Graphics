#include "Matrix4f.h"


Matrix4f::Matrix4f()
{
	this->a = 0; this->b = 0; this->c = 0; this->d = 0;
	this->e = 0; this->f = 0; this->g = 0; this->h = 0;
	this->i = 0; this->j = 0; this->k = 0; this->l = 0;
	this->m = 0; this->n = 0; this->o = 0; this->p = 0;
}

Matrix4f::Matrix4f(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
{
	this->a = a; this->b = b; this->c = c; this->d = d;
	this->e = e; this->f = f; this->g = g; this->h = h;
	this->i = i; this->j = j; this->k = k; this->l = l;
	this->m = m; this->n = n; this->o = o; this->p = p;
}

Matrix4f Matrix4f::operator*(const Matrix4f mat) const
{
	Matrix4f erg;
	erg = *this;
	return erg;
}

Vector4f Matrix4f::operator*(const Vector4f vec) const
{
	Vector4f erg;
	erg.x = this->a * vec.x + this->b*vec.y + this->c * vec.z + this->d * vec.w;
	erg.y = this->e * vec.x + this->f*vec.y + this->g * vec.z + this->h * vec.w;
	erg.z = this->i * vec.x + this->j*vec.y + this->k * vec.z + this->l * vec.w;
	erg.w = this->m * vec.x + this->n*vec.y + this->o * vec.z + this->p * vec.w;
	return erg;
}

std::string Matrix4f::toString()
{
	std::stringstream ss;
	ss << "4x4-Matrix: \n";
	ss << this->a << " " << this->b << " " << this->c << " " << this->d << "\n";
	ss << this->e << " " << this->f << " " << this->g << " " << this->h << "\n";
	ss << this->i << " " << this->j << " " << this->k << " " << this->l << "\n";
	ss << this->m << " " << this->n << " " << this->o << " " << this->p << "\n";
	return ss.str();
}
