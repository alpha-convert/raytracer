#include <cmath>
#include <array>
#include <cstdio>
#include <vector>
#include <limits>
#include <cassert>
#include <memory>
#include "Math/Vec2/Vec2.h"
#include "Math/Vec3/Vec3.h"
#include "Math/Vec4/Vec4.h"
#include "Math/Quat/Quat.h"
#include "Math/Mat4/Mat4.h"
#include "Math/Ray/Ray.h"
#include "Math/Tree/Tree.h"
#include "Graphics/Graphics.h"
#include "Math/Sphere/Sphere.h"
#include "Math/Object/Object.h"
#include "OpenGL/OpenGL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GLUT/glut.h>
//https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham%E2%80%99s-Line-Drawing-Algorithm


typedef struct Light{
	Vec3 pos;
	float intensity;
} Light;


//https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
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
	s0.pos = Vec3(-15,100,120);
	s0.r = 120;
	s0.c = Color(127,0,0);
	scene.push_back(s0);

	Sphere s1;
	s1.pos = Vec3(70,50,30);
	s1.r = 15;
	s1.c = Color::Blue;
	scene.push_back(s1);

	//might be the wrong way around;
	//Z buffering
	std::sort(scene.begin(),scene.end(),[](const Sphere &lhs, const Sphere &rhs){
		return lhs.pos.z > rhs.pos.z;
	});

	Light l0;
	l0.pos = Vec3(20,80,10);
	l0.intensity = 2000000;

	//For each pixel
	for(int y = 0; y < g.height; ++y){
		for(int x = 0; x < g.width; ++x){
			//for each object
			for(const auto &object : scene){
				
				//construct a ray from the camera through the scrreen
				Ray cast_ray;
				cast_ray.orig = camera_pos;

				//get a vector from the camera through the pixel
				auto px_vec = camera_pos * SGN(camera_pos.z) + screen_top_left;
				px_vec.x += x;
				px_vec.y -= y;

				//Set and normalize the ray direction
				cast_ray.dir = px_vec.normalized();

				float dist; //unfortunately, we have to use the ugly fill-out-param pattern
				auto hit = object.IntersectDist(cast_ray,dist);

				if(hit){
					//Iterate over lights
					auto intersection_point = cast_ray.orig + cast_ray.dir * dist;
					auto normal = (intersection_point - object.pos).normalized();
					float intensity_factor = std::abs(l0.intensity/SQ(dist));
					USE(intensity_factor);
					USE(normal);

					Color ambient = object.c;
					ambient.r = CLAMP(ambient.r + intensity_factor,0,255);


					g.PutPixel(x,y,ambient);
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

