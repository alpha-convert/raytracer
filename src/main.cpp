#include <cmath>
#include <array>
#include <cstdio>
#include <vector>
#include <limits>
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

/**
 * @note: x0<=x1
 */
bool quad_solve(const float a, const float b, const float c, float &x0, float &x1){
	auto discr = SQ(b) - 4*a*c;
	if(discr < 0) return false;
	x0 = (-b + sqrt(discr))/(2*a);
	x1 = (-b - sqrt(discr))/(2*a);
	if(x1 < x0) std::swap(x1,x0);
	return true;
}

//https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
bool sphere_ray_intersect_dist(const Sphere &sphere, const Ray &ray, float &d0, float &d1){
	auto a = SQ(ray.dir.dot(ray.dir));
	auto b = 2*(ray.dir.dot(ray.orig - sphere.pos));
	auto c = SQ((ray.orig - sphere.pos).dot(ray.orig - sphere.pos)) - SQ(sphere.r);
	d0 = std::numeric_limits<float>::infinity();
	d1 = std::numeric_limits<float>::infinity();
	auto hit = quad_solve(a,b,c,d0,d1);
	return hit;
}

int main(int argc, char** argv){
	(void) argc;
	(void) argv;


	Graphics g = Graphics(1920/2,1080/2,"Window");
	g.Clear();

	Sphere s0;
	s0.pos = Vec3(0,0,100);
	s0.r = 40.0;

	Vec3 camera_pos = Vec3(0,0,-100);
	Vec3 screen_pos = Vec3(0,0,0);
	Vec3 screen_top_left = screen_pos + Vec3(-g.width/2,g.height/2,0);

	float a0 = 0;
	float a1 = 0;
	quad_solve(2,-1,-6,a0,a1);
	printf("Solved quadratic. Roots: %.2f, %.2f\n",a0,a1);

	for(int y = 0; y < g.height; ++y){
		g.Clear();
		for(int x = 0; x < g.width; ++x){
			Ray cast_ray;
			cast_ray.orig = camera_pos;

			auto px_vec = screen_top_left - camera_pos;
			px_vec.x += x;
			px_vec.y -= y;
			cast_ray.dir = px_vec;

			float d0;
			float d1;

			auto hit = sphere_ray_intersect_dist(s0,cast_ray,d0,d1);
			float dist = std::min(d0,d1);
			(void) dist;

			if(hit){
				g.PutPixel(x,y,Color::Red);
			}
		}
		g.Update();
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


