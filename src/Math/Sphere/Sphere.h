#pragma once
/***
* @Author Joseph Cutler
* @Date April 12, 2016
* @Copyright WTFPL
*/
#include <cmath>
#include <array>
#include <cstdio>
#include <vector>
#include <limits>
#include <cassert>
#include "Object/Object.h"
#include "Ray/Ray.h"
#include "Vec3/Vec3.h"
#include "Color/Color.h"
#include "macros.h"
class Sphere : public Object{
public:
	Vec3 pos;
	float r;
	Color c = Color::Red;

	bool IntersectDist(const Ray &ray, float &dist) const;

	Sphere();
	Sphere(Vec3 pos, float r);
	virtual ~Sphere(){};

	static const ObjectType type = ObjectType::type_plane;
private:
};
