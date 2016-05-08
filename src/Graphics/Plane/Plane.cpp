#include "Plane.h"
//https://www.cs.princeton.edu/courses/archive/fall00/cs426/lectures/raycast/sld017.htm
//I love how I can learn from schools I can't get into
bool Plane::IntersectDist(const Ray &ray, float &dist) const{
	bool hit = false;
	Vec3 Pr = ray.orig;
	Vec3 P0 = pos;
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

Color Plane::ColorAt(const Vec3 &v) const{
	USE(v);
	return surface_color;
}

Plane::Plane(const json &j){
	pos.x = j["pos"]["x"];
	pos.y = j["pos"]["y"];
	pos.z = j["pos"]["z"];
	normal.x = j["normal"]["x"];
	normal.y = j["normal"]["y"];
	normal.z = j["normal"]["z"];
	surface_color.r = j["surface_color"]["r"];
	surface_color.g = j["surface_color"]["g"];
	surface_color.b = j["surface_color"]["b"];
	ks = j["blinn"]["ks"];
	kd = j["blinn"]["kd"];
	ka = j["blinn"]["ka"];
	alpha = j["blinn"]["alpha"];
	if(j["texture"] != ""){
		std::string texture_name = j["texture"];
		tex = new Texture(texture_name.c_str());
	}
	printf("Loaded texture for Plane\n");
}

Plane::Plane(){
	auto i = -std::numeric_limits<float>::infinity();
	pos = Vec3(i,i,i);
	normal = Vec3(0,0,-1); //must be unit length or something will go horribly wrong

}

Plane::Plane(Vec3 &p, Vec3& normal) : pos(p){
	assert(UNITLENGTH(normal));
	this->normal = normal;
	ks = 0.05;
	kd = 0.8;
	ka = 0.1;
	alpha = 2;
} 

