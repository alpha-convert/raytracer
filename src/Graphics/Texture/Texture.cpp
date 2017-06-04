#include "Texture.h"

const Texture::texturetype Texture::TypeImage = "__image__";
const Texture::texturetype Texture::TypePerlin = "__perlin__";

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

Texture::Texture(const json &settings){
    type = settings["texture_type"];
    texname = settings["texname"];
    real_width = settings["width"];
    real_height = settings["height"];

    if(type == TypeImage){
        std::string fname = settings["fname"];
        printf("Creating new texture from file %s...\n",fname.c_str());
        std::vector<unsigned char> buffer;
        lodepng::load_file(buffer, fname); //load the image file with given filename
        // width and height will be overloaded
        auto error = lodepng::decode(tex_data, real_width, real_height, buffer); //decode the png
        if(error) printf("Error making texture\n");
    } else if(type == TypePerlin){
        
        printf("Greating new perlin map.\n");
        tex_data.reserve(4*real_height*real_width);
        printf("tex_data_ptr: %p",&tex_data);
        for(int y = 0; y < real_height ; ++y){
            for(int x = 0; x < real_width; ++x){
                SetReal(x,y,Color(0,0,0,0));
            }
        }

    }
}


void Texture::SetReal(int u, int v, Color c){
    tex_data[4 * v * real_width + 4 * u + 0] = c.r * 255;
    tex_data[4 * v * real_width + 4 * u + 1] = c.g * 255;
    tex_data[4 * v * real_width + 4 * u + 2] = c.b * 255;
    tex_data[4 * v * real_width + 4 * u + 3] = c.a * 255;

}

Texture::~Texture(){}

Color Texture::AtReal(int u, int v) const{
    assert(u <= real_width && u >= 0);
    assert(v <= real_height && v >= 0);
    //Pixels are ordered RGBA,RGBA,RGBA,RGBA...
    float r = static_cast<float>(tex_data[4 * v * real_width + 4 * u + 0]) / 255;
    float g = static_cast<float>(tex_data[4 * v * real_width + 4 * u + 1]) / 255;
    float b = static_cast<float>(tex_data[4 * v * real_width + 4 * u + 2]) / 255;
    float a = static_cast<float>(tex_data[4 * v * real_width + 4 * u + 3]) / 255;
    return Color(r,g,b,a);
}

