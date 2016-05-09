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
#include "Texture.h"
#include "Vec3/Vec3.h"
#include "macros.h"
class Sphere : public Object{
public:
	Vec3 pos;
	float r;

	bool IntersectDist(const Ray &ray, float &dist) const;
	Vec3 NormalAt(const Vec3 &p) const;
	Color ColorAt(const Vec3 &) const;

	Sphere(const json &data);
	Sphere();
	Sphere(Vec3 pos, float r);
	~Sphere(){if(tex != nullptr) delete tex;};

	static const ObjectType type = ObjectType::type_plane;
private:
};
