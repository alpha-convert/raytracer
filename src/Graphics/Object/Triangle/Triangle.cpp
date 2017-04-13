#include "Triangle.h"
#include <iostream>
#include "macros.h"

Triangle::Triangle(){
	a = b = c = Vec3(0,0,0);
}

Triangle::Triangle(const json &j,std::shared_ptr<Texture::texturemap> _gtm){
	a.x = j["a"]["x"];
	a.y = j["a"]["y"];
	a.z = j["a"]["z"];
	b.x = j["b"]["x"];
	b.y = j["b"]["y"];
	b.z = j["b"]["z"];
	c.x = j["c"]["x"];
	c.y = j["c"]["y"];
	c.z = j["c"]["z"];
	ks = j["blinn"]["ks"];
	kd = j["blinn"]["kd"];
	ka = j["blinn"]["ka"];
	alpha = j["blinn"]["alpha"];
	tex = nullptr;
    LoadTexture(j,_gtm);
}


bool Triangle::IntersectDist(const Ray &ray, float &dist) const{
	USE(ray);
	USE(dist);
	//https://www.cs.princeton.edu/courses/archive/fall00/cs426/lectures/raycast/sld018.htm
	return false;
}

//TODO: might work?
Vec3 Triangle::NormalAt(const Vec3 & p) const{
	USE(p); //just for compatibility
	auto ab = b - a;
	auto ac = c - a;
	return ab.cross(ac);
}

Color Triangle::ColorAt(const Vec3 &p) const{
	USE(p);
	if(tex){
		return surface_color;
	} else {
		return surface_color;
	}
}
