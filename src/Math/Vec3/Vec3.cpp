#include "Vec3.h"
#include "Quat/Quat.h"
#include "Vec2/Vec2.h"
#include <cmath>
#include <cassert>

Vec3::Vec3() : x(0), y(0), z(0) {};

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {};
const Vec3 Vec3::I = Vec3(1,0,0);
const Vec3 Vec3::J = Vec3(0,1,0);
const Vec3 Vec3::K = Vec3(0,0,1);

#define SQ(x) (x*x)
float Vec3::mag() const{
	return sqrt(SQ(x) + SQ(y) + SQ(z));
}
#undef SQ


Vec3 Vec3::operator+(const Vec3& v) const{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3& v) const{
	return Vec3(x - v.x, y - v.y, z - v.z);
}
Vec3 Vec3::operator*(float f) const{
	return Vec3(x * f, y * f, z * f);
}
Vec3 Vec3::operator/(float f) const{
	return Vec3(x / f, y / f, z / f);
}


Vec3 Vec3::operator-() const{
	return Vec3(-x,-y,-z);
}

Vec3::operator Quat() const{
	return Quat(x,y,z,0);
}

Vec3::operator Vec2() const{
	assert(z == 0);
	return Vec2(x,y);
}

Vec3 Vec3::normalized() const{
	return *this/mag();

}
void Vec3::normalizeInPlace(){
	*this = this->normalized();

}
void Vec3::normalize(Vec3& v){
	v = v.normalized();
}

Vec3 Vec3::cross(const Vec3& v) const{
	Vec3 c;
	c.x = y*v.z - z*v.y;
	c.y = z*v.x - x*v.z;
	c.z = x*v.y - y*v.x;
	return c;
}

void Vec3::crossInPlace(const Vec3& v){
	*this = this->cross(v);
}

Vec3 Vec3::rotate(const Quat& q) const{
	//v' = qvq*
	auto q_normal = q.normalized();
	Quat q_conj = q_normal.conj();
	Quat qv = q_normal* (Quat) *this;
	Quat qvp = qv * q_conj;
	return (Vec3) qvp;
}


float Vec3::dot(const Vec3& v) const{
	return x*v.x + y*v.y + z*v.z;
}


float Vec3::dot(const Vec3& a,const Vec3& b){
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
