#pragma once
/***
* @Author Joseph Cutler
* @Date May 08, 2016
* @Copyright WTFPL
*/
#include <cstdio>
#include <vector>
#include <limits>
#include <cassert>
#include <memory>
#include "Color.h"
#include "macros.h"
#include "lodepng.h"

//operates on ppm images
class Texture {
public:
	Color At(float u, float v) const;
	Color AtReal(int u, int v) const;
	int GetHeight() const;
	int GetWidth() const;
	Texture(const char*);
	Texture();
	~Texture();
private:
	unsigned int real_width;
	unsigned int real_height;
	std::vector<unsigned char> image_data;
	const char *fname;
};

