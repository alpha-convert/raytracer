#pragma once
/***
* @Author Joseph Cutler
* @Date April 12, 2016
* @Copyright WTFPL
*/
#include "Ray/Ray.h"
#include "Color/Color.h"
#include "json/json.hpp"

enum ObjectType{
	type_sphere,
	type_plane,
	type_light

};

using json = nlohmann::json;

class Object {
public:
	Object(const json &data);
	Object(){};
	virtual bool IntersectDist(const Ray &, float &) const = 0;
	virtual Vec3 NormalAt(const Vec3 &) const = 0;
	const static ObjectType type;
	Color surface_color;

	float ks;
	float kd;
	float ka;
	float alpha;

private:
};
