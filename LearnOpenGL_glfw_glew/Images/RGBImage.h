#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Color.h"

/*---------------FILE-HEADER-WINDOwS-DEFINITION---------------*/
//BYTE  = unsigned char		| 1 byte  | 8 bit
//WORD	= unsigned short	| 2 bytes | 16 bit
//DWORD = unsigned long		| 4 bytes | 32 bit
//LONG  = unsigned long		| 4 bytes | 32 bit
//INT	= unsigned int		| 4 bytes | 32 bit
typedef struct {
	unsigned short  bfType;
	unsigned int	bfSize;
	unsigned short  bfReserved1;
	unsigned short  bfReserved2;
	unsigned int	bfOffBits;
}bmp_file_header;

typedef struct{
	unsigned int	biSize;
	unsigned int	biWidth;
	unsigned int	biHeight;
	unsigned short	biPlanes;
	unsigned short  biBitCount;
	unsigned int	biCompression;
	unsigned int	biSizeImage;
	unsigned int	biXPelsPerMeter;
	unsigned int	biYPelsPerMeter;
	unsigned int	biClrUsed;
	unsigned int	biClrImportant;
} bmp_info_header;


class RGBImage
{
public:
	RGBImage();
	RGBImage(unsigned int  Width, unsigned int Height);
	~RGBImage();
	void setPixelColor(unsigned int x, unsigned int y, const Color& c);
	const Color& getPixelColor(unsigned int x, unsigned int y) const;
	bool saveToDisk(const char* Filename);
	bool loadFromDisk(const char* Filename);
	unsigned int width() const;
	unsigned int height() const;

	static unsigned char convertColorChannel(float f);
protected:
	Color* m_Image;
	unsigned int m_Height;
	unsigned int m_Width;
};

