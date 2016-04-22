#include "Light.h"
Light::Light(const Vec3 &p){
	pos = p;
	test_sphere.pos = p;
	test_sphere.r = 10;
	is = Color::White;
	id = Color::White;
}


Light::Light(const json &j){
	//TODO: Find the source of the negative light bug
	pos.x = j["pos"]["x"];
	pos.y = j["pos"]["y"];
	pos.z = j["pos"]["z"];
	pos = -pos;
	is.r = j["is"]["r"];
	is.g = j["is"]["g"];
	is.b = j["is"]["b"];
	id.r = j["id"]["r"];
	id.g = j["id"]["g"];
	id.b = j["id"]["b"];
	test_sphere.pos = pos;
	test_sphere.r = 10;
	test_sphere.surface_color = Color::Green;
}

