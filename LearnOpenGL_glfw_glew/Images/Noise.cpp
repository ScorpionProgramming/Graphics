#include "Noise.h"


Noise::Noise()
{
	
}


Noise::Noise(int width, int height)
{
}

Noise::~Noise()
{
}

void Noise::Interpolate(unsigned int xStart, unsigned int yStart, unsigned int width, unsigned int height)
{
	/*for (unsigned int i = 0; i<image.height(); i++)
	{
		for (unsigned int j = 0; j<image.width(); j++)
		{
			float u = (float)j / (float)image.width();
			float v = (float)i / (float)image.height();
			Color cu0 = c0 *(1.0f - u) + c1*u;
			Color cu1 = c2 *(1.0f - u) + c3*u;
			Color co = cu0 *(1.0f - v) + cu1*v;
			image.setPixelColor(j, i, co);
		}
	}*/
}


/*
RGBImage image(500, 500);

std::srand(time(NULL));
double rand;
rand = ((double)std::rand() / (RAND_MAX));
std::cout << rand << std::endl;
Color c0(rand, rand, rand);
rand = ((double)std::rand() / (RAND_MAX));
std::cout << rand << std::endl;
Color c1(rand, rand, rand);
rand = ((double)std::rand() / (RAND_MAX));
std::cout << rand << std::endl;
Color c2(rand, rand, rand);
rand = ((double)std::rand() / (RAND_MAX));
std::cout << rand << std::endl;
Color c3(rand, rand, rand);


for (unsigned int i = 0; i<image.height(); i++)
{
	for (unsigned int j = 0; j<image.width(); j++)
	{
		float u = (float)j / (float)image.width();
		float v = (float)i / (float)image.height();
		Color cu0 = c0 *(1.0f - u) + c1*u;
		Color cu1 = c2 *(1.0f - u) + c3*u;
		Color co = cu0 *(1.0f - v) + cu1*v;
		image.setPixelColor(j, i, co);
	}
}

image.saveToDisk("Loading_Test/Images/TestImageBlackWhite.bmp");

*/