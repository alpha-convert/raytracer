#ifndef VEC3_H_
#define VEC3_H_
#include <cmath>

#ifndef VEC2_H_
class Vec2;
#endif

#ifndef QUAT_H_
class Quat;
#endif

#ifndef VEC4_H_
class Vec4;
#endif


class Vec3{
public:
	float x,y,z;

	Vec3();
	Vec3(float,float,float);

	static const Vec3 I;
	static const Vec3 J;
	static const Vec3 K;

	float mag() const;

	Vec3 operator+(const Vec3& v) const;
	Vec3 operator-(const Vec3& v) const;
	Vec3 operator*(float f) const;
	Vec3 operator/(float f) const;
	Vec3 operator-() const;

	operator Quat() const;
	operator Vec2() const;
	operator Vec4() const;

	Vec3 normalized() const;
	void normalizeInPlace();
	static void normalize(Vec3& v);

	float dot(const Vec3& v) const;
	static float dot(const Vec3& a,const Vec3& b);

	Vec3 cross(const Vec3& v) const;
	void crossInPlace(const Vec3& v);

	Vec3 rotate(const Quat& q) const;
	

};

#endif
