#include "Plane.h"
bool Plane::IntersectDist(const Ray &ray, float &dist) const{
	auto plane = *this;
	//TODO: this obviously doesn't work
	return false;
}

Vec3 Plane::NormalAt(const Vec3 & p) const{
	USE(p); //just for compatibility
	return normal;
}

Plane::Plane(){
	auto i = -std::numeric_limits<float>::infinity();
	p = Vec3(i,i,i);
	normal = Vec3(0,0,-1); //must be unit length or something will go horribly wrong
}

Plane::Plane(Vec3 &p, Vec3& normal) : p(p){
	assert(UNITLENGTH(normal));
	this->normal = normal;
} 

