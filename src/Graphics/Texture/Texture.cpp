#include "Texture.h"

Color Texture::At(float u, float v) const{
	assert(u <= 1 && u >= 0);
	assert(v <= 1 && v >= 0);
	return AtReal(u*real_width,v*real_height);
}

int Texture::GetHeight() const{
	return real_height;
}

int Texture::GetWidth() const{
	return real_width;
}

Texture::Texture(const char* _fname) {
	fname = _fname;
	printf("Creating new texture from file %s...\n TODO: Cache multi-use textures\n",_fname);
	std::vector<unsigned char> buffer;
	lodepng::load_file(buffer, fname); //load the image file with given filename
	auto error = lodepng::decode(image_data, real_width, real_height, buffer); //decode the png
	if(error) printf("Error making texture\n");
}

Texture::~Texture(){}
Texture::Texture(){}

Color Texture::AtReal(int u, int v) const{
	assert(u <= real_width && u >= 0);
	assert(v <= real_height && v >= 0);
	//Pixels are ordered RGBA,RGBA,RGBA,RGBA...
	float r = static_cast<float>(image_data[4 * v * real_width + 4 * u + 0]) / 255;
	float g = static_cast<float>(image_data[4 * v * real_width + 4 * u + 1]) / 255;
	float b = static_cast<float>(image_data[4 * v * real_width + 4 * u + 2]) / 255;
	float a = static_cast<float>(image_data[4 * v * real_width + 4 * u + 3]) / 255;
	return Color(r,g,b,a);
}
