#ifndef MAT4_H_
#define MAT4_H_ 

#include <cmath>
#include <vector>
#include <algorithm>

#ifndef VEC3_H_
class Vec3;
#endif

#ifndef VEC4_H_
class Vec4;
#endif

class Mat4{
public:
	Mat4();
	virtual ~Mat4(){};

	void print();

    float& operator[](unsigned index);
    float operator[](unsigned index) const;
	static Mat4 Ident();

	Mat4 operator*(float f) const;
	Mat4 operator*(const Mat4& m) const;
	Vec4 operator*(const Vec4& v) const;

protected:
	std::vector<float> data;
};
#endif
