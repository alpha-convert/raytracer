#pragma once
/***
* @Author Joseph Cutler
* @Date April 15, 2016
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
#include "macros.h"

class Plane : public Object{
public:
	Vec3 p;
	Vec3 normal;

	bool IntersectDist(const Ray &ray, float &dist) const;
	Vec3 NormalAt(const Vec3 &p) const;
	const static ObjectType type = ObjectType::type_plane;

	Plane();
	Plane(Vec3 &p, Vec3& normal);
	virtual ~Plane(){};
private:
};
