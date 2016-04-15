#pragma once
/***
* @Author Joseph Cutler
* @Date April 12, 2016
* @Copyright WTFPL
*/
#include "Ray/Ray.h"
#include "Color/Color.h"

enum ObjectType{
	type_sphere,
	type_plane
};

class Object {
public:
	virtual bool IntersectDist(const Ray &, float &) const = 0;
	virtual Vec3 NormalAt(const Vec3 &) const = 0;
	const static ObjectType type;
	Color surface_color;

private:
};
