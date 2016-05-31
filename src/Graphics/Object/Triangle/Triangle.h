#pragma once
/***
* @Author Joseph Cutler
* @Date May 08, 2016
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



class Triangle : public Object{
public:
	Vec3 a,b,c;

	bool IntersectDist(const Ray &ray, float &dist) const;
	Vec3 NormalAt(const Vec3 &p) const;
	Color ColorAt(const Vec3 &) const;

	Triangle(const json &data);
	Triangle();
	Triangle(const Vec3 &a, const Vec3 &b, const Vec3 &c);
	~Triangle(){if(tex != nullptr) delete tex;};

	static const ObjectType type = ObjectType::type_triangle;


private:
};
