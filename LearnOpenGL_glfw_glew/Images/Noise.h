#pragma once
#include <math.h>
#include "Images/Color.h"
class Noise
{
public:
	//Generiert ein Standartbild von 500x500pxl	
	Noise();
	//Generiert ein Noisebild von Width x Height 
	Noise(int width, int height);
	~Noise();
};

