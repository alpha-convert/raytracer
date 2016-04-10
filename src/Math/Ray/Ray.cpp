#include "Ray.h"
Ray::Ray(){
	orig = Vec3(0,0,0);
	dir = Vec3(0,0,0);
}

Ray::Ray(Vec3 orig, Vec3 dir) : orig(orig), dir(dir){}
