#pragma once
/***
 * @Author Joseph Cutler
 * @Date April 12, 2016
 * @Copyright WTFPL
 */
#include "Ray.h"
#include "Color.h"
#include "json/json.hpp"
#include "Texture.h"
#include <cstdio>

enum ObjectType{
  type_sphere,
  type_plane,
  type_light,
  type_triangle
};

using json = nlohmann::json;

//Objects MUST be givena access to the gtm.
//

class Object {
  public:
    Object(const json &data,std::shared_ptr<Texture::texturemap>);
    Object(){};
    ~Object(){
      if(tex){
        auto use_count = tex.use_count();
        printf("Deleting an object with tex name: %s, tex use count: %ld\n"
            ,texture_name.c_str(), tex.use_count());

        //This is true if "this" is the only item left that has tex
        //Only "this" and the gtm own the tex pointer
        if(use_count == 2){
          //Remove tex from the gtm
          global_texture_map->erase(texture_name);
          printf("Texture %s is no longer used and has been removed from the gtm.\n",texture_name.c_str());
        }
      }

    };
    virtual bool IntersectDist(const Ray &, float &) const = 0;
    virtual Vec3 NormalAt(const Vec3 &) const = 0;
    virtual Color ColorAt(const Vec3 &) const = 0;

    void LoadTexture(const json &settings, std::shared_ptr<Texture::texturemap> _gtm){
      global_texture_map = _gtm;
      this->texture_name = settings["texname"];
      if(texture_name != "NO_TEXTURE"){
        if(global_texture_map->find(texture_name) != global_texture_map->end()){
          tex = global_texture_map->at(texture_name);
        } else {
          tex = std::make_shared<Texture>(settings);
          global_texture_map->insert(std::make_pair(texture_name,tex));
        }
      }
    }

    const static ObjectType type;
    Color surface_color;
    std::string texture_name;

    float ks;
    float kd;
    float ka;
    float alpha;

    std::shared_ptr<Texture> tex;
    std::shared_ptr<Texture::texturemap> global_texture_map;
};
