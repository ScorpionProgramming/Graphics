#pragma once
#include "Vector4f.h"
#include <sstream>
#include <string>

#define PI 3.14159265359
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

	float data[16];
	Matrix4f();
	Matrix4f(	float a, float b, float c, float d,
				float e, float f, float g, float h,
				float i, float j, float k, float l,
				float m, float n, float o, float p	);
	/*Matrix4f(	float a, float e, float i, float m,
				float b, float f, float j, float n,
				float c, float g, float k, float o,
				float d, float h, float l, float p);*/
	~Matrix4f();

	/*Muss eventuell wieder rausgepatched werden*/
	void operator=(const Matrix4f mat);

	/*Matrix x Matrix = Matrix*/
	Matrix4f operator*(const Matrix4f mat) const;
	/*Matrix x Vector = Vector*/
	Vector4f operator*(const Vector4f vec) const;

	Matrix4f operator*(float value) const;
	
	void identity();

	void rotate(float degree, float x, float y, float z);
	void rotate(float degree, Vector3f vec);
	void rotateX(float degree);
	void rotateY(float degree);
	void rotateZ(float degree);

	void translate(float x, float y, float z);
	void translate(Vector3f vec);

	void scale(float x, float y, float z);
	void scale(Vector3f vec);
	void scale(float xyz);

	/*
	fov: field of view -> Sichtfeld, realistisch is 45 Grad.
	radio: aspect radio -> Bildverhaeltnis, width / height
	near und far sind die Flächen die den Sichtberech nah der Kamera und weit weg von der Kamera eingrenzen
	*/
	void perspective(float fov, float ratio, float near, float far);

	void orthograpic(float left, float right, float buttom, float top, float near, float far);

	//void lookAt(Vector3f target);
	void lookAt(float x, float y, float z);

	void invert();

	float getDet();

	//ausgabe wie stringstream
	friend std::ostream &operator<<(std::ostream &os, const Matrix4f &mat);
	/*DEBUG Ausgeben von der Matrix*/
	std::string toString();

private:
	float det3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i);  //Helperfunktion fuer die determinantenberechnung
};

