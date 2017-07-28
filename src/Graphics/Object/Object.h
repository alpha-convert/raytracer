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
        ~Object(){};
	virtual bool IntersectDist(const Ray &, float &) const = 0;
	virtual Vec3 NormalAt(const Vec3 &) const = 0;
	virtual Color ColorAt(const Vec3 &) const = 0;

        void LoadTexture(const json &settings, std::shared_ptr<Texture::texturemap> _gtm){
                global_texture_map = _gtm;
                std::string texture_name = settings["texname"];
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
        const std::string texture_key;

	float ks;
	float kd;
	float ka;
	float alpha;

        std::shared_ptr<Texture> tex;
        std::shared_ptr<Texture::texturemap> global_texture_map;
};
