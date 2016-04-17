#include "Light.h"
Light::Light(const Vec3 &p){
	pos = p;
	emit_color = Color::White;
	intensity_factor = 1;
}
Light::Light(const Vec3 &p, const Color& c){
	pos = p;
	emit_color = c;
	intensity_factor = 1;
}
Light::Light(const Vec3 &p, const Color& c, float f){
	assert(INEQ(0,<=,f,<=,1));
	pos = p;
	emit_color = c;
	intensity_factor = f;
}

