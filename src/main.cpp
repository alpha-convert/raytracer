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
#include "Sphere/Sphere.h"
#include "Object/Object.h"
#include "Light/Light.h"
#include "OpenGL/OpenGL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GLUT/glut.h>
#include "settings.h"
//https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham%E2%80%99s-Line-Drawing-Algorithm


//https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
int main(int argc, char** argv){
	(void) argc;
	(void) argv;


	Graphics g = Graphics(1920/2,1080/2,"Window");
	g.Clear();

	Vec3 camera_pos = Vec3(0,0,-500);
	Vec3 screen_pos = Vec3(0,0,0);
	Vec3 screen_top_left = screen_pos + Vec3(-static_cast<int>(g.width)/2,g.height/2,0);

	std::vector<Object *> scene;
	std::vector<Light> lights;

	Sphere s0;
	s0.pos = Vec3(-30,100,100);
	s0.r = 70;
	s0.surface_color = Color(1,0,0);
	scene.push_back(&s0);

	Sphere s1;
	s1.pos = Vec3(60,0,50);
	s1.r = 30;
	s1.surface_color = Color::Blue;
	scene.push_back(&s1);

	Sphere s2;
	s2.pos = Vec3(-60,0,50);
	s2.r = 30;
	s2.surface_color = Color::Green;
	scene.push_back(&s2);

	Light l0 = Light(Vec3(20,80,10));
	lights.push_back(l0);

	//For each pixel
	for(int y = 0; y < g.height; ++y){
		for(int x = 0; x < g.width; ++x){
			Ray px_ray = Ray::ThroughPixel(x,y,camera_pos,screen_top_left);
			Color final_color = g.Trace(scene,lights,px_ray,0);
			g.PutPixel(x,y,final_color);
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

