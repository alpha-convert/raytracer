#include "Sphere.h"
#include <typeinfo>
#include <iostream>

Sphere::Sphere(){
	this->pos = Vec3(0,0,0);
	this->r = 0;
}

Sphere::Sphere(const json &j,std::shared_ptr<Texture::texturemap> _gtm){ 

    auto geom_info = j["geom_info"];
    auto color_info = j["color_info"];
    auto texture_info = j["texture_info"];

	pos.x = geom_info["pos"]["x"];
	pos.y = geom_info["pos"]["y"];
	pos.z = geom_info["pos"]["z"];
	r = geom_info["r"];
	surface_color.r = color_info["surface_color"]["r"];
	surface_color.g = color_info["surface_color"]["g"];
	surface_color.b = color_info["surface_color"]["b"];
	ks = color_info["blinn"]["ks"];
	kd = color_info["blinn"]["kd"];
	ka = color_info["blinn"]["ka"];
	alpha = color_info["blinn"]["alpha"];
	tex = nullptr;
    LoadTexture(texture_info,_gtm);
	
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
