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
#include "Ray/Ray.h"
#include "Color/Color.h"
#include "Vec3/Vec3.h"
#include "macros.h"

class Light{
public:
	Vec3 pos;
	Color emit_color;
	///Range: [0,1]
	float intensity_factor;
	Light(const Vec3 &p);
	Light(const Vec3 &p, const Color& c);
	Light(const Vec3 &p, const Color& c, float f);
	~Light(){};

private:
};
