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


/**
 * \class Vec3
 * \brief 3 component vector (x,y,z)
 * \author Joseph Cutler
 * \date
 */
class Vec3{
public:
	/** x component of Vec3 */
	float x; 
	 /** y component of Vec3 */
	float y;
	 /** z component of Vec3 */
	float z;

	Vec3();
	Vec3(float,float,float);

	/**  Unit vector in +x direction */
	static const Vec3 I;	
	/**  Unit vector in +y direction */
	static const Vec3 J;	
	/**  Unit vector in +z direction */
	static const Vec3 K;	

	///Magnitude (or size) of Vec3.
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

	float squared() const;

	Vec3 cross(const Vec3& v) const;
	void crossInPlace(const Vec3& v);

	Vec3 rotate(const Quat& q) const;
	

};

#endif
