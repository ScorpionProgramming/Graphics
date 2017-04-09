#include "Matrix4f.h"


Matrix4f::Matrix4f()
{
	data = new float[16];
	this->data[0] = 0; this->data[1] = 0; this->data[2] = 0; this->data[3] = 0;
	this->data[4] = 0; this->data[5] = 0; this->data[6] = 0; this->data[7] = 0;
	this->data[8] = 0; this->data[9] = 0; this->data[10] = 0; this->data[11] = 0;
	this->data[12] = 0; this->data[13] = 0; this->data[14] = 0; this->data[15] = 0;
}

Matrix4f::Matrix4f(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
{
	data = new float[16];
	this->data[0] = a; this->data[1] = b; this->data[2] = c; this->data[3] = d;
	this->data[4] = e; this->data[5] = f; this->data[6] = g; this->data[7] = h;
	this->data[8] = i; this->data[9] = j; this->data[10] = k; this->data[11] = l;
	this->data[12] = m; this->data[13] = n; this->data[14] = o; this->data[15] = p;
}

void Matrix4f::operator=(const Matrix4f mat)
{
	for (int i = 0; i < 16; i++) {
		this->data[i] = mat.data[i];
	}
}

/*
a b c d  |  0  1  2  3
e f g h  |  4  5  6  7
i j k l  |  8  9 10 11 
m n o p  | 12 13 14 15 
*/

Matrix4f Matrix4f::operator*(const Matrix4f mat) const
{
	Matrix4f erg;
	erg.data[0] = this->data[0] * mat.data[0] + this->data[1] * mat.data[4] + this->data[2] * mat.data[8] +	this->data[3] * mat.data[12];
	erg.data[1] = this->data[0] * mat.data[1] + this->data[1] * mat.data[5] + this->data[2] * mat.data[9] +	this->data[3] * mat.data[13];
	erg.data[2] = this->data[0] * mat.data[2] + this->data[1] * mat.data[6] + this->data[2] * mat.data[10] + this->data[3] * mat.data[14];
	erg.data[3] = this->data[0] * mat.data[3] + this->data[1] * mat.data[7] + this->data[2] * mat.data[11] + this->data[3] * mat.data[15];
	erg.data[4] = this->data[4] * mat.data[0] + this->data[5] * mat.data[4] + this->data[6] * mat.data[8] +	this->data[7] * mat.data[12];
	erg.data[7] = this->data[4] * mat.data[3] + this->data[5] * mat.data[7] + this->data[6] * mat.data[11] + this->data[7] * mat.data[15];
	erg.data[5] = this->data[4] * mat.data[1] + this->data[5] * mat.data[5] + this->data[6] * mat.data[9] +	this->data[7] * mat.data[13];
	erg.data[6] = this->data[4] * mat.data[2] + this->data[5] * mat.data[6] + this->data[6] * mat.data[10] + this->data[7] * mat.data[14];
	erg.data[8] = this->data[8] * mat.data[0] + this->data[9] * mat.data[4] + this->data[10] *mat.data[8] +	this->data[11] * mat.data[12];
	erg.data[9] = this->data[8] * mat.data[1] + this->data[9] * mat.data[5] + this->data[10] * mat.data[9] + this->data[11] * mat.data[13];
	erg.data[10] = this->data[8] * mat.data[2] + this->data[9] * mat.data[6] + this->data[10] * mat.data[10] + this->data[11] * mat.data[14];
	erg.data[11] = this->data[8] * mat.data[3] + this->data[9] * mat.data[7] + this->data[10] * mat.data[11] + this->data[11] * mat.data[15];
	erg.data[12] = this->data[12] * mat.data[0] + this->data[13] * mat.data[4] + this->data[14] * mat.data[8] + this->data[15] * mat.data[12];
	erg.data[13] = this->data[12] * mat.data[1] + this->data[13] * mat.data[5] + this->data[14] * mat.data[9] + this->data[15] * mat.data[13];
	erg.data[14] = this->data[12] * mat.data[2] + this->data[13] * mat.data[6] + this->data[14] * mat.data[10] + this->data[15] * mat.data[14];
	erg.data[15] = this->data[12] * mat.data[3] + this->data[13] * mat.data[7] + this->data[14] * mat.data[11] + this->data[15] * mat.data[15];
	return erg;
}

Vector4f Matrix4f::operator*(const Vector4f vec) const
{
	Vector4f erg;
	erg.x = this->data[0] * vec.x + this->data[1] * vec.y + this->data[2] * vec.z + this->data[3] * vec.w;
	erg.y = this->data[4] * vec.x + this->data[5] * vec.y + this->data[6] * vec.z + this->data[7] * vec.w;
	erg.z = this->data[8] * vec.x + this->data[9] * vec.y + this->data[10] * vec.z + this->data[11] * vec.w;
	erg.w = this->data[12] * vec.x + this->data[13] * vec.y + this->data[14] * vec.z + this->data[15] * vec.w;
	return erg;
}

Matrix4f Matrix4f::operator*(float value) const {
	Matrix4f mat;
	for (int i = 0; i < sizeof(this->data) / sizeof(float); i++) {
		mat.data[i] = (this->data[i] * value);
	}
	return mat;
}

void Matrix4f::rotate(float degree, float x, float y, float z)
{
	//opengl nutzt radiance daher muessen wir die Grad umrechenen
	degree = degree * (PI / 180.0f);
	// xx = 0 kann auskommentiert bzw geloescht werden
	Matrix4f rot = Matrix4f();
	rot.data[0] = cos(degree) + x * x  * (1 - cos(degree));
	rot.data[1] = x * y * (1 - cos(degree)) - z * sin(degree);
	rot.data[2] = x * z * (1 - cos(degree)) + y * sin(degree);
	rot.data[3] = 0;
	rot.data[4] = y*x * (1 - cos(degree)) + z * sin(degree);
	rot.data[5] = cos(degree) + y*y*(1 - cos(degree));
	rot.data[6] = y * z * (1 - cos(degree)) - x * sin(degree);
	rot.data[7] = 0;
	rot.data[8] = z * x * (1 - cos(degree)) - y * sin(degree);
	rot.data[9] = z * y * (1 - cos(degree)) + x * sin(degree);
	rot.data[10] = cos(degree) + z * z * (1 - cos(degree));
	rot.data[11] = 0;
	rot.data[12] = 0;
	rot.data[13] = 0;
	rot.data[14] = 0;
	rot.data[15] = 1;

	(*this) = rot * (*this);
}

void Matrix4f::rotate(float degree, Vector3f vec)
{
	this->rotate(degree, vec.x, vec.y, vec.z);
}

void Matrix4f::rotateX(float degree)
{
	this->rotate(degree, 1, 0, 0);
}

void Matrix4f::rotateY(float degree)
{
	this->rotate(degree, 0, 1, 0);
}

void Matrix4f::rotateZ(float degree)
{
	//this->rotate(degree, 0, 0, 1);
	degree = degree * (PI / 180.0f);
	Matrix4f mat;
	mat.identity();
	mat.data[0] = cos(degree);
	mat.data[1] = -sin(degree);
	mat.data[4] = sin(degree);
	mat.data[5] = cos(degree);

	(*this) = mat * (*this);
}

void Matrix4f::identity()
{
	for (int i = 0; i < 16; i++) {
		this->data[i] = 0;
	}

	this->data[0] = 1;
	this->data[5] = 1;
	this->data[10] = 1;
	this->data[15] = 1;
}

void Matrix4f::perspective(float fov, float ratio, float near, float far)
{
	Matrix4f mat;

	float fn = far - near;
	float s = 1 / tan((fov/2)*(PI/180)); //scale

	mat.data[0] = s;
	mat.data[5] = s;
	mat.data[10] = -(far / (fn));
	mat.data[11] = -1;
	mat.data[14] = -((far * near) / fn);

	(*this) = mat * (*this);
}

void Matrix4f::orthograpic(float left, float right, float buttom, float top, float near, float far)
{
	Matrix4f mat;
	float rl = right - left;
	float tb = top - buttom;
	float fn = far - near;

	mat.data[0] = 2 / rl;
	mat.data[3] = -((right + left) / rl);
	mat.data[5] = 2 / tb;
	mat.data[7] = -((top + buttom) / tb);
	mat.data[10] = -2 / fn;
	mat.data[11] = -((far + near) / fn);
	mat.data[15] = 1;

	(*this) = mat * (*this);
}

float Matrix4f::det3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
	//float output = (a * e * i + b * f * g + c* d * h - c * e * g - b * d * i - a * f * h);
	float output = ((a * (e * i - f * h)) - (b * (d * i - f * g)) + (c * (d * h - e * g)));
	return output;
}

void Matrix4f::invert() {
	Matrix4f mB = Matrix4f();
	//(*this) = (*this) * (1 / this->getDet());

	float* help = new float[9];
	int swapper = 1;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			int x_temp = 0, y_temp = 0;
			bool x_bool = false, y_bool = false;


			for (int by = 0; by < 3; by++) {
				for (int bx = 0; bx < 3; bx++) {
					x_temp = bx;
					y_temp = by;
					if (bx == x || x_bool == true) {
						x_temp++;
						x_bool = true;
					}
					if (by == y || y_bool == true) {
						y_temp++;
						y_bool = true;
					}
					help[bx + by * 3] = this->data[x_temp + y_temp * 4];

				}
			}

			mB.data[x + y * 4] = det3x3(help[0], help[1], help[2],
				help[3], help[4], help[5],
				help[6], help[7], help[8]) * swapper;
			swapper = swapper * (-1);
		}
		swapper = swapper * (-1);
	}

	(*this) = mB * (1 / this->getDet());
}


float Matrix4f::getDet() {
	// http://matheguru.com/lineare-algebra/207-determinante.html

	// http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
	float erg = 0;
	erg += this->data[0] * this->det3x3(data[1 * 4 + 1], data[1 * 4 + 2], data[1 * 4 + 3],
										data[2 * 4 + 1], data[2 * 4 + 2], data[2 * 4 + 3],
										data[3 * 4 + 1], data[3 * 4 + 2], data[3 * 4 + 3]);

	erg += -this->data[1] * this->det3x3(data[1 * 4 + 0], data[1 * 4 + 2], data[1 * 4 + 3],
										 data[2 * 4 + 0], data[2 * 4 + 2], data[2 * 4 + 3],
										 data[3 * 4 + 0], data[3 * 4 + 2], data[3 * 4 + 3]);

	erg += this->data[2] * this->det3x3(data[1 * 4 + 0], data[1 * 4 + 1], data[1 * 4 + 3],
										data[2 * 4 + 0], data[2 * 4 + 1], data[2 * 4 + 3],
										data[3 * 4 + 0], data[3 * 4 + 1], data[3 * 4 + 3]);

	erg += -this->data[3] * this->det3x3(data[1 * 4 + 0], data[1 * 4 + 1], data[1 * 4 + 2],
										 data[2 * 4 + 0], data[2 * 4 + 1], data[2 * 4 + 2],
										 data[3 * 4 + 0], data[3 * 4 + 1], data[3 * 4 + 2]);

	return erg;
}
void Matrix4f::scale(float x, float y, float z) {
	Matrix4f ms;
	ms.data[0] = x;
	ms.data[5] = y;
	ms.data[10] = z;
	ms.data[15] = 1;

	//skalier matrix
	(*this) = ms * (*this);
}

void Matrix4f::scale(Vector3f vec)
{
	this->scale(vec.x, vec.y, vec.z);
}

void Matrix4f::scale(float xyz) {
	this->scale(xyz, xyz, xyz);
}

void Matrix4f::lookAt(float x, float y, float z)
{
}

//diagonale mit einsen und die letzt spalte von oben nach unten mit x y und z
void Matrix4f::translate(float x, float y, float z) {
	Matrix4f mt = Matrix4f(); //translatematrix
	mt.identity();

	mt.data[3]  = x;
	mt.data[7]  = y;
	mt.data[11] = z;

	(*this) = mt * (*this);
}

void Matrix4f::translate(Vector3f vec)
{
	this->translate(vec.x, vec.y, vec.z);
}

std::string Matrix4f::toString()
{
	std::stringstream ss;
	ss << "4x4-Matrix: \n";
	/*
	ss << this->a << " " << this->b << " " << this->c << " " << this->d << "\n";
	ss << this->e << " " << this->f << " " << this->g << " " << this->h << "\n";
	ss << this->i << " " << this->j << " " << this->k << " " << this->l << "\n";
	ss << this->m << " " << this->n << " " << this->o << " " << this->p << "\n";
	return ss.str();
	*/

	for (int i = 0; i < 16; i++) {
		if (i % 4 == 0) {
			ss << "[\t";
		}

		ss << this->data[i] << "\t";

		if (i % 4 == 3) {
			ss << "]\n";
		}
	}
	return ss.str();
}

std::ostream & operator<<(std::ostream &os, const Matrix4f & mat)
{
	for (int i = 0; i < 16; i++) {
		if (i % 4 == 0) {
			os << "[\t";
		}

		os << mat.data[i] << "\t";

		if (i % 4 == 3) {
			os << "]\n";
		}
	}
	return os;
}
