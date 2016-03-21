#ifndef VEC4_H_
#define VEC4_H_ 

#ifndef VEC3_H_
class Vec3;
#endif

#ifndef QUAT_H_
class Quat;
#endif

/* *
 * \class Vec4
 * \brief 4-component vector (x,y,z,w)
 * \author Joseph Cutler
 * \date
 */

class Vec4{
public:
	float x; /**<x-component of vec4*/
	float y; /**<y-component of vec4*/
	float z; /**<z-component of vec4*/
	float w; /**<w-component of vec4*/

	Vec4();
	Vec4(float,float,float,float);
	Vec4(float,float,float);

	static const Vec4 I;
	static const Vec4 J;
	static const Vec4 K;
	static const Vec4 L;

	float mag() const;


	Vec4 operator+(const Vec4& v) const;
	Vec4 operator-(const Vec4& v) const;
	Vec4 operator*(float f) const;
	Vec4 operator/(float f) const;

	operator Vec3() const;

	Vec4 normalized() const;
	void normalized();
	static void normalize(Vec4& v);

	float dot(const Vec4& v) const;
	static float dot(const Vec4& a, const Vec4& b);

	Vec4 cross(const Vec4& v) const;
	void crossInPlace(const Vec4& v) const;

	Vec4 rotate(const Quat& q) const;

};
#endif
