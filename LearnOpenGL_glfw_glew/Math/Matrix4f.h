#pragma once
#include "Vector4f.h"
#include <sstream>
#include <string>

/*
	http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

	Was ich alles brauche:
	translations matrix mit float x float y float z
	identitätsmatrix mit float i
	skalierungsmatrix mit float x, float y float z und 1
	rotationsmatrix (zu kompliziert gerade)
*/

class Matrix4f
{
public:
	//TODO: hinzufügen von  Einheitsmatrix, Skalierungsmatrix und Drehmatrix

	float a, b, c, d, 
		  e, f, g, h,
		  i, j, k, l,
		  m, n, o, p;
	Matrix4f();
	Matrix4f(	float a, float b, float c, float d,
				float e, float f, float g, float h,
				float i, float j, float k, float l,
				float m, float n, float o, float p	);

	/*Muss eventuell wieder rausgepatched werden*/
	void operator=(const Matrix4f mat);

	/*Matrix x Matrix = Matrix*/
	Matrix4f operator*(const Matrix4f mat) const;
	/*Matrix x Vector = Vector*/
	Vector4f operator*(const Vector4f vec) const;
	/*DEBUG Ausgeben von der Matrix*/
	std::string toString();
};

