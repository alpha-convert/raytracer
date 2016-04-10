#pragma once
/***
* @Author Joseph Cutler
* @Date April 07, 2016
* @Copyright WTFPL
*/
#include "Math/Vec3/Vec3.h"
class Ray {
public:
	Vec3 orig;
	Vec3 dir;
	Ray();
	Ray(Vec3 orig, Vec3 dir);
	virtual ~Ray(){};
private:
};
