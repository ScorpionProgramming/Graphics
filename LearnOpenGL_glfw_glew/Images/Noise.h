#pragma once
#include <math.h>
#include "Color.h"
#include "RGBImage.h"
class Noise
{
public:
	//Generiert ein Standartbild von 500x500pxl	
	Noise();
	//Generiert ein Noisebild von Width x Height 
	Noise(int width, int height);

	//hilfsmethode
	void Interpolate(unsigned int xStart, unsigned int yStart, unsigned int width, unsigned int height);
	~Noise();
};

