#include <cmath>
#include <array>
#include <cstdio>
#include <vector>
#include <limits>
#include <cassert>
#include "Math/Vec2/Vec2.h"
#include "Math/Vec3/Vec3.h"
#include "Math/Vec4/Vec4.h"
#include "Math/Quat/Quat.h"
#include "Math/Mat4/Mat4.h"
#include "Math/Ray/Ray.h"
#include "Math/Tree/Tree.h"
#include "Graphics/Graphics.h"
#include "OpenGL/OpenGL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GLUT/glut.h>
//https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham%E2%80%99s-Line-Drawing-Algorithm



typedef struct Sphere{
	Vec3 pos;
	float r;
} Sphere;

bool wierd_quad_solve(const float a, const float b, const float c, float &x0, float &x1){
	auto discr = SQ(b) - a*c;
//	printf("Discr: %f\n",discr);
	if(discr < 0) return false;
	x0 = (-b + sqrt(discr));
	x1 = (-b - sqrt(discr));
	if(x1 < x0) std::swap(x1,x0);
	return true;
}

//https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
bool sphere_ray_intersect_dist(const Sphere &sphere, const Ray &ray, float &d0, float &d1){
	auto o = ray.orig;
	auto l = ray.dir;
	auto x = sphere.pos;
	auto r = sphere.r;

	//Must be unit vector
	assert(FLEQUAL(l.mag(),1));

	auto a = l.dot(l);
	//since l is unit length
	assert(FLEQUAL(a,1));

	auto b = (l.dot(o-x));
	auto c = (o-x).squared() - SQ(r);
	d0 = std::numeric_limits<float>::infinity();
	d1 = std::numeric_limits<float>::infinity();
	auto hit = wierd_quad_solve(a,b,c,d0,d1);
	return hit;
}

int main(int argc, char** argv){
	(void) argc;
	(void) argv;


	Graphics g = Graphics(1920/2,1080/2,"Window");
	g.Clear();

	Vec3 camera_pos = Vec3(0,0,-100);
	Vec3 screen_pos = Vec3(0,0,0);
	Vec3 screen_top_left = screen_pos + Vec3(-static_cast<int>(g.width)/2,g.height/2,0);

	std::vector<Sphere> scene;

	Sphere s0;
	s0.pos = Vec3(0,0,30);
	s0.r = 120;
	scene.push_back(s0);

	Sphere s1;
	s1.pos = Vec3(50,50,130);
	s1.r = 30;
	scene.push_back(s1);

	//might be the wrong way around;
	//Z buffering
	std::sort(scene.begin(),scene.end(),[](const Sphere &lhs, const Sphere &rhs){
		return lhs.pos.z < rhs.pos.z;
	});


	P_VEC3(camera_pos);
	P_VEC3(screen_pos);
	P_VEC3(screen_top_left);

	//For each pixel
	for(int y = 0; y < g.height; ++y){
		for(int x = 0; x < g.width; ++x){
			//for each object
			for(const auto &object : scene){
				
				//construct a ray from the camera through the scrreen
				Ray cast_ray;
				cast_ray.orig = camera_pos;

				auto px_vec = camera_pos * SGN(camera_pos.z) + screen_top_left;
				px_vec.x += x;
				px_vec.y -= y;

				cast_ray.dir = px_vec.normalized();


				float d0;
				float d1;

				auto hit = sphere_ray_intersect_dist(object,cast_ray,d0,d1);
				float dist = std::min(d0,d1);


				Color px_color = Color::Black;

				if(hit){
					g.PutPixel(x,y,px_color);
				}
			}
		}
	}

	g.Update();

	SDL_Event e;
	bool running =  true;
	while(running){
		//TODO: DEBUGGING
		if(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT || e.window.event == SDL_WINDOWEVENT_CLOSE){
				running = false;
			}
		}
		
	}

	SDL_Quit();
}

