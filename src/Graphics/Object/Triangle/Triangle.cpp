#include "Triangle.h"
#include <iostream>

Triangle::Triangle(){
	a = b = c = Vec3(0,0,0);
}

Triangle::Triangle(const json &j){
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
	if(j["texture"] != ""){
		std::string texture_name = j["texture"];
		tex = new Texture(texture_name.c_str());
	}
}


bool Triangle::IntersectDist(const Ray &ray, float &dist) const{
	//https://www.cs.princeton.edu/courses/archive/fall00/cs426/lectures/raycast/sld018.htm
	return false;
}

Triangle::Triangle(const Vec3 &a, const Vec3 &b, const Vec3 &c){
	this->a = a;
	this->b = b;
	this->c = c;
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
