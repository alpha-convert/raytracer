#include <fstream>
#include <streambuf>
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
#include "Plane/Plane.h"
#include "Object/Object.h"
#include "Light/Light.h"
#include "OpenGL/OpenGL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GLUT/glut.h>
#include "settings.h"
#include "json/json.hpp"

#define SUBPIXEL 1
using json = nlohmann::json;

void read_entire_json_file(const std::string &fname, json &contents){
	std::ifstream ifs (fname,std::ifstream::in);
	ifs >> contents;
}

int main(int argc, char** argv){
	(void) argc;
	(void) argv;

	json json_scene;
	read_entire_json_file("scene.json",json_scene);


	Graphics g = Graphics(1920/2,1080/2,"Raytracer");
	g.Clear();

	//this doesn't really work but it's a start
	float scene_angle = -M_PI/2;
	float camera_dist = 1500;
	float screen_dist = 300;

	Vec3 camera_pos = Vec3(camera_dist * cos(scene_angle),0,camera_dist * sin(scene_angle));
	Vec3 screen_pos = Vec3(screen_dist * cos(scene_angle),0,screen_dist * sin(scene_angle));
	Vec3 screen_normal = (camera_pos - screen_pos).normalized();
	Vec3 screen_top_left = screen_pos + Vec3(-static_cast<float>(g.width)/2,static_cast<float>(g.height)/2,0);
	USE(screen_normal);

	std::vector<Object *> scene;
	std::vector<Light> lights;

	for(const auto &o : json_scene["objects"]){
		if(o["type"] == "type_sphere"){
			scene.push_back(new Sphere(o));
		} else if(o["type"] == "type_plane"){
			scene.push_back(new Plane(o));
		}
	}

	for(const auto &l : json_scene["lights"]){
		Light nl = Light(l);
		lights.push_back(nl);
		Sphere *s = new Sphere();
		*s = nl.test_sphere;
		scene.push_back(s);

	}

	//For each pixel
	for(int y = 0; y < g.height; ++y){
		for(int x = 0; x < g.width; ++x){
#if SUBPIXEL
			Ray px_ray0 = Ray::ThroughPixel(x-0.5,y,camera_pos,screen_top_left);
			Ray px_ray1 = Ray::ThroughPixel(x,y-0.5,camera_pos,screen_top_left);
			Ray px_ray2 = Ray::ThroughPixel(x-0.5,y-0.5,camera_pos,screen_top_left);
			Ray px_ray3 = Ray::ThroughPixel(x,y,camera_pos,screen_top_left);
			Color c0 = g.Trace(scene,lights,px_ray0,camera_pos,0);
			Color c1 = g.Trace(scene,lights,px_ray1,camera_pos,0);
			Color c2 = g.Trace(scene,lights,px_ray2,camera_pos,0);
			Color c3 = g.Trace(scene,lights,px_ray3,camera_pos,0);
			Color final_color = c0.UnclampedAdd(c1).UnclampedAdd(c2).UnclampedAdd(c3) * (0.25);
#else
			Ray px_ray = Ray::ThroughPixel(x,y,camera_pos,screen_top_left);
			Color final_color = g.Trace(scene,lights,px_ray,camera_pos,0);
#endif
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

	for(auto &a:scene){
		delete a;
	}

	SDL_Quit();
}
