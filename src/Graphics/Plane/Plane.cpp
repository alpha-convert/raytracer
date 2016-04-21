#include "Plane.h"
//https://www.cs.princeton.edu/courses/archive/fall00/cs426/lectures/raycast/sld017.htm
//I love how I can learn from schools I can't get into
bool Plane::IntersectDist(const Ray &ray, float &dist) const{
	bool hit = false;
	Vec3 Pr = ray.orig;
	Vec3 P0 = p;
	Vec3 n = normal;
	Vec3 ur = ray.dir;

	float denom = n.dot(ur);
	if(denom < 0){
		hit = true;
		float num = n.dot(Pr - P0);
		dist = -num/denom;
	}

	return hit;
}

Vec3 Plane::NormalAt(const Vec3 & p) const{
	USE(p); //just for compatibility
	return normal;
}

Plane::Plane(){
	auto i = -std::numeric_limits<float>::infinity();
	p = Vec3(i,i,i);
	normal = Vec3(0,0,-1); //must be unit length or something will go horribly wrong

	ks = 0.2;
	kd = 0.5;
	ka = 0.3;
	alpha = 2;
}

Plane::Plane(Vec3 &p, Vec3& normal) : p(p){
	assert(UNITLENGTH(normal));
	this->normal = normal;

	ks = 0.05;
	kd = 0.8;
	ka = 0.1;
	alpha = 2;
} 

