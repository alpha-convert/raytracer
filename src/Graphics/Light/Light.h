#pragma once
/***
* @Author Joseph Cutler
* @Date April 17, 2016
* @Copyright WTFPL
*/
#include <cmath>
#include <array>
#include <cstdio>
#include <vector>
#include <limits>
#include <cassert>
#include "Object/Object.h"
#include "Sphere/Sphere.h"
#include "Ray/Ray.h"
#include "Color/Color.h"
#include "Vec3/Vec3.h"
#include "json/json.hpp"
#include "macros.h"

class Light{
public:
	Vec3 pos;
	Sphere test_sphere;
	Color is; //specular component
	Color id; //diffuse component

	Light(const json &j);
	Light(const Vec3 &p);
	~Light(){};

private:
};
