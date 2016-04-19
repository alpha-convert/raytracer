#include "Light.h"
Light::Light(const Vec3 &p){
	pos = p;
	test_sphere.pos = p;
	test_sphere.r = 0.01f;
	is = Color::White;
	id = Color::White;
}

