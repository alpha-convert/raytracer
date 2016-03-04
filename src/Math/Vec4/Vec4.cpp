#include "Vec4.h"
#include "Vec3/Vec3.h"
#include "Vec3/Vec3.h"
#include <cmath>
#include <assert.h>
Vec4::Vec4() : x(0), y(0), z(0), w(1) {};

Vec4::Vec4(float x,float y,float z,float w) : x(x), y(y), z(z), w(w) {};
Vec4::Vec4(float x,float y,float z) : x(x), y(y), z(z), w(1) {};

const Vec4 Vec4::I = Vec4(1,0,0,1);
const Vec4 Vec4::J = Vec4(0,1,0,1);
const Vec4 Vec4::K = Vec4(0,0,1,1);
const Vec4 Vec4::L = Vec4(0,0,0,1);


#define SQ(x) (x*x)
#undef SQ

Vec4 Vec4::operator*(float f) const{
	return Vec4(x*f,y*f,z*f,w*f);
}
Vec4 Vec4::operator/(float f) const{
	return *this * (1/f);
}

Vec4::operator Vec3() const{
	assert(w == 1);
	Vec3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}


