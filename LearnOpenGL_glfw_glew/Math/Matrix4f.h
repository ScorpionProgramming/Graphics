#pragma once
#include "Vector4f.h"
#include <sstream>
#include <string>

/*
	http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

	############################################################################
	>>>>>>>>> http://www.songho.ca/opengl/gl_matrix.html#example1  <<<<<<<<<<<<<
	############################################################################

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

	float* data;
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

	Matrix4f operator*(float value) const;

	void rotate(float degree, float x, float y, float z);
	void rotateX(float degree);
	void rotateY(float degree);
	void rotatez(float degree);

	void identity();

	//void lookAt(Vector3f target);
	void lookAt(float x, float y, float z);

	void translate(float x, float y, float z);

	void scale(float x, float y, float z);
	void scale(float xyz);

	void invert();

	float getDet();

	//ausgabe wie stringstream
	friend std::ostream &operator<<(std::ostream &os, const Matrix4f &mat);
	/*DEBUG Ausgeben von der Matrix*/
	std::string toString();

private:
	float det3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i);  //Helperfunktion fuer die determinantenberechnung

};

