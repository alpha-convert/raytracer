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

class Object {
public:
	Object(const json &data);
	Object(){};
	virtual bool IntersectDist(const Ray &, float &) const = 0;
	virtual Vec3 NormalAt(const Vec3 &) const = 0;
	virtual Color ColorAt(const Vec3 &) const = 0;
	const static ObjectType type;
	Color surface_color;
        const std::string texture_key;

	float ks;
	float kd;
	float ka;
	float alpha;

private:
        std::shared_ptr<std::map<std::string,const Texture &>> global_texture_map;
};
