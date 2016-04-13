#include "Sphere.h"

Sphere::Sphere(){
	this->pos = Vec3(0,0,0);
	this->r = 0;
}

Sphere::Sphere(Vec3 pos, float r){
	this->pos = pos;
	this->r = r;
}
bool wierd_quad_solve(const float a, const float b, const float c, float &x0, float &x1){
	auto discr = SQ(b) - a*c;
//	printf("Discr: %f\n",discr);
	if(discr < 0) return false;
	x0 = (-b + sqrt(discr));
	x1 = (-b - sqrt(discr));
	if(x1 < x0) std::swap(x1,x0);
	return true;
}


bool Sphere::IntersectDist(const Ray &ray, float &dist) const{
	auto sphere = *this;
	auto o = ray.orig;
	auto l = ray.dir;
	auto x = sphere.pos;
	auto r = sphere.r;

	//Must be unit vector
	assert(FLEQUAL(l.mag(),1));

	auto a = l.dot(l);
	//since l is unit length
	assert(FLEQUAL(a,1));

	auto b = (l.dot(o-x));
	auto c = (o-x).squared() - SQ(r);
	auto d0 = std::numeric_limits<float>::infinity();
	auto d1 = std::numeric_limits<float>::infinity();
	auto hit = wierd_quad_solve(a,b,c,d0,d1);
	dist = std::min(d0,d1);
	return hit;
}

