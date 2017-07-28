#include "Texture.h"

const Texture::texturetype Texture::TypeImage = "__image__";
const Texture::texturetype Texture::TypeNoise = "__noise__";

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
        printf("Creating new texture \"%s\" from file %s...\n",texname.c_str(),fname.c_str());
        std::vector<unsigned char> buffer;
        lodepng::load_file(buffer, fname); //load the image file with given filename
        // width and height will be overloaded
        auto error = lodepng::decode(tex_data, real_width, real_height, buffer); //decode the png
        if(error) printf("Error making texture\n");
    } else if(type == TypeNoise){
        printf("Greating new noise map.\n");
        tex_data.resize(4*real_height*real_width);
        GenerateNoiseInPlace();
    }
}


void Texture::SetReal(int u, int v, Color c){
    auto base = 4 * v * real_width + 4 * u;

    tex_data.at(base + 0) = c.r * 255;
    tex_data.at(base + 1) = c.g * 255;
    tex_data.at(base + 2) = c.b * 255;
    tex_data.at(base + 3) = c.a * 255;

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

void Texture::GenerateNoiseInPlace(){
    //Generate random field

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator (seed);
    std::uniform_int_distribution<int> distribution(0, 1);

    for(int x = 0; x < real_width; ++x){
        for(int y = 0; y < real_height; ++y){
            float bw = static_cast<float>(distribution(generator));
            SetReal(x,y,Color(bw,bw,bw));
        }
    }


    for(int x = 1; x < real_width - 1; ++x){
        for(int y = 1; y < real_height - 1; ++y){
            auto val = AtReal(x,y);
            auto up = AtReal(x,y-1);
            auto down = AtReal(x,y+1);
            auto right = AtReal(x+1,y);
            auto left = AtReal(x-1,y);
            auto avg_val = ((val.r + up.r + down.r + left.r + right.r) / 5.0);
            auto new_col = avg_val < 0.5 ? 0 : 1;

            SetReal(x,y,Color(new_col,new_col,new_col));
        }
    }


    //smooth the field

}
