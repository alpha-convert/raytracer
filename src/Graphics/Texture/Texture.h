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
#include <map>
#include "Color.h"
#include "macros.h"
#include "lodepng.h"


//operates on ppm images
//
//FOR CREATING TEXTURES: CHECK IF WE'RE A PART OF THE GLOBAL BUFFER
//IF WE ARE, SET IMAGE_DATA TO THAT THING.
//OTHERWISE, LOAD IT UP.
class Texture {
public:
        typedef std::map<std::string,std::shared_ptr<Texture>> texturemap;

	Color At(float u, float v) const;
	Color AtReal(int u, int v) const;
	int GetHeight() const;
	int GetWidth() const;
	Texture(const char*); 
	~Texture();
private:
	unsigned int real_width;
	unsigned int real_height;
	std::vector<unsigned char> image_data;
	const char *fname;

};

