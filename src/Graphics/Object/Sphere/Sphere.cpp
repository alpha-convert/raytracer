#include "Sphere.h"
#include <typeinfo>
#include <iostream>

Sphere::Sphere(){
	this->pos = Vec3(0,0,0);
	this->r = 0;
}

Sphere::Sphere(const json &j){
	pos.x = j["pos"]["x"];
	pos.y = j["pos"]["y"];
	pos.z = j["pos"]["z"];
	r = j["r"];
	surface_color.r = j["surface_color"]["r"];
	surface_color.g = j["surface_color"]["g"];
	surface_color.b = j["surface_color"]["b"];
	ks = j["blinn"]["ks"];
	kd = j["blinn"]["kd"];
	ka = j["blinn"]["ka"];
	alpha = j["blinn"]["alpha"];
	tex = nullptr;
	if(j["texture"] != ""){
		std::string texture_name = j["texture"];
		tex = new Texture(texture_name.c_str());
	}
}

Sphere::Sphere(Vec3 pos, float r) : pos(pos), r(r){
	ks = 0;
	kd = 0;
	ka = 0;
	alpha = 0;
}

bool wierd_quad_solve(const float a, const float b, const float c, float &x0, float &x1){
	auto discr = SQ(b) - a*c;
	if(discr < 0) return false;
	x0 = (-b + sqrt(discr));
	x1 = (-b - sqrt(discr));
	if(x1 < x0) std::swap(x1,x0);
	return true;
}


bool Sphere::IntersectDist(const Ray &ray, float &dist) const{
	auto o = ray.orig;
	auto l = ray.dir.normalized();
	auto x = pos;
//	auto r = sphere.r;

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

Vec3 Sphere::NormalAt(const Vec3 &v) const{
	return (v - pos).normalized();
}

Color Sphere::ColorAt(const Vec3 &p) const{
	if(tex){
		auto u = 2*cos(p.z/r)/M_PI;
		auto v = 2*cos(p.x/(r*sin(M_PI*u)))/(2*M_PI);
		return tex->At(u,v);
	} else{
		return surface_color;
	}
}
