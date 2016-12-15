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

void Matrix4f::operator=(const Matrix4f mat)
{
	this->a = mat.a; this->b = mat.b; this->c = mat.c; this->d = mat.d;
	this->e = mat.e; this->f = mat.f; this->g = mat.g; this->h = mat.h;
	this->i = mat.i; this->j = mat.j; this->k = mat.k; this->l = mat.l;
	this->m = mat.m; this->n = mat.n; this->o = mat.o; this->p = mat.p;
}

Matrix4f Matrix4f::operator*(const Matrix4f mat) const
{
	Matrix4f erg;
	erg.a = this->a * mat.a + this->b * mat.e + this->c * mat.i + this->d * mat.m;
	erg.b = this->a * mat.b + this->b * mat.f + this->c * mat.j + this->d * mat.n;
	erg.c = this->a * mat.c + this->b * mat.g + this->c * mat.k + this->d * mat.o;
	erg.d = this->a * mat.d + this->b * mat.h + this->c * mat.l + this->d * mat.p;

	erg.e = this->e * mat.a + this->f * mat.e + this->g * mat.i + this->h * mat.m;
	erg.f = this->e * mat.b + this->f * mat.f + this->g * mat.j + this->h * mat.n;
	erg.g = this->e * mat.c + this->f * mat.g + this->g * mat.k + this->h * mat.o;
	erg.h = this->e * mat.d + this->f * mat.h + this->g * mat.l + this->h * mat.p;

	erg.i = this->i * mat.a + this->j * mat.e + this->k * mat.i + this->l * mat.m;
	erg.j = this->i * mat.b + this->j * mat.f + this->k * mat.j + this->l * mat.n;
	erg.k = this->i * mat.c + this->j * mat.g + this->k * mat.k + this->l * mat.o;
	erg.l = this->i * mat.d + this->j * mat.h + this->k * mat.l + this->l * mat.p;

	erg.m = this->m * mat.a + this->n * mat.e + this->o  * mat.i + this->p * mat.m;
	erg.n = this->m * mat.b + this->n * mat.f + this->o  * mat.j + this->p * mat.n;
	erg.o = this->m * mat.c + this->n * mat.g + this->o  * mat.k + this->p * mat.o;
	erg.p = this->m * mat.d + this->n * mat.h + this->o  * mat.l + this->p * mat.p;
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
